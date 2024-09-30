#pragma once


//#include "engine_struct.h"
#include "VulkanCommon.h"
#include "OgreTexture.h"
#include <utils/RangeMap.h>

namespace filament::backend {
    struct VulkanContext;
    class VulkanCommands;
    class VulkanStagePool;
}
class VulkanRenderSystemBase;


class VulkanTexture :public Ogre::OgreTexture
{
public:
    VulkanTexture(
        const std::string& name, 
        Ogre::TextureProperty* texProperty,
        VulkanRenderSystemBase* engine);

    void updateTextureName(const char* name, uint32_t size)
    {
        mName.assign(name, size);
    }

    ~VulkanTexture();

    VkImageView getVkImageView()
    {
        return mTextureImageView;
    }

    VkImage getVkImage()
    {
        return mTextureImage;
    }

    VkFormat getVkFormat()
    {
        return mVulkanFormat;
    }

    VkSampler getSampler()
    {
        return mTextureSampler;
    }

    uint32_t getMipLevels()
    {
        return mMipLevels;
    }

    void setSidecar(VulkanTexture* sidecar) {
        mSidecarMSAA.reset(sidecar);
    }

    VulkanTexture* getSidecar() const {
        return mSidecarMSAA.get();
    }

    void setPrimaryRange(uint32_t minMiplevel, uint32_t maxMiplevel);

    VkImageSubresourceRange getPrimaryViewRange() const;

    VkImageViewType getViewType() const;

    VkImageView getViewForType(VkImageSubresourceRange const& range, VkImageViewType type);

    VkImageView getAttachmentView(VkImageSubresourceRange range);


    void updateTextureData();
    void* getVulkanBuffer(uint32_t offset);


    int32_t getSlot()
    {
        return mSlot;
    }

    void setSlot(int32_t slot)
    {
        mSlot = slot;
    }
private:
    void _createSurfaceList(void);
    virtual void createInternalResourcesImpl(void);
    virtual void freeInternalResourcesImpl(void);
    virtual void postLoad();
private:
    void createImage(
        uint32_t width,
        uint32_t height,
        VkFormat format,
        VkImageTiling tiling,
        VkImageUsageFlags usage,
        VkMemoryPropertyFlags properties,
        VkImage& image,
        VkDeviceMemory& imageMemory);
    VkImageView createImageView(VkImage image, VkFormat format);
    void createTextureSampler();

    
private:
    VulkanRenderSystemBase* mRenderSystem;
    VkDevice mVKDevice;

    VkBuffer mStagingBuffer = VK_NULL_HANDLE;
    VkDeviceMemory mStagingBufferMemory = VK_NULL_HANDLE;
    char* mMappedMemory;

    VkImage mTextureImage = VK_NULL_HANDLE;
    VkDeviceMemory mTextureImageMemory;

    VkImageView mTextureImageView;
    VkSampler mTextureSampler;

    VkFormat mVulkanFormat = VK_FORMAT_UNDEFINED;
    filament::backend::TextureUsage mTextureUsage = filament::backend::TextureUsage::NONE;
    bool mNeedMipmaps = false;
    uint32_t mMipLevels = 1;

    // The texture with the sidecar owns the sidecar.
    std::unique_ptr<VulkanTexture> mSidecarMSAA;
    
    VmaAllocator mAllocator;
    VulkanCommands* mCommands;
    VulkanStagePool* mStagePool = nullptr;

    int32_t mSlot = -1;
};