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

    return true;
}


void VulkanRenderSystem::frameStart()
{
    mTriangleCount = 0;
    mBatchCount = 0;

    mCurrentVulkanFrame = mRenderWindow->getNextFrame();

    VkCommandBuffer pCommandBuffer =
        mCurrentVulkanFrame->getVkCommandBuffer();

    if (vkResetCommandBuffer(pCommandBuffer, 0) != VK_SUCCESS)
    {
        OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "failed to vkResetCommandBuffer!");
    }

    VkCommandBufferBeginInfo cmdBufInfo = vks::initializers::commandBufferBeginInfo();
    if (vkBeginCommandBuffer(pCommandBuffer, &cmdBufInfo) != VK_SUCCESS)
    {
        OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "failed to vkBeginCommandBuffer!");
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
    mActiveVulkanRenderTarget->preRender(
        mCurrentVulkanFrame->getVkCommandBuffer());
}

EngineType VulkanRenderSystem::getRenderType()
{
    return EngineType_Vulkan;
}

void VulkanRenderSystem::clearFrameBuffer(uint32 buffers,
    const ColourValue& colour,
    float depth, uint16 stencil)
{
    VkCommandBuffer pCommandBuffer =
        mCurrentVulkanFrame->getVkCommandBuffer();
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

void VulkanRenderSystem::render(Renderable* r, RenderListType t)
{
    VulkanRenderableData* rd = (VulkanRenderableData*)r->getRenderableData();
    rd->update(mCurrentVulkanFrame);
    rd->render(mCurrentVulkanFrame);
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