#include "OgreHeader.h"
#include "DDGI.h"
#include "engine_struct.h"
#include <OgreRoot.h>
#include <OgreRenderTarget.h>
#include"DDGIVolumeImpl.h"
#include <OgreResourceManager.h>

DDGIPass::DDGIPass(SDFGIContext& context)
    :mContext(context)
{

}

bool DDGIPass::initialize()
{
    if (!loadAndCompileShaders())
        return false;
    
    uint32_t numVolumes = mContext.mConfig.ddgi.volumes.size();

    CreateDDGIVolumeResourceIndicesBuffer(numVolumes);
    CreateDDGIVolumeConstantsBuffer(numVolumes);

    
    for (uint32_t volumeIndex = 0; volumeIndex < numVolumes; volumeIndex++)
    {
        Configs::DDGIVolume volumeConfig = mContext.mConfig.ddgi.volumes[volumeIndex];
        if (!CreateDDGIVolume(volumeConfig))
        {
            return false;
        }

        DDGIVolume* volume = static_cast<DDGIVolume*>(mContext.volumes[volumeIndex]);
        volume->ClearProbes();
    }

    updateDescriptorSet();

    setlist.push_back(mProbeTracingZeroSet);
    setlist.push_back(mProbeTracingFirstSet);
    setlist.push_back(mProbeTracingSecondSet);
    setlist.push_back(mProbeTracingThirdSet);

    return true;
}

void DDGIPass::update(float delta)
{

}

void DDGIPass::execute(RenderSystem* rs)
{
    return;
    auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();
    rs->pushGroupMarker("probeTracePass", Ogre::Vector3i(0.0, 0.0, 1.0f));
    rs->bindPipeline(mProgramHandle, setlist.data(), setlist.size());
    rs->traceRay(mProgramHandle, ogreConfig.width, ogreConfig.height, 1);
    rs->popGroupMarker();
}

bool DDGIPass::loadAndCompileShaders()
{
    RaytracingShaderInfo shaderInfo;
    shaderInfo.args.push_back(L"-D __spirv__");
    addMacro(shaderInfo, "HLSL", "1");
    addMacro(shaderInfo, "RAYTRACING", "1");
    addMacro(shaderInfo, "RTXGI_PUSH_CONSTS_TYPE", "2");
    addMacro(shaderInfo, "RTXGI_PUSH_CONSTS_STRUCT_NAME", "GlobalConstants");
    addMacro(shaderInfo, "RTXGI_PUSH_CONSTS_VARIABLE_NAME", "GlobalConst");
    addMacro(shaderInfo, "RTXGI_PUSH_CONSTS_FIELD_DDGI_VOLUME_INDEX_NAME", "ddgi_volumeIndex");
    addMacro(shaderInfo, "RTXGI_PUSH_CONSTS_FIELD_DDGI_REDUCTION_INPUT_SIZE_X_NAME", "ddgi_reductionInputSizeX");
    addMacro(shaderInfo, "RTXGI_PUSH_CONSTS_FIELD_DDGI_REDUCTION_INPUT_SIZE_Y_NAME", "ddgi_reductionInputSizeY");
    addMacro(shaderInfo, "RTXGI_PUSH_CONSTS_FIELD_DDGI_REDUCTION_INPUT_SIZE_Z_NAME", "ddgi_reductionInputSizeZ");
    addMacro(shaderInfo, "RTXGI_BINDLESS_TYPE", "RTXGI_BINDLESS_TYPE_RESOURCE_ARRAYS");
    addMacro(shaderInfo, "RTXGI_COORDINATE_SYSTEM", "RTXGI_COORDINATE_SYSTEM");


    shaderInfo.rayGenShaderName = "ProbeTraceRGS.hlsl";
    shaderInfo.rayGenEntryName = "RayGen";

    shaderInfo.rayClosethitShaderName = "ProbeTraceClosethit.hlsl";
    shaderInfo.rayClosethitEntryName = "CHS_GI";

    shaderInfo.rayMissShaderName = "ProbeTraceMiss.hlsl";
    shaderInfo.rayMissEntryName = "Miss";

    shaderInfo.rayAnyHitShaderName = "ProbeTraceAnyhit.hlsl";
    shaderInfo.rayAnyHitEntryName = "AHS_GI";

    RenderSystem* rs = Ogre::Root::getSingleton().getRenderSystem();

    mProgramHandle = rs->createRaytracingProgram(shaderInfo);

    mProbeTracingZeroSet = rs->createDescriptorSet(mProgramHandle, 0);
    mProbeTracingFirstSet = rs->createDescriptorSet(mProgramHandle, 1);
    mProbeTracingSecondSet = rs->createDescriptorSet(mProgramHandle, 2);
    mProbeTracingThirdSet = rs->createDescriptorSet(mProgramHandle, 3);

    return true;
}

