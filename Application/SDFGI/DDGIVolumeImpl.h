
#pragma once
#include <OgreHeader.h>
#include "DDGIVolume.h"
#include "DriverBase.h"
#include "ddgiTypes.h"
#include "DDGIRootConstants.h"


enum class EResourceViewType
{
    UAV = 0,
    SRV,
    COUNT
};

enum class EDDGIVolumeBindings
{
    Constants = 0,
    RayData,
    ProbeIrradiance,
    ProbeDistance,
    ProbeData,
    ProbeVariability,
    ProbeVariabilityAverage
};

//------------------------------------------------------------------------
// Managed Resource Mode (SDK manages volume resources)
//------------------------------------------------------------------------

struct ProbeRelocationBytecode
{
    std::string updateCS;                                           // Probe relocation compute shader bytecode
     
    std::string resetCS;                                            // Probe relocation reset compute shader bytecode
};

struct ProbeClassificationBytecode
{
    std::string updateCS;                                           // Probe classification compute shader bytecode
    std::string resetCS;                                            // Probe classification reset compute shader bytecode
};

struct ProbeVariabilityByteCode
{
    std::string reductionCS;                                       // Probe variability reduction compute shader bytecode
    std::string extraReductionCS;                                  // Probe variability reduction extra passes compute shader bytecode
};

struct DDGIVolumeManagedResourcesDesc
{
    bool                         enabled = false;                                    // Enable or disable managed resources mode
    // Shader bytecode
    std::string probeBlendingIrradianceCS;                          // Probe blending (irradiance) compute shader bytecode
    std::string probeBlendingDistanceCS;                            // Probe blending (distance) compute shader bytecode

    ProbeRelocationBytecode      probeRelocation;                                    // Probe Relocation bytecode
    ProbeClassificationBytecode  probeClassification;                                // Probe Classification bytecode
    ProbeVariabilityByteCode     probeVariability;                                   // Probe Classification bytecode
};

//------------------------------------------------------------------------
// Unmanaged Resource Mode (Application manages volume resources)
//------------------------------------------------------------------------

struct ProbeRelocationPipeline
{
    Handle<HwComputeProgram> updateModule;                             // Probe relocation shader module
    Handle<HwComputeProgram> resetModule;                              // Probe relocation reset shader module

    Handle<HwPipeline> updatePipeline;                           // Probe relocation compute pipeline
    Handle<HwPipeline> resetPipeline;                            // Probe relocation reset compute pipeline
};

struct ProbeClassificationPipeline
{
    Handle<HwComputeProgram> updateModule;                             // Probe classification shader module
    Handle<HwComputeProgram> resetModule;                              // Probe classification reset shader module

    Handle<HwPipeline> updatePipeline;                           // Probe classification compute pipeline
    Handle<HwPipeline> resetPipeline;                            // Probe classification reset compute pipeline
};

struct ProbeVariabilityPipeline
{
    Handle<HwComputeProgram> reductionModule;                          // Probe variability reduction shader module
    Handle<HwComputeProgram> extraReductionModule;                     // Probe variability reduction extra passes shader module

    Handle<HwPipeline> reductionPipeline;                        // Probe variability reduction compute pipeline
    Handle<HwPipeline> extraReductionPipeline;                   // Probe variability extra reduction compute pipeline
};

struct DDGIVolumeUnmanagedResourcesDesc
{
    bool                        enabled = false;                                    // Enable or disable unmanaged resources mode

    // Texture Resources
    OgreTexture* probeRayData = nullptr;                             // Probe ray data texture array - RGB: radiance | A: hit distance
    OgreTexture* probeIrradiance = nullptr;                          // Probe irradiance texture array - RGB: irradiance, encoded with a high gamma curve
    OgreTexture* probeDistance = nullptr;                            // Probe distance texture array - R: mean distance | G: mean distance^2
    OgreTexture* probeData = nullptr;                                // Probe data texture array - XYZ: world-space relocation offsets | W: classification state
    OgreTexture* probeVariability = nullptr;                         // Probe variability texture array
    OgreTexture* probeVariabilityAverage = nullptr;                  // Average of Probe variability for whole volume
    Handle<HwBufferObject> probeVariabilityReadback;                 // CPU-readable resource containing final Probe variability average

};

