#pragma once


//#include "engine_struct.h"
#include "VulkanCommon.h"
#include "OgreTexture.h"
#include <filament/DriverEnums.h>
#include <filament/DriverBase.h>
#include <VulkanResources.h>
#include <VulkanImageUtility.h>
#include <utils/RangeMap.h>

namespace filament::backend {
    struct VulkanContext;
    class VulkanCommands;
    class VulkanStagePool;
}
class VulkanRenderSystem;
using namespace filament::backend;

class VulkanTexture :public Ogre::OgreTexture, public filament::backend::HwTexture, public filament::backend::VulkanResource
{
public:
    VulkanTexture(
        const std::string& name, 
        Ogre::TextureProperty* texProperty,
        VulkanRenderSystem* engine);

    VulkanTexture(VkDevice device, VkPhysicalDevice physicalDevice, VulkanContext const& context,
        VmaAllocator allocator, VulkanCommands* commands, SamplerType target, uint8_t levels,
        filament::backend::TextureFormat tformat, uint8_t samples, uint32_t w, uint32_t h, uint32_t depth,
        filament::backend::TextureUsage tusage, VulkanStagePool& stagePool, bool heapAllocated = false,
        VkComponentMapping swizzle = {});

    // Specialized constructor for internally created textures (e.g. from a swap chain)
   // The texture will never destroy the given VkImage, but it does manages its subresources.
    VulkanTexture(VkDevice device, VmaAllocator allocator, VulkanCommands* commands, VkImage image,
        VkFormat format, uint8_t samples, uint32_t width, uint32_t height, filament::backend::TextureUsage tusage,
        VulkanStagePool& stagePool, bool heapAllocated = false);

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

    VkImageAspectFlags getImageAspect() const {
        // Helper function in VulkanUtility
        return filament::backend::getImageAspect(mVulkanFormat);
    }

    VulkanLayout getLayout(uint32_t layer, uint32_t level) const;

    void setPrimaryRange(uint32_t minMiplevel, uint32_t maxMiplevel);

    void updateImage(const PixelBufferDescriptor& data, uint32_t width, uint32_t height,
        uint32_t depth, uint32_t xoffset, uint32_t yoffset, uint32_t zoffset, uint32_t miplevel);

    VulkanLayout getPrimaryImageLayout() const;
    void transitionLayout(VkCommandBuffer commands, const VkImageSubresourceRange& range, VulkanLayout newLayout);

    VkImageSubresourceRange getPrimaryViewRange() const;

    VkImageViewType getViewType() const;

    VkImageView getViewForType(VkImageSubresourceRange const& range, VkImageViewType type);

    VkImageView getAttachmentView(VkImageSubresourceRange range);

    void setLayout(const VkImageSubresourceRange& range, VulkanLayout newLayout);

    void updateTextureData();
    void* getVulkanBuffer(uint32_t offset);
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
    VulkanRenderSystem* mRenderSystem;
    VkDevice mVKDevice;

    VkBuffer mStagingBuffer;
    VkDeviceMemory mStagingBufferMemory;
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
    
    // Track the image layout of each subresource using a sparse range map.
    utils::RangeMap<uint32_t, filament::backend::VulkanLayout> mSubresourceLayouts;

    VkImageSubresourceRange mFullViewRange;

    // Track the range of subresources that define the "primary" image view, which is the special
    // image view that gets bound to an actual texture sampler.
    VkImageSubresourceRange mPrimaryViewRange;

    VmaAllocator mAllocator;
    VulkanCommands* mCommands;
    VulkanStagePool* mStagePool = nullptr;
};