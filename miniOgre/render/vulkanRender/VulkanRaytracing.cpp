#include "OgreHeader.h"
#include "VulkanRaytracing.h"
#include "OgreRenderable.h"
#include "VulkanTools.h"
#include "VulkanBuffer.h"
#include "VulkanTexture.h"
#include "VulkanRenderData.h"
#include "OgreRoot.h"
#include "OgreResourceManager.h"
#include "OgreMaterial.h"
#include "OgreTextureUnit.h"
#include "VulkanRenderSystem.h"
#include "VulkanFrame.h"
#include "OgreBase.h"

void VulkanRayTracingContext::init()
{
    if (mInit)
    {
        return;
    }

    mInit = true;
    mMaxObjectCount = 100;
    mTransformMatrices.resize(mMaxObjectCount);

    

    for (auto i = 0; i < 1; i++)
    {
        mTransformMatrices[i] = {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f
        };
    }

    
    VulkanHelper::getSingleton().createBuffer(
        VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        &geometryNodesBuffer,
        mMaxObjectCount * sizeof(GeometryNode),
        nullptr);

    VulkanHelper::getSingleton().createBuffer(
        VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        &transformBuffer,
        mMaxObjectCount * sizeof(VkTransformMatrixKHR),
        nullptr);
    mVKDevice = VulkanHelper::getSingletonPtr()->_getVkDevice();

    mGeometryNodes.reserve(mMaxObjectCount);
    mBuildRangeInfos.reserve(mMaxObjectCount);
    mBuildRangePointerInfos.reserve(mMaxObjectCount);
    mTransformMatrices.reserve(mMaxObjectCount);
    maxPrimitiveCounts.reserve(mMaxObjectCount);

    transformBuffer.map();
    transformBuffer.copyTo(mTransformMatrices.data(),
        mTransformMatrices.size() * sizeof(VkTransformMatrixKHR));
    transformBuffer.unmap();


    uint32_t maxTextureCount = 100;
    mTextures.resize(maxTextureCount);

    std::shared_ptr<OgreTexture>& defaultTex = VulkanHelper::getSingleton().getDefaultTexture();
    mDefaultTexture = (VulkanTexture*)defaultTex.get();
    for (uint32_t i = 0; i < maxTextureCount; i++)
    {
        mTextures[i] = mDefaultTexture;
    }
    prepare();
    createStorageImage();
    createUniformBuffer();
    createRayTracingPipeline();
    createShaderBindingTables();
    createDescriptorSets();
    buildCommandBuffers();

    mVulkanRenderSystem = VulkanHelper::getSingleton()._getRenderSystem();
}

int32_t VulkanRayTracingContext::allocGeometrySlot(GeometryNode& geometry)
{
    mGeometryNodes.push_back(geometry);
    mBuildRangeInfos.emplace_back();
    return mGeometryNodes.size() - 1;
}

void VulkanRayTracingContext::updateTransform(int32_t index, const Ogre::Matrix4& m)
{
    VkTransformMatrixKHR& tmp = mTransformMatrices[index];
    char* dst = (char*)&tmp;
    for (auto i = 0; i < 3; i++)
    {
        const Real* src = m[i];
        memcpy(dst, src, sizeof(float) * 4);
        dst += sizeof(float) * 4;
    }
    
}

int32_t VulkanRayTracingContext::allocTextureSlot(VulkanTexture* texture)
{
    for (auto i = 0; i < mTextures.size(); i++)
    {
        if (mTextures[i] == mDefaultTexture)
        {
            mTextures[i] = texture;
            return i;
        }
    }
    
    assert(false);
    return -1;
}

VkBuffer VulkanRayTracingContext::getTransformBuffer()
{
    return transformBuffer.buffer;
}

void VulkanRayTracingContext::render(std::vector<Ogre::Renderable*>& renderList, ICamera* cam)
{
    VulkanFrame* frame = mVulkanRenderSystem->_getCurrentFrame();

    uint32_t frameIndex = frame->getFrameIndex();
    updateUniformBuffer(cam, frameIndex);
    updateRayTracing(renderList, frameIndex);

    VkCommandBuffer commandBuffer = VulkanHelper::getSingleton().getMainCommandBuffer(frameIndex);

    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR, pipeline);

    vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR, pipelineLayout,
        0, 1, &descriptorSet[frameIndex], 0, 0);

    auto rt = Ogre::Root::getSingleton().getMainRect();

    uint32_t width = rt.width();
    uint32_t height = rt.height();

    VkStridedDeviceAddressRegionKHR emptySbtEntry = {};
    vkCmdTraceRaysKHR(
        commandBuffer,
        &shaderBindingTables.raygen.stridedDeviceAddressRegion,
        &shaderBindingTables.miss.stridedDeviceAddressRegion,
        &shaderBindingTables.hit.stridedDeviceAddressRegion,
        &emptySbtEntry,
        width,
        height,
        1);

    VkImageSubresourceRange subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };

    auto swapchain = VulkanHelper::getSingleton().getSwapchainBuffer();
    vks::tools::setImageLayout(
        commandBuffer,
        swapchain[frameIndex]._image,
        VK_IMAGE_LAYOUT_UNDEFINED,
        VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
        subresourceRange);

    vks::tools::setImageLayout(
        commandBuffer,
        mStorageImage.image,
        VK_IMAGE_LAYOUT_GENERAL,
        VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
        subresourceRange);

    VkImageCopy copyRegion{};
    copyRegion.srcSubresource = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1 };
    copyRegion.srcOffset = { 0, 0, 0 };
    copyRegion.dstSubresource = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1 };
    copyRegion.dstOffset = { 0, 0, 0 };
    copyRegion.extent = { width, height, 1 };
    vkCmdCopyImage(commandBuffer, mStorageImage.image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, 
        swapchain[frameIndex]._image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &copyRegion);

    // Transition swap chain image back for presentation
    vks::tools::setImageLayout(
        commandBuffer,
        swapchain[frameIndex]._image,
        VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
        VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
        subresourceRange);

    // Transition ray tracing output image back to general layout
    vks::tools::setImageLayout(
        commandBuffer,
        mStorageImage.image,
        VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
        VK_IMAGE_LAYOUT_GENERAL,
        subresourceRange);
}

