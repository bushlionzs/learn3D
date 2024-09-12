#include "OgreHeader.h"
#include "VulkanRenderSystem.h"
#include "VulkanShader.h"
#include "VulkanTexture.h"
#include "OgreRenderable.h"
#include "OgreVertexData.h"
#include "OgreIndexData.h"
#include "OgreVertexDeclaration.h"
#include "VulkanRenderData.h"
#include "OgreMaterial.h"
#include "OgreHardwareIndexBuffer.h"
#include "VulkanHardwareBufferManager.h"
#include "OgreCamera.h"
#include "VulkanTools.h"
#include "VulkanObjectPool.h"
#include "VulkanHelper.h"
#include "VulkanFrame.h"
#include "VulkanWindow.h"
#include "OgreViewport.h"
#include "VulkanRenderTarget.h"
#include "OgreSceneManager.h"
#include "OgreRoot.h"
#include "OgreNode.h"
#include "OgreMath.h"
#include "OgreEntity.h"
#include "OgreSubEntity.h"
#include "OgreMeshManager.h"
#include "OgreResourceManager.h"
#include "VulkanMappings.h"
#include "VulkanRaytracing.h"

static const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

static const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME,
};

VulkanRenderSystem::VulkanRenderSystem(HWND wnd)
{
    bluevk::initialize();
#ifdef _DEBUG
    mEnableValidationLayers = true;
#else
    mEnableValidationLayers = false;
#endif


    mRenderSystemName = "Vulkan";

    new VulkanHelper(this, wnd);

    mRenderList.reserve(3000);
    
}

VulkanRenderSystem::~VulkanRenderSystem()
{

}

bool VulkanRenderSystem::engineInit()
{
    RenderSystem::engineInit();
    
    
    VulkanHelper::getSingleton()._initialise(nullptr);

    enki::TaskSchedulerConfig config;
    config.numTaskThreadsToCreate = VULKAN_COMMAND_THREAD;
    mTaskScheduler.Initialize(config);

    mRayTracingContext = new VulkanRayTracingContext;

    

    return true;
}


void VulkanRenderSystem::frameStart()
{
    if (VulkanHelper::getSingleton().haveRayTracing())
    {
        mRayTracingContext->init();
    }
    
    mTriangleCount = 0;
    mBatchCount = 0;

    mCurrentVulkanFrame = mRenderWindow->getNextFrame();
    mRenderWindow->start();

    VulkanHelper::getSingleton()._resetCommandBuffer(mCurrentVulkanFrame->getFrameIndex());

    static std::vector<VkCommandBuffer>  cmdlist;
    VulkanHelper::getSingleton().fillCommandBufferList(cmdlist, mCurrentVulkanFrame->getFrameIndex(), true);

    VkCommandBufferBeginInfo cmdBeginInfo{};
    cmdBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    auto framebuffer = mRenderWindow->getFrameBuffer(mCurrentVulkanFrame->getFrameIndex());
    auto renderPass = VulkanHelper::getSingleton()._getRenderPass();
    VkCommandBufferInheritanceInfo inheritanceInfo = vks::initializers::commandBufferInheritanceInfo();
    inheritanceInfo.renderPass = renderPass;
    // Secondary command buffer also use the currently active framebuffer
    inheritanceInfo.framebuffer = framebuffer;



    VkCommandBufferBeginInfo secondBufferBeginInfo = vks::initializers::commandBufferBeginInfo();
    secondBufferBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT;
    secondBufferBeginInfo.pInheritanceInfo = &inheritanceInfo;


    auto result = vkBeginCommandBuffer(cmdlist[0], &cmdBeginInfo);

    if (result != VK_SUCCESS)
    {
        throw std::runtime_error("vkBeginCommandBuffer failed");
    }

    for (int32_t i = 1; i < cmdlist.size(); i++)
    {
        auto* commandBuffer = cmdlist.at(i);
        auto result = vkBeginCommandBuffer(commandBuffer, &secondBufferBeginInfo);

        if (result != VK_SUCCESS)
        {
            throw std::runtime_error("vkBeginCommandBuffer failed");
        }

    }
}

void VulkanRenderSystem::frameEnd()
{

}

void VulkanRenderSystem::preRender(Ogre::Camera* cam)
{
    mCamera = cam;
    
    

    updateMainPassCB(mCamera);    
}


void VulkanRenderSystem::postRender()
{
    
}




OgreTexture* VulkanRenderSystem::createTextureFromFile(
    const std::string& name,
    TextureProperty* texProperty)
{
    auto tex =  new VulkanTexture(name, texProperty, this);
    return tex;
}