void DDGIPass::updateDescriptorSet()
{
    DescriptorData descriptorData[16];

    descriptorData[0].mCount = 3;
    descriptorData[0].pName = "Samplers";
    descriptorData[0].descriptorType = DESCRIPTOR_TYPE_SAMPLER;
    descriptorData[0].ppSamplers = &mContext.mSamplerHandle[0];

    descriptorData[1].mCount = 1;
    descriptorData[1].pName = "CameraCB";
    descriptorData[1].descriptorType = DESCRIPTOR_TYPE_BUFFER;
    descriptorData[1].ppBuffers = &mContext.mCameraBufferHandle;

    descriptorData[2].mCount = 1;
    descriptorData[2].pName = "Lights";
    descriptorData[2].descriptorType = DESCRIPTOR_TYPE_BUFFER;
    descriptorData[2].ppBuffers = &mContext.mLightBufferHandle;

    descriptorData[3].mCount = 1;
    descriptorData[3].pName = "Materials";
    descriptorData[3].descriptorType = DESCRIPTOR_TYPE_BUFFER;
    descriptorData[3].ppBuffers = &mContext.materialBufferHandle;

    descriptorData[4].mCount = 1;
    descriptorData[4].pName = "TLASInstances";
    descriptorData[4].descriptorType = DESCRIPTOR_TYPE_BUFFER;
    descriptorData[4].ppBuffers = &mContext.pTopAS->instanceDescBuffer;

    descriptorData[5].mCount = 1;
    descriptorData[5].pName = "DDGIVolumes";
    descriptorData[5].descriptorType = DESCRIPTOR_TYPE_BUFFER;
    descriptorData[5].ppBuffers = &mContext.mDDGIVolumeDescGPUPackedHandle;

    descriptorData[6].mCount = 1;
    descriptorData[6].pName = "DDGIVolumeBindless";
    descriptorData[6].descriptorType = DESCRIPTOR_TYPE_BUFFER;
    descriptorData[6].ppBuffers = &mContext.mDDGIVolumeResourceIndicesHandle;

    std::array<OgreTexture*, 7> rwTex2D =
    {
        mContext.mGBufferTargetA->getTarget(),
        mContext.mGBufferTargetB->getTarget(),
        mContext.mGBufferTargetC->getTarget(),
        mContext.mGBufferTargetD->getTarget(),
        mContext.mOutputView->getTarget(),
        nullptr,
        nullptr
    };
    descriptorData[7].mCount = rwTex2D.size();
    descriptorData[7].pName = "RWTex2D";
    descriptorData[7].descriptorType = DESCRIPTOR_TYPE_TEXTURE;
    descriptorData[7].ppTextures = (const OgreTexture**)rwTex2D.data();

    uint32_t numVolumes = mContext.volumes.size();
    std::vector<OgreTexture*> rwTex2DArray;

    uint32_t descriptorIndex = 7;
    
   
    descriptorData[descriptorIndex].mCount = 1;
    descriptorData[descriptorIndex].pName = "TLAS";
    descriptorData[descriptorIndex].descriptorType = DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE;
    descriptorData[descriptorIndex].pAS = mContext.pTopAS;
    descriptorIndex++;

    auto* rs = Ogre::Root::getSingleton().getRenderSystem();
    assert(descriptorIndex <= 16);
    rs->updateDescriptorSet(mProbeTracingZeroSet, descriptorIndex, descriptorData);

    descriptorIndex = 0;
    if (numVolumes > 0)
    {
        rwTex2DArray.clear();
        for (uint32_t volumeIndex = 0; volumeIndex < numVolumes; volumeIndex++)
        {
            // Add the DDGIVolume texture arrays
            const DDGIVolume* volume = static_cast<DDGIVolume*>(mContext.volumes[volumeIndex]);
            rwTex2DArray.push_back(volume->GetProbeRayData());
            rwTex2DArray.push_back(volume->GetProbeIrradiance());
            rwTex2DArray.push_back(volume->GetProbeDistance());
            rwTex2DArray.push_back(volume->GetProbeData());
            rwTex2DArray.push_back(volume->GetProbeVariability());
            rwTex2DArray.push_back(volume->GetProbeVariabilityAverage());
        }
        descriptorData[descriptorIndex].mCount = rwTex2DArray.size();
        descriptorData[descriptorIndex].pName = "RWTex2DArray";
        descriptorData[descriptorIndex].descriptorType = DESCRIPTOR_TYPE_RW_TEXTURE;
        descriptorData[descriptorIndex].ppTextures = (const OgreTexture**)rwTex2DArray.data();
        descriptorIndex++;
    }

    std::vector<OgreTexture*> tex2D;
    tex2D.push_back(nullptr);
    tex2D.push_back(nullptr);

    for (auto tex : mContext.sceneTextureList)
    {
        tex2D.push_back(tex);
    }
    descriptorData[descriptorIndex].mCount = tex2D.size();
    descriptorData[descriptorIndex].pName = "Tex2D";
    descriptorData[descriptorIndex].descriptorType = DESCRIPTOR_TYPE_TEXTURE;
    descriptorData[descriptorIndex].ppTextures = (const OgreTexture**)tex2D.data();
    descriptorIndex++;

    rs->updateDescriptorSet(mProbeTracingFirstSet, descriptorIndex, descriptorData);
    descriptorIndex = 0;
    std::vector<OgreTexture*> tex2DArray;
    if (numVolumes > 0)
    {
        tex2DArray.clear();
        for (uint32_t volumeIndex = 0; volumeIndex < numVolumes; volumeIndex++)
        {
            // Add the DDGIVolume texture arrays
            const DDGIVolume* volume = static_cast<DDGIVolume*>(mContext.volumes[volumeIndex]);
            tex2DArray.push_back(volume->GetProbeRayData());
            tex2DArray.push_back(volume->GetProbeIrradiance());
            tex2DArray.push_back(volume->GetProbeDistance());
            tex2DArray.push_back(volume->GetProbeData());
            tex2DArray.push_back(volume->GetProbeVariability());
            tex2DArray.push_back(volume->GetProbeVariabilityAverage());
        }
        descriptorData[descriptorIndex].mCount = tex2DArray.size();
        descriptorData[descriptorIndex].pName = "Tex2DArray";
        descriptorData[descriptorIndex].descriptorType = DESCRIPTOR_TYPE_RW_TEXTURE;
        descriptorData[descriptorIndex].ppTextures = (const OgreTexture**)tex2DArray.data();
        descriptorIndex++;
    }
    rs->updateDescriptorSet(mProbeTracingSecondSet, descriptorIndex, descriptorData);

    std::vector<Handle<HwBufferObject>> buffers;
    buffers.push_back(mContext.geometryBufferHandle);
    buffers.push_back(mContext.geometryBufferHandle);
    for (uint32_t i = 0; i < mContext.mIndexBufferList.size(); i++)
    {
        buffers.push_back(mContext.mIndexBufferList[i]);
        buffers.push_back(mContext.mVertexBufferList[i]);
    }

    descriptorData[0].mCount = buffers.size();
    descriptorData[0].pName = "ByteAddrBuffer";
    descriptorData[0].descriptorType = DESCRIPTOR_TYPE_RW_BUFFER;
    descriptorData[0].ppBuffers = buffers.data();


    rs->updateDescriptorSet(mProbeTracingThirdSet, 1, descriptorData);
}