//------------------------------------------------------------------------

struct DDGIVolumeBindlessResourcesDesc
{
    // Specifies if bindless resources are used
    bool                        enabled;                                      
    // Offset to the DDGIConsts data in the push constants block
    int  pushConstantsOffset = 0;                      
    // Indices of volume resources in bindless resource arrays
    DDGIVolumeResourceIndices   resourceIndices;                              
    // Resource indices structured buffer 
    Handle<HwBufferObject> resourceIndicesBuffer;              
    // [Optional] Size (in bytes) of the constants structured buffer
    uint64_t                    resourceIndicesBufferSizeInBytes = 0;         
};

/**
    * Specifies the resources used by the DDGIVolume.
    */
struct DDGIVolumeResources
{
    // [Optional] Specifies properties of bindless resources
    DDGIVolumeBindlessResourcesDesc   bindless; 
    // [Managed Resource Mode] Provides Vulkan device handles and compiled shader bytecode.
    DDGIVolumeManagedResourcesDesc    managed;             
    // [Unmanaged Resource Mode] Provides a pipeline layout, descriptor set, and pointers to texture resources and pipelines.
    DDGIVolumeUnmanagedResourcesDesc  unmanaged;                                   
    // Constants structured buffer (device)
    Handle<HwBufferObject>                constantsBuffer;                             
    // [Optional] Size (in bytes) of the constants structured buffer
    uint64_t                constantsBufferSizeInBytes = 0;                         
};


//------------------------------------------------------------------------
// DDGIVolume
//------------------------------------------------------------------------

/**
    * DDGIVolume
    * A volume within which irradiance queries at arbitrary points are supported using a grid
    * of probes. A single DDGIVolume may cover the entire scene or some sub-volume of the scene.
    *
    * The probe grid of the volume is centered around the provided origin. Grid probes are numbered
    * in ascending order from left to right, back to front (in a left handed coordinate system).
    *
    * If there are parts of a scene with very different geometric density or dimensions, use
    * multiple DDGIVolumes with varying probe densities.
    */
class  DDGIVolume : public DDGIVolumeBase
{
public:
    /**
        * Performs other initialization of the DDGIVolume
        * Validates resource pointers or allocates resources if resource management is enabled
        */
    ERTXGIStatus Create(const DDGIVolumeDesc& desc, const DDGIVolumeResources& resources);

    /**
        * Clears the volume's probe texture arrays
        */
    ERTXGIStatus ClearProbes();

    /**
        * Releases resources owned by the volume
        */
    void Destroy();

    //------------------------------------------------------------------------
    // Resource Getters
    //------------------------------------------------------------------------

    // Stats
    uint32_t GetGPUMemoryUsedInBytes() const;


    bool GetBindlessEnabled() const { return m_bindlessResources.enabled; }


    // Push Constants
    uint32_t GetPushConstantsOffset() const { return m_pushConstantsOffset; }
    DDGIRootConstants GetPushConstants() const { return { m_desc.index, 0, 0, 0, 0, 0 }; }

    // Resource Indices (Bindless)
    DDGIVolumeResourceIndices GetResourceIndices() const { return m_bindlessResources.resourceIndices; }
    Handle<HwBufferObject> GetResourceIndicesBuffer() const
    { 
        return m_bindlessResources.resourceIndicesBuffer; 
    }
    uint64_t GetResourceIndicesBufferSizeInBytes() const { return m_bindlessResources.resourceIndicesBufferSizeInBytes; }

    // Constants
    Handle<HwBufferObject> GetConstantsBuffer() const 
    { 
        return m_constantsBuffer; 
    }
    uint64_t GetConstantsBufferSizeInBytes() const { return m_constantsBufferSizeInBytes; }

    // Texture Arrays Format
    EDDGIVolumeTextureFormat GetRayDataFormat() const { return m_desc.probeRayDataFormat; }
    EDDGIVolumeTextureFormat GetIrradianceFormat() const { return m_desc.probeIrradianceFormat; }
    EDDGIVolumeTextureFormat GetDistanceFormat() const { return m_desc.probeDistanceFormat; }
    EDDGIVolumeTextureFormat GetProbeDataFormat() const { return m_desc.probeDataFormat; }
    EDDGIVolumeTextureFormat GetProbeVariabilityFormat() const { return m_desc.probeVariabilityFormat; }

