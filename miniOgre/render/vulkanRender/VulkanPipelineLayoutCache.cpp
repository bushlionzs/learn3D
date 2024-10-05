#include <OgreHeader.h>
#include "VulkanPipelineLayoutCache.h"


void VulkanPipelineLayoutCache::terminate() noexcept
{

}

VkPipelineLayout VulkanPipelineLayoutCache::getLayout(
    PipelineLayoutKey const& key)
{
    auto iter = mPipelineLayouts.find(key);
    if (iter != mPipelineLayouts.end()) {
        PipelineLayoutCacheEntry& entry = mPipelineLayouts[key];
        entry.lastUsed = mTimestamp++;
        return entry.handle;
    }
    uint8_t descSetLayoutCount = 0;
    for (auto layoutHandle : key) {
        if (layoutHandle == VK_NULL_HANDLE) {
            break;
        }
        descSetLayoutCount++;
    }

    VkPipelineLayoutCreateInfo info{
        .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        .pNext = nullptr,
        .setLayoutCount = descSetLayoutCount,
        .pSetLayouts = key.data(),
        .pushConstantRangeCount = 0,
    };

    
    VkPipelineLayout layout;
    vkCreatePipelineLayout(mDevice, &info, VKALLOC, &layout);

    mPipelineLayouts[key] = {
        .handle = layout,
        .lastUsed = mTimestamp++,
    };
    return layout;
}
