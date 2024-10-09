#include <OgreHeader.h>
#include "OgreRoot.h"
#include "OgreNode.h"
#include "OgreResourceManager.h"
#include "OgreMeshManager.h"
#include "OgreSceneManager.h"
#include "OgreEntity.h"
#include "OgreSubEntity.h"
#include "OgreVertexData.h"
#include "OgreIndexData.h"
#include "OgreVertexDeclaration.h"
#include "OgreHardwareIndexBuffer.h"
#include "VulkanRenderSystemBase.h"
#include "VulkanWindow.h"
#include "VulkanTexture.h"
#include "VulkanHelper.h"
#include "VulkanMappings.h"
#include "VulkanTools.h"
#include "VulkanPipelineLayoutCache.h"
#include "VulkanPipelineCache.h"
#include "VulkanBuffer.h"
#include "shaderManager.h"
#include "glslUtil.h"

static VmaAllocator createAllocator(VkInstance instance, VkPhysicalDevice physicalDevice,
    VkDevice device) {
    VmaAllocator allocator;
    VmaVulkanFunctions const funcs{
#if VMA_DYNAMIC_VULKAN_FUNCTIONS
        .vkGetInstanceProcAddr = vkGetInstanceProcAddr,
        .vkGetDeviceProcAddr = vkGetDeviceProcAddr,
#else
        .vkGetPhysicalDeviceProperties = vkGetPhysicalDeviceProperties,
        .vkGetPhysicalDeviceMemoryProperties = vkGetPhysicalDeviceMemoryProperties,
        .vkAllocateMemory = vkAllocateMemory,
        .vkFreeMemory = vkFreeMemory,
        .vkMapMemory = vkMapMemory,
        .vkUnmapMemory = vkUnmapMemory,
        .vkFlushMappedMemoryRanges = vkFlushMappedMemoryRanges,
        .vkInvalidateMappedMemoryRanges = vkInvalidateMappedMemoryRanges,
        .vkBindBufferMemory = vkBindBufferMemory,
        .vkBindImageMemory = vkBindImageMemory,
        .vkGetBufferMemoryRequirements = vkGetBufferMemoryRequirements,
        .vkGetImageMemoryRequirements = vkGetImageMemoryRequirements,
        .vkCreateBuffer = vkCreateBuffer,
        .vkDestroyBuffer = vkDestroyBuffer,
        .vkCreateImage = vkCreateImage,
        .vkDestroyImage = vkDestroyImage,
        .vkCmdCopyBuffer = vkCmdCopyBuffer,
        .vkGetBufferMemoryRequirements2KHR = vkGetBufferMemoryRequirements2KHR,
        .vkGetImageMemoryRequirements2KHR = vkGetImageMemoryRequirements2KHR
#endif
    };
    VmaAllocatorCreateInfo const allocatorInfo{
        .physicalDevice = physicalDevice,
        .device = device,
        .pVulkanFunctions = &funcs,
        .instance = instance,
    };
    vmaCreateAllocator(&allocatorInfo, &allocator);
    return allocator;
}

VulkanRenderSystemBase::VulkanRenderSystemBase()
    :
    mResourceAllocator(8388608, false)
{
    new VulkanHelper(this);
}

VulkanRenderSystemBase::~VulkanRenderSystemBase()
{

}

bool VulkanRenderSystemBase::engineInit()
{
    mVulkanPlatform = new VulkanPlatform();


    VulkanHelper& helper = VulkanHelper::getSingleton();
    helper._initialise(mVulkanPlatform);

    auto device = mVulkanPlatform->getDevice();
    mAllocator = createAllocator(
        mVulkanPlatform->getInstance(), mVulkanPlatform->getPhysicalDevice(), device);

    
    auto queue = mVulkanPlatform->getGraphicsQueue();
    auto queueIndex = mVulkanPlatform->getGraphicsQueueIndex();

    mCommands = new VulkanCommands(device, queue, queueIndex, &mVulkanContext, &mResourceAllocator);
    mStagePool = new VulkanStagePool(mAllocator, mCommands);

    mPipelineCache = helper.getPipelineCache();
    mPipelineLayoutCache = helper.getPipelineLayoutCache();
    mDescriptorSetManager = new VulkanDescriptorSetManager(device, &mResourceAllocator);
    return true;
}

OgreTexture* VulkanRenderSystemBase::createTextureFromFile(
    const std::string& name,
    TextureProperty* texProperty)
{
    auto tex = new VulkanTexture(name, mVulkanPlatform, mCommands, texProperty);
    return tex;
}

void VulkanRenderSystemBase::ready()
{
    VulkanHelper::getSingleton().loadDefaultResources();
}

RenderableData* VulkanRenderSystemBase::createRenderableData(Ogre::Renderable* r)
{
    return nullptr;
}

void VulkanRenderSystemBase::updateMainPassCB(ICamera* camera)
{
    const Ogre::Matrix4& view = camera->getViewMatrix();
    const Ogre::Matrix4& proj = camera->getProjectMatrix();
    const Ogre::Vector3& camepos = camera->getDerivedPosition();

    Ogre::Matrix4 invView = view.inverse();
    Ogre::Matrix4 viewProj = proj * view;
    Ogre::Matrix4 invProj = proj.inverse();
    Ogre::Matrix4 invViewProj = viewProj.inverse();

    mFrameConstantBuffer.Shadow = mCurrentRenderPassInfo.shadowPass?1:0;


    mFrameConstantBuffer.View = view.transpose();
    mFrameConstantBuffer.InvView = invView.transpose();
    mFrameConstantBuffer.Proj = proj.transpose();
    mFrameConstantBuffer.InvProj = invProj.transpose();
    mFrameConstantBuffer.ViewProj = viewProj.transpose();
    mFrameConstantBuffer.InvViewProj = invViewProj.transpose();
    
    mFrameConstantBuffer.EyePosW = camepos;


    auto width = mRenderWindow->getWidth();
    auto height = mRenderWindow->getHeight();
    mFrameConstantBuffer.RenderTargetSize =
        Ogre::Vector2((float)width,
            (float)height);
    mFrameConstantBuffer.InvRenderTargetSize =
        Ogre::Vector2(1.0f / width, 1.0f / height);
    mFrameConstantBuffer.NearZ = 0.1f;
    mFrameConstantBuffer.FarZ = 10000.0f;
    mFrameConstantBuffer.TotalTime += Ogre::Root::getSingleton().getFrameEvent().timeSinceLastFrame;
    mFrameConstantBuffer.DeltaTime = Ogre::Root::getSingleton().getFrameEvent().timeSinceLastFrame;
}



ICamera* VulkanRenderSystemBase::_getCamera()
{
    return mCurrentRenderPassInfo.cam;
}

Ogre::RenderWindow* VulkanRenderSystemBase::createRenderWindow(
    const String& name, unsigned int width, unsigned int height,
    const NameValuePairList* miscParams)
{
    mRenderWindow = new VulkanWindow();

    auto itor = miscParams->find("externalWindowHandle");
    if (itor == miscParams->end())
    {
        OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS, "externalWindowHandle should be provided");
    }

    HWND wnd = (HWND)StringConverter::parseSizeT(itor->second);
    VkExtent2D extent;
    extent.width = 0;
    extent.height = 0;

    uint32_t flags = backend::SWAP_CHAIN_CONFIG_SRGB_COLORSPACE;
    flags |= SWAP_CHAIN_CONFIG_HAS_STENCIL_BUFFER;
    mSwapChain = new VulkanSwapChain(
        mVulkanPlatform, 
        mVulkanContext, 
        mAllocator, mCommands, &mResourceAllocator, *mStagePool, (void*)wnd, flags, extent);

    mRenderWindow->create(mSwapChain);

    return mRenderWindow;
}

