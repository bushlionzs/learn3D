#include "OgreHeader.h"
#include "VulkanTexture.h"
#include "OgreImage.h"
#include "VulkanRenderSystem.h"
#include "OgreResourceManager.h"
#include "myutils.h"
#include "VulkanHelper.h"
#include "VulkanMappings.h"
#include "VulkanTools.h"



VulkanTexture::VulkanTexture(
    const std::string& name,
    VulkanPlatform* platform,
    VulkanCommands* commands,
    Ogre::TextureProperty* texProperty):
    OgreTexture(name, texProperty)
{
    mName = name;
    mCommands = commands;
    mPlatform = platform;
    mTextureImageView = VK_NULL_HANDLE;
    if (texProperty)
    {
        createInternalResourcesImpl();
    }
}

VulkanTexture::VulkanTexture(
    const std::string& name,
    VulkanPlatform* platform,
    VulkanCommands* commands,
    VkImage image,
    Ogre::TextureProperty* texProperty
):OgreTexture(name, texProperty)
{
    mName = name;
    mCommands = commands;
    mPlatform = platform;
    mTextureImage = image;
    mTextureImageView = VK_NULL_HANDLE;
    if (texProperty && texProperty->_width > 0)
    {
        createInternalResourcesImpl();
    }
}

VulkanTexture::~VulkanTexture()
{
    
}

bool VulkanTexture::need_midmap()
{
    if (!mTextureProperty._need_mipmap)
        return false;
    if (mTextureProperty._tex_usage.has_flag(TEXTURE_USAGE_COLOR_ATTACHMENT_BIT))
    {
        //return false;
    }
    if (mTextureProperty._tex_usage.has_flag(TEXTURE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT))
    {
        return false;
    }
    return true;
}

void VulkanTexture::_createSurfaceList(void)
{
    if (mTextureProperty._tex_usage.has_flag(TEXTURE_USAGE_COLOR_ATTACHMENT_BIT))
    {
        return;
    }
    if (mTextureProperty._tex_usage.has_flag(TEXTURE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT))
    {
        return;
    }

    if (mTextureProperty._texType == TEX_TYPE_3D)
    {
        return;
    }
    
    uint64_t bufferSizeAll = 0;
    mOffsetList.clear();
    for (size_t face = 0; face < mTextureProperty._face; ++face)
    {
        size_t width = mTextureProperty._width;
        size_t height = mTextureProperty._height;
        for (size_t mip = 0; mip <= mTextureProperty._numMipmaps; ++mip)
        {
            mOffsetList.push_back(bufferSizeAll);
            bufferSizeAll += PixelUtil::getMemorySize(width, height, 1, mFormat);
            if (width > 1) width /= 2;
            if (height > 1) height /= 2;
        }
    }
    if (bufferSizeAll == 32)
    {
        int kk = 0;
    }
    VulkanHelper::getSingleton()._createBuffer(
        bufferSizeAll,
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        mStagingBuffer,
        mStagingBufferMemory);

    VkResult result = vkMapMemory(mPlatform->getDevice(), mStagingBufferMemory, 0, bufferSizeAll, 0, (void**)&mMappedMemory);

    if (result != VK_SUCCESS)
    {
        OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS, "vkMapMemory error");
    }
}

void VulkanTexture::createInternalResourcesImpl(void)
{
    if (mTextureProperty._tex_format == Ogre::PF_DEPTH16)
    {
        int kk = 0;
    }
    if (VK_FORMAT_UNDEFINED == mVulkanFormat)
    {
        mFormat = VulkanMappings::_getClosestSupportedPF(mTextureProperty._tex_format);

        mVulkanFormat = VulkanMappings::_getGammaFormat(VulkanMappings::_getPF(mFormat), false);
    }
    

    if (mTextureImage == VK_NULL_HANDLE)
    {
        createImage(
            mTextureProperty._width,
            mTextureProperty._height,
            mVulkanFormat,
            VK_IMAGE_TILING_OPTIMAL,
            VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
            mTextureImage,
            mTextureImageMemory);
    }
    else
    {
        int kk = 0;
    }
    
    if (mTextureProperty._texType == TEX_TYPE_2D_ARRAY)
    {
        mTextureImageArrayView = createImageViewArray(mTextureImage, mVulkanFormat);
    }
    
     mTextureImageView = createImageView(mTextureImage, mVulkanFormat);
    
    

    createTextureSampler();

    _createSurfaceList();
}