Shader* VulkanRenderSystem::createShader(ShaderInfo& sinfo)
{
    return new VulkanShader(sinfo, this);
}


void VulkanRenderSystem::ready()
{
    VulkanHelper::getSingleton().loadDefaultResources();
}

RenderableData* VulkanRenderSystem::createRenderableData(Ogre::Renderable* r)
{
    return new VulkanRenderableData(this, r, mRayTracingContext);
}

void VulkanRenderSystem::_setViewport(ICamera* cam, Ogre::Viewport* vp)
{
    mViewport = vp;
    mCamera = cam;
    Ogre::RenderTarget* target;
    target = vp->getTarget();
    updateMainPassCB(cam);
    mActiveVulkanRenderTarget = dynamic_cast<Ogre::VulkanRenderTarget*>(target);
    
}

EngineType VulkanRenderSystem::getRenderType()
{
    return EngineType_Vulkan;
}

void VulkanRenderSystem::clearFrameBuffer(uint32 buffers,
    const ColourValue& colour,
    float depth, uint16 stencil)
{

    mActiveVulkanRenderTarget->preRender(mCurrentVulkanFrame, colour);
}

Ogre::RenderWindow* VulkanRenderSystem::createRenderWindow(
    const String& name, unsigned int width, unsigned int height,
    const NameValuePairList* miscParams)
{
    mRenderWindow = new VulkanWindow();

    mRenderWindow->create(name, width, height, false, miscParams);

    attachRenderTarget(*mRenderWindow);

    return mRenderWindow;
}

void VulkanRenderSystem::update(Renderable* r)
{
    VulkanRenderableData* rd = (VulkanRenderableData*)r->getRenderableData();

    rd->update(mCurrentVulkanFrame, nullptr);
}

void VulkanRenderSystem::render(Renderable* r, RenderListType t)
{
    VulkanRenderableData* rd = (VulkanRenderableData*)r->getRenderableData();
    VkCommandBuffer commandBuffer = VulkanHelper::getSingleton().getMainCommandBuffer(mCurrentVulkanFrame->getFrameIndex());
    rd->update(mCurrentVulkanFrame, nullptr);
    rd->render(mCurrentVulkanFrame, commandBuffer);
}

using fn_on_got_tracker_info = std::function<void(uint32_t)>;

struct ParallelTaskSet : public enki::IPinnedTask
{
    void update(int32_t start, int32_t end, VulkanFrame* frame, std::vector<Ogre::Renderable*>* objs)
    {
        _start = start;
        _end = end;
        _frame = frame;
        _objs = objs;
    }

    ParallelTaskSet(uint32_t tdx):IPinnedTask(tdx)
    {

    }
    virtual void Execute() 
    { 
        auto tdx = threadNum;
        std::vector<Ogre::Renderable*>& objs = *_objs;
        for (int32_t i = _start; i < _end; i++)
        {
            Ogre::Renderable* r = objs[i];
            VulkanRenderableData* rd = (VulkanRenderableData*)r->getRenderableData();

            VkCommandBuffer commandBuffer = VulkanHelper::getSingleton()._getThreadCommandBuffer(tdx, _frame->getFrameIndex());
            rd->render(_frame, commandBuffer);
        }
    }

    int32_t _start;
    int32_t _end;
    std::vector<Ogre::Renderable*>* _objs;
    VulkanFrame* _frame;
};

