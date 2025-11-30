#include "OgreHeader.h"
#include "DDGI.h"
#include "engine_struct.h"
#include <OgreRoot.h>
#include <OgreRenderTarget.h>
#include"DDGIVolumeImpl.h"
#include <OgreResourceManager.h>
#include "SDFGI_util.h"

DDGIPass::DDGIPass(SDFGIContext& context)
    :mContext(context)
{

}

bool DDGIPass::initialize(RenderContext& context)
{
    mDDGIFrameDatas.resize(mContext.frameCount);
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
    }

    loadIndirectShader();

    updateDescriptorSet();
    updateDescriptorSetOfComputeShader();

    std::vector<Ogre::TextureBarrier> textureBarriers;
    for (uint32_t volumeIndex = 0; volumeIndex < numVolumes; volumeIndex++)
    {
        DDGIVolume* volume = static_cast<DDGIVolume*>(mContext.volumes[volumeIndex]);

        textureBarriers.push_back(
            { 
                volume->GetProbeDistance(),
                Ogre::RESOURCE_STATE_UNDEFINED,
                Ogre::RESOURCE_STATE_COPY_DEST
            });

        textureBarriers.push_back(
            {
                volume->GetProbeIrradiance(),
                Ogre::RESOURCE_STATE_UNDEFINED,
                Ogre::RESOURCE_STATE_COPY_DEST
            });

        textureBarriers.push_back(
            {
                volume->GetProbeData(),
                Ogre::RESOURCE_STATE_UNDEFINED,
                Ogre::RESOURCE_STATE_PIXEL_SHADER_RESOURCE
            });

        textureBarriers.push_back(
            {
                volume->GetProbeRayData(),
                Ogre::RESOURCE_STATE_UNDEFINED,
                Ogre::RESOURCE_STATE_PIXEL_SHADER_RESOURCE
            });

        textureBarriers.push_back(
            {
                mContext.mIndirectTarget->getTarget(),
                Ogre::RESOURCE_STATE_UNDEFINED,
                Ogre::RESOURCE_STATE_PIXEL_SHADER_RESOURCE
            });
        
    }

    RenderSystem* rs = Ogre::Root::getSingleton().getRenderSystem();
    rs->resourceBarrier(0, nullptr, textureBarriers.size(), textureBarriers.data(), 0, nullptr, nullptr);

    for (uint32_t volumeIndex = 0; volumeIndex < numVolumes; volumeIndex++)
    {
        DDGIVolume* volume = static_cast<DDGIVolume*>(mContext.volumes[volumeIndex]);
        volume->ClearProbes(context);
    }

    textureBarriers.clear();
    for (uint32_t volumeIndex = 0; volumeIndex < numVolumes; volumeIndex++)
    {
        DDGIVolume* volume = static_cast<DDGIVolume*>(mContext.volumes[volumeIndex]);

        textureBarriers.push_back(
            {
                volume->GetProbeDistance(),
                Ogre::RESOURCE_STATE_COPY_DEST,
                Ogre::RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
                
            });

        textureBarriers.push_back(
            {
                volume->GetProbeIrradiance(),
                Ogre::RESOURCE_STATE_COPY_DEST,
                Ogre::RESOURCE_STATE_PIXEL_SHADER_RESOURCE
            });
    }

    rs->resourceBarrier(0, nullptr, textureBarriers.size(), textureBarriers.data(), 0, nullptr, nullptr);

    

    return true;
}

void DDGIPass::update(float delta)
{
    RenderSystem* rs = Ogre::Root::getSingleton().getRenderSystem();
    uint32_t numVolumes = mContext.volumes.size();
 
    uint64_t frameIndex =  Ogre::Root::getSingleton().getCurrentFrameIndex();
    DDGIVolume** volumes = mContext.volumes.data();
    for (uint32_t i = 0; i < numVolumes; i++)
    {
        volumes[i]->Update();
    }

    UploadDDGIVolumeResourceIndices(&mContext, frameIndex, numVolumes, volumes);
    UploadDDGIVolumeConstants(&mContext, frameIndex, numVolumes, mContext.volumes.data());

}

