#pragma once
#include "VulkanCommon.h"
#include "renderSystem.h"
#include "SHADER.H"
#include <VulkanStagePool.h>
#include <VulkanHandles.h>
#include <VulkanResourceAllocator.h>
#include <VulkanResources.h>
#include <VulkanCommands.h>
#include <VulkanSwapChain.h>
#include <VulkanPlatform.h>
#include <VulkanContext.h>

class VulkanGraphicsCommandList;
class VulkanFrame;
class VulkanWindow;
class VulkanPipelineCache;
class Ogre::ICamera;

class VulkanRenderSystemBase: public RenderSystem
{
public:
	VulkanRenderSystemBase();
	~VulkanRenderSystemBase();
public:
    virtual OgreTexture* createTextureFromFile(
        const std::string& name,
        Ogre::TextureProperty* texProperty);
    virtual void ready();
    virtual RenderableData* createRenderableData(Ogre::Renderable* r);
    virtual Ogre::RenderWindow* createRenderWindow(
        const String& name, unsigned int width, unsigned int height,
        const NameValuePairList* miscParams) override;

    virtual Ogre::RenderTarget* createRenderTarget(
        const String& name, 
        uint32_t width, 
        uint32_t height, 
        Ogre::PixelFormat format, 
        uint32_t usage) override;
    //
    VulkanFrame* _getCurrentFrame();
    ICamera* _getCamera();
protected:
    void updateMainPassCB(ICamera* camera);
    VulkanFrame* getNextFrame();

    virtual Ogre::OgreTexture* generateCubeMap(
        const std::string& name,
        Ogre::OgreTexture* environmentCube,
        Ogre::PixelFormat format,
        int32_t dim,
        CubeType type);
    virtual Ogre::OgreTexture* generateBRDFLUT(const std::string& name);

    virtual FrameConstantBuffer* getFrameConstantBuffer()
    {
        return &mFrameConstantBuffer;
    }

    virtual Handle<HwBufferObject> createBufferObject(
        BufferObjectBinding bindingType,
        BufferUsage usage,
        uint32_t bufferCount) override;

    virtual void updateBufferObject(
        Handle<HwBufferObject> boh,
        const char* data, 
        uint32_t size) override;

protected:
    RenderPassInfo mCurrentRenderPassInfo;

    FrameConstantBuffer mFrameConstantBuffer;

    VulkanFrame* mCurrentVulkanFrame = nullptr;

    VulkanWindow* mRenderWindow;

    VkImage mCurrentVKImage;

    std::vector<Ogre::Renderable*> mRenderList;

    uint32_t mFrameIndex = 0;
    uint32_t mImageIndex = 0;

    VulkanPipelineCache* mPipelineCache = nullptr;

    VmaAllocator mAllocator = VK_NULL_HANDLE;
    VulkanResourceAllocator mResourceAllocator;

    VulkanStagePool mStagePool;
    VulkanCommands* mCommands;
    VulkanSwapChain* mSwapChain;
    VulkanPlatform* mVulkanPlatform;
    VulkanContext mVulkanContext;
};