    // Texture Arrays
    OgreTexture* GetProbeRayData() const { 
        return m_probeRayData; 
    }
    OgreTexture* GetProbeIrradiance() const { 
        return m_probeIrradiance; 
    }
    OgreTexture* GetProbeDistance() const { 
        return m_probeDistance; 
    }
    OgreTexture* GetProbeData() const { return m_probeData; }
    OgreTexture* GetProbeVariability() const { return m_probeVariability; }
    OgreTexture* GetProbeVariabilityAverage() const { return m_probeVariabilityAverage; }
    Handle<HwBufferObject> GetProbeVariabilityReadback() const { return m_probeVariabilityReadback; }

    // Shader Modules
    Handle<HwComputeProgram> GetProbeBlendingIrradianceModule() const
    { 
        return m_probeBlendingIrradianceModule; 
    }
    Handle<HwComputeProgram> GetProbeBlendingDistanceModule() const
    { 
        return m_probeBlendingDistanceModule; 
    }
    Handle<HwComputeProgram> GetProbeRelocationModule() const
    { 
        return m_probeRelocationModule; 
    }
    Handle<HwComputeProgram> GetProbeRelocationResetModule() const
    { 
        return m_probeRelocationResetModule; 
    }
    Handle<HwComputeProgram> GetProbeClassificationModule() const
    { 
        return m_probeClassificationModule; 
    }
    Handle<HwComputeProgram> GetProbeClassificationResetModule() const
    { 
        return m_probeClassificationResetModule; 
    }
    Handle<HwComputeProgram> GetProbeVariabilityReductionModule() const
    { 
        return m_probeVariabilityReductionModule; 
    }
    Handle<HwComputeProgram> GetProbeVariabilityExtraReductionModule() const
    { 
        return m_probeVariabilityExtraReductionModule; 
    }


    Handle<HwDescriptorSet> GetProbeBlendingIrradianceDescriptorSet() const
    {
        return m_probeBlendingIrradianceDescSet;
    }


    Handle<HwDescriptorSet> GetProbeBlendingDistanceDescriptorSet() const
    {
        return m_probeBlendingDistanceDescSet;
    }


    Handle<HwDescriptorSet> GetProbeRelocationDescriptorSet() const
    {
        return m_probeRelocationDescSet;
    }


    Handle<HwDescriptorSet> GetProbeRelocationResetDescriptorSet() const
    {
        return m_probeRelocationResetDescSet;
    }

    Handle<HwDescriptorSet> GetProbeClassificationDescriptorSet() const
    {
        return m_probeClassificationDescSet;
    }

    Handle<HwDescriptorSet> GetProbeClassificationResetDescriptorSet() const
    {
        return m_probeClassificationResetDescSet;
    }


    Handle<HwDescriptorSet> GetProbeVariabilityReductionDescriptorSet() const
    {
        return m_probeVariabilityReductionDescSet;
    }


    Handle<HwDescriptorSet> GetProbeVariabilityExtraReductionDescriptorSet() const
    {
        return m_probeVariabilityExtraReductionDescSet;
    }
    //------------------------------------------------------------------------
    // Resource Setters
    //------------------------------------------------------------------------

    // Push Constants
    void SetPushConstantsOffset(uint32_t offset) 
    { 
        m_pushConstantsOffset = offset; 
    }

    // Resource Indices (Bindless)
    void SetResourceIndices(DDGIVolumeResourceIndices resourceIndices) 
    { 
        m_bindlessResources.resourceIndices = resourceIndices; 
    }
    void SetResourceIndicesBuffer(Handle<HwBufferObject> indicesBuffer)
    { 
        m_bindlessResources.resourceIndicesBuffer = indicesBuffer;
    }


    void SetResourceIndicesBufferSizeInBytes(uint64_t size) 
    { 
        m_bindlessResources.resourceIndicesBufferSizeInBytes = size; 
    }

