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
#include "VulkanConstants.h"
#include "VulkanUtility.h"
#include "VulkanStagePool.h"
#include <filament/BackendUtils.h>


VulkanTexture::VulkanTexture(
    const std::string& name,
    Ogre::TextureProperty* texProperty,
    VulkanRenderSystem* rs):
    OgreTexture(name, texProperty),
    HwTexture(SamplerType::SAMPLER_2D, 1, 0, 0, 0, 1, TextureFormat::UNUSED, filament::backend::TextureUsage::NONE),
    VulkanResource(VulkanResourceType::TEXTURE)
{
    mLoad = false;
    mRenderSystem = rs;

    mName = name;
    mVKDevice = VulkanHelper::getSingleton()._getVkDevice();
}

VulkanTexture::VulkanTexture(VkDevice device, VkPhysicalDevice physicalDevice, VulkanContext const& context,
    VmaAllocator allocator, VulkanCommands* commands, SamplerType target, uint8_t levels,
    filament::backend::TextureFormat tformat, uint8_t samples, uint32_t w, uint32_t h, uint32_t depth,
    filament::backend::TextureUsage tusage, VulkanStagePool& stagePool, bool heapAllocated,
    VkComponentMapping swizzle)
    :
    OgreTexture("", nullptr),
    HwTexture(target, 1, samples, width, height, 1, TextureFormat::UNUSED, tusage),
    VulkanResource(heapAllocated ? VulkanResourceType::HEAP_ALLOCATED : VulkanResourceType::TEXTURE),
    mAllocator(allocator),
    mCommands(commands),
    mStagePool(&stagePool)
{
    mTextureProperty._width = w;
    mTextureProperty._height = h;
    mTextureProperty._depth = depth;
    mTextureProperty._numMipmaps = 0;
    if (target == SamplerType::SAMPLER_CUBEMAP)
    {
        mTextureProperty._texType = TEX_TYPE_CUBE_MAP;
        mFace = 6;
    }
    mVulkanFormat = filament::backend::getVkFormat(tformat);
    mTextureUsage = tusage;
    mVKDevice = device;
    createInternalResourcesImpl();
}

VulkanTexture::VulkanTexture(VkDevice device, VmaAllocator allocator, VulkanCommands* commands, VkImage image,
    VkFormat format, uint8_t samples, uint32_t width, uint32_t height, filament::backend::TextureUsage tusage,
    VulkanStagePool& stagePool, bool heapAllocated)
    :
    OgreTexture("", nullptr),
    HwTexture(SamplerType::SAMPLER_2D, 1, samples, width, height, 1, TextureFormat::UNUSED, tusage),
    VulkanResource(heapAllocated ? VulkanResourceType::HEAP_ALLOCATED : VulkanResourceType::TEXTURE),
    mAllocator(allocator),
    mCommands(commands),
    mStagePool(&stagePool)

{
    mTextureProperty._width = width;
    mTextureProperty._height = height;
    mTextureProperty._depth = depth;
    mTextureProperty._numMipmaps = 0;
    mVulkanFormat = format;
    mTextureUsage = tusage;
    mVKDevice = device;
    mTextureImage = image;
    createInternalResourcesImpl();
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

    VkResult result = vkMapMemory(mVKDevice, mStagingBufferMemory, 0, bufferSizeAll, 0, (void**)&mMappedMemory);

    if (result != VK_SUCCESS)
    {
        OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS, "vkMapMemory error");
    }
}

void VulkanTexture::createInternalResourcesImpl(void)
{
    if (VK_FORMAT_UNDEFINED == mVulkanFormat)
    {
        mFormat = VulkanMappings::_getClosestSupportedPF(mFormat);

        mVulkanFormat = VulkanMappings::_getGammaFormat(VulkanMappings::_getPF(mFormat), false);

        if (mUsage & Ogre::TU_RENDERTARGET)
        {
            mVulkanFormat = VK_FORMAT_B8G8R8A8_UNORM;
        }
    }
    

    if (mTextureImage == VK_NULL_HANDLE)
    {
        createImage(
            mTextureProperty._width,
            mTextureProperty._height,
            mVulkanFormat,
            VK_IMAGE_TILING_OPTIMAL,
            VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
            VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
            mTextureImage,
            mTextureImageMemory);
    }
    

    mTextureImageView = createImageView(mTextureImage, mVulkanFormat);
    createTextureSampler();

    _createSurfaceList();
}


