#pragma once

#include "OgreTexture.h"
#include "engine_struct.h"
#include "VulkanCommon.h"

class VulkanRenderSystem;

class VulkanTexture :public ITexture
{
public:
    VulkanTexture(
        const std::string& name, 
        Ogre::TextureProperty* texProperty,
        VulkanRenderSystem* engine);
    ~VulkanTexture();

    VkImageView getImageView()
    {
        return mTextureImageView;
    }

    VkImage getImage()
    {
        return mTextureImage;
    }

    VkSampler getSampler()
    {
        return mTextureSampler;
    }


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

    VkImage mTextureImage;
    VkDeviceMemory mTextureImageMemory;

    VkImageView mTextureImageView;
    VkSampler mTextureSampler;

    VkFormat mVulkanFormat;

    bool mNeedMipmaps = false;
};