Ogre::RenderTarget* VulkanRenderSystemBase::createRenderTarget(
    const String& name, 
    uint32_t width, 
    uint32_t height, 
    Ogre::PixelFormat format, 
    uint32_t usage)
{
    TextureProperty texProperty;
    texProperty._width = width;
    texProperty._height = height;
    texProperty._tex_usage = usage;
    texProperty._tex_format = format;
    texProperty._need_mipmap = false;

    if (usage & (uint32_t)Ogre::TextureUsage::DEPTH_ATTACHMENT)
    {
        texProperty._samplerParams.wrapS = filament::backend::SamplerWrapMode::CLAMP_TO_EDGE;
        texProperty._samplerParams.wrapT = filament::backend::SamplerWrapMode::CLAMP_TO_EDGE;
        texProperty._samplerParams.wrapR = filament::backend::SamplerWrapMode::CLAMP_TO_EDGE;
    }
    Ogre::VulkanRenderTarget* renderTarget = new Ogre::VulkanRenderTarget(
        name, mVulkanPlatform, mCommands, texProperty);
    return renderTarget;
}

Ogre::OgreTexture* VulkanRenderSystemBase::generateCubeMap(
    const std::string& name,
    Ogre::OgreTexture* environmentCube,
    Ogre::PixelFormat format,
    int32_t dim,
    CubeType type)
{
    Ogre::TextureProperty texProperty;
    texProperty._tex_usage = Ogre::TextureUsage::UPLOADABLE;
    texProperty._texType = TEX_TYPE_CUBE_MAP;
    texProperty._width = dim;
    texProperty._height = dim;
    texProperty._tex_format = format;
    texProperty._samplerParams.filterMag = filament::backend::SamplerMagFilter::LINEAR;
    texProperty._samplerParams.filterMin = filament::backend::SamplerMinFilter::LINEAR_MIPMAP_LINEAR;
    texProperty._samplerParams.wrapS = filament::backend::SamplerWrapMode::REPEAT;
    texProperty._samplerParams.wrapT = filament::backend::SamplerWrapMode::REPEAT;
    texProperty._samplerParams.wrapR = filament::backend::SamplerWrapMode::REPEAT;
    texProperty._samplerParams.anisotropyLog2 = 0;
    VulkanTexture* tex = new VulkanTexture(name, mVulkanPlatform, mCommands, &texProperty);

    tex->load(nullptr);


    // FB, Att, RP, Pipe, etc.
    VkAttachmentDescription attDesc{};

    auto vulkanFormat = VulkanMappings::_getPF(format);
    // Color attachment
    attDesc.format = vulkanFormat;
    attDesc.samples = VK_SAMPLE_COUNT_1_BIT;
    attDesc.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    attDesc.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    attDesc.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attDesc.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attDesc.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    attDesc.finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    VkAttachmentReference colorReference = { 0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL };

    VkSubpassDescription subpassDescription{};
    subpassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpassDescription.colorAttachmentCount = 1;
    subpassDescription.pColorAttachments = &colorReference;

    // Use subpass dependencies for layout transitions
    std::array<VkSubpassDependency, 2> dependencies;
    dependencies[0].srcSubpass = VK_SUBPASS_EXTERNAL;
    dependencies[0].dstSubpass = 0;
    dependencies[0].srcStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
    dependencies[0].dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependencies[0].srcAccessMask = VK_ACCESS_MEMORY_READ_BIT;
    dependencies[0].dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    dependencies[0].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;
    dependencies[1].srcSubpass = 0;
    dependencies[1].dstSubpass = VK_SUBPASS_EXTERNAL;
    dependencies[1].srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependencies[1].dstStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
    dependencies[1].srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    dependencies[1].dstAccessMask = VK_ACCESS_MEMORY_READ_BIT;
    dependencies[1].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

    // Renderpass
    VkRenderPassCreateInfo renderPassCI{};
    renderPassCI.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassCI.attachmentCount = 1;
    renderPassCI.pAttachments = &attDesc;
    renderPassCI.subpassCount = 1;
    renderPassCI.pSubpasses = &subpassDescription;
    renderPassCI.dependencyCount = 2;
    renderPassCI.pDependencies = dependencies.data();
    VkRenderPass renderpass;

    auto device = mVulkanPlatform->getDevice();
    VK_CHECK_RESULT(vkCreateRenderPass(device, &renderPassCI, nullptr, &renderpass));

    struct Offscreen {
        VkImage image;
        VkImageView view;
        VkDeviceMemory memory;
        VkFramebuffer framebuffer;
    } offscreen;

    // Create offscreen framebuffer
    {
        // Image
        VkImageCreateInfo imageCI{};
        imageCI.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        imageCI.imageType = VK_IMAGE_TYPE_2D;
        imageCI.format = vulkanFormat;
        imageCI.extent.width = dim;
        imageCI.extent.height = dim;
        imageCI.extent.depth = 1;
        imageCI.mipLevels = 1;
        imageCI.arrayLayers = 1;
        imageCI.samples = VK_SAMPLE_COUNT_1_BIT;
        imageCI.tiling = VK_IMAGE_TILING_OPTIMAL;
        imageCI.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        imageCI.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
        imageCI.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        VK_CHECK_RESULT(vkCreateImage(device, &imageCI, nullptr, &offscreen.image));
        VkMemoryRequirements memReqs;
        vkGetImageMemoryRequirements(device, offscreen.image, &memReqs);
        VkMemoryAllocateInfo memAllocInfo{};
        memAllocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        memAllocInfo.allocationSize = memReqs.size;
        memAllocInfo.memoryTypeIndex = VulkanHelper::getSingleton()._findMemoryType(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
        VK_CHECK_RESULT(vkAllocateMemory(device, &memAllocInfo, nullptr, &offscreen.memory));
        VK_CHECK_RESULT(vkBindImageMemory(device, offscreen.image, offscreen.memory, 0));

        // View
        VkImageViewCreateInfo viewCI{};
        viewCI.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        viewCI.viewType = VK_IMAGE_VIEW_TYPE_2D;
        viewCI.format = vulkanFormat;
        viewCI.flags = 0;
        viewCI.subresourceRange = {};
        viewCI.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        viewCI.subresourceRange.baseMipLevel = 0;
        viewCI.subresourceRange.levelCount = 1;
        viewCI.subresourceRange.baseArrayLayer = 0;
        viewCI.subresourceRange.layerCount = 1;
        viewCI.image = offscreen.image;
        VK_CHECK_RESULT(vkCreateImageView(device, &viewCI, nullptr, &offscreen.view));

        // Framebuffer
        VkFramebufferCreateInfo framebufferCI{};
        framebufferCI.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferCI.renderPass = renderpass;
        framebufferCI.attachmentCount = 1;
        framebufferCI.pAttachments = &offscreen.view;
        framebufferCI.width = dim;
        framebufferCI.height = dim;
        framebufferCI.layers = 1;
        VK_CHECK_RESULT(vkCreateFramebuffer(device, &framebufferCI, nullptr, &offscreen.framebuffer));

        VkCommandBuffer layoutCmd = mCommands->get().buffer();
        VkImageMemoryBarrier imageMemoryBarrier{};
        imageMemoryBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        imageMemoryBarrier.image = offscreen.image;
        imageMemoryBarrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        imageMemoryBarrier.newLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
        imageMemoryBarrier.srcAccessMask = 0;
        imageMemoryBarrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
        imageMemoryBarrier.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };
        vkCmdPipelineBarrier(layoutCmd, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, 0, 0, nullptr, 0, nullptr, 1, &imageMemoryBarrier);
    }

    // Descriptors
    VkDescriptorSetLayout descriptorsetlayout;
    VkDescriptorSetLayoutBinding setLayoutBinding = { 0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1, VK_SHADER_STAGE_FRAGMENT_BIT, nullptr };
    VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCI{};
    descriptorSetLayoutCI.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    descriptorSetLayoutCI.pBindings = &setLayoutBinding;
    descriptorSetLayoutCI.bindingCount = 1;
    VK_CHECK_RESULT(vkCreateDescriptorSetLayout(device, &descriptorSetLayoutCI, nullptr, &descriptorsetlayout));

    // Descriptor Pool
    VkDescriptorPoolSize poolSize = { VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1 };
    VkDescriptorPoolCreateInfo descriptorPoolCI{};
    descriptorPoolCI.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    descriptorPoolCI.poolSizeCount = 1;
    descriptorPoolCI.pPoolSizes = &poolSize;
    descriptorPoolCI.maxSets = 2;
    VkDescriptorPool descriptorpool;
    VK_CHECK_RESULT(vkCreateDescriptorPool(device, &descriptorPoolCI, nullptr, &descriptorpool));

    // Descriptor sets
    VkDescriptorSet descriptorset;
    VkDescriptorSetAllocateInfo descriptorSetAllocInfo{};
    descriptorSetAllocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    descriptorSetAllocInfo.descriptorPool = descriptorpool;
    descriptorSetAllocInfo.pSetLayouts = &descriptorsetlayout;
    descriptorSetAllocInfo.descriptorSetCount = 1;
    VK_CHECK_RESULT(vkAllocateDescriptorSets(device, &descriptorSetAllocInfo, &descriptorset));
    VkWriteDescriptorSet writeDescriptorSet{};
    writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writeDescriptorSet.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    writeDescriptorSet.descriptorCount = 1;
    writeDescriptorSet.dstSet = descriptorset;
    writeDescriptorSet.dstBinding = 0;
    VulkanTexture* cube = (VulkanTexture*)environmentCube;
    VkDescriptorImageInfo imageInfo;
    imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    imageInfo.imageView = cube->getVkImageView();
    imageInfo.sampler = cube->getSampler();
    writeDescriptorSet.pImageInfo = &imageInfo;
    vkUpdateDescriptorSets(device, 1, &writeDescriptorSet, 0, nullptr);
#define M_PI 3.14159265358979323846
    struct PushBlockIrradiance {
        Ogre::Matrix4 mvp;
        float deltaPhi = (2.0f * float(M_PI)) / 180.0f;
        float deltaTheta = (0.5f * float(M_PI)) / 64.0f;
    } pushBlockIrradiance;

    struct PushBlockPrefilterEnv {
        Ogre::Matrix4 mvp;
        float roughness;
        uint32_t numSamples = 32u;
    } pushBlockPrefilterEnv;


    // Pipeline layout
    VkPipelineLayout pipelinelayout;
    VkPushConstantRange pushConstantRange{};
    pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
    if (type == CubeType_Irradiance)
    {
        pushConstantRange.size = sizeof(PushBlockIrradiance);
    }
    else
    {
        pushConstantRange.size = sizeof(PushBlockPrefilterEnv);
    }



    VkPipelineLayoutCreateInfo pipelineLayoutCI{};
    pipelineLayoutCI.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutCI.setLayoutCount = 1;
    pipelineLayoutCI.pSetLayouts = &descriptorsetlayout;
    pipelineLayoutCI.pushConstantRangeCount = 1;
    pipelineLayoutCI.pPushConstantRanges = &pushConstantRange;
    VK_CHECK_RESULT(vkCreatePipelineLayout(device, &pipelineLayoutCI, nullptr, &pipelinelayout));

    // Pipeline
    VkPipelineInputAssemblyStateCreateInfo inputAssemblyStateCI{};
    inputAssemblyStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssemblyStateCI.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

    VkPipelineRasterizationStateCreateInfo rasterizationStateCI{};
    rasterizationStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizationStateCI.polygonMode = VK_POLYGON_MODE_FILL;
    rasterizationStateCI.cullMode = VK_CULL_MODE_NONE;
    rasterizationStateCI.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
    rasterizationStateCI.lineWidth = 1.0f;

    VkPipelineColorBlendAttachmentState blendAttachmentState{};
    blendAttachmentState.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    blendAttachmentState.blendEnable = VK_FALSE;

    VkPipelineColorBlendStateCreateInfo colorBlendStateCI{};
    colorBlendStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlendStateCI.attachmentCount = 1;
    colorBlendStateCI.pAttachments = &blendAttachmentState;

    VkPipelineDepthStencilStateCreateInfo depthStencilStateCI{};
    depthStencilStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    depthStencilStateCI.depthTestEnable = VK_FALSE;
    depthStencilStateCI.depthWriteEnable = VK_FALSE;
    depthStencilStateCI.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
    depthStencilStateCI.front = depthStencilStateCI.back;
    depthStencilStateCI.back.compareOp = VK_COMPARE_OP_ALWAYS;

    VkPipelineViewportStateCreateInfo viewportStateCI{};
    viewportStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportStateCI.viewportCount = 1;
    viewportStateCI.scissorCount = 1;

    VkPipelineMultisampleStateCreateInfo multisampleStateCI{};
    multisampleStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampleStateCI.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

    std::vector<VkDynamicState> dynamicStateEnables = { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };
    VkPipelineDynamicStateCreateInfo dynamicStateCI{};
    dynamicStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamicStateCI.pDynamicStates = dynamicStateEnables.data();
    dynamicStateCI.dynamicStateCount = static_cast<uint32_t>(dynamicStateEnables.size());

    // Vertex input state
    VkVertexInputBindingDescription vertexInputBinding = { 0, sizeof(SVertexElement), VK_VERTEX_INPUT_RATE_VERTEX };
    VkVertexInputAttributeDescription vertexInputAttribute = { 0, 0, VK_FORMAT_R32G32B32_SFLOAT, 0 };

    VkPipelineVertexInputStateCreateInfo vertexInputStateCI{};
    vertexInputStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputStateCI.vertexBindingDescriptionCount = 1;
    vertexInputStateCI.pVertexBindingDescriptions = &vertexInputBinding;
    vertexInputStateCI.vertexAttributeDescriptionCount = 1;
    vertexInputStateCI.pVertexAttributeDescriptions = &vertexInputAttribute;

    std::array<VkPipelineShaderStageCreateInfo, 2> shaderStages;

    VkGraphicsPipelineCreateInfo pipelineCI{};
    pipelineCI.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineCI.layout = pipelinelayout;
    pipelineCI.renderPass = renderpass;
    pipelineCI.pInputAssemblyState = &inputAssemblyStateCI;
    pipelineCI.pVertexInputState = &vertexInputStateCI;
    pipelineCI.pRasterizationState = &rasterizationStateCI;
    pipelineCI.pColorBlendState = &colorBlendStateCI;
    pipelineCI.pMultisampleState = &multisampleStateCI;
    pipelineCI.pViewportState = &viewportStateCI;
    pipelineCI.pDepthStencilState = &depthStencilStateCI;
    pipelineCI.pDynamicState = &dynamicStateCI;
    pipelineCI.stageCount = 2;
    pipelineCI.pStages = shaderStages.data();
    pipelineCI.renderPass = renderpass;
    shaderStages[0] = {};
    shaderStages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
    shaderStages[0].pName = "main";

    auto resInfo = ResourceManager::getSingleton().getResource("filtercube.vert");
    shaderStages[0].module = vks::tools::loadShaderAssic(resInfo->_fullname.c_str(), device, Ogre::VertexShader);
    shaderStages[1] = {};
    shaderStages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    shaderStages[1].pName = "main";
    switch (type) {
    case CubeType_Irradiance:
        resInfo = ResourceManager::getSingleton().getResource("irradiancecube.frag");
        shaderStages[1].module = vks::tools::loadShaderAssic(resInfo->_fullname.c_str(), device, Ogre::PixelShader);
        break;
    case CubeType_Prefiltered:
        resInfo = ResourceManager::getSingleton().getResource("prefilterenvmap.frag");
        shaderStages[1].module = vks::tools::loadShaderAssic(resInfo->_fullname.c_str(), device, Ogre::PixelShader);
        break;
    };
    VkPipeline pipeline;
    VK_CHECK_RESULT(vkCreateGraphicsPipelines(device, nullptr, 1, &pipelineCI, nullptr, &pipeline));
    for (auto shaderStage : shaderStages) {
        vkDestroyShaderModule(device, shaderStage.module, nullptr);
    }

    // Render cubemap
    VkClearValue clearValues[1];
    clearValues[0].color = { { 0.2f, 0.0f, 0.0f, 0.0f } };

    VkRenderPassBeginInfo renderPassBeginInfo{};
    renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassBeginInfo.renderPass = renderpass;
    renderPassBeginInfo.framebuffer = offscreen.framebuffer;
    renderPassBeginInfo.renderArea.extent.width = dim;
    renderPassBeginInfo.renderArea.extent.height = dim;
    renderPassBeginInfo.clearValueCount = 1;
    renderPassBeginInfo.pClearValues = clearValues;

    Ogre::Matrix4 mat;

    std::vector<Ogre::Matrix4> matrices = {
        Ogre::Math::makeRotateMatrix(Ogre::Math::makeRotateMatrix(Ogre::Matrix4::IDENTITY, 90.0f, Ogre::Vector3(0.0f, 1.0f, 0.0f)), 180.0f, Ogre::Vector3(1.0f, 0.0f, 0.0f)),
        Ogre::Math::makeRotateMatrix(Ogre::Math::makeRotateMatrix(Ogre::Matrix4::IDENTITY, -90.0f, Ogre::Vector3(0.0f, 1.0f, 0.0f)), 180.0f, Ogre::Vector3(1.0f, 0.0f, 0.0f)),
        Ogre::Math::makeRotateMatrix(Ogre::Matrix4::IDENTITY, -90.0f, Ogre::Vector3(1.0f, 0.0f, 0.0f)),
        Ogre::Math::makeRotateMatrix(Ogre::Matrix4::IDENTITY, 90.0f, Ogre::Vector3(1.0f, 0.0f, 0.0f)),
        Ogre::Math::makeRotateMatrix(Ogre::Matrix4::IDENTITY, 180.0f, Ogre::Vector3(1.0f, 0.0f, 0.0f)),
        Ogre::Math::makeRotateMatrix(Ogre::Matrix4::IDENTITY, 180.0f, Ogre::Vector3(0.0f, 0.0f, 1.0f)),
    };



    VkViewport viewport{};
    viewport.width = (float)dim;
    viewport.height = (float)dim;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    VkRect2D scissor{};
    scissor.extent.width = dim;
    scissor.extent.height = dim;

    const uint32_t numMips = static_cast<uint32_t>(floor(log2(dim))) + 1;

    VkImageSubresourceRange subresourceRange{};
    subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    subresourceRange.baseMipLevel = 0;
    subresourceRange.levelCount = numMips;
    subresourceRange.layerCount = 6;
    auto cubeImage = tex->getVkImage();
    // Change image layout for all cubemap faces to transfer destination
    {
        VkCommandBuffer cmdBuf = mCommands->get().buffer();
        VkImageMemoryBarrier imageMemoryBarrier{};
        imageMemoryBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        imageMemoryBarrier.image = cubeImage;
        imageMemoryBarrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        imageMemoryBarrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
        imageMemoryBarrier.srcAccessMask = 0;
        imageMemoryBarrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        imageMemoryBarrier.subresourceRange = subresourceRange;
        vkCmdPipelineBarrier(cmdBuf, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, 0, 0, nullptr, 0, nullptr, 1, &imageMemoryBarrier);
    }

    std::string meshName = "box.mesh";
    auto mesh = MeshManager::getSingleton().createBox(meshName, 512, "SkyLan");
    auto sceneManager = Ogre::Root::getSingletonPtr()->getSceneManager(MAIN_SCENE_MANAGER);
    auto entity = sceneManager->createEntity(name, meshName);
    auto r = entity->getSubEntity(0);
    IndexData* indexData = r->getIndexData();
    VertexData* vertexData = r->getVertexData();
    for (uint32_t m = 0; m < numMips; m++) {
        for (uint32_t f = 0; f < 6; f++) {

            VkCommandBuffer cmdBuf = mCommands->get().buffer();

            viewport.width = static_cast<float>(dim * std::pow(0.5f, m));
            viewport.height = static_cast<float>(dim * std::pow(0.5f, m));
            vkCmdSetViewport(cmdBuf, 0, 1, &viewport);
            vkCmdSetScissor(cmdBuf, 0, 1, &scissor);

            // Render scene from cube face's point of view
            vkCmdBeginRenderPass(cmdBuf, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

            // Pass parameters for current pass using a push constant block
            auto perspective = Ogre::Math::makePerspectiveMatrixRH((float)(M_PI / 2.0), 1.0f, 0.1f, 512);
            if (type == CubeType_Irradiance)
            {
                pushBlockIrradiance.mvp = perspective * matrices[f];
                pushBlockIrradiance.mvp = pushBlockIrradiance.mvp.transpose();
                vkCmdPushConstants(cmdBuf, pipelinelayout, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(pushBlockIrradiance), &pushBlockIrradiance);
            }
            else
            {
                pushBlockPrefilterEnv.mvp = perspective * matrices[f];
                pushBlockPrefilterEnv.mvp = pushBlockPrefilterEnv.mvp.transpose();
                pushBlockPrefilterEnv.roughness = (float)m / (float)(numMips - 1);
                vkCmdPushConstants(cmdBuf, pipelinelayout, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(pushBlockPrefilterEnv), &pushBlockPrefilterEnv);
            }

            bluevk::vkCmdBindPipeline(cmdBuf, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
            bluevk::vkCmdBindDescriptorSets(cmdBuf, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelinelayout, 0, 1, &descriptorset, 0, NULL);

            VkDeviceSize offsets[1] = { 0 };

            vertexData->bind(cmdBuf);

            if (indexData)
            {
                indexData->bind();
                IndexDataView* view = r->getIndexView();
                vkCmdDrawIndexed(cmdBuf, view->mIndexCount, 1,
                    view->mIndexLocation, view->mBaseVertexLocation, 0);
            }

            vkCmdEndRenderPass(cmdBuf);

            VkImageSubresourceRange subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };
            subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            subresourceRange.baseMipLevel = 0;
            subresourceRange.levelCount = numMips;
            subresourceRange.layerCount = 6;

            {
                VkImageMemoryBarrier imageMemoryBarrier{};
                imageMemoryBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
                imageMemoryBarrier.image = offscreen.image;
                imageMemoryBarrier.oldLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
                imageMemoryBarrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
                imageMemoryBarrier.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
                imageMemoryBarrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
                imageMemoryBarrier.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };
                vkCmdPipelineBarrier(cmdBuf, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, 0, 0, nullptr, 0, nullptr, 1, &imageMemoryBarrier);
            }

            // Copy region for transfer from framebuffer to cube face
            VkImageCopy copyRegion{};

            copyRegion.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            copyRegion.srcSubresource.baseArrayLayer = 0;
            copyRegion.srcSubresource.mipLevel = 0;
            copyRegion.srcSubresource.layerCount = 1;
            copyRegion.srcOffset = { 0, 0, 0 };

            copyRegion.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            copyRegion.dstSubresource.baseArrayLayer = f;
            copyRegion.dstSubresource.mipLevel = m;
            copyRegion.dstSubresource.layerCount = 1;
            copyRegion.dstOffset = { 0, 0, 0 };

            copyRegion.extent.width = static_cast<uint32_t>(viewport.width);
            copyRegion.extent.height = static_cast<uint32_t>(viewport.height);
            copyRegion.extent.depth = 1;

            bluevk::vkCmdCopyImage(
                cmdBuf,
                offscreen.image,
                VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                cubeImage,
                VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                1,
                &copyRegion);

            {
                VkImageMemoryBarrier imageMemoryBarrier{};
                imageMemoryBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
                imageMemoryBarrier.image = offscreen.image;
                imageMemoryBarrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
                imageMemoryBarrier.newLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
                imageMemoryBarrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
                imageMemoryBarrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
                imageMemoryBarrier.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };
                vkCmdPipelineBarrier(cmdBuf, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, 0, 0, nullptr, 0, nullptr, 1, &imageMemoryBarrier);
            }

        }
    }

    {
        VkCommandBuffer cmdBuf = mCommands->get().buffer();
        VkImageMemoryBarrier imageMemoryBarrier{};
        imageMemoryBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        imageMemoryBarrier.image = cubeImage;
        imageMemoryBarrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
        imageMemoryBarrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        imageMemoryBarrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        imageMemoryBarrier.dstAccessMask = VK_ACCESS_HOST_WRITE_BIT | VK_ACCESS_TRANSFER_WRITE_BIT;
        imageMemoryBarrier.subresourceRange = subresourceRange;
        vkCmdPipelineBarrier(cmdBuf, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, 0, 0, nullptr, 0, nullptr, 1, &imageMemoryBarrier);
    }


    bluevk::vkDestroyRenderPass(device, renderpass, nullptr);
    bluevk::vkDestroyFramebuffer(device, offscreen.framebuffer, nullptr);
    bluevk::vkFreeMemory(device, offscreen.memory, nullptr);
    bluevk::vkDestroyImageView(device, offscreen.view, nullptr);
    bluevk::vkDestroyImage(device, offscreen.image, nullptr);
    bluevk::vkDestroyDescriptorPool(device, descriptorpool, nullptr);
    bluevk::vkDestroyDescriptorSetLayout(device, descriptorsetlayout, nullptr);
    bluevk::vkDestroyPipeline(device, pipeline, nullptr);
    bluevk::vkDestroyPipelineLayout(device, pipelinelayout, nullptr);
    return tex;
}

