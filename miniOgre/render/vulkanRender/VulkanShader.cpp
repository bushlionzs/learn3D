#include "OgreHeader.h"
#include "OgreHeader.h"
#include "VulkanShader.h"
#include "myutils.h"
#include "VulkanRenderSystem.h"
#include "OgreRenderable.h"
#include "OgreVertexData.h"
#include "OgreVertexDeclaration.h"
#include "OgreResourceManager.h"
#include "VulkanRenderData.h"
#include "shaderManager.h"
#include "glslUtil.h"
#include "OgreResourceManager.h"
#include "OgreMaterial.h"
#include "VulkanMappings.h"
#include "VulkanHelper.h"

VulkanShader::VulkanShader(ShaderInfo& info, VulkanRenderSystem* engine)
{
	mShaderInfo = info;
	mEngine = engine;
}

VulkanShader::~VulkanShader()
{

}

bool VulkanShader::load()
{
    Ogre::ShaderPrivateInfo* privateInfo =
        ShaderManager::getSingleton().getShader(mShaderInfo.shaderName, EngineType_Vulkan);

    String* vertexContent = ShaderManager::getSingleton().getShaderContent(privateInfo->vertexShaderName);
    auto res = ResourceManager::getSingleton().getResource(privateInfo->vertexShaderName);

    if (res == nullptr)
    {
        OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "fail to find shader!");
    }
    String vertexSpv;

    
    glslCompileShader(
        vertexSpv, 
        res->_fullname,
        *vertexContent, 
        privateInfo->vertexShaderEntryPoint,
        mShaderInfo.shaderMacros,
        shaderc_glsl_vertex_shader);
    mVertexShader = createShaderModule(vertexSpv);

    
    parserGlslInputDesc(vertexSpv, mInputDesc);

    String* fragContent = ShaderManager::getSingleton().getShaderContent(privateInfo->fragShaderName);

    String fragSpv;

    res = ResourceManager::getSingleton().getResource(privateInfo->fragShaderName);
    glslCompileShader(
        fragSpv,
        res->_fullname,
        *fragContent,
        privateInfo->fragShaderEntryPoint,
        mShaderInfo.shaderMacros,
        shaderc_glsl_fragment_shader);

    mFragShader = createShaderModule(fragSpv);

	return true;
}

void VulkanShader::updateInputDesc(VertexDeclaration* vDeclaration)
{

}

