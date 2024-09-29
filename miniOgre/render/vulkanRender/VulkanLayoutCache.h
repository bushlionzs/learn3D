#pragma once
#include <vulkan/VulkanHandles.h>
#include <vulkan/VulkanResourceAllocator.h>
#include <utils/FixedCapacityVector.h>
#include <utils/Panic.h>
#include <utils/Hash.h>

class VulkanLayoutCache {
public:
    using Key = filament::backend::VulkanDescriptorSetLayout::Bitmask;
    using BitmaskHashFn = utils::hash::MurmurHashFn<filament::backend::VulkanDescriptorSetLayout::Bitmask>;
    struct BitmaskEqual {
        bool operator()(filament::backend::VulkanDescriptorSetLayout::Bitmask const& k1, 
            filament::backend::VulkanDescriptorSetLayout::Bitmask const& k2) const {
            return k1 == k2;
        }
    };
    // Make sure the key is 8-bytes aligned.
    static_assert(sizeof(Key) % 8 == 0);

    using LayoutMap = std::unordered_map<Key, VkDescriptorSetLayout, BitmaskHashFn,
        BitmaskEqual>;

public:
    explicit VulkanLayoutCache(VkDevice device, VulkanResourceAllocator* allocator)
        : mDevice(device),
        mAllocator(allocator) {}

    ~VulkanLayoutCache() {
        for (auto [key, layout] : mLayouts) {
            //
        }
        mLayouts.clear();
    }

    void destroyLayout(VkDescriptorSetLayout handle) {
        for (auto [key, layout] : mLayouts) {
            if (layout == handle) {
                mLayouts.erase(key);
                break;
            }
        }
        
    }

    VkDescriptorSetLayout getLayout(const std::vector<DescriptorSetLayoutBindingInfo>& layout);

private:
    VkDevice mDevice;
    VulkanResourceAllocator* mAllocator;
    LayoutMap mLayouts;
};