void VulkanTexture::freeInternalResourcesImpl(void)
{
    auto device = mPlatform->getDevice();
    if (mTextureImageView)
    {
        vkDestroyImageView(device, mTextureImageView, nullptr);
        mTextureImageView = VK_NULL_HANDLE;
    }

    if (mTextureImage)
    {
        vkDestroyImage(device, mTextureImage, nullptr);
        mTextureImage = VK_NULL_HANDLE;
    }

    if (mTextureImageMemory)
    {
        vkFreeMemory(device, mTextureImageMemory, nullptr);
    }
}

void VulkanTexture::updateTexture(const std::vector<const CImage*>& images)
{
        uint32 faces = mTextureProperty._face;
        int32_t depth = 1;
        uint32_t offset = 0;

        for (uint32 i = 0; i < faces; ++i)
        {
            uint32_t width = mTextureProperty._width;
            uint32_t height = mTextureProperty._height;
            for (uint32 mip = 0; mip <= mTextureProperty._numMipmaps; ++mip)
            {
                PixelBox src;
                size_t face = (depth == 1) ? i : 0;


                Box dst(0, 0, 0, width, height, depth);
                // Load from faces of images[0]
                src = images[0]->getPixelBox(i, mip);
                Vector3i srcSize(src.getWidth(), src.getHeight(), src.getDepth());
                Vector3i dstSize(dst.getWidth(), dst.getHeight(), dst.getDepth());
                if (srcSize != dstSize)
                {
                    OGRE_EXCEPT(Exception::ERR_RENDERINGAPI_ERROR, "size invalid");
                }

                void* data = mMappedMemory + offset;

                PixelBox dstBox = PixelBox(src.getWidth(), src.getHeight(),
                    src.getDepth(), mFormat, data);
                PixelUtil::bulkPixelConversion(src, dstBox);

                offset += PixelUtil::getMemorySize(width, height, depth, mFormat);

                width = width > 1 ? width / 2 : 1;
                height = height > 1 ? height / 2 : 1;
            }
        }

        postLoad();
}

void VulkanTexture::postLoad()
{
    TransferCommandInfo* commandInfo = VulkanHelper::getSingleton().beginTransferCommand();

    if (mStagingBuffer)
    {
        vks::tools::copyBufferToImage(
            commandInfo->commandBuffer,
            mStagingBuffer,
            mTextureImage,
            this
        );
    }
    

    if (mNeedMipmaps)
    {
        vks::tools::generateMipmaps(commandInfo->commandBuffer, this);
    }

    VulkanHelper::getSingleton().endTransferCommand(commandInfo);
}


void VulkanTexture::uploadTextureData(const char* data, uint32_t size, TextureProperty& tp)
{
    

    PixelBox src(tp._width, tp._height, tp._depth, tp._tex_format, (void*)data);

    PixelBox dstBox = PixelBox(src.getWidth(), src.getHeight(),
        src.getDepth(), mFormat, mMappedMemory);
    PixelUtil::bulkPixelConversion(src, dstBox);

    mMipLevels = mTextureProperty._numMipmaps + 1;
    
    if (need_midmap())
    {
        if (mTextureProperty._numMipmaps == 0)
        {
            auto current = static_cast<uint32_t>(floor(log2(std::max(tp._width, tp._height))) + 1.0);

            if (current > mMipLevels)
            {
                mNeedMipmaps = true;
                mMipLevels = current;
            }
        }
    }
 
    postLoad();
}