bool DDGIPass::CreateDDGIVolumeResourceIndicesBuffer(uint32_t volumeCount)
{
    auto* rs = Ogre::Root::getSingleton().getRenderSystem();
    BufferDesc desc{};
    desc.mBindingType = BufferObjectBinding_Storge;
    desc.mMemoryUsage = RESOURCE_MEMORY_USAGE_CPU_TO_GPU;
    desc.bufferCreationFlags = BUFFER_CREATION_FLAG_ACCELERATION_STRUCTURE_BUILD_INPUT |
        BUFFER_CREATION_FLAG_SHADER_DEVICE_ADDRESS;
    desc.mElementCount = volumeCount * 2;
    desc.mStructStride = sizeof(DDGIVolumeResourceIndices);
    desc.mSize = desc.mElementCount * desc.mStructStride;

    mContext.mDDGIVolumeResourceIndicesHandle = rs->createBufferObject(desc);

    return true;
}

bool DDGIPass::CreateDDGIVolumeConstantsBuffer(uint32_t volumeCount)
{
    auto* rs = Ogre::Root::getSingleton().getRenderSystem();
    BufferDesc desc{};
    desc.mBindingType = BufferObjectBinding_Storge;
    desc.mMemoryUsage = RESOURCE_MEMORY_USAGE_CPU_TO_GPU;
    desc.bufferCreationFlags = BUFFER_CREATION_FLAG_ACCELERATION_STRUCTURE_BUILD_INPUT |
        BUFFER_CREATION_FLAG_SHADER_DEVICE_ADDRESS;
    desc.mStructStride = sizeof(DDGIVolumeDescGPUPacked);
    desc.mElementCount = volumeCount * 2;
    desc.mSize = desc.mStructStride * desc.mElementCount;
    mContext.mDDGIVolumeDescGPUPackedHandle = rs->createBufferObject(desc);
    return true;
}

