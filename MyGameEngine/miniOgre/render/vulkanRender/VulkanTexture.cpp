#include "OgreHeader.h"
#include "VulkanTexture.h"
#include "OgreImage.h"
#include "VulkanRenderSystem.h"
#include "OgreResourceManager.h"
#include "myutils.h"
#include "VulkanHelper.h"
#include "VulkanHardwarePixelBuffer.h"
#include "VulkanMappings.h"


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

    _createSurfaceList();
}

void VulkanTexture::freeInternalResourcesImpl(void)
{

}

void VulkanTexture::postLoad()
{
    VulkanHelper::getSingleton().copyBufferToImage(
        mStagingBuffer,
        mTextureImage,
        this
    );


    mTextureImageView = createImageView(mTextureImage, mVulkanFormat);
    createTextureSampler();
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
    uint32_t numMips = mTextureProperty._numMipmaps + 1;
    VkImageCreateInfo imageInfo = {};
    imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imageInfo.imageType = VK_IMAGE_TYPE_2D;
    
    imageInfo.extent.width = width;
    imageInfo.extent.height = height;
    imageInfo.extent.depth = 1;
    imageInfo.mipLevels = numMips;
    imageInfo.arrayLayers = mFace;
    imageInfo.format = format;
    imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
    imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    imageInfo.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT |
        VK_IMAGE_USAGE_SAMPLED_BIT;

    if (mUsage & Ogre::TU_RENDERTARGET)
    {
        imageInfo.usage |= VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    }
    imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
    imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

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

    VkResult result = vkBindImageMemory(device, image, imageMemory, 0);

    if (result != VK_SUCCESS)
    {
        OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS, "");
    }
}

VkImageView VulkanTexture::createImageView(VkImage image, VkFormat format) 
{
    VkImageViewCreateInfo viewInfo = {};
    viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    viewInfo.image = image;
    int face = 1;
    if (isCubeTexture())
    {
        viewInfo.viewType = VK_IMAGE_VIEW_TYPE_CUBE;
        face = 6;
    }
    else
    {
        viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    }
    
    viewInfo.format = format;
    viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    viewInfo.subresourceRange.baseMipLevel = 0;
    viewInfo.subresourceRange.levelCount = 1;
    viewInfo.subresourceRange.baseArrayLayer = 0;
    viewInfo.subresourceRange.layerCount = face;

    VkImageView imageView;
    if (vkCreateImageView(mVKDevice, &viewInfo, nullptr, &imageView) != VK_SUCCESS) {
        OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "failed to create texture image view!");
    }

    return imageView;
}

void VulkanTexture::createTextureSampler()
{
    VkSamplerCreateInfo samplerInfo = {};
    samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    samplerInfo.magFilter = VK_FILTER_LINEAR;
    samplerInfo.minFilter = VK_FILTER_LINEAR;
    samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    samplerInfo.anisotropyEnable = VK_FALSE;
    samplerInfo.maxAnisotropy = 1.0f;
    samplerInfo.borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE;
    samplerInfo.unnormalizedCoordinates = VK_FALSE;
    samplerInfo.compareEnable = VK_FALSE;
    samplerInfo.compareOp = VK_COMPARE_OP_NEVER;
    samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;


    if (vkCreateSampler(mVKDevice, &samplerInfo, nullptr, &mTextureSampler) != VK_SUCCESS)
    {
        OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "failed to create texture sampler!");
    }
}


void* VulkanTexture::getVulkanBuffer(size_t face, size_t mipmap)
{
    uint32_t offset = face * PixelUtil::getMemorySize(
        getWidth(), getHeight(), getDepth(), mFormat);
    return mMappedMemory + offset;
}

void VulkanTexture::updateTextureData()
{
    if (mSurfaceList.empty())
    {
        return;
    }

    int faceNum = 1;
    if (isCubeTexture())
    {
        faceNum = 6;
    }

    /*VulkanHelper::getSingleton().copyBufferToImage(
        mStagingBuffer,
        mTextureImage,
        static_cast<uint32_t>(mImages[0].getWidth()),
        static_cast<uint32_t>(mImages[0].getHeight()),
        faceNum
    );*/
    

    
}