void VulkanRayTracingContext::updateRayTracing(std::vector<Ogre::Renderable*>& renderList, uint32_t frameIndex)
{
    bool object_change = false;
    bool tex_change = false;
    for (auto r : renderList)
    {
        VulkanRenderableData* rd = (VulkanRenderableData*)r->getRenderableData();

        if (rd->updateRayTracingData())
        {
            object_change = true;
        }
    }

    if (object_change)
    {
        if (mBottomLevelAS.handle != VK_NULL_HANDLE)
        {
            deleteAccelerationStructure(mBottomLevelAS);
        }

        if (mTopLevelAS.handle != VK_NULL_HANDLE)
        {
            deleteAccelerationStructure(mTopLevelAS);
        }

        createBottomLevelAccelerationStructure(renderList);
        createTopLevelAccelerationStructure();
    }

    transformBuffer.map();
    char buffer[1024] = { 0 };
    transformBuffer.copyTo(buffer,
        mTransformMatrices.size() * sizeof(VkTransformMatrixKHR));
    transformBuffer.unmap();
    
    updateDescriptorSets(frameIndex);
}

void VulkanRayTracingContext::updateUniformBuffer(ICamera* cam, uint32_t frameIndex)
{
    
    const Ogre::Matrix4& view = cam->getViewMatrix();
    const Ogre::Matrix4& proj = cam->getProjectMatrix();
    uniformData.viewInverse = view.inverse();
    uniformData.projInverse = proj.inverse();
    memcpy(uniformBuffer.mapped, &uniformData, sizeof(uniformData));
}

