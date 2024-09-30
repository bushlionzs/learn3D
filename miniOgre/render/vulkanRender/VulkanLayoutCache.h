#pragma once
#include <VulkanCommon.h>
#include <VulkanResourceAllocator.h>
#include <utils/FixedCapacityVector.h>
#include <utils/Panic.h>
#include <utils/Hash.h>
using UniformBufferBitmask = uint32_t;
using SamplerBitmask = uint64_t;
struct VulkanDescriptorSetLayout
{
    
    // The bitmask representation of a set layout.
    struct Bitmask {
        UniformBufferBitmask ubo = 0;         // 4 bytes
        UniformBufferBitmask dynamicUbo = 0;  // 4 bytes
        SamplerBitmask sampler = 0;           // 8 bytes
     

        bool operator==(Bitmask const& right) const {
            return ubo == right.ubo && dynamicUbo == right.dynamicUbo && sampler == right.sampler;
        }

        static Bitmask fromBackendLayout(const std::vector<DescriptorSetLayoutBindingInfo>& layout);
    };
};

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

    VkDescriptorSetLayout getLayout(const std::vector<DescriptorSetLayoutBindingInfo>& layout);

private:
    VkDevice mDevice;
    filament::backend::VulkanResourceAllocator* mAllocator;
    LayoutMap mLayouts;
};