void DDGIPass::execute(RenderContext& context)
{
    auto rs = Ogre::Root::getSingleton().getRenderSystem();
    auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();
    
    uint32_t numVolumes = mContext.mConfig.ddgi.volumes.size();
    uint32_t frameIndex = Ogre::Root::getSingleton().getCurrentFrameIndex();
    std::vector<Ogre::TextureBarrier> textureBarriers;

    if (1)
    {
        for (uint32_t volumeIndex = 0; volumeIndex < numVolumes; volumeIndex++)
        {
            DDGIVolume* volume = static_cast<DDGIVolume*>(mContext.volumes[volumeIndex]);

            textureBarriers.clear();
            textureBarriers.push_back(
                {
                    volume->GetProbeRayData(),
                    RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
                    RESOURCE_STATE_UNORDERED_ACCESS
                }
            );

            rs->resourceBarrier(0, nullptr, textureBarriers.size(), textureBarriers.data(), 0, nullptr, &context.frameContext->cbh);

            uint32_t width, height, depth;
            volume->GetRayDispatchDimensions(width, height, depth);

            rs->pushGroupMarker(context.frameContext->cbh, "probeTracePass", Ogre::Vector3i(0.0, 0.0, 1.0f));
            rs->bindPipeline(context.frameContext->cbh, mProbeTracingHandle);
            rs->bindDescriptorSet(context.frameContext->cbh, mProbeTracingHandle, mDDGIFrameDatas[frameIndex].probeTracingZeroSet);
            rs->traceRay(context.frameContext->cbh, mProbeTracingHandle, width, height, depth);
            rs->popGroupMarker(context.frameContext->cbh);

            textureBarriers.clear();
            textureBarriers.push_back(
                {
                    volume->GetProbeRayData(),
                    RESOURCE_STATE_UNORDERED_ACCESS,
                    RESOURCE_STATE_PIXEL_SHADER_RESOURCE
                }
            );

            rs->resourceBarrier(0, nullptr, textureBarriers.size(), textureBarriers.data(), 0, nullptr, &context.frameContext->cbh);
        }
    }
    

    if (1)
    {
        for (uint32_t volumeIndex = 0; volumeIndex < numVolumes; volumeIndex++)
        {
            DDGIVolume* volume = static_cast<DDGIVolume*>(mContext.volumes[volumeIndex]);

            textureBarriers.clear();
            textureBarriers.push_back(
                {
                    volume->GetProbeIrradiance(),
                    RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
                    RESOURCE_STATE_UNORDERED_ACCESS
                }
            );
            rs->resourceBarrier(0, nullptr, textureBarriers.size(), textureBarriers.data(), 0, nullptr, &context.frameContext->cbh);
            uint32_t probeCountX, probeCountY, probeCountZ;
            GetDDGIVolumeProbeCounts(volume->GetDesc(), probeCountX, probeCountY, probeCountZ);

            rs->pushGroupMarker(context.frameContext->cbh, "Probe Irradiance", Ogre::Vector3i(0.0, 0.0, 1.0f));
            rs->bindComputePipeline(mProbeBlendingIrradianceHandle, context.frameContext->cbh, 
                &mDDGIFrameDatas[frameIndex].blendingIrradianceDescriptorSet, 1);
            
            rs->dispatchComputeShader(probeCountX, probeCountY, probeCountZ, &context.frameContext->cbh);
            rs->popGroupMarker(context.frameContext->cbh);

            textureBarriers.clear();
            textureBarriers.push_back(
                {
                    volume->GetProbeIrradiance(),
                    RESOURCE_STATE_UNORDERED_ACCESS,
                    RESOURCE_STATE_PIXEL_SHADER_RESOURCE
                }
            );
            rs->resourceBarrier(0, nullptr, textureBarriers.size(), textureBarriers.data(), 0, nullptr, &context.frameContext->cbh);
        }

        for (uint32_t volumeIndex = 0; volumeIndex < numVolumes; volumeIndex++)
        {
            DDGIVolume* volume = static_cast<DDGIVolume*>(mContext.volumes[volumeIndex]);
            textureBarriers.clear();
            textureBarriers.push_back(
                {
                    volume->GetProbeDistance(),
                     RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
                    RESOURCE_STATE_UNORDERED_ACCESS
                }
            );
            rs->resourceBarrier(0, nullptr, textureBarriers.size(), textureBarriers.data(), 0, nullptr, &context.frameContext->cbh);
            uint32_t probeCountX, probeCountY, probeCountZ;
            GetDDGIVolumeProbeCounts(volume->GetDesc(), probeCountX, probeCountY, probeCountZ);

            rs->pushGroupMarker(context.frameContext->cbh, "Probe Distance", Ogre::Vector3i(0.0, 0.0, 1.0f));
            rs->bindComputePipeline(mProbeBlendingDistanceHandle, context.frameContext->cbh , &mDDGIFrameDatas[frameIndex].blendingDistanceDescriptorSet, 1);
            rs->dispatchComputeShader(probeCountX, probeCountY, probeCountZ, &context.frameContext->cbh);
            rs->popGroupMarker(context.frameContext->cbh);

            textureBarriers.clear();
            textureBarriers.push_back(
                {
                    volume->GetProbeDistance(),
                    RESOURCE_STATE_UNORDERED_ACCESS,
                     RESOURCE_STATE_PIXEL_SHADER_RESOURCE
                }
            );
            rs->resourceBarrier(0, nullptr, textureBarriers.size(), textureBarriers.data(), 0, nullptr, &context.frameContext->cbh);
        }
    }
    

    if (1)
    {
        rs->pushGroupMarker(context.frameContext->cbh, "Indirect Lighting", Ogre::Vector3i(0.0, 0.0, 1.0f));

        textureBarriers.clear();
        textureBarriers.push_back(
            {
                mContext.mIndirectTarget->getTarget(),
                RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
                RESOURCE_STATE_UNORDERED_ACCESS
            }
        );

        rs->resourceBarrier(0, nullptr, textureBarriers.size(), textureBarriers.data(), 0, nullptr, &context.frameContext->cbh);

        rs->bindComputePipeline(mIndirectHandle, context.frameContext->cbh, &mDDGIFrameDatas[frameIndex].mIndirectZeroSet, 1);

        uint32_t groupsX = DivRoundUp(ogreConfig.width, 8);
        uint32_t groupsY = DivRoundUp(ogreConfig.height, 4);

        rs->dispatchComputeShader(groupsX, groupsY, 1, &context.frameContext->cbh);
        

        textureBarriers.clear();
        textureBarriers.push_back(
            {
                mContext.mIndirectTarget->getTarget(),
                RESOURCE_STATE_UNORDERED_ACCESS,
                 RESOURCE_STATE_PIXEL_SHADER_RESOURCE
            }
        );
       
        rs->resourceBarrier(0, nullptr, textureBarriers.size(), textureBarriers.data(), 0, nullptr, &context.frameContext->cbh);

        rs->popGroupMarker(context.frameContext->cbh);
    }
    
    
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
    addMacro(shaderInfo, "RTXGI_COORDINATE_SYSTEM", std::to_string(RTXGI_COORDINATE_SYSTEM));

    shaderInfo.rayGenShaderName = "ProbeTraceRGS.hlsl";
    shaderInfo.rayGenEntryName = "RayGen";

    shaderInfo.rayClosethitShaderName = "ProbeTraceClosethit.hlsl";
    shaderInfo.rayClosethitEntryName = "CHS_GI";

    shaderInfo.rayMissShaderName = "ProbeTraceMiss.hlsl";
    shaderInfo.rayMissEntryName = "Miss";

    shaderInfo.rayAnyHitShaderName = "ProbeTraceAnyhit.hlsl";
    shaderInfo.rayAnyHitEntryName = "AHS_GI";

    RenderSystem* rs = Ogre::Root::getSingleton().getRenderSystem();

    mProbeTracingHandle = rs->createRaytracingProgram(shaderInfo);


    for (uint32_t i = 0; i < mContext.frameCount; i++)
    {
        mDDGIFrameDatas[i].probeTracingZeroSet = rs->createDescriptorSet(mProbeTracingHandle, 0);
    }
    
   

    
   
    return true;
}

