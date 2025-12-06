#pragma once
#include <DriverBase.h>
#include "ddgiTypes.h"
#include "GIContext.h"
#include "Configs.h"
#include "DDGIVolumeImpl.h"

class DDGIPass: public PassBase
{
public:
    DDGIPass(SDFGIContext& context);
    virtual bool initialize(RenderContext& context);
    virtual void update(float delta);
    virtual void execute(RenderContext& context);
private:
    bool loadAndCompileShaders();
    void loadIndirectShader();
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
    struct DDGIFrameData
    {
        Handle<HwDescriptorSet> probeTracingZeroSet;
        Handle<HwDescriptorSet> blendingIrradianceDescriptorSet;
        Handle<HwDescriptorSet> blendingDistanceDescriptorSet;
        Handle<HwComputeProgram> probeRelocationResetHandle;
        Handle<HwComputeProgram> probeClassificationResetHandle;
        Handle<HwComputeProgram> probeExtraReductionHandle;
        Handle<HwDescriptorSet> mIndirectZeroSet;
    };

    std::vector<DDGIFrameData> mDDGIFrameDatas;
    Handle<HwRaytracingProgram> mProbeTracingHandle;

    Handle<HwComputeProgram> mIndirectHandle;
    
    


    SDFGIContext& mContext;

    

    Handle<HwComputeProgram> mProbeBlendingIrradianceHandle;
    

    Handle<HwComputeProgram> mProbeBlendingDistanceHandle;
    

    Handle<HwComputeProgram> mProbeRelocationUpdateHandle;
    

    Handle<HwComputeProgram> mProbeClassificationUpdateHandle;
    

    Handle<HwComputeProgram> mProbeVariabilityReductionHandle;
    

    

};