VkPipeline VulkanShader::getVKPipeline(Ogre::Renderable* r)
{
    if (mGraphicsPipeline != VK_NULL_HANDLE)
    {
        return mGraphicsPipeline;
    }

    VkPipelineShaderStageCreateInfo vertShaderStageInfo = {};
    vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
    vertShaderStageInfo.module = mVertexShader;
    vertShaderStageInfo.pName = "main";

    VkPipelineShaderStageCreateInfo fragShaderStageInfo = {};
    fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragShaderStageInfo.module = mFragShader;
    fragShaderStageInfo.pName = "main";

    std::vector<VkPipelineShaderStageCreateInfo> shaderStages = { vertShaderStageInfo, fragShaderStageInfo };



    VertexData* vertexData = r->getVertexData();

    std::vector<VkVertexInputBindingDescription> vertexInputBindings;

    for (uint32_t binding = 0; binding < 10; binding++)
    {
        int32_t stride = vertexData->getVertexDeclaration()->getVertexSize(binding);

        if (stride <= 0)
            continue;
        vertexInputBindings.emplace_back();
        vertexInputBindings.back().binding = binding;
        vertexInputBindings.back().stride = stride;
        vertexInputBindings.back().inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    }



    auto attributeDescriptions = getAttributeDescriptions(vertexData->getVertexDeclaration());
    VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
    vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputInfo.vertexBindingDescriptionCount = vertexInputBindings.size();
    vertexInputInfo.pVertexBindingDescriptions = vertexInputBindings.data();
    vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());

    vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

    VkPipelineInputAssemblyStateCreateInfo inputAssemblyState =
        vks::initializers::pipelineInputAssemblyStateCreateInfo(
            VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
            0,
            VK_FALSE);

    VkPipelineRasterizationStateCreateInfo rasterizationState =
        vks::initializers::pipelineRasterizationStateCreateInfo(
            VK_POLYGON_MODE_FILL,
            VK_CULL_MODE_NONE,
            VK_FRONT_FACE_COUNTER_CLOCKWISE,
            0);

    VkPipelineColorBlendAttachmentState blendAttachmentState =
        vks::initializers::pipelineColorBlendAttachmentState(
            0xf,
            VK_FALSE);
    auto& mat = r->getMaterial();
    auto blendState = mat->getBlendState();
    if (blendState.blendingEnabled())
    {
        blendAttachmentState.blendEnable = true;
        blendAttachmentState.srcColorBlendFactor = VulkanMappings::get(blendState.sourceFactor, false);
        blendAttachmentState.dstColorBlendFactor = VulkanMappings::get(blendState.destFactor, false);
        blendAttachmentState.colorBlendOp = VulkanMappings::get(blendState.operation);
        blendAttachmentState.srcAlphaBlendFactor = VulkanMappings::get(blendState.sourceFactorAlpha, true);
        blendAttachmentState.dstAlphaBlendFactor = VulkanMappings::get(blendState.destFactorAlpha, true);
        blendAttachmentState.alphaBlendOp = VulkanMappings::get(blendState.alphaOperation);
    }

    VkPipelineColorBlendStateCreateInfo colorBlendState =
        vks::initializers::pipelineColorBlendStateCreateInfo(
            1,
            &blendAttachmentState);

    VkPipelineDepthStencilStateCreateInfo depthStencilState =
        vks::initializers::pipelineDepthStencilStateCreateInfo(
            mat->isDepthTest(),
            mat->isWriteDepth(),
            VK_COMPARE_OP_LESS_OR_EQUAL);

    VkPipelineViewportStateCreateInfo viewportState =
        vks::initializers::pipelineViewportStateCreateInfo(1, 1, 0);

    auto& settings = VulkanHelper::getSingleton().getVulkanSettings();

    VkPipelineMultisampleStateCreateInfo multisampleState =
        vks::initializers::pipelineMultisampleStateCreateInfo(
            settings.sampleCount,
            0);

    std::vector<VkDynamicState> dynamicStateEnables = {
        VK_DYNAMIC_STATE_VIEWPORT,
        VK_DYNAMIC_STATE_SCISSOR
    };
    VkPipelineDynamicStateCreateInfo dynamicState =
        vks::initializers::pipelineDynamicStateCreateInfo(
            dynamicStateEnables.data(),
            static_cast<uint32_t>(dynamicStateEnables.size()),
            0);

    bool pbr = mat->isPbr();
    auto pipelineLayout = VulkanHelper::getSingleton()._getPipelineLayout(pbr);
    VkGraphicsPipelineCreateInfo pipelineCreateInfo =
        vks::initializers::pipelineCreateInfo(
            pipelineLayout,
            VulkanHelper::getSingleton()._getRenderPass(),
            0);

    pipelineCreateInfo.pVertexInputState = &vertexInputInfo;
    pipelineCreateInfo.pInputAssemblyState = &inputAssemblyState;
    pipelineCreateInfo.pRasterizationState = &rasterizationState;
    pipelineCreateInfo.pColorBlendState = &colorBlendState;
    pipelineCreateInfo.pMultisampleState = &multisampleState;
    pipelineCreateInfo.pViewportState = &viewportState;
    pipelineCreateInfo.pDepthStencilState = &depthStencilState;
    pipelineCreateInfo.pDynamicState = &dynamicState;
    pipelineCreateInfo.stageCount = static_cast<uint32_t>(shaderStages.size());
    pipelineCreateInfo.pStages = shaderStages.data();

    if (vkCreateGraphicsPipelines(
        VulkanHelper::getSingleton()._getVkDevice(),
        nullptr,
        1,
        &pipelineCreateInfo, nullptr, &mGraphicsPipeline) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create graphics pipeline!");
    }

    return mGraphicsPipeline;
}

std::vector<VkVertexInputAttributeDescription> VulkanShader::getAttributeDescriptions(VertexDeclaration* vd)
{
    std::vector<VkVertexInputAttributeDescription>
        attributeDescriptions(mInputDesc.size());
    int32_t i = 0;

    for (auto& input : mInputDesc)
    {
        bool find = false;

        auto& elementlist = vd->getElementList();
        for (auto elem : elementlist)
        {
            if (input._name == VulkanMappings::getSemanticName(elem.getSemantic()) &&
                input._index == elem.getIndex())
            {
                attributeDescriptions[i].binding = elem.getSource();
                attributeDescriptions[i].location = input._location;
                attributeDescriptions[i].format = getVKFormatFromType(elem.getType());
                attributeDescriptions[i].offset = elem.getOffset();
                i++;
                find = true;
                break;
            }
        }


        if (!find)
        {
            OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS, "can not find input param");
        }
    }
    

    return attributeDescriptions;
}

VkShaderModule VulkanShader::createShaderModule(const std::string& code)
{
    VkShaderModuleCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

    VkShaderModule shaderModule;
    if (vkCreateShaderModule(
        VulkanHelper::getSingleton()._getVkDevice(),
        &createInfo, nullptr, &shaderModule) != VK_SUCCESS) 
    {
        OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "failed to create shader module!");
    }

    return shaderModule;
}