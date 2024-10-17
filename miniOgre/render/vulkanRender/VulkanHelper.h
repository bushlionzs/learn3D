#pragma once


#include "OgreSingleton.h"
#include "OgreCommon.h"
#include "VulkanCommon.h"
#include "VulkanContext.h"
#include "VulkanBuffer.h"
#include "VulkanResourceAllocator.h"
#include "VulkanPlatform.h"



class VulkanRenderSystemBase;
class VulkanTexture;
class VulkanLayoutCache;
class VulkanPipelineCache;
class VulkanPipelineLayoutCache;


struct CommandHelper
{
    VkCommandPool _commandPool;
    VkCommandBuffer _commandBuffer;
};


enum VulkanLayoutIndex
{
    VulkanLayoutIndex_Data = 0,
    VulkanLayoutIndex_Unlit = 1,
    VulkanLayoutIndex_Pbr = 2
};

class VulkanHelper : public Ogre::Singleton<VulkanHelper>
{
public:
	VulkanHelper(VulkanRenderSystemBase* rs);
	~VulkanHelper();

    void _initialise(VulkanPlatform* platform);
    void _createBuffer(
        VkDeviceSize size,
        VkBufferUsageFlags usage,
        VkMemoryPropertyFlags properties,
        VkBuffer& buffer,
        VkDeviceMemory& bufferMemory);

    VkDevice getDevcie()
    {
        return mVKDevice;
    }
    VkPhysicalDeviceProperties& _getVkPhysicalDeviceProperties();

    int32_t _findMemoryType(
        uint32_t typeFilter,
        VkMemoryPropertyFlags properties);
    VulkanRenderSystemBase* _getRenderSystem()
    {
        return mVulkanRenderSystem;
    }
    void loadDefaultResources();
    VkSampler getSampler(const filament::backend::SamplerParams& samplerParams);

    std::shared_ptr<OgreTexture>& getDefaultTexture();
    VkCommandBuffer beginSingleTimeCommands();
    void endSingleTimeCommands(VkCommandBuffer commandBuffer);

    bool haveRayTracing()
    {
        return mSettings.mRayPipelineSupported;
    }

     VulkanSettings& getVulkanSettings()
    {
        return mSettings;
    }

     VulkanPipelineCache* getPipelineCache()
     {
         return mPipelineCache;
     }

     VulkanPipelineLayoutCache* getPipelineLayoutCache()
     {
         return mPipelineLayoutCache;
     }

     VulkanLayoutCache* getLayoutCache()
     {
         return mLayoutCache;
     }
private:
    void createCommandPool();
    void createVulkanResourceCache();
private:
    VulkanRenderSystemBase* mVulkanRenderSystem;

    VkDevice mVKDevice;
    VkInstance mVKInstance;


    VulkanPlatform* mPlatform;
    VkPhysicalDevice mPhysicalDevice = VK_NULL_HANDLE;
    VkPhysicalDeviceProperties mPhysicalDeviceProperties;
    VkPhysicalDeviceFeatures mDeviceFeatures;
    VkPhysicalDeviceMemoryProperties mPhysicalMemoryProperties;
 

    VkCommandPool mSingleCommandPool;

    //default texture

    std::shared_ptr<OgreTexture> mDefaultTexture;
    tsl::robin_map<SamplerParams, VkSampler, SamplerParams::Hasher, SamplerParams::EqualTo> mSamplersCache;

    VmaAllocator mAllocator = VK_NULL_HANDLE;
    VulkanResourceAllocator mResourceAllocator;
    VulkanLayoutCache* mLayoutCache;
    VulkanPipelineLayoutCache* mPipelineLayoutCache = nullptr;
    VulkanPipelineCache* mPipelineCache = nullptr;
    struct ComputePipelineKey
    {
        VkShaderModule shaderModule;
        VkPipelineLayout pipelineLayout;
        struct Hasher {
            size_t operator()(const ComputePipelineKey& key) const noexcept {
                // we don't use std::hash<> here, so we don't have to include <functional>
                return (uint64_t)((uint64_t)key.shaderModule << 32) +
                    ((uint64_t)key.pipelineLayout >> 32);
            }
        };

        struct EqualTo {
            bool operator()(const ComputePipelineKey& lhs, const ComputePipelineKey& rhs) const noexcept {
                return lhs.shaderModule == rhs.shaderModule &&
                    lhs.pipelineLayout == rhs.pipelineLayout;
            }
        };
    };
    tsl::robin_map<ComputePipelineKey, VkPipeline, ComputePipelineKey::Hasher, ComputePipelineKey::EqualTo> mComputePipelineCache;

    std::array<DescriptorSetLayout, 2> mLayouts;
    VulkanSettings mSettings;

    VkPhysicalDeviceFeatures deviceFeatures{};
    VkPhysicalDeviceDescriptorIndexingFeaturesEXT physicalDeviceDescriptorIndexingFeatures{};
};