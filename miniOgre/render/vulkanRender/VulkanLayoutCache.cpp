#include <OgreHeader.h>
#include "VulkanLayoutCache.h"



VkDescriptorSetLayout VulkanLayoutCache::getLayout(VkDescriptorSetLayoutBinding* binding, uint32 count) {
    std::sort(binding, binding + count, [](
        const VkDescriptorSetLayoutBinding& a, const VkDescriptorSetLayoutBinding& b)->bool {
            return a.binding < b.binding;
        });

    VulkanDescriptorSetLayout::VulkanLayoutKey key;
    for (auto i = 0; i < count; i++)
    {
        key[i] = (binding[i].descriptorCount << 16) |
            (binding[i].binding << 8) |
            (uint8_t)binding[i].descriptorType & 0xf;
    }

    for (auto i = count; i < VulkanDescriptorSetLayout::MAX_BINDINGS; i++)
    {
        key[i] = 0;
    }
    if (auto iter = mLayouts.find(key); iter != mLayouts.end()) {
        return iter->second;
    }

    VkDescriptorSetLayoutCreateInfo descriptorLayout =
        vks::initializers::descriptorSetLayoutCreateInfo(
            binding,
            count);

    VkDescriptorSetLayout vklayout;

    
    vkCreateDescriptorSetLayout(mDevice, &descriptorLayout,
        nullptr, &vklayout);

    mLayouts[key] = vklayout;

    return vklayout;
}