void DDGIPass::loadIndirectShader()
{
    uint32_t numVolumes = mContext.volumes.size();
    ShaderInfo computeShaderInfo;
    computeShaderInfo.shaderName = "IndirectCS";
    addMacro(computeShaderInfo, "HLSL", "1");
    addMacro(computeShaderInfo, "RAYTRACING", "1");
    addMacro(computeShaderInfo, "RTXGI_PUSH_CONSTS_TYPE", "2");
    addMacro(computeShaderInfo, "RTXGI_PUSH_CONSTS_STRUCT_NAME", "GlobalConstants");
    addMacro(computeShaderInfo, "RTXGI_PUSH_CONSTS_VARIABLE_NAME", "GlobalConst");
    addMacro(computeShaderInfo, "RTXGI_PUSH_CONSTS_FIELD_DDGI_VOLUME_INDEX_NAME", "ddgi_volumeIndex");
    addMacro(computeShaderInfo, "RTXGI_PUSH_CONSTS_FIELD_DDGI_REDUCTION_INPUT_SIZE_X_NAME", "ddgi_reductionInputSizeX");
    addMacro(computeShaderInfo, "RTXGI_PUSH_CONSTS_FIELD_DDGI_REDUCTION_INPUT_SIZE_Y_NAME", "ddgi_reductionInputSizeY");
    addMacro(computeShaderInfo, "RTXGI_PUSH_CONSTS_FIELD_DDGI_REDUCTION_INPUT_SIZE_Z_NAME", "ddgi_reductionInputSizeZ");
    addMacro(computeShaderInfo, "RTXGI_BINDLESS_TYPE", "RTXGI_BINDLESS_TYPE_RESOURCE_ARRAYS");
    addMacro(computeShaderInfo, "RTXGI_COORDINATE_SYSTEM", "RTXGI_COORDINATE_SYSTEM");
    addMacro(computeShaderInfo, "RTXGI_COORDINATE_SYSTEM", "RTXGI_COORDINATE_SYSTEM");
    addMacro(computeShaderInfo, "RTXGI_DDGI_NUM_VOLUMES", std::to_string(numVolumes));
    addMacro(computeShaderInfo, "THGP_DIM_X", "8");
    addMacro(computeShaderInfo, "THGP_DIM_Y", "4");

    RenderSystem* rs = Ogre::Root::getSingleton().getRenderSystem();
    mIndirectHandle = rs->createComputeProgram(computeShaderInfo);

    for (uint32_t i = 0; i < mContext.frameCount; i++)
    {
        mDDGIFrameDatas[i].mIndirectZeroSet = rs->createDescriptorSet(mIndirectHandle, 0);
    }
     
}