Ogre::OgreTexture* VulkanRenderSystemBase::generateBRDFLUT(const std::string& name)
{
    auto dim = 512;
    const uint32_t numMips = static_cast<uint32_t>(floor(log2(dim))) + 1;

    Ogre::TextureProperty texProperty;
    texProperty._tex_usage = Ogre::TextureUsage::COLOR_ATTACHMENT;
    texProperty._texType = TEX_TYPE_2D;
    texProperty._width = dim;
    texProperty._height = dim;
    texProperty._need_mipmap = false;
    texProperty._tex_format = PF_FLOAT16_GR;
    texProperty._samplerParams.filterMag = filament::backend::SamplerMagFilter::LINEAR;
    texProperty._samplerParams.filterMin = filament::backend::SamplerMinFilter::LINEAR_MIPMAP_LINEAR;
    texProperty._samplerParams.wrapS = filament::backend::SamplerWrapMode::CLAMP_TO_EDGE;
    texProperty._samplerParams.wrapT = filament::backend::SamplerWrapMode::CLAMP_TO_EDGE;
    texProperty._samplerParams.wrapR = filament::backend::SamplerWrapMode::CLAMP_TO_EDGE;
    texProperty._samplerParams.anisotropyLog2 = 0;
    VulkanTexture* tex = new VulkanTexture(name, mVulkanPlatform, mCommands, &texProperty);

    tex->load(nullptr);

    auto device = mVulkanPlatform->getDevice();
    auto vulkanFormat = VK_FORMAT_R16G16_SFLOAT;

    // FB, Att, RP, Pipe, etc.
    VkAttachmentDescription attDesc{};
    // Color attachment
    attDesc.format = vulkanFormat;
    attDesc.samples = VK_SAMPLE_COUNT_1_BIT;
    attDesc.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    attDesc.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    attDesc.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attDesc.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attDesc.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    attDesc.finalLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    VkAttachmentReference colorReference = { 0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL };

    VkSubpassDescription subpassDescription{};
    subpassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpassDescription.colorAttachmentCount = 1;
    subpassDescription.pColorAttachments = &colorReference;

    // Use subpass dependencies for layout transitions
    std::array<VkSubpassDependency, 2> dependencies;
    dependencies[0].srcSubpass = VK_SUBPASS_EXTERNAL;
    dependencies[0].dstSubpass = 0;
    dependencies[0].srcStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
    dependencies[0].dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependencies[0].srcAccessMask = VK_ACCESS_MEMORY_READ_BIT;
    dependencies[0].dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    dependencies[0].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;
    dependencies[1].srcSubpass = 0;
    dependencies[1].dstSubpass = VK_SUBPASS_EXTERNAL;
    dependencies[1].srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependencies[1].dstStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
    dependencies[1].srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    dependencies[1].dstAccessMask = VK_ACCESS_MEMORY_READ_BIT;
    dependencies[1].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

    // Create the actual renderpass
    VkRenderPassCreateInfo renderPassCI{};
    renderPassCI.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassCI.attachmentCount = 1;
    renderPassCI.pAttachments = &attDesc;
    renderPassCI.subpassCount = 1;
    renderPassCI.pSubpasses = &subpassDescription;
    renderPassCI.dependencyCount = 2;
    renderPassCI.pDependencies = dependencies.data();

    VkRenderPass renderpass;
    VK_CHECK_RESULT(bluevk::vkCreateRenderPass(device, &renderPassCI, nullptr, &renderpass));

    VkImageView imageView = tex->getVkImageView();
    VkFramebufferCreateInfo framebufferCI{};
    framebufferCI.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebufferCI.renderPass = renderpass;
    framebufferCI.attachmentCount = 1;
    framebufferCI.pAttachments = &imageView;
    framebufferCI.width = dim;
    framebufferCI.height = dim;
    framebufferCI.layers = 1;

    VkFramebuffer framebuffer;
    VK_CHECK_RESULT(bluevk::vkCreateFramebuffer(device, &framebufferCI, nullptr, &framebuffer));

    // Desriptors
    VkDescriptorSetLayout descriptorsetlayout;
    VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCI{};
    descriptorSetLayoutCI.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    VK_CHECK_RESULT(bluevk::vkCreateDescriptorSetLayout(device, &descriptorSetLayoutCI, nullptr, &descriptorsetlayout));

    // Pipeline layout
    VkPipelineLayout pipelinelayout;
    VkPipelineLayoutCreateInfo pipelineLayoutCI{};
    pipelineLayoutCI.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutCI.setLayoutCount = 1;
    pipelineLayoutCI.pSetLayouts = &descriptorsetlayout;
    VK_CHECK_RESULT(bluevk::vkCreatePipelineLayout(device, &pipelineLayoutCI, nullptr, &pipelinelayout));

    // Pipeline
    VkPipelineInputAssemblyStateCreateInfo inputAssemblyStateCI{};
    inputAssemblyStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssemblyStateCI.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

    VkPipelineRasterizationStateCreateInfo rasterizationStateCI{};
    rasterizationStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizationStateCI.polygonMode = VK_POLYGON_MODE_FILL;
    rasterizationStateCI.cullMode = VK_CULL_MODE_NONE;
    rasterizationStateCI.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
    rasterizationStateCI.lineWidth = 1.0f;

    VkPipelineColorBlendAttachmentState blendAttachmentState{};
    blendAttachmentState.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    blendAttachmentState.blendEnable = VK_FALSE;

    VkPipelineColorBlendStateCreateInfo colorBlendStateCI{};
    colorBlendStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlendStateCI.attachmentCount = 1;
    colorBlendStateCI.pAttachments = &blendAttachmentState;

    VkPipelineDepthStencilStateCreateInfo depthStencilStateCI{};
    depthStencilStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    depthStencilStateCI.depthTestEnable = VK_FALSE;
    depthStencilStateCI.depthWriteEnable = VK_FALSE;
    depthStencilStateCI.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
    depthStencilStateCI.front = depthStencilStateCI.back;
    depthStencilStateCI.back.compareOp = VK_COMPARE_OP_ALWAYS;

    VkPipelineViewportStateCreateInfo viewportStateCI{};
    viewportStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportStateCI.viewportCount = 1;
    viewportStateCI.scissorCount = 1;

    VkPipelineMultisampleStateCreateInfo multisampleStateCI{};
    multisampleStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampleStateCI.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

    std::vector<VkDynamicState> dynamicStateEnables = { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };
    VkPipelineDynamicStateCreateInfo dynamicStateCI{};
    dynamicStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamicStateCI.pDynamicStates = dynamicStateEnables.data();
    dynamicStateCI.dynamicStateCount = static_cast<uint32_t>(dynamicStateEnables.size());

    VkPipelineVertexInputStateCreateInfo emptyInputStateCI{};
    emptyInputStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

    std::array<VkPipelineShaderStageCreateInfo, 2> shaderStages;

    VkGraphicsPipelineCreateInfo pipelineCI{};
    pipelineCI.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineCI.layout = pipelinelayout;
    pipelineCI.renderPass = renderpass;
    pipelineCI.pInputAssemblyState = &inputAssemblyStateCI;
    pipelineCI.pVertexInputState = &emptyInputStateCI;
    pipelineCI.pRasterizationState = &rasterizationStateCI;
    pipelineCI.pColorBlendState = &colorBlendStateCI;
    pipelineCI.pMultisampleState = &multisampleStateCI;
    pipelineCI.pViewportState = &viewportStateCI;
    pipelineCI.pDepthStencilState = &depthStencilStateCI;
    pipelineCI.pDynamicState = &dynamicStateCI;
    pipelineCI.stageCount = 2;
    pipelineCI.pStages = shaderStages.data();

    // Look-up-table (from BRDF) pipeline		
    shaderStages[0] = {};
    shaderStages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
    shaderStages[0].pName = "main";
    auto resInfo = ResourceManager::getSingleton().getResource("genbrdflut.vert");
    shaderStages[0].module = vks::tools::loadShaderAssic(resInfo->_fullname.c_str(), device, Ogre::VertexShader);

    shaderStages[1] = {};
    shaderStages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    shaderStages[1].pName = "main";
    resInfo = ResourceManager::getSingleton().getResource("genbrdflut.frag");
    shaderStages[1].module = vks::tools::loadShaderAssic(resInfo->_fullname.c_str(), device, Ogre::PixelShader);

    VkPipeline pipeline;
    VK_CHECK_RESULT(bluevk::vkCreateGraphicsPipelines(device, nullptr, 1, &pipelineCI, nullptr, &pipeline));
    for (auto shaderStage : shaderStages) {
        vkDestroyShaderModule(device, shaderStage.module, nullptr);
    }

    // Render
    VkClearValue clearValues[1];
    clearValues[0].color = { { 0.0f, 0.0f, 0.0f, 1.0f } };

    VkRenderPassBeginInfo renderPassBeginInfo{};
    renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassBeginInfo.renderPass = renderpass;
    renderPassBeginInfo.renderArea.extent.width = dim;
    renderPassBeginInfo.renderArea.extent.height = dim;
    renderPassBeginInfo.clearValueCount = 1;
    renderPassBeginInfo.pClearValues = clearValues;
    renderPassBeginInfo.framebuffer = framebuffer;

    VkCommandBuffer cmdBuf = mCommands->get().buffer();
    bluevk::vkCmdBeginRenderPass(cmdBuf, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

    VkViewport viewport{};
    viewport.width = (float)dim;
    viewport.height = (float)dim;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    VkRect2D scissor{};
    scissor.extent.width = dim;
    scissor.extent.height = dim;

    bluevk::vkCmdSetViewport(cmdBuf, 0, 1, &viewport);
    bluevk::vkCmdSetScissor(cmdBuf, 0, 1, &scissor);
    bluevk::vkCmdBindPipeline(cmdBuf, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
    bluevk::vkCmdDraw(cmdBuf, 3, 1, 0, 0);
    bluevk::vkCmdEndRenderPass(cmdBuf);

    

    bluevk::vkDestroyPipeline(device, pipeline, nullptr);
    bluevk::vkDestroyPipelineLayout(device, pipelinelayout, nullptr);
    bluevk::vkDestroyRenderPass(device, renderpass, nullptr);
    bluevk::vkDestroyFramebuffer(device, framebuffer, nullptr);
    bluevk::vkDestroyDescriptorSetLayout(device, descriptorsetlayout, nullptr);

    return tex;
}

void* VulkanRenderSystemBase::lockBuffer(Handle<HwBufferObject> bufHandle, uint32_t offset, uint32_t numBytes)
{
    VulkanBufferObject* vulkanBufferObject = mResourceAllocator.handle_cast<VulkanBufferObject*>(bufHandle);
    return vulkanBufferObject->buffer.lock(offset, numBytes);
}

void VulkanRenderSystemBase::unlockBuffer(Handle<HwBufferObject> bufHandle)
{
    VulkanBufferObject* vulkanBufferObject = mResourceAllocator.handle_cast<VulkanBufferObject*>(bufHandle);
    vulkanBufferObject->buffer.unlock(mCommands->get().buffer());
}

void VulkanRenderSystemBase::bindVertexBuffer(Handle<HwBufferObject> bufferHandle, uint32_t binding)
{
    VulkanBufferObject* vulkanBufferObject = mResourceAllocator.handle_cast<VulkanBufferObject*>(bufferHandle);

    VkDeviceSize offsets[1] = { 0 };
    auto cmdBuffer = mCommands->get().buffer();

    VkBuffer vkBuffer = vulkanBufferObject->buffer.getGpuBuffer();
    vkCmdBindVertexBuffers(cmdBuffer, binding, 1, &vkBuffer, offsets);

}

void VulkanRenderSystemBase::bindIndexBuffer(Handle<HwBufferObject> bufferHandle, uint32_t indexSize)
{
    VulkanBufferObject* vulkanBufferObject = mResourceAllocator.handle_cast<VulkanBufferObject*>(bufferHandle);
    auto cmdBuffer = mCommands->get().buffer();

    VkBuffer vkBuffer = vulkanBufferObject->buffer.getGpuBuffer();

    vkCmdBindIndexBuffer(cmdBuffer, vkBuffer, 0, indexSize==2? VK_INDEX_TYPE_UINT16: VK_INDEX_TYPE_UINT32);
}

Handle<HwBufferObject> VulkanRenderSystemBase::createBufferObject(
    BufferObjectBinding bindingType,
    BufferUsage usage,
    uint32_t byteCount,
    const char* debugName)
{
    Handle<HwBufferObject> boh =  mResourceAllocator.allocHandle<VulkanBufferObject>();

    VulkanBufferObject* bufferObject = mResourceAllocator.construct<VulkanBufferObject>(boh, mAllocator,
        *mStagePool, byteCount, bindingType);
    if (debugName)
    {
        bufferObject->buffer.setBufferName(mVulkanPlatform->getDevice(), debugName);
    }
    
    return boh;
}

void VulkanRenderSystemBase::updateBufferObject(
    Handle<HwBufferObject> boh,
    const char* data,
    uint32_t size)
{
    VulkanCommandBuffer& commands = mCommands->get();
    VulkanBufferObject* bo = mResourceAllocator.handle_cast<VulkanBufferObject*>(boh);
    bo->buffer.loadFromCpu(commands.buffer(), data, 0, size);
}

Handle<HwDescriptorSetLayout> VulkanRenderSystemBase::createDescriptorSetLayout(DescriptorSetLayout& info)
{
    Handle<HwDescriptorSetLayout> dslh = mResourceAllocator.allocHandle<VulkanDescriptorSetLayout>();
    VulkanDescriptorSetLayout* uboLayout = mResourceAllocator.construct<VulkanDescriptorSetLayout>(dslh, info);
    mDescriptorSetManager->initVkLayout(uboLayout);
    return dslh;
}

Handle<HwDescriptorSetLayout> VulkanRenderSystemBase::getDescriptorSetLayout(Handle<HwProgram> programHandle, uint32_t index)
{
    VulkanProgram* vulkanProgram = mResourceAllocator.handle_cast<VulkanProgram*>(programHandle);

    return vulkanProgram->getLayout(index);
}

Handle<HwDescriptorSet> VulkanRenderSystemBase::createDescriptorSet(Handle<HwDescriptorSetLayout> dslh)
{
    Handle<HwDescriptorSet> dsh = mResourceAllocator.allocHandle<VulkanDescriptorSet>();

    VulkanDescriptorSetLayout* layout = mResourceAllocator.handle_cast<VulkanDescriptorSetLayout*>(dslh);
    mDescriptorSetManager->createSet(dsh, layout);
    return dsh;
}

Handle<HwPipelineLayout> VulkanRenderSystemBase::createPipelineLayout(std::array<Handle<HwDescriptorSetLayout>, 4>& layouts)
{
    Handle<HwPipelineLayout> plo = mResourceAllocator.allocHandle<VulkanPipelineLayout>();
    uint32_t index = 0;

    VulkanPipelineLayoutCache::PipelineLayoutKey key;
    for (auto& layoutHandle : layouts)
    {
        auto layout = mResourceAllocator.handle_cast<VulkanDescriptorSetLayout*>(layoutHandle);
        VkDescriptorSetLayout vkLayout = layout->getVkLayout();
        key[index] = vkLayout;
        index++;
    }
    VkPipelineLayout vulkanPipelineLayout = mPipelineLayoutCache->getLayout(key);
    VulkanPipelineLayout* pipeLayout = mResourceAllocator.construct<VulkanPipelineLayout>(plo, vulkanPipelineLayout);
    return plo;
}

Handle<HwProgram> VulkanRenderSystemBase::createShaderProgram(const ShaderInfo& shaderInfo, VertexDeclaration* decl)
{
    Handle<HwProgram> program = mResourceAllocator.allocHandle<VulkanProgram>();
    VulkanProgram* vulkanProgram = mResourceAllocator.construct<VulkanProgram>(program, shaderInfo.shaderName);

    Ogre::ShaderPrivateInfo* privateInfo =
        ShaderManager::getSingleton().getShader(shaderInfo.shaderName, EngineType_Vulkan);

    auto res = ResourceManager::getSingleton().getResource(privateInfo->vertexShaderName);
    if (res)
    {
        String* vertexContent = ShaderManager::getSingleton().getShaderContent(privateInfo->vertexShaderName);
        VkShaderModuleInfo moduleInfo;
        moduleInfo.shaderType = Ogre::VertexShader;
        glslCompileShader(
            res->_fullname,
            *vertexContent,
            privateInfo->vertexShaderEntryPoint,
            shaderInfo.shaderMacros,
            moduleInfo);
        vulkanProgram->updateVertexShader(moduleInfo.shaderModule);
        std::vector<VkVertexInputAttributeDescription>& attributeDescriptions = 
            vulkanProgram->getAttributeDescriptions();
        this->parseAttributeDescriptions(decl, moduleInfo.inputDesc, attributeDescriptions);
        std::vector<VkVertexInputBindingDescription>& vertexInputBindings =
            vulkanProgram->getVertexInputBindings();
        this->parseInputBindingDescription(decl, moduleInfo.inputDesc, vertexInputBindings);
    }
    
    res = ResourceManager::getSingleton().getResource(privateInfo->fragShaderName);
    if (res)
    {
        String* vertexContent = ShaderManager::getSingleton().getShaderContent(privateInfo->fragShaderName);
        VkShaderModuleInfo moduleInfo;
        moduleInfo.shaderType = Ogre::PixelShader;

        glslCompileShader(
            res->_fullname,
            *vertexContent,
            privateInfo->vertexShaderEntryPoint,
            shaderInfo.shaderMacros,
            moduleInfo);
        vulkanProgram->updateFragmentShader(moduleInfo.shaderModule);
    }
    
    DescriptorSetLayout info;
    info.bindings.reserve(10);
    DescriptorSetLayoutBinding binding;
    for (auto i = 0; i < 16; i++)
    {
        bool hasVertex = (shaderInfo.uboVertexMask & (1uLL << i)) != 0;
        bool hasFragment = (shaderInfo.uboFragMask & (1uLL << i)) != 0;

        if (!hasVertex && !hasFragment)
            continue;
        binding.binding = i;

        binding.flags = DescriptorFlags::NONE;
        binding.count = 0;
        binding.type = DescriptorType::UNIFORM_BUFFER;
        if (hasVertex)
        {
            binding.stageFlags = ShaderStageFlags::VERTEX;
        }

        if (hasFragment)
        {
            binding.stageFlags = static_cast<ShaderStageFlags>(
                binding.stageFlags | ShaderStageFlags::FRAGMENT);
        }

        info.bindings.push_back(binding);
    }

    Handle<HwDescriptorSetLayout> uboLayoutHandle = mResourceAllocator.allocHandle<VulkanDescriptorSetLayout>();
    VulkanDescriptorSetLayout* uboLayout = mResourceAllocator.construct<VulkanDescriptorSetLayout>(uboLayoutHandle, info);
    mDescriptorSetManager->initVkLayout(uboLayout);

    info.bindings.clear();

    for (auto i = 0; i < 32; i++)
    {
        bool hasFragment = (shaderInfo.samplerFragMask & (1uLL << i)) != 0;

        if (!hasFragment)
        {
            continue;
        }

        binding.binding = i;
        binding.flags = DescriptorFlags::NONE;
        binding.count = 0;
        binding.type = DescriptorType::SAMPLER;

   
        binding.stageFlags = static_cast<ShaderStageFlags>(
            binding.stageFlags | ShaderStageFlags::FRAGMENT);


        info.bindings.push_back(binding);
    }

    Handle<HwDescriptorSetLayout> samplerLayoutHandle = mResourceAllocator.allocHandle<VulkanDescriptorSetLayout>();
    VulkanDescriptorSetLayout* samplerLayout = mResourceAllocator.construct<VulkanDescriptorSetLayout>(samplerLayoutHandle, info);
    mDescriptorSetManager->initVkLayout(samplerLayout);
    VulkanPipelineLayoutCache::PipelineLayoutKey key;
    key[0] = uboLayout->getVkLayout();
    key[1] = samplerLayout->getVkLayout();
    key[2] = VK_NULL_HANDLE;
    key[3] = VK_NULL_HANDLE;
    VkPipelineLayout vulkanPipelineLayout = mPipelineLayoutCache->getLayout(key);
    vulkanProgram->updateVulkanPipelineLayout(vulkanPipelineLayout);
    vulkanProgram->updateLayout(0, uboLayoutHandle);
    vulkanProgram->updateLayout(1, samplerLayoutHandle);
    return program;
}

Handle<HwDescriptorSetLayout> VulkanRenderSystemBase::getDescriptorSetLayout(Handle<HwComputeProgram> programHandle, uint32_t set)
{
    VulkanComputeProgram* program = mResourceAllocator.handle_cast<VulkanComputeProgram*>(programHandle);
    return program->getSetLayoutHandle(set);
}

Handle<HwComputeProgram> VulkanRenderSystemBase::createComputeProgram(const ShaderInfo& shaderInfo)
{
    Handle<HwComputeProgram> program = mResourceAllocator.allocHandle<VulkanComputeProgram>();
    VulkanComputeProgram* vulkanProgram = mResourceAllocator.construct<VulkanComputeProgram>(program, shaderInfo.shaderName);


    Ogre::ShaderPrivateInfo* privateInfo =
        ShaderManager::getSingleton().getShader(shaderInfo.shaderName, EngineType_Vulkan);

    auto res = ResourceManager::getSingleton().getResource(privateInfo->computeShaderName);
    
    String* vertexContent = ShaderManager::getSingleton().getShaderContent(privateInfo->computeShaderName);
    VkShaderModuleInfo moduleInfo;
    moduleInfo.shaderType = Ogre::ComputeShader;
    glslCompileShader(
        res->_fullname,
        *vertexContent,
        privateInfo->vertexShaderEntryPoint,
        shaderInfo.shaderMacros,
        moduleInfo);
    vulkanProgram->updateComputeShader(moduleInfo.shaderModule);

    auto results = vks::tools::getProgramBindings(moduleInfo.spv);

   
    assert_invariant(!results.empty() && "Need at least one binding for descriptor set layout.");

    std::array<VkDescriptorSetLayout, 4> layoutlist;

    for (auto& pair : results)
    {
        VkDescriptorSetLayoutCreateInfo dlinfo = {
            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
            .pNext = nullptr,
            .bindingCount = (uint32_t)pair.second.size(),
            .pBindings = pair.second.data(),
        };

        VkDescriptorSetLayout vkLayout;
        vkCreateDescriptorSetLayout(mVulkanPlatform->getDevice(), &dlinfo, VKALLOC, &vkLayout);
        layoutlist[pair.first] = vkLayout;
        vulkanProgram->updateSetLayout(vkLayout);
        DescriptorSetLayout layoutInfo;
        Handle<HwDescriptorSetLayout> dslh = mResourceAllocator.allocHandle<VulkanDescriptorSetLayout>();
        VulkanDescriptorSetLayout* uboLayout = mResourceAllocator.construct<VulkanDescriptorSetLayout>(dslh, layoutInfo);
        uboLayout->setVkLayout(vkLayout);
        vulkanProgram->updateSetLayoutHandle(pair.first, dslh);
    }
    
    VkPipelineLayout pipelineLayout;
    VkPipelineLayoutCreateInfo pPipelineLayoutCreateInfo =
        vks::initializers::pipelineLayoutCreateInfo(
            layoutlist.data(),
            results.size());

    if (vkCreatePipelineLayout(mVulkanPlatform->getDevice(), &pPipelineLayoutCreateInfo,
        nullptr, &pipelineLayout) != VK_SUCCESS)
    {
        assert_invariant(!results.empty() && "vkCreatePipelineLayout failed.");
    }

    vulkanProgram->updatePipelineLayout(pipelineLayout);

    VkPipelineShaderStageCreateInfo stage{};
    stage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    stage.pNext = NULL;
    stage.flags = 0;
    stage.stage = VK_SHADER_STAGE_COMPUTE_BIT;
    stage.module = moduleInfo.shaderModule;
    stage.pName = "main";
    stage.pSpecializationInfo = nullptr;

    VkComputePipelineCreateInfo create_info{};
    create_info.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
    create_info.pNext = NULL;
    create_info.flags = 0;
    create_info.stage = stage;
    create_info.layout = pipelineLayout;
    create_info.basePipelineHandle = 0;
    create_info.basePipelineIndex = 0;
    VkPipeline pipeline;
    vkCreateComputePipelines(mVulkanPlatform->getDevice(), NULL, 1, &create_info,
        nullptr, &pipeline);

    vulkanProgram->updatePipeline(pipeline);
    return program;
}

Handle<HwPipeline> VulkanRenderSystemBase::createPipeline(
    backend::RasterState& rasterState,
    Handle<HwProgram>& program)
{
    Handle<HwPipeline> pipelineHandle = mResourceAllocator.allocHandle<VulkanPipeline>();
    
    VulkanProgram* vulkanProgram = mResourceAllocator.handle_cast<VulkanProgram*>(program);
    VkPipelineLayout pipelineLayout = vulkanProgram->getVulkanPipelineLayout();
    VulkanPipelineCache::RasterState vulkanRasterState;
    vulkanRasterState.cullMode = getCullMode(rasterState.culling);
    vulkanRasterState.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
    vulkanRasterState.depthBiasEnable = VK_FALSE;


    vulkanRasterState.blendEnable = rasterState.hasBlending();
    vulkanRasterState.depthWriteEnable = rasterState.depthWrite;
    vulkanRasterState.alphaToCoverageEnable = rasterState.alphaToCoverage;

    vulkanRasterState.srcColorBlendFactor = getBlendFactor(rasterState.blendFunctionSrcRGB);
    vulkanRasterState.dstColorBlendFactor = getBlendFactor(rasterState.blendFunctionDstRGB);
    vulkanRasterState.srcAlphaBlendFactor = getBlendFactor(rasterState.blendFunctionSrcAlpha);
    vulkanRasterState.dstAlphaBlendFactor = getBlendFactor(rasterState.blendFunctionDstAlpha);
    vulkanRasterState.colorBlendOp = rasterState.blendEquationRGB;
    vulkanRasterState.alphaBlendOp = rasterState.blendEquationAlpha;

    vulkanRasterState.colorWriteMask = 0xf;
    vulkanRasterState.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    vulkanRasterState.colorTargetCount = 1;
    vulkanRasterState.depthCompareOp = SamplerCompareFunc::LE;
    vulkanRasterState.depthBiasConstantFactor = 0.0f;
    vulkanRasterState.depthBiasSlopeFactor = 0.0f;

    std::vector<VkVertexInputBindingDescription>& vertexInputBindings =
        vulkanProgram->getVertexInputBindings();
    std::vector<VkVertexInputAttributeDescription>& attributeDescriptions =
        vulkanProgram->getAttributeDescriptions();
    mPipelineCache->bindRenderPass(nullptr, 0);
    mPipelineCache->bindProgram(vulkanProgram->getVertexShader(), vulkanProgram->getFragmentShader());
    mPipelineCache->bindRasterState(vulkanRasterState);
    mPipelineCache->bindPrimitiveTopology(VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST);
    mPipelineCache->bindLayout(pipelineLayout);
    mPipelineCache->bindVertexArray(
        attributeDescriptions.data(),
        attributeDescriptions.size(),
        vertexInputBindings.data(),
        vertexInputBindings.size());

    VkPipeline pipeline = mPipelineCache->getPipeline();

    mPipelineCache->bindProgram(vulkanProgram->getVertexShader(), nullptr);

    VkPipeline pipelineShadow = mPipelineCache->getPipeline();
    VulkanPipeline* vulkanPipeline = mResourceAllocator.construct<VulkanPipeline>(
        pipelineHandle, pipeline, pipelineShadow);
    return pipelineHandle;
}

void VulkanRenderSystemBase::updateDescriptorSetBuffer(
    Handle<HwDescriptorSet> dsh,
    backend::descriptor_binding_t binding,
    backend::BufferObjectHandle* boh,
    uint32_t handleCount)
{
    VulkanDescriptorSet* set = mResourceAllocator.handle_cast<VulkanDescriptorSet*>(dsh);

    assert(handleCount < 10);
    VulkanBufferObject* bufferObjects[10];

    for (auto i = 0; i < handleCount; i++)
    {
        bufferObjects[i] = mResourceAllocator.handle_cast<VulkanBufferObject*>(boh[i]);
    }
    
    mDescriptorSetManager->updateBuffer(set, binding, &bufferObjects[0], handleCount);
}

void VulkanRenderSystemBase::updateDescriptorSetTexture(
    Handle<HwDescriptorSet> dsh,
    backend::descriptor_binding_t binding,
    OgreTexture* tex)
{
    VulkanDescriptorSet* set = mResourceAllocator.handle_cast<VulkanDescriptorSet*>(dsh);

    VulkanTexture* vulkanTexture = (VulkanTexture*)tex;
    VkDescriptorImageInfo info{};

    info.imageView = vulkanTexture->getVkImageView();
    info.sampler = vulkanTexture->getSampler();
    info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    VkWriteDescriptorSet const descriptorWrite = {
            .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
            .pNext = nullptr,
            .dstSet = set->vkSet,
            .dstBinding = binding,
            .descriptorCount = 1,
            .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
            .pImageInfo = &info,
        };

    vkUpdateDescriptorSets(
        mVulkanPlatform->getDevice(),
        1,
        &descriptorWrite, 0, nullptr);
}

void VulkanRenderSystemBase::bindDescriptorSet(
    Handle<HwDescriptorSet> dsh,
    uint8_t setIndex,
    backend::DescriptorSetOffsetArray&& offsets)
{
    VulkanDescriptorSet* set = mResourceAllocator.handle_cast<VulkanDescriptorSet*>(dsh);
    mDescriptorSetManager->bind(setIndex, set, std::move(offsets));
}

void VulkanRenderSystemBase::parseInputBindingDescription(
    VertexDeclaration* decl,
    std::vector<GlslInputDesc>& inputDesc,
    std::vector<VkVertexInputBindingDescription>& vertexInputBindings)
{
    vertexInputBindings.clear();
    for (uint32_t binding = 0; binding < 10; binding++)
    {
        int32_t stride = decl->getVertexSize(binding);

        if (stride <= 0)
            continue;
        vertexInputBindings.emplace_back();
        vertexInputBindings.back().binding = binding;
        vertexInputBindings.back().stride = stride;
        vertexInputBindings.back().inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    }
}

void VulkanRenderSystemBase::parseAttributeDescriptions(
    VertexDeclaration* vd,
    std::vector<GlslInputDesc>& inputDesc,
    std::vector<VkVertexInputAttributeDescription>& attributeDescriptions)
{
    attributeDescriptions.resize(inputDesc.size());
    int32_t i = 0;

    for (auto& input : inputDesc)
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
}