    // Constants
    void SetConstantsBuffer(Handle<HwBufferObject> constantsBuffer) 
    { 
        m_constantsBuffer = constantsBuffer;
    }

    void SetConstantsBufferSizeInBytes(uint64_t value) 
    { 
        m_constantsBufferSizeInBytes = value; 
    }

    // Texture Array Format
    void SetRayDataFormat(EDDGIVolumeTextureFormat format)
    { 
        m_desc.probeRayDataFormat = format; 
    }
    void SetIrradianceFormat(EDDGIVolumeTextureFormat format)
    { 
        m_desc.probeIrradianceFormat = format; 
    }
    void SetDistanceFormat(EDDGIVolumeTextureFormat format)
    { 
        m_desc.probeDistanceFormat = format; 
    }
    void SetProbeDataFormat(EDDGIVolumeTextureFormat format)
    { 
        m_desc.probeDataFormat = format; 
    }
    void SetProbeVariabilityFromat(EDDGIVolumeTextureFormat format)
    { 
        m_desc.probeVariabilityFormat = format; 
    }

    void SetProbeRayData(OgreTexture* rayData)
    {
        m_probeRayData = rayData;
    }

    void SetProbeIrradiance(OgreTexture* irradiance) 
    { 
        m_probeIrradiance = irradiance;
    }
    void SetProbeDistance(OgreTexture* distance)
    { 
        m_probeDistance = distance;
    }
    void SetProbeData(OgreTexture* probeData) 
    { 
        m_probeData = probeData;
    }
    void SetProbeVariability(OgreTexture* variability) 
    { 
        m_probeVariability = variability;
    }
    void SetProbeVariabilityAverage(OgreTexture* variabilityAverage) 
    { 
        m_probeVariabilityAverage = variabilityAverage;
    }
    void SetProbeVariabilityReadback(Handle<HwBufferObject> variabilityReadback) 
    { 
        m_probeVariabilityReadback = variabilityReadback;
    }

private:
    // Volume Constants (if you use UploadDDGIVolumeConstants() to transfer constants to the GPU)
    // Structured buffer that stores the volume's constants (device)
    Handle<HwBufferObject> m_constantsBuffer; 
    // Size (in bytes) of the structured buffer that stores constants for *all* volumes
    uint64_t                        m_constantsBufferSizeInBytes = 0;                   

    // Texture Arrays
    OgreTexture* m_probeRayData = nullptr;                           // Probe ray data texture array - RGB: radiance | A: hit distance
    OgreTexture* m_probeIrradiance = nullptr;                        // Probe irradiance texture array - RGB: irradiance, encoded with a high gamma curve
    OgreTexture* m_probeDistance = nullptr;                          // Probe distance texture array - R: mean distance | G: mean distance^2
    OgreTexture* m_probeData = nullptr;                              // Probe data texture array - XYZ: world-space relocation offsets | W: classification state
    OgreTexture* m_probeVariability = nullptr;                       // Probe variability texture
    OgreTexture* m_probeVariabilityAverage = nullptr;                // Probe variability average texture
    Handle<HwBufferObject> m_probeVariabilityReadback;               // Probe variability readback buffer

    // Descriptors
    Handle<HwDescriptorSet> mDescriptorSet;
    // Push Constants
    uint32_t                        m_pushConstantsOffset = 0;                          // Offset in the push constants block to DDGIRootConstants

    // Bindless
    DDGIVolumeBindlessResourcesDesc m_bindlessResources = {};                           // Properties associated with bindless resources

    // Shader Modules
    // Probe blending (irradiance) shader module
    Handle<HwComputeProgram> m_probeBlendingIrradianceModule; 
    // Probe blending (distance) shader module
    Handle<HwComputeProgram> m_probeBlendingDistanceModule;
    // Probe relocation shader module
    Handle<HwComputeProgram> m_probeRelocationModule;
    // Probe relocation reset shader module
    Handle<HwComputeProgram> m_probeRelocationResetModule;
    // Probe classification shader module
    Handle<HwComputeProgram> m_probeClassificationModule;
    // Probe classification reset shader module
    Handle<HwComputeProgram> m_probeClassificationResetModule;
    // Probe variability reduction shader module
    Handle<HwComputeProgram> m_probeVariabilityReductionModule;
    // Probe variability reduction extra passes shader module
    Handle<HwComputeProgram> m_probeVariabilityExtraReductionModule;