void DDGIPass::updateDescriptorSetOfComputeShader()
{
    DescriptorData descriptorData[10];

    descriptorData[0].mCount = 1;
    descriptorData[0].pName = "DDGI";
    descriptorData[0].descriptorType = DESCRIPTOR_TYPE_BUFFER;
    descriptorData[0].ppBuffers = &mContext.mDDGIHandle;

    descriptorData[1].mCount = 1;
    descriptorData[1].pName = "DDGIVolumes";
    descriptorData[1].descriptorType = DESCRIPTOR_TYPE_BUFFER;
    descriptorData[1].ppBuffers = &mContext.mDDGIVolumeDescGPUPackedHandles[0];

    descriptorData[2].mCount = 1;
    descriptorData[2].pName = "DDGIVolumeBindless";
    descriptorData[2].descriptorType = DESCRIPTOR_TYPE_BUFFER;
    descriptorData[2].ppBuffers = &mContext.mDDGIVolumeResourceIndicesHandles[0];    
    std::vector<OgreTexture*> rwTex2DArray;


    rwTex2DArray.clear();

    uint32_t numVolumes = mContext.volumes.size();
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

    descriptorData[3].mCount = rwTex2DArray.size();
    descriptorData[3].pName = "RWTex2DArray";
    descriptorData[3].descriptorType = DESCRIPTOR_TYPE_RW_TEXTURE;
    descriptorData[3].ppTextures = (const OgreTexture**)rwTex2DArray.data();


    auto* rs = Ogre::Root::getSingleton().getRenderSystem();


    for (uint32_t i = 0; i < mContext.frameCount; i++)
    {
        rs->updateDescriptorSet(mDDGIFrameDatas[i].blendingIrradianceDescriptorSet, 4, descriptorData);
        rs->updateDescriptorSet(mDDGIFrameDatas[i].blendingDistanceDescriptorSet, 4, descriptorData);
    }
    
}

