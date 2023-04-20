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
    new VulkanObjectPool;

    VulkanObjectPool::getSingleton().init(this);

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
        OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS, "failed to vkResetCommandBuffer!");
    }

    VkCommandBufferBeginInfo cmdBufInfo = vks::initializers::commandBufferBeginInfo();
    if (vkBeginCommandBuffer(pCommandBuffer, &cmdBufInfo) != VK_SUCCESS)
    {
        OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS, "failed to vkBeginCommandBuffer!");
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


void VulkanRenderSystem::render(Renderable* r, RenderListType t)
{
    const std::shared_ptr<Material>& mat = r->getMaterial();
    const std::shared_ptr<Shader>& shader = mat->getShader();
    mCurrentPass.mRenderListType = t;
    mCurrentPass.mMaterial = mat.get();
    mCurrentPass.mMaterial->load();
    mCurrentPass.mShader = (VulkanShader*)shader.get();
    mCurrentPass.mRenderable = r;
    mCurrentPass.mVulkanRenderableData = (VulkanRenderableData*)r->getRenderableData();
    mCurrentPass.mVulkanRenderableData->buildMaterial(mCurrentPass.mMaterial);

    auto descriptorSet = mCurrentPass.mVulkanRenderableData->getDescriptorSet();

    auto pipelineLayout = mCurrentPass.mVulkanRenderableData->getPipelineLayout();
    vkCmdBindDescriptorSets(
        mCurrentVulkanFrame->getVkCommandBuffer(),
        VK_PIPELINE_BIND_POINT_GRAPHICS,
        pipelineLayout, 0, 1, &descriptorSet, 0, NULL);

    renderImpl(&mCurrentPass);
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

void* VulkanRenderSystem::createRenderableData()
{
    return new VulkanRenderableData(this);
}

void VulkanRenderSystem::_setViewport(Viewport* vp)
{
    mViewport = vp;
    mCamera = vp->getCamera();
    RenderTarget* target;
    target = vp->getTarget();

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
    clearValues[0].color = { { 0.3f, 0.3f, 0.3f, 1.0f } };
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




void VulkanRenderSystem::renderImpl(VulkanPass* pass)
{
    //bind object and texture

    pass->mVulkanRenderableData->updateDescriptorSet(pass);

    VkCommandBuffer pCommandBuffer = mCurrentVulkanFrame->getVkCommandBuffer();

    //bind pipeline
    VkPipeline pipeline = pass->mShader->getVKPipeline(pass);
    
    vkCmdBindPipeline(pCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
    //draw object

    VertexData* vertexData = pass->mRenderable->getVertexData();
    IndexData* indexData = pass->mRenderable->getIndexData();
    vertexData->bind();
    if (indexData)
    {
        indexData->getIndexBuffer()->bind();
        IndexDataView* view = pass->mRenderable->getIndexView();
        vkCmdDrawIndexed(pCommandBuffer, view->mIndexCount, 1,
            view->mIndexLocation, view->mBaseVertexLocation, 0);
        mTriangleCount += view->mIndexCount / 3;
    }
    else
    {
        vkCmdDraw(pCommandBuffer, vertexData->vertexCount, 1, 0, 0);
        mTriangleCount += vertexData->vertexCount / 3;
    }

   
}

void VulkanRenderSystem::updateMainPassCB(Camera* camera)
{
    const Ogre::Matrix4& view = camera->getViewMatrix();
    const Ogre::Matrix4& proj = camera->getProjectMatrix();
    const Ogre::Vector3& camepos = camera->getDerivedPosition();

    Ogre::Matrix4 invView = view.inverse();
    Ogre::Matrix4 viewProj = proj * view;
    Ogre::Matrix4 invProj = proj.inverse();
    Ogre::Matrix4 invViewProj = viewProj.inverse();

    mFrameConstantBuffer.Shadow = 0;

    
    mFrameConstantBuffer.View = view.transpose();
    mFrameConstantBuffer.InvView = invView.transpose();
    mFrameConstantBuffer.Proj = proj.transpose();
    mFrameConstantBuffer.InvProj = invProj.transpose();
    mFrameConstantBuffer.ViewProj = viewProj.transpose();
    mFrameConstantBuffer.InvViewProj = invViewProj.transpose();
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
    mFrameConstantBuffer.TotalTime = 0;
    mFrameConstantBuffer.DeltaTime = 0;
    mFrameConstantBuffer.AmbientLight = { 0.25f, 0.25f, 0.35f, 1.0f };
    mFrameConstantBuffer.Lights[0].Direction = { 0.57735f, -0.57735f, 0.57735f };
    mFrameConstantBuffer.Lights[0].Strength = { 0.6f, 0.6f, 0.6f };
    mFrameConstantBuffer.Lights[1].Direction = { -0.57735f, -0.57735f, 0.57735f };
    mFrameConstantBuffer.Lights[1].Strength = { 0.3f, 0.3f, 0.3f };
    mFrameConstantBuffer.Lights[2].Direction = { 0.0f, -0.707f, -0.707f };
    mFrameConstantBuffer.Lights[2].Strength = { 0.15f, 0.15f, 0.15f };


    mCurrentVulkanFrame->updateFrameConstantBuffer(mFrameConstantBuffer, 0);
}


VulkanFrame* VulkanRenderSystem::_getCurrentFrame()
{
    return mCurrentVulkanFrame;
}

Ogre::Camera* VulkanRenderSystem::_getCamera()
{
    return mCamera;
}