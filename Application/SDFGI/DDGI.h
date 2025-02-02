#pragma once
#include <DriverBase.h>
#include "ddgiTypes.h"
#include "SDFGIContext.h"
#include "Configs.h"
#include "DDGIVolumeImpl.h"

class DDGIPass: public PassBase
{
public:
    DDGIPass(SDFGIContext& context);
    virtual bool initialize();
    virtual void update(float delta);
    virtual void execute(RenderSystem* rs);
private:
    bool loadAndCompileShaders();

    void updateDescriptorSet();

    bool CreateDDGIVolumeResourceIndicesBuffer(uint32_t volumeCount);
    bool CreateDDGIVolumeConstantsBuffer(uint32_t volumeCount);
    bool CreateDDGIVolume(
        const Configs::DDGIVolume& volumeConfig);

    void DestroyDDGIVolumeResources(DDGIVolumeBase* volume);

    void GetDDGIVolumeDesc(const Configs::DDGIVolume& config, DDGIVolumeDesc& volumeDesc);

    bool GetDDGIVolumeResources(
        const DDGIVolumeDesc& volumeDesc,
        DDGIVolumeResources& volumeResources);
    void CompileDDGIVolumeShaders(const DDGIVolumeDesc& volumeDesc);
    void AddCommonShaderDefines(ShaderInfo& shaderInfo, const DDGIVolumeDesc& volumeDesc, bool spirv);
    bool CreateDDGIVolumeResources(
        const DDGIVolumeDesc& volumeDesc,
        DDGIVolumeResources& volumeResources);
private:
    Handle<HwRaytracingProgram> mProgramHandle;
    std::vector< Handle<HwDescriptorSet>> setlist;
    Handle<HwDescriptorSet> mProbeTracingZeroSet;
    Handle<HwDescriptorSet> mProbeTracingFirstSet;
    Handle<HwDescriptorSet> mProbeTracingSecondSet;
    Handle<HwDescriptorSet> mProbeTracingThirdSet;

    SDFGIContext& mContext;

    

    Handle<HwComputeProgram> mProbeBlendingIrradianceHandle;
    Handle<HwComputeProgram> mProbeBlendingDistanceHandle;

    Handle<HwComputeProgram> mProbeRelocationUpdateHandle;
    Handle<HwComputeProgram> mProbeRelocationResetHandle;

    Handle<HwComputeProgram> mProbeClassificationUpdateHandle;
    Handle<HwComputeProgram> mProbeClassificationResetHandle;

    Handle<HwComputeProgram> mProbeVariabilityReductionHandle;
    Handle<HwComputeProgram> mProbeExtraReductionHandle;


    /////
    // Shader Modules
    Handle<HwComputeProgram> probeBlendingIrradianceModule;             // Probe blending (irradiance) shader module
    Handle<HwComputeProgram> probeBlendingDistanceModule;               // Probe blending (distance) shader module

    // Pipelines
    Handle<HwPipeline> probeBlendingIrradiancePipeline;           // Probe blending (irradiance) compute pipeline
    Handle<HwPipeline> probeBlendingDistancePipeline;             // Probe blending (distance) compute pipeline

    ProbeRelocationPipeline     probeRelocation;                                     // Probe Relocation pipelines
    ProbeClassificationPipeline probeClassification;                                 // Probe Classification pipelines
    ProbeVariabilityPipeline    probeVariabilityPipelines;                           // Probe Variability pipelines
};