bool DDGIPass::CreateDDGIVolume(
    const Configs::DDGIVolume& volumeConfig)
{
    if (volumeConfig.index < mContext.volumes.size())
    {
        DDGIVolumeBase* volume = mContext.volumes[volumeConfig.index];
        if (volume)
        {
            DestroyDDGIVolumeResources(volume);
            SAFE_DELETE(volume);
        }
    }
    else
    {
        mContext.volumes.emplace_back();
        mContext.volumeDescs.emplace_back();
    }

    DDGIVolumeDesc& volumeDesc = mContext.volumeDescs[volumeConfig.index];
    GetDDGIVolumeDesc(volumeConfig, volumeDesc);

    DDGIVolumeResources volumeResources;
    GetDDGIVolumeResources(volumeDesc, volumeResources);

    DDGIVolume* volume = new DDGIVolume();

    ERTXGIStatus status = volume->Create(volumeDesc, volumeResources);

    mContext.volumes[volumeConfig.index] = volume;

    return true;
}

void DDGIPass::DestroyDDGIVolumeResources(DDGIVolumeBase* volume)
{

}

void DDGIPass::GetDDGIVolumeDesc(const Configs::DDGIVolume& config, DDGIVolumeDesc& volumeDesc)
{
    volumeDesc.name = config.name.c_str();

    volumeDesc.index = config.index;
    volumeDesc.rngSeed = config.rngSeed;
    volumeDesc.origin = config.origin;
    volumeDesc.eulerAngles = config.eulerAngles;
    volumeDesc.probeSpacing = config.probeSpacing;
    volumeDesc.probeCounts = config.probeCounts;
    volumeDesc.probeNumRays = config.probeNumRays;
    volumeDesc.probeNumIrradianceTexels = config.probeNumIrradianceTexels;
    volumeDesc.probeNumIrradianceInteriorTexels = (config.probeNumIrradianceTexels - 2);
    volumeDesc.probeNumDistanceTexels = config.probeNumDistanceTexels;
    volumeDesc.probeNumDistanceInteriorTexels = (config.probeNumDistanceTexels - 2);
    volumeDesc.probeHysteresis = config.probeHysteresis;
    volumeDesc.probeNormalBias = config.probeNormalBias;
    volumeDesc.probeViewBias = config.probeViewBias;
    volumeDesc.probeMaxRayDistance = config.probeMaxRayDistance;
    volumeDesc.probeIrradianceThreshold = config.probeIrradianceThreshold;
    volumeDesc.probeBrightnessThreshold = config.probeBrightnessThreshold;

    volumeDesc.showProbes = config.showProbes;
    volumeDesc.probeVisType = config.probeVisType;

    volumeDesc.probeRayDataFormat = config.textureFormats.rayDataFormat;
    volumeDesc.probeIrradianceFormat = config.textureFormats.irradianceFormat;
    volumeDesc.probeDistanceFormat = config.textureFormats.distanceFormat;
    volumeDesc.probeDataFormat = config.textureFormats.dataFormat;
    volumeDesc.probeVariabilityFormat = config.textureFormats.variabilityFormat;

    volumeDesc.probeRelocationEnabled = config.probeRelocationEnabled;
    volumeDesc.probeMinFrontfaceDistance = config.probeMinFrontfaceDistance;
    volumeDesc.probeClassificationEnabled = config.probeClassificationEnabled;
    volumeDesc.probeVariabilityEnabled = config.probeVariabilityEnabled;

    if (config.infiniteScrollingEnabled)
    {
        volumeDesc.movementType = EDDGIVolumeMovementType::Scrolling;
    }
    else
    {
        volumeDesc.movementType = EDDGIVolumeMovementType::Default;
    }
}

