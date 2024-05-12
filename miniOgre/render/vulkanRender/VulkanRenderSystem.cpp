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


    mRenderList.reserve(10000);
}

VulkanRenderSystem::~VulkanRenderSystem()
{

}

bool VulkanRenderSystem::engineInit()
{
    RenderSystem::engineInit();
    new VulkanHardwareBufferManager(this);
    
    VulkanHelper::getSingleton()._initialise(nullptr);

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
    return new VulkanRenderableData(this, r);
}

void VulkanRenderSystem::_setViewport(ICamera* cam, Ogre::Viewport* vp)
{
    mViewport = vp;
    mCamera = cam;
    RenderTarget* target;
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