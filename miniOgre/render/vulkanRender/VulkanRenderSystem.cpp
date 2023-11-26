#include "OgreHeader.h"
#include "VulkanRenderSystem.h"
#include "VulkanShader.h"
#include "VulkanTexture.h"
#include "OgreRenderable.h"
#include "vertex_data.h"
#include "index_data.h"
#include "vertex_declaration.h"
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

static const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

static const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME,
};

VulkanRenderSystem::VulkanRenderSystem(HWND wnd)
{
#ifdef _DEBUG
    mEnableValidationLayers = true;
#else
    mEnableValidationLayers = false;
#endif


    mRenderSystemName = "Vulkan";

    new VulkanHelper(this, wnd);
}

VulkanRenderSystem::~VulkanRenderSystem()
{

}

bool VulkanRenderSystem::engineInit()
{
    RenderSystem::engineInit();
    new VulkanHardwareBufferManager(this);
    
    VulkanHelper::getSingleton()._initialise();

    enki::TaskSchedulerConfig config;
    config.numTaskThreadsToCreate = VULKAN_COMMAND_THREAD;
    mTaskScheduler.Initialize(config);
    return true;
}


void VulkanRenderSystem::frameStart()
{
    mTriangleCount = 0;
    mBatchCount = 0;

    mCurrentVulkanFrame = mRenderWindow->getNextFrame();


    VulkanHelper::getSingleton()._resetCommandBuffer(mCurrentVulkanFrame->getFrameIndex());
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




ITexture* VulkanRenderSystem::createTextureFromFile(
    const std::string& name,
    TextureProperty* texProperty)
{
    auto tex =  new VulkanTexture(name, texProperty, this);

    tex->load();
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
    return new VulkanRenderableData(this, r);
}

void VulkanRenderSystem::_setViewport(ICamera* cam, Ogre::Viewport* vp)
{
    mViewport = vp;
    mCamera = cam;
    RenderTarget* target;
    target = vp->getTarget();
    updateMainPassCB(cam);
    mActiveVulkanRenderTarget = dynamic_cast<VulkanRenderTarget*>(target);
    mActiveVulkanRenderTarget->preRender(VulkanHelper::getSingleton().
        getMainCommandBuffer(mCurrentVulkanFrame->getFrameIndex()));
}

EngineType VulkanRenderSystem::getRenderType()
{
    return EngineType_Vulkan;
}

void VulkanRenderSystem::clearFrameBuffer(uint32 buffers,
    const ColourValue& colour,
    float depth, uint16 stencil)
{
    VkCommandBuffer pCommandBuffer = VulkanHelper::getSingleton().getMainCommandBuffer(
        mCurrentVulkanFrame->getFrameIndex());
    VkClearValue clearValues[2];
    memcpy(clearValues[0].color.float32, colour.ptr(), sizeof(ColourValue));
    clearValues[1].depthStencil = { 1.0f, 0 };

    auto renderPass = VulkanHelper::getSingleton()._getRenderPass();

    VkRenderPassBeginInfo renderPassBeginInfo = 
        vks::initializers::renderPassBeginInfo();
    renderPassBeginInfo.renderPass = renderPass;
    renderPassBeginInfo.renderArea.offset.x = 0;
    renderPassBeginInfo.renderArea.offset.y = 0;
    renderPassBeginInfo.renderArea.extent.width = 
        mActiveVulkanRenderTarget->getTargetWidth();
    renderPassBeginInfo.renderArea.extent.height = 
        mActiveVulkanRenderTarget->getTargetHeight();
    renderPassBeginInfo.clearValueCount = 2;
    renderPassBeginInfo.pClearValues = clearValues;

    auto framebuffer = mActiveVulkanRenderTarget->getFrameBuffer(
        mCurrentVulkanFrame->getFrameIndex());
    renderPassBeginInfo.framebuffer = framebuffer;
        

    vkCmdBeginRenderPass(pCommandBuffer, &renderPassBeginInfo,
        VK_SUBPASS_CONTENTS_INLINE);

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

struct ParallelTaskSet : enki::ITaskSet
{
    void update(int32_t start, int32_t end, VulkanFrame* frame, std::vector<Ogre::Renderable*>* objs)
    {
        _start = start;
        _end = end;
        _frame = frame;
        _objs = objs;
    }
    void ExecuteRange(enki::TaskSetPartition range_, uint32_t tdx) override
    {
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

void VulkanRenderSystem::multiRender(std::vector<Ogre::Renderable*>& objs)
{
    uint32_t size = (uint32_t)objs.size();

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
            tasklist[i] = new ParallelTaskSet;
        }
    }

    
    for (int32_t i = 0; i < VULKAN_COMMAND_THREAD - 1; i++)
    {
        end = start + every;
        ParallelTaskSet* task = tasklist[i];
        task->update(start, end, mCurrentVulkanFrame, &objs);
        mTaskScheduler.AddTaskSetToPipe(task);
        start = end;
    }

    mTaskScheduler.WaitforAll();
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
    mFrameConstantBuffer.EyePosW = { camepos.x, camepos.y, camepos.z };

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


    mCurrentVulkanFrame->updateFrameConstantBuffer(mFrameConstantBuffer, 0);
}


VulkanFrame* VulkanRenderSystem::_getCurrentFrame()
{
    return mCurrentVulkanFrame;
}

ICamera* VulkanRenderSystem::_getCamera()
{
    return mCamera;
}