void VulkanRenderSystem::multiRender(std::vector<Ogre::Renderable*>& objs, bool multithread)
{
    multithread = false;

    mRenderList.clear();
    
    for (auto r : objs)
    {
        VulkanRenderableData* rd = (VulkanRenderableData*)r->getRenderableData();
        if (rd->update(mCurrentVulkanFrame, nullptr))
        {
            mRenderList.push_back(r);
        }
    }

    if (mRenderList.empty())
    {
        return;
    }

    if (VulkanHelper::getSingleton().haveRayTracing())
    {
        rayTracingRender(mRenderList);
        return;
    }
    
    
    uint32_t size = (uint32_t)mRenderList.size();

    if(mActiveVulkanRenderTarget->offset())
    {
        for (auto r : mRenderList)
        {
            VulkanRenderableData* rd = (VulkanRenderableData*)r->getRenderableData();
            // VkCommandBuffer commandBuffer = VulkanHelper::getSingleton()._getThreadCommandBuffer(3, mCurrentVulkanFrame->getFrameIndex());
            VkCommandBuffer commandBuffer = VulkanHelper::getSingleton().getMainCommandBuffer(mCurrentVulkanFrame->getFrameIndex());
            rd->render(mCurrentVulkanFrame, commandBuffer);
        }
        return;
    }
    if (!multithread)
    {
        for (auto r : mRenderList)
        {
            VulkanRenderableData* rd = (VulkanRenderableData*)r->getRenderableData();
            //VkCommandBuffer commandBuffer = VulkanHelper::getSingleton()._getThreadCommandBuffer(3, mCurrentVulkanFrame->getFrameIndex());
            VkCommandBuffer commandBuffer = VulkanHelper::getSingleton().getMainCommandBuffer(mCurrentVulkanFrame->getFrameIndex());
            rd->render(mCurrentVulkanFrame, commandBuffer);
        }
        return;
    }

    uint32_t every = size / VULKAN_COMMAND_THREAD;

    uint32_t left = size - every * VULKAN_COMMAND_THREAD;

    int32 start = 0;
    int32 end = 0;
    VulkanFrame* frame = mCurrentVulkanFrame;

    

    static std::vector<ParallelTaskSet*> tasklist;
    if (tasklist.empty())
    {
        tasklist.resize(VULKAN_COMMAND_THREAD);
        for (int32_t i = 0; i < VULKAN_COMMAND_THREAD; i++)
        {
            tasklist[i] = new ParallelTaskSet(i);
        }
    }

    
    for (int32_t i = 0; i < VULKAN_COMMAND_THREAD - 1; i++)
    {
        end = start + every;
        if (end > start)
        {
            ParallelTaskSet* task = tasklist[i];
            task->update(start, end, mCurrentVulkanFrame, &objs);
            mTaskScheduler.AddPinnedTask(task);
        }
        
        start = end;
    }

    ParallelTaskSet* task = tasklist[VULKAN_COMMAND_THREAD - 1];
    end = start + every + left;
    task->update(start, end, mCurrentVulkanFrame, &objs);
    mTaskScheduler.AddPinnedTask(task);

    mTaskScheduler.RunPinnedTasks();

    for (int32_t i = 0; i < VULKAN_COMMAND_THREAD; i++)
    {
        mTaskScheduler.WaitforTask(tasklist[i]);
    }
}

void VulkanRenderSystem::rayTracingRender(std::vector<Ogre::Renderable*>& objs)
{
    mRayTracingContext->render(objs, mCamera);
}

void VulkanRenderSystem::updateMainPassCB(ICamera* camera)
{
    const Ogre::Matrix4& view = camera->getViewMatrix();
    const Ogre::Matrix4& proj = camera->getProjectMatrix();
    const Ogre::Vector3& camepos = camera->getDerivedPosition();

    Ogre::Matrix4 invView = view.inverse();
    Ogre::Matrix4 viewProj = view * proj;
    Ogre::Matrix4 invProj = proj.inverse();
    Ogre::Matrix4 invViewProj = viewProj.inverse();

    mFrameConstantBuffer.Shadow = 0;

    
    mFrameConstantBuffer.View = view;
    mFrameConstantBuffer.InvView = invView;
    mFrameConstantBuffer.Proj = proj;
    mFrameConstantBuffer.InvProj = invProj;
    mFrameConstantBuffer.ViewProj = viewProj;
    mFrameConstantBuffer.InvViewProj = invViewProj;
    //mFrameConstantBuffer.ShadowTransform = mShadowTransform;
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
    if (camera->getCameraType() == CameraType_Light)
    {
        auto sceneMgr = camera->getCreator();
        mFrameConstantBuffer.AmbientLight = sceneMgr->getAmbientLight();

        const std::vector<Light*>& lights = sceneMgr->getLightList();

        uint32_t directionIndex = 0;
        for (auto l : lights)
        {
            if (l->getLightType() == LightType_Direction)
            {
                mFrameConstantBuffer.directionLights[directionIndex].Direction = l->getLightDirection();
                directionIndex++;
            }
        }
    }


    mCurrentVulkanFrame->updateFrameConstantBuffer(mFrameConstantBuffer, camera);
}


VulkanFrame* VulkanRenderSystem::_getCurrentFrame()
{
    return mCurrentVulkanFrame;
}

ICamera* VulkanRenderSystem::_getCamera()
{
    return mCamera;
}

void VulkanRenderSystem::generateIrradianceMap()
{

}

void VulkanRenderSystem::generatePrefilteredMap()
{

}