void DDGIPass::updateDescriptorSet()
{
    uint32_t frameIndex = Ogre::Root::getSingleton().getCurrentFrameIndex();

    DescriptorData descriptorData[32];

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


    std::array<OgreTexture*, 7> rwTex2D =
    {
        mContext.mGBufferTargetA->getTarget(),
        mContext.mGBufferTargetB->getTarget(),
        mContext.mGBufferTargetC->getTarget(),
        mContext.mGBufferTargetD->getTarget(),
        mContext.mIndirectTarget->getTarget(),
        nullptr,
        nullptr
    };
    descriptorData[7].mCount = rwTex2D.size();
    descriptorData[7].pName = "RWTex2D";
    descriptorData[7].descriptorType = DESCRIPTOR_TYPE_TEXTURE;
    descriptorData[7].ppTextures = (const OgreTexture**)rwTex2D.data();

    uint32_t numVolumes = mContext.volumes.size();
    std::vector<OgreTexture*> rwTex2DArray;

    descriptorData[8].mCount = 1;
    descriptorData[8].pName = "TLAS";
    descriptorData[8].descriptorType = DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE;
    descriptorData[8].pAS = mContext.pTopAS;


    descriptorData[9].mCount = 1;
    descriptorData[9].pName = "DDGI";
    descriptorData[9].descriptorType = DESCRIPTOR_TYPE_BUFFER;
    descriptorData[9].ppBuffers = &mContext.mDDGIHandle;


    descriptorData[10].mCount = 1;
    descriptorData[10].pName = "GlobalConst";
    descriptorData[10].descriptorType = DESCRIPTOR_TYPE_BUFFER;
    descriptorData[10].ppBuffers = &mContext.mGlobalConstHandle;


    auto* rs = Ogre::Root::getSingleton().getRenderSystem();
    
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
        descriptorData[11].mCount = rwTex2DArray.size();
        descriptorData[11].pName = "RWTex2DArray";
        descriptorData[11].descriptorType = DESCRIPTOR_TYPE_RW_TEXTURE;
        descriptorData[11].ppTextures = (const OgreTexture**)rwTex2DArray.data();
    }

    std::vector<OgreTexture*> tex2D;

    for (auto tex : mContext.sceneTextureList)
    {
        tex2D.push_back(tex);
    }
    descriptorData[12].mCount = tex2D.size();
    descriptorData[12].pName = "Tex2D";
    descriptorData[12].descriptorType = DESCRIPTOR_TYPE_TEXTURE;
    descriptorData[12].ppTextures = (const OgreTexture**)tex2D.data();


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
        descriptorData[13].mCount = tex2DArray.size();
        descriptorData[13].pName = "Tex2DArray";
        descriptorData[13].descriptorType = DESCRIPTOR_TYPE_RW_TEXTURE;
        descriptorData[13].ppTextures = (const OgreTexture**)tex2DArray.data();
    }
    
    std::vector<Handle<HwBufferObject>> buffers;
    buffers.push_back(mContext.geometryBufferHandle);
    buffers.push_back(mContext.geometryBufferHandle);
    for (uint32_t i = 0; i < mContext.mIndexBufferList.size(); i++)
    {
        buffers.push_back(mContext.mIndexBufferList[i]);
        buffers.push_back(mContext.mVertexBufferList[i]);
    }

    descriptorData[14].mCount = buffers.size();
    descriptorData[14].pName = "ByteAddrBuffer";
    descriptorData[14].descriptorType = DESCRIPTOR_TYPE_RW_BUFFER;
    descriptorData[14].ppBuffers = buffers.data();

    descriptorData[15].mCount = rwTex2D.size();
    descriptorData[15].pName = "RWTex2D";
    descriptorData[15].descriptorType = DESCRIPTOR_TYPE_TEXTURE;
    descriptorData[15].ppTextures = (const OgreTexture**)rwTex2D.data();

    descriptorData[16].mCount = 1;
    descriptorData[16].pName = "GeometryDatas";
    descriptorData[16].descriptorType = DESCRIPTOR_TYPE_BUFFER;
    descriptorData[16].ppBuffers = &mContext.geometryBufferHandle;

    uint32_t volumeCount = mContext.volumes.size();
    for (uint32_t i = 0; i < mContext.frameCount; i++)
    {
        BufferView cameraCBBufferView;
        cameraCBBufferView.buffer = mContext.mCameraBufferHandle;
        cameraCBBufferView.offset = SDFGICameraInfo::GetAlignedSizeInBytes() * i;
        descriptorData[1].mCount = 1;
        descriptorData[1].pName = "CameraCB";
        descriptorData[1].descriptorType = DESCRIPTOR_TYPE_BUFFER_VIEW;
        descriptorData[1].pBufferView = &cameraCBBufferView;


        descriptorData[5].mCount = 1;
        descriptorData[5].pName = "DDGIVolumes";
        descriptorData[5].descriptorType = DESCRIPTOR_TYPE_BUFFER;
        descriptorData[5].ppBuffers = &mContext.mDDGIVolumeDescGPUPackedHandles[frameIndex];;

        descriptorData[6].mCount = 1;
        descriptorData[6].pName = "DDGIVolumeBindless";
        descriptorData[6].descriptorType = DESCRIPTOR_TYPE_BUFFER;
        descriptorData[6].ppBuffers = &mContext.mDDGIVolumeResourceIndicesHandles[frameIndex];

        BufferView globalConstBufferView;
        globalConstBufferView.buffer = mContext.mGlobalConstHandle;
        globalConstBufferView.offset = GlobalConstants::GetAlignedSizeInBytes()* i;

        descriptorData[10].mCount = 1;
        descriptorData[10].pName = "GlobalConst";
        descriptorData[10].descriptorType = DESCRIPTOR_TYPE_BUFFER_VIEW;
        descriptorData[10].pBufferView = &globalConstBufferView;

        rs->updateDescriptorSet(mDDGIFrameDatas[i].probeTracingZeroSet, 17, descriptorData);
    }
    

    descriptorData[0].mCount = rwTex2D.size();
    descriptorData[0].pName = "RWTex2D";
    descriptorData[0].descriptorType = DESCRIPTOR_TYPE_TEXTURE;
    descriptorData[0].ppTextures = (const OgreTexture**)rwTex2D.data();

    descriptorData[1].mCount = tex2DArray.size();
    descriptorData[1].pName = "Tex2DArray";
    descriptorData[1].descriptorType = DESCRIPTOR_TYPE_TEXTURE;
    descriptorData[1].ppTextures = (const OgreTexture**)tex2DArray.data();

    descriptorData[2].mCount = 3;
    descriptorData[2].pName = "Samplers";
    descriptorData[2].descriptorType = DESCRIPTOR_TYPE_SAMPLER;
    descriptorData[2].ppSamplers = &mContext.mSamplerHandle[0];

    for (uint32_t i = 0; i < mContext.frameCount; i++)
    {
        BufferView cameraCBBufferView;
        cameraCBBufferView.buffer = mContext.mCameraBufferHandle;
        cameraCBBufferView.offset = SDFGICameraInfo::GetAlignedSizeInBytes() * i;
        descriptorData[3].mCount = 1;
        descriptorData[3].pName = "CameraCB";
        descriptorData[3].descriptorType = DESCRIPTOR_TYPE_BUFFER_VIEW;
        descriptorData[3].pBufferView = &cameraCBBufferView;


        descriptorData[4].mCount = 1;
        descriptorData[4].pName = "DDGIVolumes";
        descriptorData[4].descriptorType = DESCRIPTOR_TYPE_BUFFER;
        descriptorData[4].ppBuffers = &mContext.mDDGIVolumeDescGPUPackedHandles[frameIndex];;

        descriptorData[5].mCount = 1;
        descriptorData[5].pName = "DDGIVolumeBindless";
        descriptorData[5].descriptorType = DESCRIPTOR_TYPE_BUFFER;
        descriptorData[5].ppBuffers = &mContext.mDDGIVolumeResourceIndicesHandles[frameIndex];

        rs->updateDescriptorSet(mDDGIFrameDatas[i].mIndirectZeroSet, 6, descriptorData);
    }

    
}