bool DDGIPass::GetDDGIVolumeResources(
    const DDGIVolumeDesc& volumeDesc,
    DDGIVolumeResources& volumeResources)
{
    CompileDDGIVolumeShaders(volumeDesc);

    volumeResources.constantsBuffer = mContext.mGlobalConstHandle;

    volumeResources.bindless.enabled = (bool)RTXGI_DDGI_BINDLESS_RESOURCES;

    volumeResources.bindless.resourceIndicesBuffer = mContext.mDDGIVolumeResourceIndicesHandle;

    DDGIVolumeResourceIndices& resourceIndices = volumeResources.bindless.resourceIndices;

    resourceIndices.rayDataUAVIndex = (volumeDesc.index * GetDDGIVolumeNumTex2DArrayDescriptors());
    resourceIndices.rayDataSRVIndex = (volumeDesc.index * GetDDGIVolumeNumTex2DArrayDescriptors());
    resourceIndices.probeIrradianceUAVIndex = (volumeDesc.index * GetDDGIVolumeNumTex2DArrayDescriptors()) + 1;
    resourceIndices.probeIrradianceSRVIndex = (volumeDesc.index * GetDDGIVolumeNumTex2DArrayDescriptors()) + 1;
    resourceIndices.probeDistanceUAVIndex = (volumeDesc.index * GetDDGIVolumeNumTex2DArrayDescriptors()) + 2;
    resourceIndices.probeDistanceSRVIndex = (volumeDesc.index * GetDDGIVolumeNumTex2DArrayDescriptors()) + 2;
    resourceIndices.probeDataUAVIndex = (volumeDesc.index * GetDDGIVolumeNumTex2DArrayDescriptors()) + 3;
    resourceIndices.probeDataSRVIndex = (volumeDesc.index * GetDDGIVolumeNumTex2DArrayDescriptors()) + 3;
    resourceIndices.probeVariabilityUAVIndex = (volumeDesc.index * GetDDGIVolumeNumTex2DArrayDescriptors()) + 4;
    resourceIndices.probeVariabilitySRVIndex = (volumeDesc.index * GetDDGIVolumeNumTex2DArrayDescriptors()) + 4;
    resourceIndices.probeVariabilityAverageUAVIndex = (volumeDesc.index * GetDDGIVolumeNumTex2DArrayDescriptors()) + 5;
    resourceIndices.probeVariabilityAverageSRVIndex = (volumeDesc.index * GetDDGIVolumeNumTex2DArrayDescriptors()) + 5;


    volumeResources.unmanaged.enabled = true;

    CreateDDGIVolumeResources(volumeDesc, volumeResources);

    return true;
}
void DDGIPass::CompileDDGIVolumeShaders(const DDGIVolumeDesc& volumeDesc)
{
    auto* rs = Ogre::Root::getSingleton().getRenderSystem();

    std::string numRays = std::to_string(volumeDesc.probeNumRays);
    std::string numIrradianceTexels = std::to_string(volumeDesc.probeNumIrradianceTexels);
    std::string numIrradianceInteriorTexels = std::to_string(volumeDesc.probeNumIrradianceInteriorTexels);
    std::string numDistanceTexels = std::to_string(volumeDesc.probeNumDistanceTexels);
    std::string numDistanceInteriorTexels = std::to_string(volumeDesc.probeNumDistanceInteriorTexels);
    std::string waveLaneCount = std::to_string(32);

    // Probe Blending (irradiance)
    ShaderInfo shaderInfo;
    shaderInfo.shaderName = "ProbeBlendingCS";
    AddCommonShaderDefines(shaderInfo, volumeDesc, true);
    addMacro(shaderInfo, "RTXGI_DDGI_BLEND_RADIANCE", "1");
    addMacro(shaderInfo, "RTXGI_DDGI_PROBE_NUM_TEXELS", numIrradianceTexels);
    addMacro(shaderInfo, "RTXGI_DDGI_PROBE_NUM_INTERIOR_TEXELS", numIrradianceInteriorTexels);
    addMacro(shaderInfo, "RTXGI_DDGI_BLEND_SHARED_MEMORY", std::to_string(RTXGI_DDGI_BLEND_SHARED_MEMORY));
#if RTXGI_DDGI_BLEND_SHARED_MEMORY
    addMacro(shaderInfo, "RTXGI_DDGI_BLEND_RAYS_PER_PROBE", numRays);
#endif
    addMacro(shaderInfo, "RTXGI_DDGI_BLEND_SCROLL_SHARED_MEMORY", std::to_string(volumeDesc.probeBlendingUseScrollSharedMemory));

    mProbeBlendingIrradianceHandle = rs->createComputeProgram(shaderInfo);

    
    // Probe Blending (distance)
    shaderInfo.shaderMacros.clear();
    AddCommonShaderDefines(shaderInfo, volumeDesc, true);
    addMacro(shaderInfo, "RTXGI_DDGI_BLEND_RADIANCE", "0");
    addMacro(shaderInfo, "RTXGI_DDGI_PROBE_NUM_TEXELS", numIrradianceTexels);
    addMacro(shaderInfo, "RTXGI_DDGI_PROBE_NUM_INTERIOR_TEXELS", numDistanceInteriorTexels);
    addMacro(shaderInfo, "RTXGI_DDGI_BLEND_SHARED_MEMORY", std::to_string(RTXGI_DDGI_BLEND_SHARED_MEMORY));
#if RTXGI_DDGI_BLEND_SHARED_MEMORY
    addMacro(shaderInfo, "RTXGI_DDGI_BLEND_RAYS_PER_PROBE", numRays);
#endif
    addMacro(shaderInfo, "RTXGI_DDGI_BLEND_SCROLL_SHARED_MEMORY", std::to_string(volumeDesc.probeBlendingUseScrollSharedMemory));
    mProbeBlendingDistanceHandle = rs->createComputeProgram(shaderInfo);

    // Probe Relocation
    {
        //update
        shaderInfo.shaderName = "ProbeRelocationUpdateCS";
        shaderInfo.shaderMacros.clear();
        AddCommonShaderDefines(shaderInfo, volumeDesc, true);
        mProbeRelocationUpdateHandle = rs->createComputeProgram(shaderInfo);

        //reset

        shaderInfo.shaderName = "ProbeRelocationResetCS";
        shaderInfo.shaderMacros.clear();
        AddCommonShaderDefines(shaderInfo, volumeDesc, true);
        mProbeRelocationResetHandle = rs->createComputeProgram(shaderInfo);
    }
    
    // Probe Classification
    {
        //update
        shaderInfo.shaderName = "ProbeClassificationUpdateCS";
        shaderInfo.shaderMacros.clear();
        AddCommonShaderDefines(shaderInfo, volumeDesc, true);
        mProbeRelocationUpdateHandle = rs->createComputeProgram(shaderInfo);

        //reset

        shaderInfo.shaderName = "ProbeClassificationResetCS";
        shaderInfo.shaderMacros.clear();
        AddCommonShaderDefines(shaderInfo, volumeDesc, true);
        mProbeRelocationResetHandle = rs->createComputeProgram(shaderInfo);
    }

    // Probe variability reduction
    shaderInfo.shaderName = "ProbeVariabilityReductionCS";
    shaderInfo.shaderMacros.clear();
    AddCommonShaderDefines(shaderInfo, volumeDesc, true);
    addMacro(shaderInfo, "RTXGI_DDGI_PROBE_NUM_INTERIOR_TEXELS", numIrradianceInteriorTexels);
    addMacro(shaderInfo, "RTXGI_DDGI_WAVE_LANE_COUNT", waveLaneCount);
    mProbeVariabilityReductionHandle = rs->createComputeProgram(shaderInfo);

    // Extra reduction passes
    shaderInfo.shaderName = "ProbeExtraReductionCS";
    shaderInfo.shaderMacros.clear();
    AddCommonShaderDefines(shaderInfo, volumeDesc, true);
    addMacro(shaderInfo, "RTXGI_DDGI_PROBE_NUM_INTERIOR_TEXELS", numIrradianceInteriorTexels);
    addMacro(shaderInfo, "RTXGI_DDGI_WAVE_LANE_COUNT", waveLaneCount);
    mProbeExtraReductionHandle = rs->createComputeProgram(shaderInfo);
}

