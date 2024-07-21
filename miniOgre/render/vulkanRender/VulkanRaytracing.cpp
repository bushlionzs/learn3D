#include "OgreHeader.h"
#include "VulkanRaytracing.h"
#include "OgreRenderable.h"
#include "VulkanTools.h"
#include "VulkanBuffer.h"
#include "OgreRoot.h"

void VulkanRayTracingContext::init()
{
    mTransformMatrices.resize(mMaxCount);

    mVulkanTransformBuffer = new VulkanUploadBuffer<VkTransformMatrixKHR>(mMaxCount, true);
    mVulkanGeometryBuffer  = new VulkanUploadBuffer<GeometryNode>(mMaxCount, true);
    mVKDevice = VulkanHelper::getSingletonPtr()->_getVkDevice();

    mGeometryNodes.reserve(mMaxCount);
    mBuildRangeInfos.reserve(mMaxCount);
    mBuildRangePointerInfos.reserve(mMaxCount);
    mTransformMatrices.reserve(mMaxCount);
    maxPrimitiveCounts.reserve(mMaxCount);
}

int32_t VulkanRayTracingContext::allocGeometrySlot(GeometryNode& geometry)
{
    mGeometryNodes.push_back(geometry);
    mBuildRangeInfos.emplace_back();
    return mGeometryNodes.size() - 1;
}

int32_t VulkanRayTracingContext::allocTransformSlot(VkTransformMatrixKHR& transform)
{
    mTransformMatrices.push_back(transform);
    return mTransformMatrices.size() - 1;
}

int32_t VulkanRayTracingContext::allocTextureSlot(VulkanTexture* texture)
{
    mTextures.push_back(texture);
    return mTextures.size() - 1;
}

VkBuffer VulkanRayTracingContext::getTransformBuffer()
{
    return mVulkanTransformBuffer->getVKBuffer();
}