Ogre::OgreTexture* VulkanRenderSystem::generateCubeMap(
    const std::string& name, 
    Ogre::OgreTexture* environmentCube,
    Ogre::PixelFormat format, 
    int32_t dim,
    CubeType type)
{
    const uint32_t numMips = static_cast<uint32_t>(floor(log2(dim))) + 1;

    Ogre::TextureProperty texProperty;
    texProperty._tex_usage = TU_DYNAMIC_WRITE_ONLY;
    texProperty._texType = TEX_TYPE_CUBE_MAP;
    texProperty._width = dim;
    texProperty._height = dim;
    texProperty._tex_format = format;
    VulkanTexture* tex = new VulkanTexture(name, &texProperty, this);

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

    auto device = VulkanHelper::getSingleton()._getVkDevice();
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

        VkCommandBuffer layoutCmd = VulkanHelper::getSingleton().beginSingleTimeCommands();
        VkImageMemoryBarrier imageMemoryBarrier{};
        imageMemoryBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        imageMemoryBarrier.image = offscreen.image;
        imageMemoryBarrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        imageMemoryBarrier.newLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
        imageMemoryBarrier.srcAccessMask = 0;
        imageMemoryBarrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
        imageMemoryBarrier.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };
        vkCmdPipelineBarrier(layoutCmd, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, 0, 0, nullptr, 0, nullptr, 1, &imageMemoryBarrier);
        VulkanHelper::getSingleton().endSingleTimeCommands(layoutCmd);
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
    writeDescriptorSet.pImageInfo= &imageInfo;
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

    auto resInfo = ResourceManager::getSingleton().getResource("filtercube.vert.spv");
    shaderStages[0].module = vks::tools::loadShaderBinary(resInfo->_fullname.c_str(), device);
    shaderStages[1] = {};
    shaderStages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    shaderStages[1].pName = "main";
    switch (type) {
    case CubeType_Irradiance:
        resInfo = ResourceManager::getSingleton().getResource("irradiancecube.frag.spv");
        shaderStages[1].module = vks::tools::loadShaderBinary(resInfo->_fullname.c_str(), device);
        break;
    case CubeType_Prefiltered:
        resInfo = ResourceManager::getSingleton().getResource("prefilterenvmap.frag.spv");
        shaderStages[1].module = vks::tools::loadShaderBinary(resInfo->_fullname.c_str(), device);
        break;
    };
    VkPipeline pipeline;
    auto pipelineCache = VulkanHelper::getSingleton().getPipelineCache();
    //pipelineCache = VK_NULL_HANDLE;
    VK_CHECK_RESULT(vkCreateGraphicsPipelines(device, pipelineCache, 1, &pipelineCI, nullptr, &pipeline));
    for (auto shaderStage : shaderStages) {
        vkDestroyShaderModule(device, shaderStage.module, nullptr);
    }

    // Render cubemap
    VkClearValue clearValues[1];
    clearValues[0].color = { { 0.0f, 0.0f, 0.2f, 0.0f } };

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

    VkImageSubresourceRange subresourceRange{};
    subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    subresourceRange.baseMipLevel = 0;
    subresourceRange.levelCount = numMips;
    subresourceRange.layerCount = 6;
    auto cubeImage = tex->getVkImage();
    // Change image layout for all cubemap faces to transfer destination
    {
        VkCommandBuffer cmdBuf = VulkanHelper::getSingleton().beginSingleTimeCommands();
        VkImageMemoryBarrier imageMemoryBarrier{};
        imageMemoryBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        imageMemoryBarrier.image = cubeImage;
        imageMemoryBarrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        imageMemoryBarrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
        imageMemoryBarrier.srcAccessMask = 0;
        imageMemoryBarrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        imageMemoryBarrier.subresourceRange = subresourceRange;
        vkCmdPipelineBarrier(cmdBuf, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, 0, 0, nullptr, 0, nullptr, 1, &imageMemoryBarrier);
        
        VulkanHelper::getSingleton().endSingleTimeCommands(cmdBuf);
    }

    std::string meshName = "box.mesh";
    auto mesh = MeshManager::getSingleton().createBox(meshName, 100, "SkyLan");
    auto sceneManager = Ogre::Root::getSingletonPtr()->getSceneManager(MAIN_SCENE_MANAGER);
    auto entity = sceneManager->createEntity(name, meshName);
    auto r = entity->getSubEntity(0);
    IndexData* indexData = r->getIndexData();
    VertexData* vertexData = r->getVertexData();
    for (uint32_t m = 0; m < numMips; m++) {
        for (uint32_t f = 0; f < 6; f++) {

            VkCommandBuffer cmdBuf = VulkanHelper::getSingleton().beginSingleTimeCommands();

            viewport.width = static_cast<float>(dim * std::pow(0.5f, m));
            viewport.height = static_cast<float>(dim * std::pow(0.5f, m));
            vkCmdSetViewport(cmdBuf, 0, 1, &viewport);
            vkCmdSetScissor(cmdBuf, 0, 1, &scissor);

            // Render scene from cube face's point of view
            vkCmdBeginRenderPass(cmdBuf, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

            // Pass parameters for current pass using a push constant block
            auto perspective = Ogre::Math::makePerspectiveMatrixRH((float)(M_PI / 2.0), 1.0f, 0.1f, 512.0f);
            if (type == CubeType_Irradiance)
            {
                pushBlockIrradiance.mvp = perspective * matrices[f];
                vkCmdPushConstants(cmdBuf, pipelinelayout, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(pushBlockIrradiance), &pushBlockIrradiance);
            }
            else
            {
                pushBlockPrefilterEnv.mvp = perspective * matrices[f];
                pushBlockPrefilterEnv.roughness = (float)m / (float)(numMips - 1);
                vkCmdPushConstants(cmdBuf, pipelinelayout, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(pushBlockPrefilterEnv), &pushBlockPrefilterEnv);
            }

            bluevk::vkCmdBindPipeline(cmdBuf, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
            bluevk::vkCmdBindDescriptorSets(cmdBuf, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelinelayout, 0, 1, &descriptorset, 0, NULL);

            VkDeviceSize offsets[1] = { 0 };

            vertexData->bind(cmdBuf);
            
            if (indexData)
            {
                indexData->getIndexBuffer()->bind(cmdBuf);
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

            VulkanHelper::getSingleton().endSingleTimeCommands(cmdBuf);
        }
    }

    {
        VkCommandBuffer cmdBuf = VulkanHelper::getSingleton().beginSingleTimeCommands();
        VkImageMemoryBarrier imageMemoryBarrier{};
        imageMemoryBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        imageMemoryBarrier.image = cubeImage;
        imageMemoryBarrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
        imageMemoryBarrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        imageMemoryBarrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        imageMemoryBarrier.dstAccessMask = VK_ACCESS_HOST_WRITE_BIT | VK_ACCESS_TRANSFER_WRITE_BIT;
        imageMemoryBarrier.subresourceRange = subresourceRange;
        vkCmdPipelineBarrier(cmdBuf, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, 0, 0, nullptr, 0, nullptr, 1, &imageMemoryBarrier);
        VulkanHelper::getSingleton().endSingleTimeCommands(cmdBuf);
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

Ogre::OgreTexture* VulkanRenderSystem::generateBRDFLUT(const std::string& name)
{
    auto dim = 512;
    const uint32_t numMips = static_cast<uint32_t>(floor(log2(dim))) + 1;

    Ogre::TextureProperty texProperty;
    texProperty._tex_usage = TU_DYNAMIC_WRITE_ONLY;
    texProperty._texType = TEX_TYPE_2D;
    texProperty._width = dim;
    texProperty._height = dim;
    texProperty._tex_format = PF_FLOAT16_GR;
    VulkanTexture* tex = new VulkanTexture(name, &texProperty, this);

    tex->load(nullptr);

    auto device = VulkanHelper::getSingleton()._getVkDevice();
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
    auto resInfo = ResourceManager::getSingleton().getResource("genbrdflut.vert.spv");
    shaderStages[0].module = vks::tools::loadShaderBinary(resInfo->_fullname.c_str(), device);

    shaderStages[1] = {};
    shaderStages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    shaderStages[1].pName = "main";
    resInfo = ResourceManager::getSingleton().getResource("genbrdflut.frag.spv");
    shaderStages[1].module = vks::tools::loadShaderBinary(resInfo->_fullname.c_str(), device);

    VkPipeline pipeline;
    auto pipelineCache = VulkanHelper::getSingleton().getPipelineCache();
    pipelineCache = VK_NULL_HANDLE;
    VK_CHECK_RESULT(bluevk::vkCreateGraphicsPipelines(device, pipelineCache, 1, &pipelineCI, nullptr, &pipeline));
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

    VkCommandBuffer cmdBuf = VulkanHelper::getSingleton().beginSingleTimeCommands();
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
    
    VulkanHelper::getSingleton().endSingleTimeCommands(cmdBuf);

    bluevk::vkDestroyPipeline(device, pipeline, nullptr);
    bluevk::vkDestroyPipelineLayout(device, pipelinelayout, nullptr);
    bluevk::vkDestroyRenderPass(device, renderpass, nullptr);
    bluevk::vkDestroyFramebuffer(device, framebuffer, nullptr);
    bluevk::vkDestroyDescriptorSetLayout(device, descriptorsetlayout, nullptr);

    return tex;
}