bool DDGIPass::CreateDDGIVolumeResourceIndicesBuffer(uint32_t volumeCount)
{
    auto* rs = Ogre::Root::getSingleton().getRenderSystem();
    BufferDesc desc{};
    desc.mBindingType = BufferObjectBinding_Storge;
    desc.mMemoryUsage = RESOURCE_MEMORY_USAGE_CPU_TO_GPU;
    desc.bufferCreationFlags = BUFFER_CREATION_FLAG_ACCELERATION_STRUCTURE_BUILD_INPUT |
        BUFFER_CREATION_FLAG_SHADER_DEVICE_ADDRESS;
    desc.mElementCount = volumeCount;
    desc.mStructStride = DDGIVolumeResourceIndices::GetAlignedSizeInBytes();
    desc.mSize = desc.mElementCount * desc.mStructStride;
    desc.pName = "DDGIVolumeBindless";
    mContext.mDDGIVolumeResourceIndicesHandles.resize(mContext.frameCount);
    for (uint32_t i = 0; i < mContext.frameCount; i++)
    {
        mContext.mDDGIVolumeResourceIndicesHandles[i] = rs->createBufferObject(desc);
    }
    

    mContext.mVolumeResourceIndices.resize(volumeCount);
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
    desc.mStructStride = DDGIVolumeDescGPUPacked::GetAlignedSizeInBytes();
    desc.mElementCount = volumeCount;
    desc.mSize = desc.mStructStride * desc.mElementCount;
    desc.pName = "DDGIVolumes";
    mContext.mDDGIVolumeDescGPUPackedHandles.resize(mContext.frameCount);
    for (uint32_t i = 0; i < mContext.frameCount; i++)
    {
        mContext.mDDGIVolumeDescGPUPackedHandles[i] = rs->createBufferObject(desc);
    }
   
    mContext.mVolumeDescGPUPacked.resize(volumeCount);
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

    volumeDesc.probeClassificationEnabled = false;
}