void VulkanTexture::createImage(
    uint32_t width,
    uint32_t height,
    VkFormat format,
    VkImageTiling tiling,
    VkMemoryPropertyFlags properties,
    VkImage& image,
    VkDeviceMemory& imageMemory)
{
    mMipLevels = mTextureProperty._numMipmaps + 1;
    if (need_midmap())
    {
        if (mTextureProperty._numMipmaps == 0)
        {
            auto current = static_cast<uint32_t>(floor(log2(std::max(width, height))) + 1.0);

            if (current > mMipLevels)
            {
                mNeedMipmaps = true;
                mMipLevels = current;
            }
        }
    }
    
    VkImageCreateInfo imageInfo = {};
    imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;

    switch (mTextureProperty._texType)
    {
    case TEX_TYPE_2D:
    case TEX_TYPE_CUBE_MAP:
        imageInfo.imageType = VK_IMAGE_TYPE_2D;
        break;
    case TEX_TYPE_2D_ARRAY:
        imageInfo.imageType = VK_IMAGE_TYPE_2D;
        break;
    case TEX_TYPE_CUBE_MAP_ARRAY:
        imageInfo.imageType = VK_IMAGE_TYPE_2D;
        break;
    case TEX_TYPE_3D:
        imageInfo.imageType = VK_IMAGE_TYPE_3D;
        break;
    default:
        assert_invariant(false);
    }
    
    imageInfo.extent = { width, height, mTextureProperty._depth };

    imageInfo.mipLevels = mMipLevels;
    imageInfo.arrayLayers = mTextureProperty._face;
    imageInfo.format = format;
    imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
    imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    BitField<BackendResourceState> state = mTextureProperty._initState;
    //imageInfo.initialLayout = VulkanMappings::util_to_vk_image_layout(state);
    imageInfo.usage = VK_IMAGE_USAGE_SAMPLED_BIT;
    
    
    imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
    imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    BitField<TextureUsageBits> usage = mTextureProperty._tex_usage;


    if (usage.has_flag(TEXTURE_USAGE_COLOR_ATTACHMENT_BIT))
    {
        imageInfo.usage |=  VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT ;
    }

    if (usage.has_flag(TEXTURE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT))
    {
        imageInfo.usage |= VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
    }
    
    if (usage.has_flag(TEXTURE_USAGE_STORAGE_BIT))
    {
        imageInfo.usage |= VK_IMAGE_USAGE_STORAGE_BIT;
    }

    if (usage.has_flag(TEXTURE_USAGE_CAN_COPY_FROM_BIT))
    {
        imageInfo.usage |= VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
    }

    if (usage.has_flag(TEXTURE_USAGE_CAN_UPDATE_BIT))
    {
        imageInfo.usage |= VK_IMAGE_USAGE_TRANSFER_DST_BIT;
    }

    if (usage.has_flag(TEXTURE_USAGE_CAN_COPY_TO_BIT))
    {
        imageInfo.usage |= VK_IMAGE_USAGE_TRANSFER_DST_BIT;
    }

    if (usage.has_flag(TEXTURE_USAGE_INPUT_ATTACHMENT_BIT))
    {
        imageInfo.usage |= VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT;
    }


    if (isCubeTexture())
    {
        imageInfo.flags = VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT;
    }

    auto device = mPlatform->getDevice();
    VK_CHECK_RESULT(vkCreateImage(device, &imageInfo, nullptr, &image));
    vks::tools::set_object_name(device,
        OBJECT_TYPE_TEXTURE,
        (uint64_t)image, mName.c_str());

    VkMemoryRequirements memRequirements;
    bluevk::vkGetImageMemoryRequirements(device, image, &memRequirements);

    VkMemoryAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = VulkanHelper::getSingleton()._findMemoryType(memRequirements.memoryTypeBits, properties);

    VK_CHECK_RESULT(vkAllocateMemory(device, &allocInfo, nullptr, &imageMemory));

    VK_CHECK_RESULT(vkBindImageMemory(device, image, imageMemory, 0));

}