void VulkanTexture::freeInternalResourcesImpl(void)
{

}

void VulkanTexture::postLoad()
{
    VkCommandBuffer commandBuffer = VulkanHelper::getSingleton().beginSingleTimeCommands(true);
    if (!mSurfaceList.empty())
    {
        vks::tools::copyBufferToImage(
            commandBuffer,
            mStagingBuffer,
            mTextureImage,
            this
        );
    }

    if (mNeedMipmaps)
    {
        //generate mipmap
        vks::tools::generateMipmaps(commandBuffer, this);
    }

    VulkanHelper::getSingleton().endSingleTimeCommands(commandBuffer, true);
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


    if (mTextureUsage == filament::backend::TextureUsage::COLOR_ATTACHMENT)
    {
        imageInfo.usage = VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    }

    if (mTextureUsage == filament::backend::TextureUsage::DEPTH_ATTACHMENT)
    {
        imageInfo.usage |= VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
    }

    if (mUsage & Ogre::TU_RENDERTARGET)
    {
        imageInfo.usage |= VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    }
    if (isCubeTexture())
    {
        imageInfo.flags = VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT;
    }


    VK_CHECK_RESULT(vkCreateImage(mVKDevice, &imageInfo, nullptr, &image));

    VkMemoryRequirements memRequirements;
    vkGetImageMemoryRequirements(mVKDevice, image, &memRequirements);

    VkMemoryAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = VulkanHelper::getSingleton()._findMemoryType(memRequirements.memoryTypeBits, properties);

    VK_CHECK_RESULT(vkAllocateMemory(mVKDevice, &allocInfo, nullptr, &imageMemory));

    VK_CHECK_RESULT(vkBindImageMemory(mVKDevice, image, imageMemory, 0));

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
    viewInfo.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, mMipLevels, 0, mFace };

    viewInfo.components.r = VK_COMPONENT_SWIZZLE_R;
    viewInfo.components.g = VK_COMPONENT_SWIZZLE_G;
    viewInfo.components.b = VK_COMPONENT_SWIZZLE_B;
    viewInfo.components.a = VK_COMPONENT_SWIZZLE_A;
    VkImageView imageView;
    if (vkCreateImageView(mVKDevice, &viewInfo, nullptr, &imageView) != VK_SUCCESS)
    {
        OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "failed to create texture image view!");
    }

    return imageView;
}

void VulkanTexture::createTextureSampler()
{
    mTextureSampler = VulkanHelper::getSingleton().getSampler(mTextureProperty._tex_addr_mod);
}

VulkanLayout VulkanTexture::getLayout(uint32_t layer, uint32_t level) const
{
    assert_invariant(level <= 0xffff && layer <= 0xffff);
    const uint32_t key = (layer << 16) | level;
    if (!mSubresourceLayouts.has(key)) {
        return VulkanLayout::UNDEFINED;
    }
    return mSubresourceLayouts.get(key);
}

void VulkanTexture::setPrimaryRange(uint32_t minMiplevel, uint32_t maxMiplevel)
{

}