    // Pipelines
    // Probe blending (irradiance) compute shader pipeline
    Handle<HwPipeline> m_probeBlendingIrradiancePipeline;
    Handle<HwDescriptorSet> m_probeBlendingIrradianceDescSet;

    // Probe blending (distance) compute shader pipeline
    //Handle<HwPipeline> m_probeBlendingDistancePipeline;
    Handle<HwDescriptorSet> m_probeBlendingDistanceDescSet;
    // Probe relocation compute shader pipeline
    //Handle<HwPipeline> m_probeRelocationPipeline;
    Handle<HwDescriptorSet> m_probeRelocationDescSet;
    // Probe relocation reset compute shader pipeline
    //Handle<HwPipeline> m_probeRelocationResetPipeline;
    Handle<HwDescriptorSet> m_probeRelocationResetDescSet;
    // Probe classification compute shader pipeline
   // Handle<HwPipeline> m_probeClassificationPipeline; 
    Handle<HwDescriptorSet> m_probeClassificationDescSet;
    // Probe classification reset compute shader pipeline
    //Handle<HwPipeline> m_probeClassificationResetPipeline;
    Handle<HwDescriptorSet> m_probeClassificationResetDescSet;
    // Probe variability reduction compute shader pipeline
    //Handle<HwPipeline> m_probeVariabilityReductionPipeline;
    Handle<HwDescriptorSet> m_probeVariabilityReductionDescSet;
    // Probe variability reduction extra passes compute shader pipeline
    //Handle<HwPipeline> m_probeVariabilityExtraReductionPipeline;  
    Handle<HwDescriptorSet> m_probeVariabilityExtraReductionDescSet;
    void StoreUnmanagedResourcesDesc(const DDGIVolumeUnmanagedResourcesDesc& unmanaged);
}; // class DDGIVolume

//------------------------------------------------------------------------
// Public RTXGI Vulkan namespace DDGIVolume Functions
//------------------------------------------------------------------------
struct SDFGIContext;
/**
    * Uploads resource indices for one or more volumes to the GPU.
    * This function is for convenience and isn't necessary if you upload volume resource indices yourself.
    */
ERTXGIStatus UploadDDGIVolumeResourceIndices(
    SDFGIContext* context,
    uint32_t bufferingIndex, 
    uint32_t numVolumes, 
    DDGIVolume** volumes);

/**
    * Uploads constants for one or more volumes to the GPU.
    * This function is for convenience and isn't necessary if you upload volume constants yourself.
    */
ERTXGIStatus UploadDDGIVolumeConstants(
    SDFGIContext* context,
    uint32_t bufferingIndex, 
    uint32_t numVolumes, 
    DDGIVolume** volumes);

/**
    * Updates one or more volume's probes using data in the volume's radiance texture.
    * Probe blending and border update workloads are batched together for better performance.
    */
ERTXGIStatus UpdateDDGIVolumeProbes(uint32_t numVolumes, DDGIVolume** volumes);

/**
    * Adjusts one or more volume's world-space probe positions to avoid them being too close to or inside of geometry.
    * If a volume has the reset flag set, all probe relocation offsets are set to zero before relocation occurs.
    */
ERTXGIStatus RelocateDDGIVolumeProbes(uint32_t numVolumes, DDGIVolume** volumes);

/**
    * Classifies one or more volume's probes as active or inactive based on the hit distance data in the ray data texture.
    * If a volume has the reset flag set, all probes are set to active before classification occurs.
    */
ERTXGIStatus ClassifyDDGIVolumeProbes(uint32_t numVolumes, DDGIVolume** volumes);

/**
    * Calculates average variability for all probes in each provided volume
    */
ERTXGIStatus CalculateDDGIVolumeVariability(uint32_t numVolumes, DDGIVolume** volumes);

/**
    * Reads back average variability for each provided volume, at the time of the call
    */
ERTXGIStatus ReadbackDDGIVolumeVariability(uint32_t numVolumes, DDGIVolume** volumes);

