#pragma once

#include <VulkanCommon.h>
#include <vulkan/VulkanResourceAllocator.h>
#include <utils/Hash.h>
namespace Ogre
{
    class VulkanPipelineLayoutCache {
    public:
        VulkanPipelineLayoutCache(VkDevice device, VulkanResourceAllocator* allocator)
            : mDevice(device),
            mAllocator(allocator),
            mTimestamp(0) {}

        void terminate() noexcept;

        using PipelineLayoutKey = std::array<VkDescriptorSetLayout,2>;

        VulkanPipelineLayoutCache(VulkanPipelineLayoutCache const&) = delete;
        VulkanPipelineLayoutCache& operator=(VulkanPipelineLayoutCache const&) = delete;

        VkPipelineLayout getLayout(PipelineLayoutKey const& key);

    private:
        using Timestamp = uint64_t;
        struct PipelineLayoutCacheEntry {
            VkPipelineLayout handle;
            Timestamp lastUsed;
        };

        using PipelineLayoutKeyHashFn = utils::hash::MurmurHashFn<PipelineLayoutKey>;
        struct PipelineLayoutKeyEqual {
            bool operator()(PipelineLayoutKey const& k1, PipelineLayoutKey const& k2) const {
                return 0 == memcmp((const void*)&k1, (const void*)&k2, sizeof(PipelineLayoutKey));
            }
        };

        using PipelineLayoutMap = tsl::robin_map<PipelineLayoutKey, PipelineLayoutCacheEntry,
            PipelineLayoutKeyHashFn, PipelineLayoutKeyEqual>;

        VkDevice mDevice;
        VulkanResourceAllocator* mAllocator;
        Timestamp mTimestamp;
        PipelineLayoutMap mPipelineLayouts;
    };
}