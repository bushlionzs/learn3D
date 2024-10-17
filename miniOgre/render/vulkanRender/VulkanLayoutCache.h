#pragma once
#include <VulkanCommon.h>
#include <VulkanHandles.h>
#include <VulkanResourceAllocator.h>
#include <utils/FixedCapacityVector.h>
#include <utils/Panic.h>
#include <utils/Hash.h>


class VulkanLayoutCache {
public:
    using key = VulkanDescriptorSetLayout::VulkanLayoutKey;
    using VulkanLayoutKeyHashFn = utils::hash::MurmurHashFn<key>;
    struct VulkanLayoutKeyEqual {
        bool operator()(key const& k1, key const& k2) const {
            const uint32_t* data1 = k1.data();
            const uint32_t* data2 = k2.data();
            return 0 == memcmp((const void*)data1, (const void*)data2, VulkanDescriptorSetLayout::MAX_BINDINGS * sizeof(uint16_t));
        }
    };

    using LayoutMap = std::unordered_map<key, VkDescriptorSetLayout, VulkanLayoutKeyHashFn,
        VulkanLayoutKeyEqual>;

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

    VkDescriptorSetLayout getLayout(VkDescriptorSetLayoutBinding* binding, uint32 count);

private:
    VkDevice mDevice;
    filament::backend::VulkanResourceAllocator* mAllocator;
    LayoutMap mLayouts;
};