VkImageView VulkanTexture::createImageView(VkImage image, VkFormat format) 
{
    auto device = mPlatform->getDevice();
    VkImageViewCreateInfo viewInfo = {};
    viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    viewInfo.image = image;

    switch (mTextureProperty._texType)
    {
    case TEX_TYPE_2D:
        viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        break;
    case TEX_TYPE_2D_ARRAY:
        viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D_ARRAY;
        break;
    case TEX_TYPE_3D:
        viewInfo.viewType = VK_IMAGE_VIEW_TYPE_3D;
        break;
    case TEX_TYPE_CUBE_MAP:
        viewInfo.viewType = VK_IMAGE_VIEW_TYPE_CUBE;
        break;
    case TEX_TYPE_CUBE_MAP_ARRAY:
        viewInfo.viewType = VK_IMAGE_VIEW_TYPE_CUBE_ARRAY;
        break;
    default:
        assert_invariant(false);
        break;
    }
       
    
    viewInfo.format = format;

    

    mAspectFlags = VK_IMAGE_ASPECT_COLOR_BIT;
    if (mTextureProperty._tex_usage.has_flag(TEXTURE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT))
    {
        mAspectFlags = VK_IMAGE_ASPECT_DEPTH_BIT;
    }

    if (format == VK_FORMAT_R32_SFLOAT)
    {
        //mAspectFlags = VK_IMAGE_ASPECT_DEPTH_BIT;
    }

    viewInfo.subresourceRange = { mAspectFlags, 0, mMipLevels, 0, mTextureProperty._face };

    viewInfo.components.r = VK_COMPONENT_SWIZZLE_R;
    viewInfo.components.g = VK_COMPONENT_SWIZZLE_G;
    viewInfo.components.b = VK_COMPONENT_SWIZZLE_B;
    viewInfo.components.a = VK_COMPONENT_SWIZZLE_A;
    VkImageView imageView;
    if (vkCreateImageView(device, &viewInfo, nullptr, &imageView) != VK_SUCCESS)
    {
        OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "failed to create texture image view!");
    }

    return imageView;
}

std::vector<VkImageView> VulkanTexture::createImageViewArray(VkImage image, VkFormat format)
{
    auto device = mPlatform->getDevice();
    VkImageViewCreateInfo viewInfo = {};
    viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    viewInfo.image = image;
    viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D_ARRAY;
    viewInfo.format = format;

    mAspectFlags = VK_IMAGE_ASPECT_COLOR_BIT;
    if (mTextureProperty._tex_usage.has_flag(TEXTURE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT))
    {
        mAspectFlags = VK_IMAGE_ASPECT_DEPTH_BIT;
    }
    viewInfo.subresourceRange = { mAspectFlags, 0, mMipLevels, 0, 1 };

    viewInfo.components.r = VK_COMPONENT_SWIZZLE_R;
    viewInfo.components.g = VK_COMPONENT_SWIZZLE_G;
    viewInfo.components.b = VK_COMPONENT_SWIZZLE_B;
    viewInfo.components.a = VK_COMPONENT_SWIZZLE_A;
    
    std::vector<VkImageView> views;
    views.reserve(mTextureProperty._face);
    for (uint32_t i = 0; i < mTextureProperty._face; i++)
    {
        VkImageView imageView;
        viewInfo.subresourceRange.baseArrayLayer = i;
        if (vkCreateImageView(device, &viewInfo, nullptr, &imageView) != VK_SUCCESS)
        {
            OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "failed to create texture image view!");
        }
        views.push_back(imageView);
    }
    

    return views;
}
void VulkanTexture::createTextureSampler()
{
    mTextureSampler = VulkanHelper::getSingleton().getSampler(mTextureProperty._samplerParams);
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

bool VulkanTexture::transitionReady()
{
    return true;
}

void VulkanTexture::transitionLayout(
    VkCommandBuffer cmdbuf,
    const VkImageSubresourceRange& range,
    VulkanLayout newLayout)
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

void VulkanTexture::blitFromMemory(
    const PixelBox& src, const Box& dst, uint32_t face, uint32_t mipmap)
{
    Vector3i srcSize(src.getWidth(), src.getHeight(), src.getDepth());
    Vector3i dstSize(dst.getWidth(), dst.getHeight(), dst.getDepth());
    if (srcSize != dstSize)
    {
        OGRE_EXCEPT(Exception::ERR_RENDERINGAPI_ERROR,
            "D3D12 device cannot copy a subresource - source and dest size are not the same and they have to be the same in DX12.",
            "D3D12HardwarePixelBuffer::blitFromMemory");
    }


    PixelBox dstBox = PixelBox(src.getWidth(), src.getHeight(),
        src.getDepth(), mFormat, mMappedMemory);
    PixelUtil::bulkPixelConversion(src, dstBox);
}

void VulkanTexture::uploadData()
{
    TransferCommandInfo* commandInfo = VulkanHelper::getSingleton().beginTransferCommand();
    vks::tools::copyBufferToImage(
        commandInfo->commandBuffer,
        mStagingBuffer,
        mTextureImage,
        this
    );
    VulkanHelper::getSingleton().endTransferCommand(commandInfo);
}