void VulkanRayTracingContext::updateRayTracing(std::vector<Ogre::Renderable*>& renderList)
{
    if (!mChange)
    {
        return;
    }

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
    createStorageImage();
    createUniformBuffer();
    createRayTracingPipeline();
    createShaderBindingTables();
    createDescriptorSets();
    buildCommandBuffers();

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
    for (auto r : renderList)
    {
        VulkanRenderableData* vrd = (VulkanRenderableData*)r->getRenderableData();
    }


    mBuildRangePointerInfos.clear();
    maxPrimitiveCounts.clear();

    uint64_t maxPrimCount = 0;
    for (auto& rangeInfo : mBuildRangeInfos) {
        mBuildRangePointerInfos.push_back(&rangeInfo);
        maxPrimitiveCounts.push_back(rangeInfo.primitiveCount);
        maxPrimCount += rangeInfo.primitiveCount;
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

void VulkanRayTracingContext::createStorageImage()
{
    // Release ressources if image is to be recreated
    if (mStorageImage.image != VK_NULL_HANDLE) {
        vkDestroyImageView(mVKDevice, mStorageImage.view, nullptr);
        vkDestroyImage(mVKDevice, mStorageImage.image, nullptr);
        vkFreeMemory(mVKDevice, mStorageImage.memory, nullptr);
        storageImage = {};
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
    vkGetImageMemoryRequirements(mVKDevice, storageImage.image, &memReqs);
    VkMemoryAllocateInfo memoryAllocateInfo = vks::initializers::memoryAllocateInfo();
    memoryAllocateInfo.allocationSize = memReqs.size;
    memoryAllocateInfo.memoryTypeIndex = VulkanHelper::getSingleton()._findMemoryType(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    VK_CHECK_RESULT(vkAllocateMemory(mVKDevice, &memoryAllocateInfo, nullptr, &storageImage.memory));
    VK_CHECK_RESULT(vkBindImageMemory(mVKDevice, storageImage.image, storageImage.memory, 0));

    VkImageViewCreateInfo colorImageView = vks::initializers::imageViewCreateInfo();
    colorImageView.viewType = VK_IMAGE_VIEW_TYPE_2D;
    colorImageView.format = VulkanHelper::getSingleton().getSwapChainImageFormat();
    colorImageView.subresourceRange = {};
    colorImageView.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    colorImageView.subresourceRange.baseMipLevel = 0;
    colorImageView.subresourceRange.levelCount = 1;
    colorImageView.subresourceRange.baseArrayLayer = 0;
    colorImageView.subresourceRange.layerCount = 1;
    colorImageView.image = storageImage.image;
    VK_CHECK_RESULT(vkCreateImageView(mVKDevice, &colorImageView, nullptr, &storageImage.view));

    VkCommandBuffer cmdBuffer = VulkanHelper::getSingleton().beginSingleTimeCommands();
    vks::tools::setImageLayout(cmdBuffer, storageImage.image,
        VK_IMAGE_LAYOUT_UNDEFINED,
        VK_IMAGE_LAYOUT_GENERAL,
        { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 });
    VulkanHelper::getSingleton().endSingleTimeCommands(cmdBuffer);
}

void VulkanRayTracingContext::createUniformBuffer()
{

}

void VulkanRayTracingContext::createRayTracingPipeline()
{
    uint32_t imageCount{ 0 };
    imageCount = static_cast<uint32_t>(mTextures.size());

    std::vector<VkDescriptorSetLayoutBinding> setLayoutBindings = {
        // Binding 0: Top level acceleration structure
        vks::initializers::descriptorSetLayoutBinding(VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR, VK_SHADER_STAGE_RAYGEN_BIT_KHR | VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR, 0),
        // Binding 1: Ray tracing result image
        vks::initializers::descriptorSetLayoutBinding(VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, VK_SHADER_STAGE_RAYGEN_BIT_KHR, 1),
        // Binding 2: Uniform buffer
        vks::initializers::descriptorSetLayoutBinding(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_RAYGEN_BIT_KHR | VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR | VK_SHADER_STAGE_MISS_BIT_KHR, 2),
        // Binding 3: Texture image
        vks::initializers::descriptorSetLayoutBinding(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR | VK_SHADER_STAGE_ANY_HIT_BIT_KHR, 3),
        // Binding 4: Geometry node information SSBO
        vks::initializers::descriptorSetLayoutBinding(VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR | VK_SHADER_STAGE_ANY_HIT_BIT_KHR, 4),
        // Binding 5: All images used by the glTF model
        vks::initializers::descriptorSetLayoutBinding(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR | VK_SHADER_STAGE_ANY_HIT_BIT_KHR, 5, imageCount)
    };

    // Unbound set
    VkDescriptorSetLayoutBindingFlagsCreateInfoEXT setLayoutBindingFlags{};
    setLayoutBindingFlags.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO_EXT;
    setLayoutBindingFlags.bindingCount = 6;
    std::vector<VkDescriptorBindingFlagsEXT> descriptorBindingFlags = {
        0,
        0,
        0,
        0,
        0,
        VK_DESCRIPTOR_BINDING_VARIABLE_DESCRIPTOR_COUNT_BIT_EXT
    };
    setLayoutBindingFlags.pBindingFlags = descriptorBindingFlags.data();

    VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCI = vks::initializers::descriptorSetLayoutCreateInfo(setLayoutBindings);
    descriptorSetLayoutCI.pNext = &setLayoutBindingFlags;
    VK_CHECK_RESULT(vkCreateDescriptorSetLayout(mVKDevice, &descriptorSetLayoutCI, nullptr, &descriptorSetLayout));

    VkPipelineLayoutCreateInfo pipelineLayoutCI = vks::initializers::pipelineLayoutCreateInfo(&descriptorSetLayout, 1);
    VK_CHECK_RESULT(vkCreatePipelineLayout(mVKDevice, &pipelineLayoutCI, nullptr, &pipelineLayout));

    /*
        Setup ray tracing shader groups
    */
    std::vector<VkPipelineShaderStageCreateInfo> shaderStages;

    // Ray generation group
    {
        shaderStages.push_back(loadShader(getShadersPath() + "raytracinggltf/raygen.rgen.spv", VK_SHADER_STAGE_RAYGEN_BIT_KHR));
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
        shaderStages.push_back(loadShader(getShadersPath() + "raytracinggltf/miss.rmiss.spv", VK_SHADER_STAGE_MISS_BIT_KHR));
        VkRayTracingShaderGroupCreateInfoKHR shaderGroup{};
        shaderGroup.sType = VK_STRUCTURE_TYPE_RAY_TRACING_SHADER_GROUP_CREATE_INFO_KHR;
        shaderGroup.type = VK_RAY_TRACING_SHADER_GROUP_TYPE_GENERAL_KHR;
        shaderGroup.generalShader = static_cast<uint32_t>(shaderStages.size()) - 1;
        shaderGroup.closestHitShader = VK_SHADER_UNUSED_KHR;
        shaderGroup.anyHitShader = VK_SHADER_UNUSED_KHR;
        shaderGroup.intersectionShader = VK_SHADER_UNUSED_KHR;
        shaderGroups.push_back(shaderGroup);
        // Second shader for shadows
        shaderStages.push_back(loadShader(getShadersPath() + "raytracinggltf/shadow.rmiss.spv", VK_SHADER_STAGE_MISS_BIT_KHR));
        shaderGroup.generalShader = static_cast<uint32_t>(shaderStages.size()) - 1;
        shaderGroups.push_back(shaderGroup);
    }

    // Closest hit group for doing texture lookups
    {
        shaderStages.push_back(loadShader(getShadersPath() + "raytracinggltf/closesthit.rchit.spv", VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR));
        VkRayTracingShaderGroupCreateInfoKHR shaderGroup{};
        shaderGroup.sType = VK_STRUCTURE_TYPE_RAY_TRACING_SHADER_GROUP_CREATE_INFO_KHR;
        shaderGroup.type = VK_RAY_TRACING_SHADER_GROUP_TYPE_TRIANGLES_HIT_GROUP_KHR;
        shaderGroup.generalShader = VK_SHADER_UNUSED_KHR;
        shaderGroup.closestHitShader = static_cast<uint32_t>(shaderStages.size()) - 1;
        shaderGroup.intersectionShader = VK_SHADER_UNUSED_KHR;
        // This group also uses an anyhit shader for doing transparency (see anyhit.rahit for details)
        shaderStages.push_back(loadShader(getShadersPath() + "raytracinggltf/anyhit.rahit.spv", VK_SHADER_STAGE_ANY_HIT_BIT_KHR));
        shaderGroup.anyHitShader = static_cast<uint32_t>(shaderStages.size()) - 1;
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

}

void VulkanRayTracingContext::createDescriptorSets()
{

}

void VulkanRayTracingContext::buildCommandBuffers()
{

}
