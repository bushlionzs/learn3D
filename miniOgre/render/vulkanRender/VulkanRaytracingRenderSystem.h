#pragma once

#include "VulkanCommon.h"
#include "VulkanBuffer.h"
#include "VulkanRenderSystemBase.h"

class VulkanTexture;

class ShaderBindingTable : public VulkanBuffer {
public:
    VkStridedDeviceAddressRegionKHR stridedDeviceAddressRegion{};
};

class VulkanRaytracingRenderSystem : public VulkanRenderSystemBase
{
public:
    VulkanRaytracingRenderSystem(HWND wnd);
	~VulkanRaytracingRenderSystem();

    struct ScratchBuffer
    {
        uint64_t deviceAddress = 0;
        VkBuffer handle = VK_NULL_HANDLE;
        VkDeviceMemory memory = VK_NULL_HANDLE;
    };

    struct ShaderBindingTables {
        ShaderBindingTable raygen;
        ShaderBindingTable miss;
        ShaderBindingTable hit;
    } shaderBindingTables;

    // Holds information for a storage image that the ray tracing shaders output to
    struct StorageImage {
        VkDeviceMemory memory = VK_NULL_HANDLE;
        VkImage image = VK_NULL_HANDLE;
        VkImageView view = VK_NULL_HANDLE;
        VkFormat format;
    };

    struct UniformData {
        Ogre::Matrix4 viewInverse;
        Ogre::Matrix4 projInverse;
    } uniformData;

    virtual bool engineInit();
    virtual void frameStart();
    virtual void frameEnd();
    virtual void update(Renderable* r);
    virtual void render(Renderable* r, RenderListType t);
    virtual void multiRender(std::vector<Ogre::Renderable*>& objs, bool multithread);

    /// 
    void beginRenderPass(RenderPassInfo& renderPassInfo);
    void endRenderPass();
    void present();

   
    int32_t allocGeometrySlot(GeometryNode& geometry);
    void updateTransform(int32_t index, const Ogre::Matrix4& m);
    int32_t allocTextureSlot(VulkanTexture* texture);
    VkBuffer getTransformBuffer();

    void render(std::vector<Ogre::Renderable*>& renderList, ICamera* cam);
    void updateRayTracing(std::vector<Ogre::Renderable*>& renderList, uint32_t frameIndex);
private:
    void updateUniformBuffer(ICamera* cam, uint32_t frameIndex);
    ScratchBuffer createScratchBuffer(VkDeviceSize size);
    void deleteScratchBuffer(ScratchBuffer& scratchBuffer);
    void createAccelerationStructureBuffer(
        AccelerationStructure& accelerationStructure,
        VkAccelerationStructureBuildSizesInfoKHR buildSizeInfo);
    void deleteAccelerationStructure(AccelerationStructure& accelerationStructure);
    void createBottomLevelAccelerationStructure(std::vector<Ogre::Renderable*>& renderList);
    void createTopLevelAccelerationStructure();
    void prepare();
    void createStorageImage();
    void createUniformBuffer();
    void createRayTracingPipeline();
    void createShaderBindingTables();
    void createShaderBindingTable(ShaderBindingTable& shaderBindingTable, uint32_t handleCount);
    VkStridedDeviceAddressRegionKHR getSbtEntryStridedDeviceAddressRegion(VkBuffer buffer, uint32_t handleCount);
    void createDescriptorSets();
    void updateDescriptorSets(uint32_t frameIndex);
    void buildCommandBuffers();
    VkPipelineShaderStageCreateInfo loadShader(std::string fileName, VkShaderStageFlagBits stage);
    
private:

    

    ////
    uint32_t mMaxObjectCount = 10000;

    std::vector<VkTransformMatrixKHR> mTransformMatrices;
    VulkanBuffer transformBuffer;
    VulkanBuffer uniformBuffer;

    std::vector<GeometryNode> mGeometryNodes;
    std::vector<VkAccelerationStructureBuildRangeInfoKHR> mBuildRangeInfos;
    std::vector<VkAccelerationStructureBuildRangeInfoKHR*> mBuildRangePointerInfos;
    VulkanBuffer geometryNodesBuffer;
    std::vector<VkAccelerationStructureGeometryKHR> mGeometries;
    std::vector<uint32_t> maxPrimitiveCounts;


    VkPhysicalDeviceRayTracingPipelinePropertiesKHR  mRayTracingPipelineProperties{};
    VkPhysicalDeviceAccelerationStructureFeaturesKHR mAccelerationStructureFeatures{};
    AccelerationStructure mBottomLevelAS{};
    AccelerationStructure mTopLevelAS{};

    StorageImage mStorageImage;

    VulkanTexture* mDefaultTexture = nullptr;
    std::vector<VulkanTexture*> mTextures;
    bool mChange = true;
    VkDevice mVKDevice;

    VkPipeline pipeline{ VK_NULL_HANDLE };
    VkPipelineLayout pipelineLayout{ VK_NULL_HANDLE };
    VkDescriptorSet descriptorSet[VULKAN_FRAME_RESOURCE_COUNT];
    VkDescriptorSetLayout descriptorSetLayout{ VK_NULL_HANDLE };

    std::vector<VkRayTracingShaderGroupCreateInfoKHR> shaderGroups{};
    std::vector<VkShaderModule> shaderModules;

    VkPhysicalDeviceRayTracingPipelinePropertiesKHR  rayTracingPipelineProperties{};
    VkPhysicalDeviceAccelerationStructureFeaturesKHR accelerationStructureFeatures{};

    VkDescriptorPool descriptorPool{ VK_NULL_HANDLE };

    void* deviceCreatepNextChain = nullptr;
};