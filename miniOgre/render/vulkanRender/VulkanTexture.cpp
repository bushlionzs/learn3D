#include "OgreHeader.h"
#include "VulkanTexture.h"
#include "OgreImage.h"
#include "VulkanRenderSystem.h"
#include "OgreResourceManager.h"
#include "myutils.h"
#include "VulkanHelper.h"
#include "VulkanHardwarePixelBuffer.h"
#include "VulkanMappings.h"
#include "VulkanTools.h"


VulkanTexture::VulkanTexture(
    const std::string& name,
    Ogre::TextureProperty* texProperty,
    VulkanRenderSystem* rs):
    ITexture(name, texProperty)
{
    mLoad = false;
    mRenderSystem = rs;

    mName = name;
    mVKDevice = VulkanHelper::getSingleton()._getVkDevice();
    mTextureImage = nullptr;
}

VulkanTexture::~VulkanTexture()
{
    
}

void VulkanTexture::_createSurfaceList(void)
{
    // Create new list of surfaces
    mSurfaceList.clear();
    size_t depth = mTextureProperty._depth;

    uint64_t bufferSizeAll = 0;
    for (size_t face = 0; face < mFace; ++face)
    {
        size_t width = mTextureProperty._width;
        size_t height = mTextureProperty._height;
        for (size_t mip = 0; mip <= mTextureProperty._numMipmaps; ++mip)
        {

            VulkanHardwarePixelBuffer* buffer;
            buffer = new VulkanHardwarePixelBuffer(
                this, // parentTexture
                mip,
                width,
                height,
                depth,
                face,
                bufferSizeAll,
                mFormat,
                (HardwareBuffer::Usage)mUsage
            );

            bufferSizeAll += buffer->getSizeInBytes();

            mSurfaceList.push_back(HardwarePixelBufferPtr(buffer));

            if (width > 1) width /= 2;
            if (height > 1) height /= 2;
        }
    }

    VulkanHelper::getSingleton()._createBuffer(
        bufferSizeAll,
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        mStagingBuffer,
        mStagingBufferMemory);

    VkResult result = vkMapMemory(VulkanHelper::getSingleton()._getVkDevice(),
        mStagingBufferMemory, 0, bufferSizeAll, 0, (void**)&mMappedMemory);

    if (result != VK_SUCCESS)
    {
        OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS, "vkMapMemory error");
    }
}

void VulkanTexture::createInternalResourcesImpl(void)
{
    mFormat = VulkanMappings::_getClosestSupportedPF(mFormat);
    
    mVulkanFormat = VulkanMappings::_getGammaFormat(VulkanMappings::_getPF(mFormat), false);
    
    if (mUsage & Ogre::TU_RENDERTARGET)
    {
        mVulkanFormat = VulkanHelper::getSingleton().getSwapChainImageFormat();
    }
    createImage(
        getWidth(),
        getHeight(),
        mVulkanFormat,
        VK_IMAGE_TILING_OPTIMAL,
        VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
        mTextureImage,
        mTextureImageMemory);

    mTextureImageView = createImageView(mTextureImage, mVulkanFormat);
    createTextureSampler();

    _createSurfaceList();
}

void VulkanTexture::freeInternalResourcesImpl(void)
{

}

void VulkanTexture::postLoad()
{
    if (!mSurfaceList.empty())
    {
        VulkanHelper::getSingleton().copyBufferToImage(
            mStagingBuffer,
            mTextureImage,
            this
        );
    }

    if (mNeedMipmaps)
    {
        //generate mipmap
        VulkanHelper::getSingleton().generateMipmaps(this);
    }
}

void VulkanTexture::createImage(
    uint32_t width,
    uint32_t height,
    VkFormat format,
    VkImageTiling tiling,
    VkImageUsageFlags usage,
    VkMemoryPropertyFlags properties,
    VkImage& image,
    VkDeviceMemory& imageMemory)
{
    mMipLevels = mTextureProperty._numMipmaps + 1;

    if (mTextureProperty._numMipmaps == 0)
    {
        auto current = static_cast<uint32_t>(floor(log2(std::max(width, height))) + 1.0);

        if (current > mMipLevels)
        {
            mNeedMipmaps = true;
            mMipLevels = current;
        }
    }

    VkImageCreateInfo imageInfo = {};
    imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imageInfo.imageType = VK_IMAGE_TYPE_2D;
    
    imageInfo.extent = { width, height, 1 };

    imageInfo.mipLevels = mMipLevels;
    imageInfo.arrayLayers = mFace;
    imageInfo.format = format;
    imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
    imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    imageInfo.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;

    
    imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
    imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (mUsage & Ogre::TU_RENDERTARGET)
    {
        imageInfo.usage |= VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    }
    if (isCubeTexture())
    {
        imageInfo.flags = VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT;
    }

    VkDevice device = VulkanHelper::getSingleton()._getVkDevice();

    if (vkCreateImage(device, &imageInfo, nullptr, &image) != VK_SUCCESS)
    {
        OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "failed to create image!");
    }

    VkMemoryRequirements memRequirements;
    vkGetImageMemoryRequirements(device, image, &memRequirements);

    VkMemoryAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = VulkanHelper::getSingleton()._findMemoryType(
        memRequirements.memoryTypeBits, 
        properties);

    if (vkAllocateMemory(device, &allocInfo, nullptr, &imageMemory) != VK_SUCCESS) {
        OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "failed to allocate image memory!");
    }

    VK_CHECK_RESULT(vkBindImageMemory(device, image, imageMemory, 0));

}

VkImageView VulkanTexture::createImageView(VkImage image, VkFormat format) 
{
    VkImageViewCreateInfo viewInfo = {};
    viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    viewInfo.image = image;
    if (isCubeTexture())
    {
        viewInfo.viewType = VK_IMAGE_VIEW_TYPE_CUBE;
    }
    else
    {
        viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    }
    
    viewInfo.format = format;
    viewInfo.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };


    viewInfo.subresourceRange.levelCount = mMipLevels;
    viewInfo.subresourceRange.layerCount = mFace;

    VkImageView imageView;
    if (vkCreateImageView(mVKDevice, &viewInfo, nullptr, &imageView) != VK_SUCCESS) {
        OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "failed to create texture image view!");
    }

    return imageView;
}

void VulkanTexture::createTextureSampler()
{
    mTextureSampler = VulkanHelper::getSingleton().getSampler(mTextureProperty._tex_addr_mod);
}


void* VulkanTexture::getVulkanBuffer(uint32_t offset)
{
    return mMappedMemory + offset;
}

void VulkanTexture::updateTextureData()
{
    VulkanHelper::getSingleton().copyBufferToImage(
        mStagingBuffer,
        mTextureImage,
        this
    );
}