bool DDGIPass::GetDDGIVolumeResources(
    const DDGIVolumeDesc& volumeDesc,
    DDGIVolumeResources& volumeResources)
{
    CompileDDGIVolumeShaders(volumeDesc);

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
    addMacro(shaderInfo, "RTXGI_DDGI_PROBE_NUM_TEXELS", numDistanceTexels);
    addMacro(shaderInfo, "RTXGI_DDGI_PROBE_NUM_INTERIOR_TEXELS", numDistanceInteriorTexels);
    addMacro(shaderInfo, "RTXGI_DDGI_BLEND_SHARED_MEMORY", std::to_string(RTXGI_DDGI_BLEND_SHARED_MEMORY));
#if RTXGI_DDGI_BLEND_SHARED_MEMORY
    addMacro(shaderInfo, "RTXGI_DDGI_BLEND_RAYS_PER_PROBE", numRays);
#endif
    addMacro(shaderInfo, "RTXGI_DDGI_BLEND_SCROLL_SHARED_MEMORY", std::to_string(volumeDesc.probeBlendingUseScrollSharedMemory));
    mProbeBlendingDistanceHandle = rs->createComputeProgram(shaderInfo);

    for (uint32_t i = 0; i < mContext.frameCount; i++)
    {
        mDDGIFrameDatas[i].blendingIrradianceDescriptorSet = rs->createDescriptorSet(mProbeBlendingIrradianceHandle, 0);
        mDDGIFrameDatas[i].blendingDistanceDescriptorSet = rs->createDescriptorSet(mProbeBlendingDistanceHandle, 0);
    }
    
    //// Probe Relocation
    //{
    //    //update
    //    shaderInfo.shaderName = "ProbeRelocationUpdateCS";
    //    shaderInfo.shaderMacros.clear();
    //    AddCommonShaderDefines(shaderInfo, volumeDesc, true);
    //    mProbeRelocationUpdateHandle = rs->createComputeProgram(shaderInfo);

    //    //reset

    //    shaderInfo.shaderName = "ProbeRelocationResetCS";
    //    shaderInfo.shaderMacros.clear();
    //    AddCommonShaderDefines(shaderInfo, volumeDesc, true);
    //    mProbeRelocationResetHandle = rs->createComputeProgram(shaderInfo);
    //}
    //
    //// Probe Classification
    //{
    //    //update
    //    shaderInfo.shaderName = "ProbeClassificationUpdateCS";
    //    shaderInfo.shaderMacros.clear();
    //    AddCommonShaderDefines(shaderInfo, volumeDesc, true);
    //    mProbeRelocationUpdateHandle = rs->createComputeProgram(shaderInfo);

    //    //reset

    //    shaderInfo.shaderName = "ProbeClassificationResetCS";
    //    shaderInfo.shaderMacros.clear();
    //    AddCommonShaderDefines(shaderInfo, volumeDesc, true);
    //    mProbeRelocationResetHandle = rs->createComputeProgram(shaderInfo);
    //}

    //// Probe variability reduction
    //shaderInfo.shaderName = "ProbeVariabilityReductionCS";
    //shaderInfo.shaderMacros.clear();
    //AddCommonShaderDefines(shaderInfo, volumeDesc, true);
    //addMacro(shaderInfo, "RTXGI_DDGI_PROBE_NUM_INTERIOR_TEXELS", numIrradianceInteriorTexels);
    //addMacro(shaderInfo, "RTXGI_DDGI_WAVE_LANE_COUNT", waveLaneCount);
    //mProbeVariabilityReductionHandle = rs->createComputeProgram(shaderInfo);

    //// Extra reduction passes
    //shaderInfo.shaderName = "ProbeExtraReductionCS";
    //shaderInfo.shaderMacros.clear();
    //AddCommonShaderDefines(shaderInfo, volumeDesc, true);
    //addMacro(shaderInfo, "RTXGI_DDGI_PROBE_NUM_INTERIOR_TEXELS", numIrradianceInteriorTexels);
    //addMacro(shaderInfo, "RTXGI_DDGI_WAVE_LANE_COUNT", waveLaneCount);
    //mProbeExtraReductionHandle = rs->createComputeProgram(shaderInfo);
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

Ogre::PixelFormat mappingPixFormat(EDDGIVolumeTextureFormat ddgiTextureFormat)
{
    switch (ddgiTextureFormat)
    {
    case EDDGIVolumeTextureFormat::U32:
        return Ogre::PixelFormat::PF_A2B10G10R10;
    case EDDGIVolumeTextureFormat::F32x2:
        return Ogre::PixelFormat::PF_FLOAT32_GR;
    case EDDGIVolumeTextureFormat::F16x2:
        return Ogre::PixelFormat::PF_FLOAT16_GR;
    case EDDGIVolumeTextureFormat::F16x4:
        return Ogre::PixelFormat::PF_FLOAT16_RGBA;
    case EDDGIVolumeTextureFormat::F16:
        return Ogre::PixelFormat::PF_FLOAT16_R;
    default:
        assert_invariant(false);
    }

    return Ogre::PixelFormat::PF_FLOAT16_RGBA;
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
            texProperty._texType = TEX_TYPE_2D_ARRAY;
            texProperty._tex_format = mappingPixFormat(volumeDesc.probeRayDataFormat);
            texProperty._width = width;
            texProperty._height = height;
            texProperty._face = arraySize;
            texProperty._tex_usage = Ogre::TEXTURE_USAGE_CAN_UPDATE_BIT| Ogre::TEXTURE_USAGE_STORAGE_BIT;
            texProperty._need_mipmap = false;
            volumeResources.unmanaged.probeRayData = rs->createManualTexture("ProbeRayData", &texProperty);
        }

        // Probe irradiance texture
        {
            GetDDGIVolumeTextureDimensions(volumeDesc, EDDGIVolumeTextureType::Irradiance, width, height, arraySize);
            
            TextureProperty texProperty;
            texProperty._texType = TEX_TYPE_2D_ARRAY;
            texProperty._tex_format = mappingPixFormat(volumeDesc.probeIrradianceFormat);
            texProperty._width = width;
            texProperty._height = height;
            texProperty._face = arraySize;
            texProperty._tex_usage = Ogre::TEXTURE_USAGE_CAN_UPDATE_BIT | Ogre::TEXTURE_USAGE_STORAGE_BIT;
            texProperty._need_mipmap = false;
            volumeResources.unmanaged.probeIrradiance = rs->createManualTexture("ProbeIrradianceTexture", &texProperty);
        }

        // Probe distance texture
        {
            GetDDGIVolumeTextureDimensions(volumeDesc, EDDGIVolumeTextureType::Distance, width, height, arraySize);
            
            TextureProperty texProperty;
            texProperty._texType = TEX_TYPE_2D_ARRAY;
            texProperty._tex_format = mappingPixFormat(volumeDesc.probeDistanceFormat);
            texProperty._width = width;
            texProperty._height = height;
            texProperty._face = arraySize;
            texProperty._tex_usage = Ogre::TEXTURE_USAGE_CAN_UPDATE_BIT | Ogre::TEXTURE_USAGE_STORAGE_BIT;
            texProperty._need_mipmap = false;
            volumeResources.unmanaged.probeDistance =
                rs->createManualTexture("ProbeDistanceTexture", &texProperty);
        }

        // Probe data texture
        {
            GetDDGIVolumeTextureDimensions(volumeDesc, EDDGIVolumeTextureType::Data, width, height, arraySize);
            if (width <= 0 || height <= 0) return false;
          
            TextureProperty texProperty;
            texProperty._texType = TEX_TYPE_2D_ARRAY;
            texProperty._tex_format = mappingPixFormat(volumeDesc.probeDataFormat);
            texProperty._width = width;
            texProperty._height = height;
            texProperty._face = arraySize;
            texProperty._tex_usage = Ogre::TEXTURE_USAGE_CAN_UPDATE_BIT|Ogre::TEXTURE_USAGE_STORAGE_BIT;
            texProperty._need_mipmap = false;
            volumeResources.unmanaged.probeData =
                rs->createManualTexture("ProbeDataTexture", &texProperty);
        }

        // Probe variability texture
        {
            GetDDGIVolumeTextureDimensions(volumeDesc, EDDGIVolumeTextureType::Variability, width, height, arraySize);
            if (width <= 0 || height <= 0) return false;
            
            TextureProperty texProperty;
            texProperty._texType = TEX_TYPE_2D_ARRAY;
            texProperty._tex_format = mappingPixFormat(volumeDesc.probeVariabilityFormat);
            texProperty._width = width;
            texProperty._height = height;
            texProperty._face = arraySize;
            texProperty._tex_usage = Ogre::TEXTURE_USAGE_CAN_UPDATE_BIT | Ogre::TEXTURE_USAGE_STORAGE_BIT;
            texProperty._need_mipmap = false;
            volumeResources.unmanaged.probeVariability =
                rs->createManualTexture("ProbeVariabilityTexture", &texProperty);
        }

        // Probe variability average
        {
            GetDDGIVolumeTextureDimensions(volumeDesc, EDDGIVolumeTextureType::VariabilityAverage, width, height, variabilityAverageArraySize);
            if (width <= 0 || height <= 0) return false;
         
            TextureProperty texProperty;
            texProperty._texType = TEX_TYPE_2D_ARRAY;
            texProperty._tex_format = mappingPixFormat(volumeDesc.probeVariabilityFormat);
            texProperty._width = width;
            texProperty._height = height;
            texProperty._face = arraySize;
            texProperty._tex_usage = Ogre::TEXTURE_USAGE_CAN_UPDATE_BIT | Ogre::TEXTURE_USAGE_STORAGE_BIT;
            texProperty._need_mipmap = false;
            volumeResources.unmanaged.probeVariabilityAverage =
                rs->createManualTexture("ProbeVariabilityAverageTexture", &texProperty);

            BufferDesc desc{};
            desc.mBindingType = BufferObjectBinding_Storge;
            desc.mMemoryUsage = RESOURCE_MEMORY_USAGE_GPU_TO_CPU;
            desc.bufferCreationFlags = 0;
            desc.mElementCount = 2;
            desc.mStructStride = sizeof(float);
            desc.mSize = desc.mElementCount * desc.mStructStride;
            texProperty._need_mipmap = false;
            volumeResources.unmanaged.probeVariabilityReadback = rs->createBufferObject(desc);
     
        }
    }

    return true;
}