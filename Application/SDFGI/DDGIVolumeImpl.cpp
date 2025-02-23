/*
* Copyright (c) 2019-2023, NVIDIA CORPORATION.  All rights reserved.
*
* NVIDIA CORPORATION and its licensors retain all intellectual property
* and proprietary rights in and to this software, related documentation
* and any modifications thereto.  Any use, reproduction, disclosure or
* distribution of this software and related documentation without an express
* license agreement from NVIDIA CORPORATION is strictly prohibited.
*/

#include "DDGIVolumeImpl.h"
#include "SDFGI_util.h"
#include <cstring>
#include <random>
#include <string>
#include <vector>
#include <OgreRoot.h>





    //------------------------------------------------------------------------
    // Private RTXGI Namespace Helper Functions
    //------------------------------------------------------------------------

    ERTXGIStatus ValidateManagedResourcesDesc(const DDGIVolumeManagedResourcesDesc& desc)
    {
        // Shader bytecode
        if (!ValidateShaderBytecode(desc.probeBlendingIrradianceCS)) 
            return ERTXGIStatus::ERROR_DDGI_INVALID_BYTECODE_PROBE_BLENDING_IRRADIANCE;
        if (!ValidateShaderBytecode(desc.probeBlendingDistanceCS)) 
            return ERTXGIStatus::ERROR_DDGI_INVALID_BYTECODE_PROBE_BLENDING_DISTANCE;
        if (!ValidateShaderBytecode(desc.probeRelocation.updateCS)) 
            return ERTXGIStatus::ERROR_DDGI_INVALID_BYTECODE_PROBE_RELOCATION;
        if (!ValidateShaderBytecode(desc.probeRelocation.resetCS)) 
            return ERTXGIStatus::ERROR_DDGI_INVALID_BYTECODE_PROBE_RELOCATION_RESET;
        if (!ValidateShaderBytecode(desc.probeClassification.updateCS)) 
            return ERTXGIStatus::ERROR_DDGI_INVALID_BYTECODE_PROBE_CLASSIFICATION;
        if (!ValidateShaderBytecode(desc.probeClassification.resetCS)) 
            return ERTXGIStatus::ERROR_DDGI_INVALID_BYTECODE_PROBE_CLASSIFICATION_RESET;
        if (!ValidateShaderBytecode(desc.probeVariability.reductionCS)) 
            return ERTXGIStatus::ERROR_DDGI_INVALID_BYTECODE_PROBE_CLASSIFICATION_RESET;
        if (!ValidateShaderBytecode(desc.probeVariability.extraReductionCS)) 
            return ERTXGIStatus::ERROR_DDGI_INVALID_BYTECODE_PROBE_VARIABILITY_EXTRA_REDUCTION;

        return ERTXGIStatus::OK;
    }

    ERTXGIStatus ValidateUnmanagedResourcesDesc(const DDGIVolumeUnmanagedResourcesDesc& desc)
    {
        // Texture Arrays
        if (desc.probeRayData == nullptr)
            return ERTXGIStatus::ERROR_DDGI_INVALID_TEXTURE_PROBE_RAY_DATA;
        if (desc.probeIrradiance == nullptr)
            return ERTXGIStatus::ERROR_DDGI_INVALID_TEXTURE_PROBE_IRRADIANCE;
        if (desc.probeDistance == nullptr)
            return ERTXGIStatus::ERROR_DDGI_INVALID_TEXTURE_PROBE_DISTANCE;
        if (desc.probeData == nullptr)
            return ERTXGIStatus::ERROR_DDGI_INVALID_TEXTURE_PROBE_DATA;
        if (desc.probeVariability == nullptr)
            return ERTXGIStatus::ERROR_DDGI_INVALID_TEXTURE_PROBE_VARIABILITY;
        if (desc.probeVariabilityAverage == nullptr)
            return ERTXGIStatus::ERROR_DDGI_INVALID_TEXTURE_PROBE_VARIABILITY_AVERAGE;
        if (!desc.probeVariabilityReadback)
            return ERTXGIStatus::ERROR_DDGI_INVALID_TEXTURE_PROBE_VARIABILITY_READBACK;
        return ERTXGIStatus::OK;
    }

    //------------------------------------------------------------------------
    // Public RTXGI Namespace DDGI Functions
    //------------------------------------------------------------------------

    

    ERTXGIStatus UploadDDGIVolumeResourceIndices(uint32_t bufferingIndex, uint32_t numVolumes, DDGIVolume** volumes)
    {
        // Copy the resource indices for each volume
        for (uint32_t volumeIndex = 0; volumeIndex < numVolumes; volumeIndex++)
        {
            // Get the volume
            const DDGIVolume* volume = volumes[volumeIndex];

            // Validate the upload and device buffers
            if (!volume->GetResourceIndicesBuffer())
                return ERTXGIStatus::ERROR_DDGI_INVALID_RESOURCE_INDICES_BUFFER;

            // Offset to the resource indices data to write to (e.g. double buffering)
            uint64_t bufferOffset = numVolumes * DDGIVolumeResourceIndices::GetAlignedSizeInBytes() * bufferingIndex;

            // Offset to the volume in current resource indices buffer
            uint32_t volumeOffset = volume->GetIndex() * DDGIVolumeResourceIndices::GetAlignedSizeInBytes();

            // Offset to the volume resource indices in the upload buffer
            uint64_t srcOffset = (bufferOffset + volumeOffset);

            auto* rs = Ogre::Root::getSingleton().getRenderSystem();
            Handle<HwBufferObject> indicesBuffer = volume->GetResourceIndicesBuffer();

            const DDGIVolumeResourceIndices gpuDesc = volume->GetResourceIndices();

            if (srcOffset == 128)
            {
                int kk = 0;
            }
            rs->updateBufferObject(indicesBuffer, (const char*)&gpuDesc, sizeof(gpuDesc), srcOffset);
            }

        return ERTXGIStatus::OK;
    }

    ERTXGIStatus UploadDDGIVolumeConstants(uint32_t bufferingIndex, uint32_t numVolumes, DDGIVolume** volumes)
    {
        auto* rs = Ogre::Root::getSingleton().getRenderSystem();
        // Copy the constants for each volume
        for (uint32_t volumeIndex = 0; volumeIndex < numVolumes; volumeIndex++)
        {
            // Get the volume
            const DDGIVolume* volume = volumes[volumeIndex];

            // Validate the upload and device buffers
            if (!volume->GetConstantsBuffer())
                return ERTXGIStatus::ERROR_DDGI_INVALID_CONSTANTS_BUFFER;
            
            // Offset to the constants data to write to (e.g. double buffering)
            uint64_t bufferOffset = numVolumes * DDGIVolumeDescGPUPacked::GetAlignedSizeInBytes() * bufferingIndex;

            // Offset to the volume in current constants buffer
            uint32_t volumeOffset = volume->GetIndex() * DDGIVolumeDescGPUPacked::GetAlignedSizeInBytes();

            // Offset to the volume constants in the upload buffer
            uint64_t srcOffset = (bufferOffset + volumeOffset);

            const DDGIVolumeDescGPUPacked gpuDesc = volume->GetDescGPUPacked();

            
            auto constantsBuffer = volume->GetConstantsBuffer();
            rs->updateBufferObject(constantsBuffer, (const char*)&gpuDesc, 
                sizeof(DDGIVolumeDescGPUPacked), srcOffset);
           }

        return ERTXGIStatus::OK;
    }

    ERTXGIStatus UpdateDDGIVolumeProbes(uint32_t numVolumes, DDGIVolume** volumes)
    {
        auto* rs = Ogre::Root::getSingleton().getRenderSystem();

        uint32_t volumeIndex;
        
        std::vector<TextureBarrier> barriers;
        // Irradiance Blending

        for (volumeIndex = 0; volumeIndex < numVolumes; volumeIndex++)
        {
            // Get the volume
            const DDGIVolume* volume = volumes[volumeIndex];

            
            // Get the number of probes on each axis
            uint32_t probeCountX, probeCountY, probeCountZ;
            GetDDGIVolumeProbeCounts(volume->GetDesc(), probeCountX, probeCountY, probeCountZ);

            // Probe irradiance blending
            {
                // Bind the pipeline and dispatch threads
                Handle<HwComputeProgram> programHandle = volume->GetProbeBlendingIrradianceModule();
                Handle<HwDescriptorSet> descSet = volume->GetProbeBlendingIrradianceDescriptorSet();
                rs->bindComputePipeline(programHandle, &descSet, 1);
                rs->dispatchComputeShader(probeCountX, probeCountY, probeCountZ);
                
            }

            // Add a barrier
            barriers.emplace_back();
            barriers.back().pTexture = volume->GetProbeIrradiance();
            barriers.emplace_back();
            barriers.back().pTexture = volume->GetProbeVariability();
        }

        // Distance Blending
        for (volumeIndex = 0; volumeIndex < numVolumes; volumeIndex++)
        {
            // Get the volume
            const DDGIVolume* volume = volumes[volumeIndex];

            
            // Get the number of probes on the X and Y dimensions of the texture
            uint32_t probeCountX, probeCountY, probeCountZ;
            GetDDGIVolumeProbeCounts(volume->GetDesc(), probeCountX, probeCountY, probeCountZ);

            // Probe distance blending
            {
                Handle<HwComputeProgram> programHandle = volume->GetProbeBlendingDistanceModule();
                Handle<HwDescriptorSet> descSet = volume->GetProbeBlendingDistanceDescriptorSet();
                rs->bindComputePipeline(programHandle, &descSet, 1);
                rs->dispatchComputeShader(probeCountX, probeCountY, probeCountZ);
            }

            // Add a barrier
            barriers.emplace_back();
            barriers.back().pTexture = volume->GetProbeDistance();
        }

        // Irradiance pass must finish generating variability before possible reduction pass
        // Also ensures that irradiance and distance complete before border update after reduction
        if (!barriers.empty())
        {
            rs->resourceBarrier(0, nullptr, barriers.size(), barriers.data(), 0, nullptr, QUEUE_TYPE_COMPUTE);
        }
        // Remove previous barriers
        barriers.clear();

        return ERTXGIStatus::OK;
    }

    ERTXGIStatus RelocateDDGIVolumeProbes(uint32_t numVolumes, DDGIVolume** volumes)
    {
        auto* rs = Ogre::Root::getSingleton().getRenderSystem();

        uint32_t volumeIndex;
        std::vector<TextureBarrier> barriers;


        // Probe Relocation Reset
        for (volumeIndex = 0; volumeIndex < numVolumes; volumeIndex++)
        {
            // Get the volume
            const DDGIVolume* volume = volumes[volumeIndex];
            if (!volume->GetProbeRelocationNeedsReset()) continue;  // Skip if the volume doesn't need to be reset

       
            // Reset all probe offsets to zero
            const float groupSizeX = 32.f;
            uint32_t numGroupsX = (uint32_t)ceil((float)volume->GetNumProbes() / groupSizeX);

            Handle<HwComputeProgram> programHandle = volume->GetProbeRelocationResetModule();
            Handle<HwDescriptorSet> descSet = volume->GetProbeRelocationResetDescriptorSet();
            rs->bindComputePipeline(programHandle, &descSet, 1);
            rs->dispatchComputeShader(numGroupsX, 1, 1);

            // Update the reset flag
            volumes[volumeIndex]->SetProbeRelocationNeedsReset(false);

            // Add a barrier
            barriers.emplace_back();
            barriers.back().pTexture = volume->GetProbeData();
        }

        // Probe Relocation Reset Barrier(s)
        if(!barriers.empty())
        {
            // Wait for the compute pass to complete
            rs->resourceBarrier(0, nullptr, barriers.size(), barriers.data(), 0, nullptr, QUEUE_TYPE_COMPUTE);
        }

        barriers.clear();

        // Probe Relocation
        for (volumeIndex = 0; volumeIndex < numVolumes; volumeIndex++)
        {
            // Get the volume
            const DDGIVolume* volume = volumes[volumeIndex];
            if (!volume->GetProbeRelocationEnabled()) continue;  // Skip if relocation is not enabled for this volume

            // Probe relocation
            float groupSizeX = 32.f;
            uint32_t numGroupsX = (uint32_t)ceil((float)volume->GetNumProbes() / groupSizeX);

            Handle<HwComputeProgram> programHandle = volume->GetProbeRelocationModule();
            Handle<HwDescriptorSet> descSet = volume->GetProbeRelocationDescriptorSet();
            rs->bindComputePipeline(programHandle, &descSet, 1);
            rs->dispatchComputeShader(numGroupsX, 1, 1);

            // Add a barrier
            barriers.emplace_back();
            barriers.back().pTexture = volume->GetProbeData();
        }

        // Probe Relocation Barrier(s)
        if (!barriers.empty())
        {
            // Wait for the compute pass to complete
            rs->resourceBarrier(0, nullptr, barriers.size(), barriers.data(), 0, nullptr, QUEUE_TYPE_COMPUTE);
        }

        return ERTXGIStatus::OK;
    }

    ERTXGIStatus ClassifyDDGIVolumeProbes(uint32_t numVolumes, DDGIVolume** volumes)
    {
        auto* rs = Ogre::Root::getSingleton().getRenderSystem();
        uint32_t volumeIndex;
        std::vector<TextureBarrier> barriers;


        // Probe Classification Reset
        for (volumeIndex = 0; volumeIndex < numVolumes; volumeIndex++)
        {
            // Get the volume
            const DDGIVolume* volume = volumes[volumeIndex];
            if (!volume->GetProbeClassificationNeedsReset()) continue;  // Skip if the volume doesn't need to be reset

            // Reset all probe states to the ACTIVE state
            const float groupSizeX = 32.f;
            uint32_t numGroupsX = (uint32_t)ceil((float)volume->GetNumProbes() / groupSizeX);
            Handle<HwComputeProgram> programHandle = volume->GetProbeClassificationResetModule();
            Handle<HwDescriptorSet> descSet = volume->GetProbeClassificationResetDescriptorSet();
            rs->bindComputePipeline(programHandle, &descSet, 1);
            rs->dispatchComputeShader(numGroupsX, 1, 1);

            // Update the reset flag
            volumes[volumeIndex]->SetProbeClassificationNeedsReset(false);

            // Add a barrier
            barriers.emplace_back();
            barriers.back().pTexture = volume->GetProbeData();
        }

        // Probe Classification Reset Barrier(s)
        if (!barriers.empty())
        {
            // Wait for the compute pass to complete
            rs->resourceBarrier(0, nullptr, barriers.size(), barriers.data(), 0, nullptr, QUEUE_TYPE_COMPUTE);
        }

        barriers.clear();

        // Probe Classification
        for (volumeIndex = 0; volumeIndex < numVolumes; volumeIndex++)
        {
            // Get the volume
            const DDGIVolume* volume = volumes[volumeIndex];
            if (!volume->GetProbeClassificationEnabled()) continue;  // Skip if classification is not enabled for this volume

            // Probe classification
            const float groupSizeX = 32.f;
            uint32_t numGroupsX = (uint32_t)ceil((float)volume->GetNumProbes() / groupSizeX);

            Handle<HwComputeProgram> programHandle = volume->GetProbeClassificationModule();
            Handle<HwDescriptorSet> descSet = volume->GetProbeClassificationDescriptorSet();
            rs->bindComputePipeline(programHandle, &descSet, 1);
            rs->dispatchComputeShader(numGroupsX, 1, 1);

            // Add a barrier
            barriers.emplace_back();
            barriers.back().pTexture = volume->GetProbeData();
        }

        // Probe Classification Barrier(s)
        if (!barriers.empty())
        {
            // Wait for the compute pass to complete
            rs->resourceBarrier(0, nullptr, barriers.size(), barriers.data(), 0, nullptr, QUEUE_TYPE_COMPUTE);
        }
        return ERTXGIStatus::OK;
    }

    ERTXGIStatus CalculateDDGIVolumeVariability(uint32_t numVolumes, DDGIVolume** volumes)
    {
        auto* rs = Ogre::Root::getSingleton().getRenderSystem();
        uint32_t volumeIndex;
        std::vector<TextureBarrier> barriers;

        // Reduction
        for (volumeIndex = 0; volumeIndex < numVolumes; volumeIndex++)
        {
            const DDGIVolume* volume = volumes[volumeIndex];
            if (!volume->GetProbeVariabilityEnabled()) continue;  // Skip if the volume is not calculating variability

            // Get the number of probes on the XYZ dimensions of the texture
            uint32_t probeCountX, probeCountY, probeCountZ;
            GetDDGIVolumeProbeCounts(volume->GetDesc(), probeCountX, probeCountY, probeCountZ);

            // Initially, the reduction input is the full variability size (same as irradiance texture)
            uint32_t inputTexelsX = probeCountX * volume->GetDesc().probeNumIrradianceInteriorTexels;
            uint32_t inputTexelsY = probeCountY * volume->GetDesc().probeNumIrradianceInteriorTexels;
            uint32_t inputTexelsZ = probeCountZ;

            const uint32_t NumThreadsInGroup[3] = {4, 8, 4}; // Each thread group will have 8x8x8 threads
            constexpr uint32_t ThreadSampleFootprint[2] = {4, 2}; // Each thread will sample 4x2 texels

            // Set push constants
            DDGIRootConstants consts = volume->GetPushConstants();

            // First pass reduction takes probe irradiance data and calculates variability, reduces as much as possible
            {
                // One thread group per output texel
                uint32_t outputTexelsX = (uint32_t)ceil((float)inputTexelsX / (float)(NumThreadsInGroup[0] * ThreadSampleFootprint[0]));
                uint32_t outputTexelsY = (uint32_t)ceil((float)inputTexelsY / (float)(NumThreadsInGroup[1] * ThreadSampleFootprint[1]));
                uint32_t outputTexelsZ = (uint32_t)ceil((float)inputTexelsZ / (float)NumThreadsInGroup[2]);

                consts.reductionInputSizeX = inputTexelsX;
                consts.reductionInputSizeY = inputTexelsY;
                consts.reductionInputSizeZ = inputTexelsZ;

                Handle<HwComputeProgram> programHandle = volume->GetProbeVariabilityReductionModule();
                Handle<HwDescriptorSet> descSet = volume->GetProbeVariabilityReductionDescriptorSet();
                rs->bindComputePipeline(programHandle, &descSet, 1);
                rs->dispatchComputeShader(outputTexelsX, outputTexelsY, outputTexelsZ);

                // Each thread group will write out a value to the averaging texture
                // If there is more than one thread group, we will need to do extra averaging passes
                inputTexelsX = outputTexelsX;
                inputTexelsY = outputTexelsY;
                inputTexelsZ = outputTexelsZ;
            }
            
            // UAV barrier needed after each reduction pass
            barriers.emplace_back();
            barriers.back().pTexture = volume->GetProbeVariabilityAverage();
            rs->resourceBarrier(0, nullptr, barriers.size(), barriers.data(), 0, nullptr, QUEUE_TYPE_COMPUTE);

            // Extra reduction passes average values in variability texture down to single value
            while (inputTexelsX > 1 || inputTexelsY > 1 || inputTexelsZ > 1)
            {
                // One thread group per output texel
                uint32_t outputTexelsX = (uint32_t)ceil((float)inputTexelsX / (float)(NumThreadsInGroup[0] * ThreadSampleFootprint[0]));
                uint32_t outputTexelsY = (uint32_t)ceil((float)inputTexelsY / (float)(NumThreadsInGroup[1] * ThreadSampleFootprint[1]));
                uint32_t outputTexelsZ = (uint32_t)ceil((float)inputTexelsZ / (float)NumThreadsInGroup[2]);

                consts.reductionInputSizeX = inputTexelsX;
                consts.reductionInputSizeY = inputTexelsY;
                consts.reductionInputSizeZ = inputTexelsZ;

                Handle<HwComputeProgram> programHandle = volume->GetProbeVariabilityExtraReductionModule();
                Handle<HwDescriptorSet> descSet = volume->GetProbeVariabilityExtraReductionDescriptorSet();
                rs->bindComputePipeline(programHandle, &descSet, 1);
                rs->dispatchComputeShader(outputTexelsX, outputTexelsY, outputTexelsZ);

                inputTexelsX = outputTexelsX;
                inputTexelsY = outputTexelsY;
                inputTexelsZ = outputTexelsZ;

                // Need a barrier in between each reduction pass
                rs->resourceBarrier(0, nullptr, barriers.size(), barriers.data(), 0, nullptr, QUEUE_TYPE_COMPUTE);
            }
        }

        // Copy readback buffer
        {
           
            for (volumeIndex = 0; volumeIndex < numVolumes; volumeIndex++)
            {
                const DDGIVolume* volume = volumes[volumeIndex];
                if (!volume->GetProbeVariabilityEnabled()) continue;  // Skip if the volume is not calculating variability
                barriers.emplace_back();
                barriers.back().pTexture = volume->GetProbeVariabilityAverage();
            }

            if (!barriers.empty())
            {
                rs->resourceBarrier(0, nullptr, barriers.size(), barriers.data(), 0, nullptr, QUEUE_TYPE_COMPUTE);

                barriers.clear();
            }

            std::vector<BufferBarrier> bufferBarriers;

            for (volumeIndex = 0; volumeIndex < numVolumes; volumeIndex++)
            {
                const DDGIVolume* volume = volumes[volumeIndex];
                if (!volume->GetProbeVariabilityEnabled()) continue;  // Skip if the volume is not calculating variability
                Extent3D extent = { 1, 1, 1 };
                rs->copyImageToBuffer(
                    volume->GetProbeVariabilityAverage(),
                    volume->GetProbeVariabilityReadback(),
                    extent);
                barriers.emplace_back();
                barriers.back().pTexture = volume->GetProbeVariabilityAverage();
            }

            if (!barriers.empty())
            {
                rs->resourceBarrier(0, nullptr, barriers.size(), barriers.data(), 0, nullptr, QUEUE_TYPE_COMPUTE);
                barriers.clear();
            }
        }
        return ERTXGIStatus::OK;
    }

    ERTXGIStatus ReadbackDDGIVolumeVariability(uint32_t numVolumes, DDGIVolume** volumes)
    {
        auto* rs = Ogre::Root::getSingleton().getRenderSystem();

        for (uint32_t volumeIndex = 0; volumeIndex < numVolumes; volumeIndex++)
        {
            // Get the volume
            DDGIVolume* volume = volumes[volumeIndex];
            if (!volume->GetProbeVariabilityEnabled()) continue;  // Skip if the volume is not calculating variability

            // Get the probe variability readback buffer
            Handle<HwBufferObject> readbackHandle = volume->GetProbeVariabilityReadback();

            float value;
            rs->getBufferObject(readbackHandle, (const char*)& value, sizeof(value));
            volume->SetVolumeAverageVariability(value);
        }
        return ERTXGIStatus::OK;
    }

    //------------------------------------------------------------------------
    // Private DDGIVolume Functions
    //------------------------------------------------------------------------
    void DDGIVolume::StoreUnmanagedResourcesDesc(const DDGIVolumeUnmanagedResourcesDesc& unmanaged)
    {
        // Texture Arrays
        m_probeRayData = unmanaged.probeRayData;
        m_probeIrradiance = unmanaged.probeIrradiance;
        m_probeDistance = unmanaged.probeDistance;
        m_probeData = unmanaged.probeData;
        m_probeVariability = unmanaged.probeVariability;
        m_probeVariabilityAverage = unmanaged.probeVariabilityAverage;
        m_probeVariabilityReadback = unmanaged.probeVariabilityReadback;
    }

    //------------------------------------------------------------------------
    // Public DDGIVolume Functions
    //------------------------------------------------------------------------

    ERTXGIStatus DDGIVolume::Create(const DDGIVolumeDesc& desc, const DDGIVolumeResources& resources)
    {
        // Validate the probe counts
        if (desc.probeCounts.x <= 0 || desc.probeCounts.y <= 0 || desc.probeCounts.z <= 0) return ERTXGIStatus::ERROR_DDGI_INVALID_PROBE_COUNTS;

        // Validate the resource indices buffer (when necessary)
        if(resources.bindless.enabled)
        {
            if(!resources.bindless.resourceIndicesBuffer)
                return ERTXGIStatus::ERROR_DDGI_INVALID_RESOURCE_INDICES_BUFFER;
        }

        // Validate the constants buffer
        if (!resources.constantsBuffer) 
            return ERTXGIStatus::ERROR_DDGI_INVALID_CONSTANTS_BUFFER;

        // Validate the resource structures
        if (resources.managed.enabled && resources.unmanaged.enabled) 
            return ERTXGIStatus::ERROR_DDGI_INVALID_RESOURCES_DESC;
        if (!resources.managed.enabled && !resources.unmanaged.enabled) 
            return ERTXGIStatus::ERROR_DDGI_INVALID_RESOURCES_DESC;

        // Validate the resources
        ERTXGIStatus result = ERTXGIStatus::OK;
        result = ValidateUnmanagedResourcesDesc(resources.unmanaged);

        assert_invariant(result == ERTXGIStatus::OK);
        
        // Store the bindless resources descriptor
        m_bindlessResources = resources.bindless;

        // Store the push constants offset
        m_pushConstantsOffset = resources.bindless.pushConstantsOffset;

        // Store the bindless resources descriptor
        m_bindlessResources = resources.bindless;

        // Store the constants structured buffer pointers and size
        if (resources.constantsBuffer) m_constantsBuffer = resources.constantsBuffer;
        m_constantsBufferSizeInBytes = resources.constantsBufferSizeInBytes;

        // Allocate or store pointers to the pipeline layout, descriptor set, textures, and pipelines
        StoreUnmanagedResourcesDesc(resources.unmanaged);

        // Store the new volume descriptor
        m_desc = desc;

        // Vulkan only: Force relocation reset in case the allocated memory isn't zeroed
        if(m_desc.probeRelocationEnabled) m_desc.probeRelocationNeedsReset = true;

        // Store the volume rotation
        m_rotationMatrix = EulerAnglesToRotationMatrix(desc.eulerAngles);

        m_rotationQuaternion.FromRotationMatrix(m_rotationMatrix);
        // Set the default scroll anchor to the origin
        m_probeScrollAnchor = m_desc.origin;

        // Initialize the random number generator if a seed is provided,
        // otherwise the RNG uses the default std::random_device().
        if (desc.rngSeed != 0)
        {
            SeedRNG((int)desc.rngSeed);
        }
        else
        {
            std::random_device rd;
            SeedRNG((int)rd());
        }

        return ERTXGIStatus::OK;
    }

    ERTXGIStatus DDGIVolume::ClearProbes()
    {
        auto* rs = Ogre::Root::getSingleton().getRenderSystem();
 
        uint32_t width, height, arraySize;
        GetDDGIVolumeProbeCounts(m_desc, width, height, arraySize);

        Ogre::Vector4 color(0.f, 0.f, 0.f, 1.f);
        rs->clearRenderTexture(m_probeIrradiance, color);
        rs->clearRenderTexture(m_probeDistance, color);


        return ERTXGIStatus::OK;
    }

    void DDGIVolume::Destroy()
    {
        m_bindlessResources = {};

        auto* rs = Ogre::Root::getSingleton().getRenderSystem();
        rs->destroyBufferObject(m_constantsBuffer);
    
        m_constantsBufferSizeInBytes = 0;

        m_desc = {};

        m_rotationQuaternion = { 0.f, 0.f, 0.f, 1.f };
        m_rotationMatrix = {
             1.f, 0.f, 0.f ,
             0.f, 1.f, 0.f ,
             0.f, 0.f, 1.f 
        };
        m_probeRayRotationQuaternion = { 0.f, 0.f, 0.f, 1.f };
        m_probeRayRotationMatrix = {
             1.f, 0.f, 0.f ,
             0.f, 1.f, 0.f ,
             0.f, 0.f, 1.f 
        };

        m_probeScrollOffsets = {};
    }

    uint32_t DDGIVolume::GetGPUMemoryUsedInBytes() const
    {
        uint32_t bytesPerVolume = DDGIVolumeBase::GetGPUMemoryUsedInBytes();

        if (m_bindlessResources.enabled)
        {
            // Add the memory used for the GPU-side DDGIVolumeResourceIndices (32B)
            bytesPerVolume += (uint32_t)sizeof(DDGIVolumeResourceIndices);
        }

        return bytesPerVolume;
    }

