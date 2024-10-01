#pragma once
#include <VulkanCommon.h>
#include <VulkanHandles.h>
#include <VulkanResourceAllocator.h>
#include <utils/FixedCapacityVector.h>
#include <utils/Panic.h>
#include <utils/Hash.h>


class VulkanLayoutCache {
public:
    using Key = VulkanDescriptorSetLayout::Bitmask;
    using BitmaskHashFn = utils::hash::MurmurHashFn<VulkanDescriptorSetLayout::Bitmask>;
    struct BitmaskEqual {
        bool operator()(VulkanDescriptorSetLayout::Bitmask const& k1, 
            VulkanDescriptorSetLayout::Bitmask const& k2) const {
            return k1 == k2;
        }
    };
    // Make sure the key is 8-bytes aligned.
    static_assert(sizeof(Key) % 8 == 0);

    using LayoutMap = std::unordered_map<Key, VkDescriptorSetLayout, BitmaskHashFn,
        BitmaskEqual>;

public:
    explicit VulkanLayoutCache(VkDevice device, filament::backend::VulkanResourceAllocator* allocator)
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

    VkDescriptorSetLayout getLayout(descset::DescriptorSetLayout& layout);

private:
    VkDevice mDevice;
    filament::backend::VulkanResourceAllocator* mAllocator;
    LayoutMap mLayouts;
};