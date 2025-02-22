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
    void updateDescriptorSetOfComputeShader();

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
    Handle<HwDescriptorSet> mProbeTracingZeroSet;
    Handle<HwComputeProgram> mIndirectHandle;
    Handle<HwDescriptorSet> mIndirectZeroSet;
    


    SDFGIContext& mContext;

    

    Handle<HwComputeProgram> mProbeBlendingIrradianceHandle;
    Handle<HwDescriptorSet> mBlendingIrradianceDescriptorSet;

    Handle<HwComputeProgram> mProbeBlendingDistanceHandle;
    Handle<HwDescriptorSet> mBlendingDistanceDescriptorSet;

    Handle<HwComputeProgram> mProbeRelocationUpdateHandle;
    Handle<HwComputeProgram> mProbeRelocationResetHandle;

    Handle<HwComputeProgram> mProbeClassificationUpdateHandle;
    Handle<HwComputeProgram> mProbeClassificationResetHandle;

    Handle<HwComputeProgram> mProbeVariabilityReductionHandle;
    Handle<HwComputeProgram> mProbeExtraReductionHandle;

    

};