void DDGIPass::AddCommonShaderDefines(
    ShaderInfo& shaderInfo, const DDGIVolumeDesc& volumeDesc, bool spirv)
{
    addMacro(shaderInfo, "RTXGI_DDGI_RESOURCE_MANAGEMENT", std::to_string(RTXGI_DDGI_RESOURCE_MANAGEMENT));
    addMacro(shaderInfo, "RTXGI_BINDLESS_TYPE", std::to_string(RTXGI_BINDLESS_TYPE_RESOURCE_ARRAYS));
    addMacro(shaderInfo, "RTXGI_COORDINATE_SYSTEM", std::to_string(RTXGI_COORDINATE_SYSTEM));
    addMacro(shaderInfo, "RTXGI_DDGI_SHADER_REFLECTION", std::to_string(RTXGI_DDGI_SHADER_REFLECTION));
    addMacro(shaderInfo, "RTXGI_DDGI_BINDLESS_RESOURCES", std::to_string(RTXGI_DDGI_BINDLESS_RESOURCES));

    if (spirv)
    {
#if RTXGI_DDGI_BINDLESS_RESOURCES
        // Using the application's pipeline layout (bindless resource arrays)
        addMacro(shaderInfo, "RTXGI_PUSH_CONSTS_TYPE", "2");                                         // use the application's push constants layout
        addMacro(shaderInfo, "RTXGI_DECLARE_PUSH_CONSTS", "1");                                      // declare the push constants struct (it is not already declared elsewhere)
        addMacro(shaderInfo, "RTXGI_PUSH_CONSTS_STRUCT_NAME", "GlobalConstants");                    // specify the struct name of the application's push constants
        addMacro(shaderInfo, "RTXGI_PUSH_CONSTS_VARIABLE_NAME", "GlobalConst");                      // specify the variable name of the application's push constants
        addMacro(shaderInfo, "RTXGI_PUSH_CONSTS_FIELD_DDGI_VOLUME_INDEX_NAME", "ddgi_volumeIndex");  // specify the name of the DDGIVolume index field in the application's push constants struct
        addMacro(shaderInfo, "RTXGI_PUSH_CONSTS_FIELD_DDGI_REDUCTION_INPUT_SIZE_X_NAME", "ddgi_reductionInputSizeX");  // specify the name of the DDGIVolume reduction pass input size fields the application's push constants struct
        addMacro(shaderInfo, "RTXGI_PUSH_CONSTS_FIELD_DDGI_REDUCTION_INPUT_SIZE_Y_NAME", "ddgi_reductionInputSizeY");
        addMacro(shaderInfo, "RTXGI_PUSH_CONSTS_FIELD_DDGI_REDUCTION_INPUT_SIZE_Z_NAME", "ddgi_reductionInputSizeZ");
        addMacro(shaderInfo, "VOLUME_CONSTS_REGISTER", "5");
        addMacro(shaderInfo, "VOLUME_CONSTS_SPACE", "0");
        addMacro(shaderInfo, "VOLUME_RESOURCES_REGISTER", "6");
        addMacro(shaderInfo, "VOLUME_RESOURCES_SPACE", "0");
        addMacro(shaderInfo, "RWTEX2DARRAY_REGISTER", "9");
        addMacro(shaderInfo, "RWTEX2DARRAY_SPACE", "0");
#endif
    }

    addMacro(shaderInfo, "RTXGI_DDGI_DEBUG_PROBE_INDEXING", std::to_string(RTXGI_DDGI_DEBUG_PROBE_INDEXING));
    addMacro(shaderInfo, "RTXGI_DDGI_DEBUG_OCTAHEDRAL_INDEXING", std::to_string(RTXGI_DDGI_DEBUG_OCTAHEDRAL_INDEXING));
    addMacro(shaderInfo, "RTXGI_DDGI_DEBUG_BORDER_COPY_INDEXING", std::to_string(RTXGI_DDGI_DEBUG_BORDER_COPY_INDEXING));
}