void VulkanTexture::updateImage(const PixelBufferDescriptor& data, uint32_t width, uint32_t height,
    uint32_t depth, uint32_t xoffset, uint32_t yoffset, uint32_t zoffset, uint32_t miplevel)
{
    assert_invariant(width <= this->width && height <= this->height);
    assert_invariant(depth <= this->depth * ((target == SamplerType::SAMPLER_CUBEMAP ||
        target == SamplerType::SAMPLER_CUBEMAP_ARRAY) ? 6 : 1));

    const PixelBufferDescriptor* hostData = &data;
    PixelBufferDescriptor reshapedData;

    // First, reshape 3-component data into 4-component data. The fourth component is usually
    // set to 1 (one exception is when type = HALF). In practice, alpha is just a dummy channel.
    // Note that the reshaped data is freed at the end of this method due to the callback.
    if (reshape(data, reshapedData)) {
        hostData = &reshapedData;
    }

    // If format conversion is both required and supported, use vkCmdBlitImage.
    const VkFormat hostFormat = backend::getVkFormat(hostData->format, hostData->type);
    const VkFormat deviceFormat = getVkFormatLinear(mVulkanFormat);
    if (hostFormat != deviceFormat && hostFormat != VK_FORMAT_UNDEFINED) {

        return;
    }

    assert_invariant(hostData->size > 0 && "Data is empty");

    // Otherwise, use vkCmdCopyBufferToImage.
    void* mapped = nullptr;
    VulkanStage const* stage = mStagePool->acquireStage(hostData->size);
    assert_invariant(stage->memory);
    vmaMapMemory(mAllocator, stage->memory, &mapped);
    memcpy(mapped, hostData->buffer, hostData->size);
    vmaUnmapMemory(mAllocator, stage->memory);
    vmaFlushAllocation(mAllocator, stage->memory, 0, hostData->size);

    VulkanCommandBuffer& commands = mCommands->get();
    VkCommandBuffer const cmdbuf = commands.buffer();
    commands.acquire(this);

    //VkBufferImageCopy copyRegion = {
    //    .bufferOffset = {},
    //    .bufferRowLength = {},
    //    .bufferImageHeight = {},
    //    .imageSubresource = {
    //        .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
    //        .mipLevel = miplevel,
    //        .baseArrayLayer = 0,
    //        .layerCount = 1
    //    },
    //    .imageOffset = { int32_t(xoffset), int32_t(yoffset), int32_t(zoffset) },
    //    .imageExtent = { width, height, depth }
    //};

    //VkImageSubresourceRange transitionRange = {
    //    .aspectMask = getImageAspect(),
    //    .baseMipLevel = miplevel,
    //    .levelCount = 1,
    //    .baseArrayLayer = 0,
    //    .layerCount = 1
    //};

    //// Vulkan specifies subregions for 3D textures differently than from 2D arrays.
    //if (target == SamplerType::SAMPLER_2D_ARRAY ||
    //    target == SamplerType::SAMPLER_CUBEMAP ||
    //    target == SamplerType::SAMPLER_CUBEMAP_ARRAY) {
    //    copyRegion.imageOffset.z = 0;
    //    copyRegion.imageExtent.depth = 1;
    //    copyRegion.imageSubresource.baseArrayLayer = zoffset;
    //    copyRegion.imageSubresource.layerCount = depth;
    //    transitionRange.baseArrayLayer = zoffset;
    //    transitionRange.layerCount = depth;
    //}

    //VulkanLayout const newLayout = VulkanLayout::TRANSFER_DST;
    //VulkanLayout nextLayout = getLayout(transitionRange.baseArrayLayer, miplevel);
    //VkImageLayout const newVkLayout = imgutil::getVkLayout(newLayout);

    //if (nextLayout == VulkanLayout::UNDEFINED) {
    //    nextLayout = imgutil::getDefaultLayout(this->usage);
    //}

    //transitionLayout(cmdbuf, transitionRange, newLayout);

    //vkCmdCopyBufferToImage(cmdbuf, stage->buffer, mTextureImage, newVkLayout, 1, &copyRegion);

    //transitionLayout(cmdbuf, transitionRange, nextLayout);

    vks::tools::copyBufferToImage(
        cmdbuf,
        stage->buffer,
        mTextureImage,
        this
    );

    if (mNeedMipmaps)
    {
        vks::tools::generateMipmaps(cmdbuf, this);
    }
}

