#include <OgreHeader.h>
#include "VulkanPipelineLayoutCacheEx.h"



namespace Ogre
{
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

        VkPipelineLayoutCreateInfo info{
            .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
            .pNext = nullptr,
            .setLayoutCount = (uint32_t)key.size(),
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
}