VulkanRayTracingContext::ScratchBuffer VulkanRayTracingContext::createScratchBuffer(VkDeviceSize size)
{
    ScratchBuffer scratchBuffer{};
    // Buffer and memory
    VkBufferCreateInfo bufferCreateInfo{};
    bufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferCreateInfo.size = size;
    bufferCreateInfo.usage = VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT;
    VK_CHECK_RESULT(vkCreateBuffer(mVKDevice, &bufferCreateInfo, nullptr, &scratchBuffer.handle));
    VkMemoryRequirements memoryRequirements{};
    vkGetBufferMemoryRequirements(mVKDevice, scratchBuffer.handle, &memoryRequirements);
    VkMemoryAllocateFlagsInfo memoryAllocateFlagsInfo{};
    memoryAllocateFlagsInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO;
    memoryAllocateFlagsInfo.flags = VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT_KHR;
    VkMemoryAllocateInfo memoryAllocateInfo = {};
    memoryAllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    memoryAllocateInfo.pNext = &memoryAllocateFlagsInfo;
    memoryAllocateInfo.allocationSize = memoryRequirements.size;
    memoryAllocateInfo.memoryTypeIndex = VulkanHelper::getSingleton()._findMemoryType(memoryRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    VK_CHECK_RESULT(vkAllocateMemory(mVKDevice, &memoryAllocateInfo, nullptr, &scratchBuffer.memory));
    VK_CHECK_RESULT(vkBindBufferMemory(mVKDevice, scratchBuffer.handle, scratchBuffer.memory, 0));
    // Buffer device address
    VkBufferDeviceAddressInfoKHR bufferDeviceAddresInfo{};
    bufferDeviceAddresInfo.sType = VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_INFO;
    bufferDeviceAddresInfo.buffer = scratchBuffer.handle;
    scratchBuffer.deviceAddress = vkGetBufferDeviceAddressKHR(mVKDevice, &bufferDeviceAddresInfo);
    return scratchBuffer;
}

void VulkanRayTracingContext::deleteScratchBuffer(VulkanRayTracingContext::ScratchBuffer& scratchBuffer)
{
    if (scratchBuffer.memory != VK_NULL_HANDLE) {
        vkFreeMemory(mVKDevice, scratchBuffer.memory, nullptr);
    }
    if (scratchBuffer.handle != VK_NULL_HANDLE) {
        vkDestroyBuffer(mVKDevice, scratchBuffer.handle, nullptr);
    }
}

void VulkanRayTracingContext::createAccelerationStructureBuffer(
    AccelerationStructure& accelerationStructure,
    VkAccelerationStructureBuildSizesInfoKHR buildSizeInfo)
{
    VkBufferCreateInfo bufferCreateInfo{};
    bufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferCreateInfo.size = buildSizeInfo.accelerationStructureSize;
    bufferCreateInfo.usage = VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT;
    VK_CHECK_RESULT(vkCreateBuffer(mVKDevice, &bufferCreateInfo, nullptr, &accelerationStructure.buffer));
    VkMemoryRequirements memoryRequirements{};
    vkGetBufferMemoryRequirements(mVKDevice, accelerationStructure.buffer, &memoryRequirements);
    VkMemoryAllocateFlagsInfo memoryAllocateFlagsInfo{};
    memoryAllocateFlagsInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO;
    memoryAllocateFlagsInfo.flags = VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT_KHR;
    VkMemoryAllocateInfo memoryAllocateInfo{};
    memoryAllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    memoryAllocateInfo.pNext = &memoryAllocateFlagsInfo;
    memoryAllocateInfo.allocationSize = memoryRequirements.size;
    memoryAllocateInfo.memoryTypeIndex = VulkanHelper::getSingleton()._findMemoryType(memoryRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    VK_CHECK_RESULT(vkAllocateMemory(mVKDevice, &memoryAllocateInfo, nullptr, &accelerationStructure.memory));
    VK_CHECK_RESULT(vkBindBufferMemory(mVKDevice, accelerationStructure.buffer, accelerationStructure.memory, 0));
}

void VulkanRayTracingContext::deleteAccelerationStructure(AccelerationStructure& accelerationStructure)
{
    
    vkFreeMemory(mVKDevice, accelerationStructure.memory, nullptr);
    vkDestroyBuffer(mVKDevice, accelerationStructure.buffer, nullptr);
    vkDestroyAccelerationStructureKHR(mVKDevice, accelerationStructure.handle, nullptr);

    accelerationStructure.handle = VK_NULL_HANDLE;
}

void VulkanRayTracingContext::createBottomLevelAccelerationStructure(std::vector<Ogre::Renderable*>& renderList)
{
    mBuildRangeInfos.clear();
    
    maxPrimitiveCounts.clear();
    mGeometries.clear();
    mGeometryNodes.clear();

    uint64_t maxPrimCount = 0;
    for (auto r : renderList)
    {
        VulkanRenderableData* vrd = (VulkanRenderableData*)r->getRenderableData();
        auto& rangeInfo = vrd->getBuildRangeInfo();
        auto& geometry = vrd->getGeometryKHR();
        auto& geometryNode = vrd->getGeometryNode();
        mBuildRangeInfos.push_back(rangeInfo);
        mGeometries.push_back(geometry);
        mGeometryNodes.push_back(geometryNode);
        maxPrimitiveCounts.push_back(rangeInfo.primitiveCount);
        maxPrimCount += rangeInfo.primitiveCount;
    }

    mBuildRangePointerInfos.clear();

    for (auto& rangeInfo : mBuildRangeInfos)
    {
        mBuildRangePointerInfos.push_back(&rangeInfo);
    }

    VkAccelerationStructureBuildGeometryInfoKHR accelerationStructureBuildGeometryInfo{};
    accelerationStructureBuildGeometryInfo.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR;
    accelerationStructureBuildGeometryInfo.type = VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR;
    accelerationStructureBuildGeometryInfo.flags = VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR;
    accelerationStructureBuildGeometryInfo.geometryCount = static_cast<uint32_t>(mGeometries.size());
    accelerationStructureBuildGeometryInfo.pGeometries = mGeometries.data();

    

    VkAccelerationStructureBuildSizesInfoKHR accelerationStructureBuildSizesInfo{};
    accelerationStructureBuildSizesInfo.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR;
    vkGetAccelerationStructureBuildSizesKHR(
        mVKDevice,
        VK_ACCELERATION_STRUCTURE_BUILD_TYPE_DEVICE_KHR,
        &accelerationStructureBuildGeometryInfo,
        maxPrimitiveCounts.data(),
        &accelerationStructureBuildSizesInfo);

    createAccelerationStructureBuffer(mBottomLevelAS, accelerationStructureBuildSizesInfo);

    VkAccelerationStructureCreateInfoKHR accelerationStructureCreateInfo{};
    accelerationStructureCreateInfo.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR;
    accelerationStructureCreateInfo.buffer = mBottomLevelAS.buffer;
    accelerationStructureCreateInfo.size = accelerationStructureBuildSizesInfo.accelerationStructureSize;
    accelerationStructureCreateInfo.type = VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR;
    vkCreateAccelerationStructureKHR(mVKDevice, &accelerationStructureCreateInfo, nullptr, &mBottomLevelAS.handle);

    ScratchBuffer scratchBuffer = createScratchBuffer(accelerationStructureBuildSizesInfo.buildScratchSize);

    accelerationStructureBuildGeometryInfo.mode = VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR;
    accelerationStructureBuildGeometryInfo.dstAccelerationStructure = mBottomLevelAS.handle;
    accelerationStructureBuildGeometryInfo.scratchData.deviceAddress = scratchBuffer.deviceAddress;

    const VkAccelerationStructureBuildRangeInfoKHR* buildOffsetInfo = mBuildRangeInfos.data();

    VkCommandBuffer commandBuffer = VulkanHelper::getSingleton().beginSingleTimeCommands();

    vkCmdBuildAccelerationStructuresKHR(
        commandBuffer,
        1,
        &accelerationStructureBuildGeometryInfo,
        mBuildRangePointerInfos.data());
    VulkanHelper::getSingleton().endSingleTimeCommands(commandBuffer);

    VkAccelerationStructureDeviceAddressInfoKHR accelerationDeviceAddressInfo{};
    accelerationDeviceAddressInfo.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_DEVICE_ADDRESS_INFO_KHR;
    accelerationDeviceAddressInfo.accelerationStructure = mBottomLevelAS.handle;
    mBottomLevelAS.deviceAddress = vkGetAccelerationStructureDeviceAddressKHR(mVKDevice, &accelerationDeviceAddressInfo);

    deleteScratchBuffer(scratchBuffer);
}

void VulkanRayTracingContext::createTopLevelAccelerationStructure()
{
    VkTransformMatrixKHR transformMatrix = {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f };

    VkAccelerationStructureInstanceKHR instance{};
    instance.transform = transformMatrix;
    instance.instanceCustomIndex = 0;
    instance.mask = 0xFF;
    instance.instanceShaderBindingTableRecordOffset = 0;
    instance.flags = VK_GEOMETRY_INSTANCE_TRIANGLE_FACING_CULL_DISABLE_BIT_KHR;
    instance.accelerationStructureReference = mBottomLevelAS.deviceAddress;

    VulkanBuffer instancesBuffer;
    VK_CHECK_RESULT(VulkanHelper::getSingleton().createBuffer(
        VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        &instancesBuffer,
        sizeof(VkAccelerationStructureInstanceKHR),
        &instance));

    VkDeviceOrHostAddressConstKHR instanceDataDeviceAddress{};
    instanceDataDeviceAddress.deviceAddress = vks::tools::getBufferDeviceAddress(&instancesBuffer);

    VkAccelerationStructureGeometryKHR accelerationStructureGeometry{};
    accelerationStructureGeometry.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR;
    accelerationStructureGeometry.geometryType = VK_GEOMETRY_TYPE_INSTANCES_KHR;
    accelerationStructureGeometry.flags = VK_GEOMETRY_OPAQUE_BIT_KHR;
    accelerationStructureGeometry.geometry.instances.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_INSTANCES_DATA_KHR;
    accelerationStructureGeometry.geometry.instances.arrayOfPointers = VK_FALSE;
    accelerationStructureGeometry.geometry.instances.data = instanceDataDeviceAddress;

    VkAccelerationStructureBuildGeometryInfoKHR accelerationStructureBuildGeometryInfo{};
    accelerationStructureBuildGeometryInfo.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR;
    accelerationStructureBuildGeometryInfo.type = VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR;
    accelerationStructureBuildGeometryInfo.flags = VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR;
    accelerationStructureBuildGeometryInfo.geometryCount = 1;
    accelerationStructureBuildGeometryInfo.pGeometries = &accelerationStructureGeometry;

    uint32_t primitive_count = 1;

    VkAccelerationStructureBuildSizesInfoKHR accelerationStructureBuildSizesInfo{};
    accelerationStructureBuildSizesInfo.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR;
    vkGetAccelerationStructureBuildSizesKHR(
        mVKDevice,
        VK_ACCELERATION_STRUCTURE_BUILD_TYPE_DEVICE_KHR,
        &accelerationStructureBuildGeometryInfo,
        &primitive_count,
        &accelerationStructureBuildSizesInfo);

    createAccelerationStructureBuffer(mTopLevelAS, accelerationStructureBuildSizesInfo);

    VkAccelerationStructureCreateInfoKHR accelerationStructureCreateInfo{};
    accelerationStructureCreateInfo.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR;
    accelerationStructureCreateInfo.buffer = mTopLevelAS.buffer;
    accelerationStructureCreateInfo.size = accelerationStructureBuildSizesInfo.accelerationStructureSize;
    accelerationStructureCreateInfo.type = VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR;
    vkCreateAccelerationStructureKHR(mVKDevice, &accelerationStructureCreateInfo, nullptr, &mTopLevelAS.handle);

    // Create a small scratch buffer used during build of the top level acceleration structure
    ScratchBuffer scratchBuffer = createScratchBuffer(accelerationStructureBuildSizesInfo.buildScratchSize);

    VkAccelerationStructureBuildGeometryInfoKHR accelerationBuildGeometryInfo{};
    accelerationBuildGeometryInfo.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR;
    accelerationBuildGeometryInfo.type = VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR;
    accelerationBuildGeometryInfo.flags = VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR;
    accelerationBuildGeometryInfo.mode = VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR;
    accelerationBuildGeometryInfo.dstAccelerationStructure = mTopLevelAS.handle;
    accelerationBuildGeometryInfo.geometryCount = 1;
    accelerationBuildGeometryInfo.pGeometries = &accelerationStructureGeometry;
    accelerationBuildGeometryInfo.scratchData.deviceAddress = scratchBuffer.deviceAddress;

    VkAccelerationStructureBuildRangeInfoKHR accelerationStructureBuildRangeInfo{};
    accelerationStructureBuildRangeInfo.primitiveCount = 1;
    accelerationStructureBuildRangeInfo.primitiveOffset = 0;
    accelerationStructureBuildRangeInfo.firstVertex = 0;
    accelerationStructureBuildRangeInfo.transformOffset = 0;
    std::vector<VkAccelerationStructureBuildRangeInfoKHR*> accelerationBuildStructureRangeInfos = { &accelerationStructureBuildRangeInfo };

    // Build the acceleration structure on the device via a one-time command buffer submission
    // Some implementations may support acceleration structure building on the host (VkPhysicalDeviceAccelerationStructureFeaturesKHR->accelerationStructureHostCommands), but we prefer device builds
    VkCommandBuffer commandBuffer = VulkanHelper::getSingleton().beginSingleTimeCommands();
    vkCmdBuildAccelerationStructuresKHR(
        commandBuffer,
        1,
        &accelerationBuildGeometryInfo,
        accelerationBuildStructureRangeInfos.data());
    VulkanHelper::getSingleton().endSingleTimeCommands(commandBuffer);

    VkAccelerationStructureDeviceAddressInfoKHR accelerationDeviceAddressInfo{};
    accelerationDeviceAddressInfo.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_DEVICE_ADDRESS_INFO_KHR;
    accelerationDeviceAddressInfo.accelerationStructure = mTopLevelAS.handle;

    deleteScratchBuffer(scratchBuffer);
    instancesBuffer.destroy();
}

void VulkanRayTracingContext::prepare()
{
    auto physicalDevice = VulkanHelper::getSingleton()._getPhysicalDevice();
    rayTracingPipelineProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_PROPERTIES_KHR;
    VkPhysicalDeviceProperties2 deviceProperties2{};
    deviceProperties2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
    deviceProperties2.pNext = &rayTracingPipelineProperties;
    vkGetPhysicalDeviceProperties2(physicalDevice, &deviceProperties2);
    accelerationStructureFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_FEATURES_KHR;
    VkPhysicalDeviceFeatures2 deviceFeatures2{};
    deviceFeatures2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
    deviceFeatures2.pNext = &accelerationStructureFeatures;
    vkGetPhysicalDeviceFeatures2(physicalDevice, &deviceFeatures2);
}

void VulkanRayTracingContext::createStorageImage()
{
    // Release ressources if image is to be recreated
    if (mStorageImage.image != VK_NULL_HANDLE) {
        vkDestroyImageView(mVKDevice, mStorageImage.view, nullptr);
        vkDestroyImage(mVKDevice, mStorageImage.image, nullptr);
        vkFreeMemory(mVKDevice, mStorageImage.memory, nullptr);
        mStorageImage = {};
    }

    VkImageCreateInfo image = vks::initializers::imageCreateInfo();
    image.imageType = VK_IMAGE_TYPE_2D;
    image.format = VulkanHelper::getSingleton().getSwapChainImageFormat();

    auto rt = Ogre::Root::getSingleton().getMainRect();
    image.extent = { (uint32_t)rt.width(), (uint32_t)rt.height(), 1};
    image.mipLevels = 1;
    image.arrayLayers = 1;
    image.samples = VK_SAMPLE_COUNT_1_BIT;
    image.tiling = VK_IMAGE_TILING_OPTIMAL;
    image.usage = VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_STORAGE_BIT;
    image.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    VK_CHECK_RESULT(vkCreateImage(mVKDevice, &image, nullptr, &mStorageImage.image));

    VkMemoryRequirements memReqs;
    vkGetImageMemoryRequirements(mVKDevice, mStorageImage.image, &memReqs);
    VkMemoryAllocateInfo memoryAllocateInfo = vks::initializers::memoryAllocateInfo();
    memoryAllocateInfo.allocationSize = memReqs.size;
    memoryAllocateInfo.memoryTypeIndex = VulkanHelper::getSingleton()._findMemoryType(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    VK_CHECK_RESULT(vkAllocateMemory(mVKDevice, &memoryAllocateInfo, nullptr, &mStorageImage.memory));
    VK_CHECK_RESULT(vkBindImageMemory(mVKDevice, mStorageImage.image, mStorageImage.memory, 0));

    VkImageViewCreateInfo colorImageView = vks::initializers::imageViewCreateInfo();
    colorImageView.viewType = VK_IMAGE_VIEW_TYPE_2D;
    colorImageView.format = VulkanHelper::getSingleton().getSwapChainImageFormat();
    colorImageView.subresourceRange = {};
    colorImageView.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    colorImageView.subresourceRange.baseMipLevel = 0;
    colorImageView.subresourceRange.levelCount = 1;
    colorImageView.subresourceRange.baseArrayLayer = 0;
    colorImageView.subresourceRange.layerCount = 1;
    colorImageView.image = mStorageImage.image;
    VK_CHECK_RESULT(vkCreateImageView(mVKDevice, &colorImageView, nullptr, &mStorageImage.view));

    VkCommandBuffer cmdBuffer = VulkanHelper::getSingleton().beginSingleTimeCommands();
    vks::tools::setImageLayout(cmdBuffer, mStorageImage.image,
        VK_IMAGE_LAYOUT_UNDEFINED,
        VK_IMAGE_LAYOUT_GENERAL,
        { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 });
    VulkanHelper::getSingleton().endSingleTimeCommands(cmdBuffer);
}

void VulkanRayTracingContext::createUniformBuffer()
{
    VulkanHelper::getSingleton().createBuffer(
        VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        &uniformBuffer,
        sizeof(uniformData),
        nullptr);

    uniformBuffer.map();
}

void VulkanRayTracingContext::createRayTracingPipeline()
{
    VkDescriptorSetLayoutBinding accelerationStructureLayoutBinding{};
    accelerationStructureLayoutBinding.binding = 0;
    accelerationStructureLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR;
    accelerationStructureLayoutBinding.descriptorCount = 1;
    accelerationStructureLayoutBinding.stageFlags = VK_SHADER_STAGE_RAYGEN_BIT_KHR;

    VkDescriptorSetLayoutBinding resultImageLayoutBinding{};
    resultImageLayoutBinding.binding = 1;
    resultImageLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
    resultImageLayoutBinding.descriptorCount = 1;
    resultImageLayoutBinding.stageFlags = VK_SHADER_STAGE_RAYGEN_BIT_KHR;

    VkDescriptorSetLayoutBinding uniformBufferBinding{};
    uniformBufferBinding.binding = 2;
    uniformBufferBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    uniformBufferBinding.descriptorCount = 1;
    uniformBufferBinding.stageFlags = VK_SHADER_STAGE_RAYGEN_BIT_KHR;

    std::vector<VkDescriptorSetLayoutBinding> bindings({
        accelerationStructureLayoutBinding,
        resultImageLayoutBinding,
        uniformBufferBinding
        });

    VkDescriptorSetLayoutCreateInfo descriptorSetlayoutCI{};
    descriptorSetlayoutCI.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    descriptorSetlayoutCI.bindingCount = static_cast<uint32_t>(bindings.size());
    descriptorSetlayoutCI.pBindings = bindings.data();
    VK_CHECK_RESULT(vkCreateDescriptorSetLayout(mVKDevice, &descriptorSetlayoutCI, nullptr, &descriptorSetLayout));

    VkPipelineLayoutCreateInfo pipelineLayoutCI{};
    pipelineLayoutCI.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutCI.setLayoutCount = 1;
    pipelineLayoutCI.pSetLayouts = &descriptorSetLayout;
    VK_CHECK_RESULT(vkCreatePipelineLayout(mVKDevice, &pipelineLayoutCI, nullptr, &pipelineLayout));

    /*
        Setup ray tracing shader groups
    */
    std::vector<VkPipelineShaderStageCreateInfo> shaderStages;

    // Ray generation group
    {
        shaderStages.push_back(loadShader("raygen.rgen.spv", VK_SHADER_STAGE_RAYGEN_BIT_KHR));
        VkRayTracingShaderGroupCreateInfoKHR shaderGroup{};
        shaderGroup.sType = VK_STRUCTURE_TYPE_RAY_TRACING_SHADER_GROUP_CREATE_INFO_KHR;
        shaderGroup.type = VK_RAY_TRACING_SHADER_GROUP_TYPE_GENERAL_KHR;
        shaderGroup.generalShader = static_cast<uint32_t>(shaderStages.size()) - 1;
        shaderGroup.closestHitShader = VK_SHADER_UNUSED_KHR;
        shaderGroup.anyHitShader = VK_SHADER_UNUSED_KHR;
        shaderGroup.intersectionShader = VK_SHADER_UNUSED_KHR;
        shaderGroups.push_back(shaderGroup);
    }

    // Miss group
    {
        shaderStages.push_back(loadShader("miss.rmiss.spv", VK_SHADER_STAGE_MISS_BIT_KHR));
        VkRayTracingShaderGroupCreateInfoKHR shaderGroup{};
        shaderGroup.sType = VK_STRUCTURE_TYPE_RAY_TRACING_SHADER_GROUP_CREATE_INFO_KHR;
        shaderGroup.type = VK_RAY_TRACING_SHADER_GROUP_TYPE_GENERAL_KHR;
        shaderGroup.generalShader = static_cast<uint32_t>(shaderStages.size()) - 1;
        shaderGroup.closestHitShader = VK_SHADER_UNUSED_KHR;
        shaderGroup.anyHitShader = VK_SHADER_UNUSED_KHR;
        shaderGroup.intersectionShader = VK_SHADER_UNUSED_KHR;
        shaderGroups.push_back(shaderGroup);
    }

    // Closest hit group for doing texture lookups
    {
        shaderStages.push_back(loadShader("closesthit.rchit.spv", VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR));
        VkRayTracingShaderGroupCreateInfoKHR shaderGroup{};
        shaderGroup.sType = VK_STRUCTURE_TYPE_RAY_TRACING_SHADER_GROUP_CREATE_INFO_KHR;
        shaderGroup.type = VK_RAY_TRACING_SHADER_GROUP_TYPE_TRIANGLES_HIT_GROUP_KHR;
        shaderGroup.generalShader = VK_SHADER_UNUSED_KHR;
        shaderGroup.closestHitShader = static_cast<uint32_t>(shaderStages.size()) - 1;
        shaderGroup.intersectionShader = VK_SHADER_UNUSED_KHR;
        shaderGroup.anyHitShader = VK_SHADER_UNUSED_KHR;
        shaderGroups.push_back(shaderGroup);
    }

    /*
        Create the ray tracing pipeline
    */
    VkRayTracingPipelineCreateInfoKHR rayTracingPipelineCI{};
    rayTracingPipelineCI.sType = VK_STRUCTURE_TYPE_RAY_TRACING_PIPELINE_CREATE_INFO_KHR;
    rayTracingPipelineCI.stageCount = static_cast<uint32_t>(shaderStages.size());
    rayTracingPipelineCI.pStages = shaderStages.data();
    rayTracingPipelineCI.groupCount = static_cast<uint32_t>(shaderGroups.size());
    rayTracingPipelineCI.pGroups = shaderGroups.data();
    rayTracingPipelineCI.maxPipelineRayRecursionDepth = 1;
    rayTracingPipelineCI.layout = pipelineLayout;
    VK_CHECK_RESULT(vkCreateRayTracingPipelinesKHR(mVKDevice, VK_NULL_HANDLE, VK_NULL_HANDLE, 1, &rayTracingPipelineCI, nullptr, &pipeline));
}

void VulkanRayTracingContext::createShaderBindingTables()
{
    const uint32_t handleSize = rayTracingPipelineProperties.shaderGroupHandleSize;
    const uint32_t handleSizeAligned = vks::tools::alignedSize(rayTracingPipelineProperties.shaderGroupHandleSize, rayTracingPipelineProperties.shaderGroupHandleAlignment);
    const uint32_t groupCount = static_cast<uint32_t>(shaderGroups.size());
    const uint32_t sbtSize = groupCount * handleSizeAligned;

    std::vector<uint8_t> shaderHandleStorage(sbtSize);
    VK_CHECK_RESULT(vkGetRayTracingShaderGroupHandlesKHR(mVKDevice, pipeline, 0, groupCount, sbtSize, shaderHandleStorage.data()));

    createShaderBindingTable(shaderBindingTables.raygen, 1);
    createShaderBindingTable(shaderBindingTables.miss, 1);
    createShaderBindingTable(shaderBindingTables.hit, 1);

    // Copy handles
    memcpy(shaderBindingTables.raygen.mapped, shaderHandleStorage.data(), handleSize);
    // We are using two miss shaders, so we need to get two handles for the miss shader binding table
    memcpy(shaderBindingTables.miss.mapped, shaderHandleStorage.data() + handleSizeAligned, handleSize);
    memcpy(shaderBindingTables.hit.mapped, shaderHandleStorage.data() + handleSizeAligned * 2, handleSize);
}

void VulkanRayTracingContext::createShaderBindingTable(ShaderBindingTable& shaderBindingTable, uint32_t handleCount)
{
    // Create buffer to hold all shader handles for the SBT
    VK_CHECK_RESULT(VulkanHelper::getSingleton().createBuffer(
        VK_BUFFER_USAGE_SHADER_BINDING_TABLE_BIT_KHR | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        &shaderBindingTable,
        rayTracingPipelineProperties.shaderGroupHandleSize * handleCount, nullptr));
    // Get the strided address to be used when dispatching the rays
    shaderBindingTable.stridedDeviceAddressRegion = getSbtEntryStridedDeviceAddressRegion(shaderBindingTable.buffer, handleCount);
    // Map persistent 
    shaderBindingTable.map();
}

VkStridedDeviceAddressRegionKHR VulkanRayTracingContext::getSbtEntryStridedDeviceAddressRegion
(VkBuffer buffer, uint32_t handleCount)
{
    const uint32_t handleSizeAligned = vks::tools::alignedSize(rayTracingPipelineProperties.shaderGroupHandleSize, rayTracingPipelineProperties.shaderGroupHandleAlignment);
    VkStridedDeviceAddressRegionKHR stridedDeviceAddressRegionKHR{};
    stridedDeviceAddressRegionKHR.deviceAddress = vks::tools::getBufferDeviceAddress(mVKDevice, buffer);
    stridedDeviceAddressRegionKHR.stride = handleSizeAligned;
    stridedDeviceAddressRegionKHR.size = handleCount * handleSizeAligned;
    return stridedDeviceAddressRegionKHR;
}

void VulkanRayTracingContext::createDescriptorSets()
{
    uint32_t imageCount = static_cast<uint32_t>(mTextures.size());
    std::vector<VkDescriptorPoolSize> poolSizes = {
        { VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR, 1 },
        { VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1 },
        { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1 }
    };
    VkDescriptorPoolCreateInfo descriptorPoolCreateInfo = vks::initializers::descriptorPoolCreateInfo(poolSizes, VULKAN_FRAME_RESOURCE_COUNT);
    VK_CHECK_RESULT(vkCreateDescriptorPool(mVKDevice, &descriptorPoolCreateInfo, nullptr, &descriptorPool));

    VkDescriptorSetAllocateInfo descriptorSetAllocateInfo = vks::initializers::descriptorSetAllocateInfo(descriptorPool, &descriptorSetLayout, 1);
    for (auto i = 0; i < VULKAN_FRAME_RESOURCE_COUNT; i++)
    {
        VK_CHECK_RESULT(vkAllocateDescriptorSets(mVKDevice, &descriptorSetAllocateInfo, &descriptorSet[i]));
    }
}

void VulkanRayTracingContext::updateDescriptorSets(uint32_t frameIndex)
{
    uint32_t imageCount = static_cast<uint32_t>(mTextures.size());
    VkWriteDescriptorSetAccelerationStructureKHR descriptorAccelerationStructureInfo = vks::initializers::writeDescriptorSetAccelerationStructureKHR();
    descriptorAccelerationStructureInfo.accelerationStructureCount = 1;
    descriptorAccelerationStructureInfo.pAccelerationStructures = &mTopLevelAS.handle;

    VkWriteDescriptorSet accelerationStructureWrite{};
    accelerationStructureWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    // The specialized acceleration structure descriptor has to be chained
    accelerationStructureWrite.pNext = &descriptorAccelerationStructureInfo;
    accelerationStructureWrite.dstSet = descriptorSet[frameIndex];
    accelerationStructureWrite.dstBinding = 0;
    accelerationStructureWrite.descriptorCount = 1;
    accelerationStructureWrite.descriptorType = VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR;

    VkDescriptorImageInfo storageImageDescriptor{ VK_NULL_HANDLE, mStorageImage.view, VK_IMAGE_LAYOUT_GENERAL };

    std::vector<VkWriteDescriptorSet> writeDescriptorSets = {
        // Binding 0: Top level acceleration structure
        accelerationStructureWrite,
        // Binding 1: Ray tracing result image
        vks::initializers::writeDescriptorSet(descriptorSet[frameIndex], VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1, &storageImageDescriptor),
        // Binding 2: Uniform data
        vks::initializers::writeDescriptorSet(descriptorSet[frameIndex], VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 2, &uniformBuffer.descriptor),
    };

    // Image descriptors for the image array
    std::vector<VkDescriptorImageInfo> textureDescriptors{};
    for (auto texture : mTextures) {
        VkDescriptorImageInfo descriptor{};
        descriptor.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        descriptor.sampler = texture->getSampler();
        descriptor.imageView = texture->getVkImageView();
        textureDescriptors.push_back(descriptor);
    }

    VkWriteDescriptorSet writeDescriptorImgArray{};
    writeDescriptorImgArray.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writeDescriptorImgArray.dstBinding = 5;
    writeDescriptorImgArray.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    writeDescriptorImgArray.descriptorCount = imageCount;
    writeDescriptorImgArray.dstSet = descriptorSet[frameIndex];
    writeDescriptorImgArray.pImageInfo = textureDescriptors.data();
    //writeDescriptorSets.push_back(writeDescriptorImgArray);

    vkUpdateDescriptorSets(mVKDevice, static_cast<uint32_t>(writeDescriptorSets.size()), writeDescriptorSets.data(), 0, VK_NULL_HANDLE);
}

void VulkanRayTracingContext::buildCommandBuffers()
{

}

VkPipelineShaderStageCreateInfo VulkanRayTracingContext::loadShader(std::string fileName, VkShaderStageFlagBits stage)
{
    VkPipelineShaderStageCreateInfo shaderStage = {};
    shaderStage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStage.stage = stage;

    ResourceInfo* res = ResourceManager::getSingleton().getResource(fileName);
    shaderStage.module = vks::tools::loadShaderBinary(res->_fullname.c_str(), mVKDevice);

    shaderStage.pName = "main";
    assert(shaderStage.module != VK_NULL_HANDLE);
    shaderModules.push_back(shaderStage.module);
    return shaderStage;
}