bool DDGIPass::CreateDDGIVolumeResources(
    const DDGIVolumeDesc& volumeDesc,
    DDGIVolumeResources& volumeResources)
{
    auto* rs = Ogre::Root::getSingleton().getRenderSystem();
    uint32_t arraySize = 0;

    uint32_t variabilityAverageArraySize = 0;


    // Create the texture arrays
    {
        uint32_t width = 0;
        uint32_t height = 0;
        Ogre::PixelFormat format = PF_UNKNOWN;

        // Probe ray data texture
        {
            GetDDGIVolumeTextureDimensions(volumeDesc, EDDGIVolumeTextureType::RayData, width, height, arraySize);
           
            TextureProperty texProperty;
            texProperty._tex_format = volumeDesc.probeRayDataFormat;
            texProperty._width = width;
            texProperty._height = height;
            texProperty._face = arraySize;
            texProperty._tex_usage = Ogre::TextureUsage::WRITEABLE;
            volumeResources.unmanaged.probeRayData = 
                rs->createManualTexture("ProbeRayData", &texProperty);
        }

        // Probe irradiance texture
        {
            GetDDGIVolumeTextureDimensions(volumeDesc, EDDGIVolumeTextureType::Irradiance, width, height, arraySize);
            
            TextureProperty texProperty;
            texProperty._tex_format = volumeDesc.probeIrradianceFormat;
            texProperty._width = width;
            texProperty._height = height;
            texProperty._face = arraySize;
            texProperty._tex_usage = Ogre::TextureUsage::WRITEABLE;
            volumeResources.unmanaged.probeIrradiance =
                rs->createManualTexture("ProbeIrradianceTexture", &texProperty);
        }

        // Probe distance texture
        {
            GetDDGIVolumeTextureDimensions(volumeDesc, EDDGIVolumeTextureType::Distance, width, height, arraySize);
            
            TextureProperty texProperty;
            texProperty._tex_format = volumeDesc.probeDistanceFormat;
            texProperty._width = width;
            texProperty._height = height;
            texProperty._face = arraySize;
            texProperty._tex_usage = Ogre::TextureUsage::WRITEABLE;
            volumeResources.unmanaged.probeDistance =
                rs->createManualTexture("ProbeDistanceTexture", &texProperty);
        }

        // Probe data texture
        {
            GetDDGIVolumeTextureDimensions(volumeDesc, EDDGIVolumeTextureType::Data, width, height, arraySize);
            if (width <= 0 || height <= 0) return false;
          
            TextureProperty texProperty;
            texProperty._tex_format = volumeDesc.probeDataFormat;
            texProperty._width = width;
            texProperty._height = height;
            texProperty._face = arraySize;
            texProperty._tex_usage = Ogre::TextureUsage::WRITEABLE;
            volumeResources.unmanaged.probeData =
                rs->createManualTexture("ProbeDataTexture", &texProperty);
        }

        // Probe variability texture
        {
            GetDDGIVolumeTextureDimensions(volumeDesc, EDDGIVolumeTextureType::Variability, width, height, arraySize);
            if (width <= 0 || height <= 0) return false;
            
            TextureProperty texProperty;
            texProperty._tex_format = volumeDesc.probeVariabilityFormat;
            texProperty._width = width;
            texProperty._height = height;
            texProperty._face = arraySize;
            texProperty._tex_usage = Ogre::TextureUsage::WRITEABLE;
            volumeResources.unmanaged.probeVariability =
                rs->createManualTexture("ProbeVariabilityTexture", &texProperty);
        }

        // Probe variability average
        {
            GetDDGIVolumeTextureDimensions(volumeDesc, EDDGIVolumeTextureType::VariabilityAverage, width, height, variabilityAverageArraySize);
            if (width <= 0 || height <= 0) return false;
         
            TextureProperty texProperty;
            texProperty._tex_format = volumeDesc.probeVariabilityFormat;
            texProperty._width = width;
            texProperty._height = height;
            texProperty._face = arraySize;
            texProperty._tex_usage = Ogre::TextureUsage::WRITEABLE;
            volumeResources.unmanaged.probeVariabilityAverage =
                rs->createManualTexture("ProbeVariabilityAverageTexture", &texProperty);

            BufferDesc desc{};
            desc.mBindingType = BufferObjectBinding_Storge;
            desc.mMemoryUsage = RESOURCE_MEMORY_USAGE_GPU_TO_CPU;
            desc.bufferCreationFlags = 0;
            desc.mElementCount = 2;
            desc.mStructStride = sizeof(float);
            desc.mSize = desc.mElementCount * desc.mStructStride;
            volumeResources.unmanaged.probeVariabilityReadback = rs->createBufferObject(desc);
     
        }
    }

    return true;
}