VulkanLayout VulkanTexture::getPrimaryImageLayout() const
{
    return VulkanLayout::READ_ONLY;
}
void VulkanTexture::transitionLayout(VkCommandBuffer cmdbuf, const VkImageSubresourceRange& range, VulkanLayout newLayout)
{
    VulkanLayout const oldLayout = getLayout(range.baseArrayLayer, range.baseMipLevel);

    uint32_t const firstLayer = range.baseArrayLayer;
    uint32_t const lastLayer = firstLayer + range.layerCount;
    uint32_t const firstLevel = range.baseMipLevel;
    uint32_t const lastLevel = firstLevel + range.levelCount;

    // If we are transitioning more than one layer/level (slice), we need to know whether they are
    // all of the same layer.  If not, we need to transition slice-by-slice. Otherwise it would
    // trigger the validation layer saying that the `oldLayout` provided is incorrect.
    // TODO: transition by multiple slices with more sophiscated range finding.
    bool transitionSliceBySlice = false;
    for (uint32_t i = firstLayer; i < lastLayer; ++i) {
        for (uint32_t j = firstLevel; j < lastLevel; ++j) {
            if (oldLayout != getLayout(i, j)) {
                transitionSliceBySlice = true;
                break;
            }
        }
    }

#if FVK_ENABLED(FVK_DEBUG_LAYOUT_TRANSITION)
    utils::slog.d << "transition texture=" << mTextureImage
        << " (" << range.baseArrayLayer
        << "," << range.baseMipLevel << ")"
        << " count=(" << range.layerCount
        << "," << range.levelCount << ")"
        << " from=" << oldLayout << " to=" << newLayout
        << " format=" << mVkFormat
        << " depth=" << isVkDepthFormat(mVkFormat)
        << " slice-by-slice=" << transitionSliceBySlice
        << utils::io::endl;
#endif

    if (transitionSliceBySlice) {
        for (uint32_t i = firstLayer; i < lastLayer; ++i) {
            for (uint32_t j = firstLevel; j < lastLevel; ++j) {
                VulkanLayout const layout = getLayout(i, j);
                imgutil::transitionLayout(cmdbuf, {
                        .image = mTextureImage,
                        .oldLayout = layout,
                        .newLayout = newLayout,
                        .subresources = {
                            .aspectMask = range.aspectMask,
                            .baseMipLevel = j,
                            .levelCount = 1,
                            .baseArrayLayer = i,
                            .layerCount = 1,
                        },
                    });
            }
        }
    }
    else {
        imgutil::transitionLayout(cmdbuf, {
            .image = mTextureImage,
            .oldLayout = oldLayout,
            .newLayout = newLayout,
            .subresources = range,
            });
    }

    setLayout(range, newLayout);
}

VkImageSubresourceRange VulkanTexture::getPrimaryViewRange() const
{
    return mPrimaryViewRange;
}

VkImageViewType VulkanTexture::getViewType() const
{
    return VK_IMAGE_VIEW_TYPE_2D;
}

VkImageView VulkanTexture::getViewForType(VkImageSubresourceRange const& range, VkImageViewType type)
{
    return mTextureImageView;
}

VkImageView VulkanTexture::getAttachmentView(VkImageSubresourceRange range)
{
    return mTextureImageView;
}

void VulkanTexture::setLayout(const VkImageSubresourceRange& range, VulkanLayout newLayout)
{
    uint32_t const firstLayer = range.baseArrayLayer;
    uint32_t const lastLayer = firstLayer + range.layerCount;
    uint32_t const firstLevel = range.baseMipLevel;
    uint32_t const lastLevel = firstLevel + range.levelCount;

    assert_invariant(firstLevel <= 0xffff && lastLevel <= 0xffff);
    assert_invariant(firstLayer <= 0xffff && lastLayer <= 0xffff);

    if (newLayout == VulkanLayout::UNDEFINED) {
        for (uint32_t layer = firstLayer; layer < lastLayer; ++layer) {
            uint32_t const first = (layer << 16) | firstLevel;
            uint32_t const last = (layer << 16) | lastLevel;
            mSubresourceLayouts.clear(first, last);
        }
    }
    else {
        for (uint32_t layer = firstLayer; layer < lastLayer; ++layer) {
            uint32_t const first = (layer << 16) | firstLevel;
            uint32_t const last = (layer << 16) | lastLevel;
            mSubresourceLayouts.add(first, last, newLayout);
        }
    }
}

void* VulkanTexture::getVulkanBuffer(uint32_t offset)
{
    return mMappedMemory + offset;
}

void VulkanTexture::updateTextureData()
{
    VkCommandBuffer commandBuffer = VulkanHelper::getSingleton().beginSingleTimeCommands(true);
    vks::tools::copyBufferToImage(
        commandBuffer,
        mStagingBuffer,
        mTextureImage,
        this
    );
    VulkanHelper::getSingleton().endSingleTimeCommands(commandBuffer, true);
}
