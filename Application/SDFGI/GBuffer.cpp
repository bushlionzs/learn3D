#include "OgreHeader.h"
#include "GBuffer.h"
#include "engine_struct.h"
#include <OgreRoot.h>
#include <OgreRenderTarget.h>

GBuffer::GBuffer(SDFGIContext& context)
    :mContext(context)
{

}

bool GBuffer::initialize()
{
    if (!loadAndCompileShaders())
        return false;
    updateDescriptorSet();
    return true;
}

void GBuffer::update(float delta)
{

}

void GBuffer::execute(RenderSystem* rs)
{
    auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();

    {
        std::vector<Ogre::TextureBarrier> textureBarriers =
        {
            {
                    mContext.mGBufferTargetA->getTarget(),
                    RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
                    RESOURCE_STATE_UNORDERED_ACCESS
             },
            {
                    mContext.mGBufferTargetB->getTarget(),
                    RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
                    RESOURCE_STATE_UNORDERED_ACCESS
             },
            {
                    mContext.mGBufferTargetC->getTarget(),
                    RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
                    RESOURCE_STATE_UNORDERED_ACCESS
             },
            {
                    mContext.mGBufferTargetD->getTarget(),
                    RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
                    RESOURCE_STATE_UNORDERED_ACCESS
             }
        };

        rs->resourceBarrier(0, nullptr, textureBarriers.size(), textureBarriers.data(), 0, nullptr);
    }
    uint32_t frameIndex = Ogre::Root::getSingleton().getCurrentFrameIndex();
    rs->pushGroupMarker("GBuffer", Ogre::Vector3i(0.0, 0.0, 1.0f));
    rs->bindPipeline(mProgramHandle, &mGBufferZeroSets[frameIndex], 1);
    rs->traceRay(mProgramHandle, ogreConfig.width, ogreConfig.height, 1);
    rs->popGroupMarker();

    {
        std::vector<Ogre::TextureBarrier> textureBarriers =
        {
            {
                    mContext.mGBufferTargetA->getTarget(),
                    RESOURCE_STATE_UNORDERED_ACCESS,
                    RESOURCE_STATE_PIXEL_SHADER_RESOURCE
             },
            {
                    mContext.mGBufferTargetB->getTarget(),
                    RESOURCE_STATE_UNORDERED_ACCESS,
                    RESOURCE_STATE_PIXEL_SHADER_RESOURCE
             },
            {
                    mContext.mGBufferTargetC->getTarget(),
                    RESOURCE_STATE_UNORDERED_ACCESS,
                    RESOURCE_STATE_PIXEL_SHADER_RESOURCE
             },
            {
                    mContext.mGBufferTargetD->getTarget(),
                    RESOURCE_STATE_UNORDERED_ACCESS,
                    RESOURCE_STATE_PIXEL_SHADER_RESOURCE
             }
        };

        rs->resourceBarrier(0, nullptr, textureBarriers.size(), textureBarriers.data(), 0, nullptr);
    }
    
}

bool GBuffer::loadAndCompileShaders()
{
    RaytracingShaderInfo shaderInfo;
    addMacro(shaderInfo, "RTXGI_BINDLESS_TYPE", std::to_string(RTXGI_BINDLESS_TYPE_RESOURCE_ARRAYS));
    addMacro(shaderInfo, "HLSL", "1");
    addMacro(shaderInfo, "RAYTRACING", "1");
    shaderInfo.args.push_back(L"-D __spirv__");
    shaderInfo.rayGenShaderName = "GBufferRGS.hlsl";
    shaderInfo.rayGenEntryName = "RayGen";

    shaderInfo.rayClosethitShaderName = "GBufferClosethit.hlsl";
    shaderInfo.rayClosethitEntryName = "CHS_PRIMARY";

    shaderInfo.rayMissShaderName = "GBufferMiss.hlsl";
    shaderInfo.rayMissEntryName = "Miss";

    shaderInfo.rayAnyHitShaderName = "GBufferAnyhit.hlsl";
    shaderInfo.rayAnyHitEntryName = "AHS_PRIMARY";

    RenderSystem* rs = Ogre::Root::getSingleton().getRenderSystem();

    mProgramHandle = rs->createRaytracingProgram(shaderInfo);
    mGBufferZeroSets.resize(mContext.frameCount);
    for (uint32_t i = 0; i < mContext.frameCount; i++)
    {
        mGBufferZeroSets[i] = rs->createDescriptorSet(mProgramHandle, 0);
    }
    return true;
}

void GBuffer::updateDescriptorSet()
{
    DescriptorData descriptorData[16];

    auto* rs = Ogre::Root::getSingleton().getRenderSystem();
    
    descriptorData[0].mCount = 1;
    descriptorData[0].pName = "GlobalConst";
    descriptorData[0].descriptorType = DESCRIPTOR_TYPE_BUFFER;
    descriptorData[0].ppBuffers = &mContext.mGlobalConstHandle;

    descriptorData[1].mCount = 3;
    descriptorData[1].pName = "Samplers";
    descriptorData[1].descriptorType = DESCRIPTOR_TYPE_SAMPLER;
    descriptorData[1].ppSamplers = &mContext.mSamplerHandle[0];

    descriptorData[2].mCount = 1;
    descriptorData[2].pName = "CameraCB";
    descriptorData[2].descriptorType = DESCRIPTOR_TYPE_BUFFER;
    descriptorData[2].ppBuffers = &mContext.mCameraBufferHandle;

    descriptorData[3].mCount = 1;
    descriptorData[3].pName = "Lights";
    descriptorData[3].descriptorType = DESCRIPTOR_TYPE_BUFFER;
    descriptorData[3].ppBuffers = &mContext.mLightBufferHandle;

    descriptorData[4].mCount = 1;
    descriptorData[4].pName = "Materials";
    descriptorData[4].descriptorType = DESCRIPTOR_TYPE_BUFFER;
    descriptorData[4].ppBuffers = &mContext.materialBufferHandle;

    descriptorData[5].mCount = 1;
    descriptorData[5].pName = "TLASInstances";
    descriptorData[5].descriptorType = DESCRIPTOR_TYPE_BUFFER;
    descriptorData[5].ppBuffers = &mContext.pTopAS->instanceDescBuffer;

    std::array<OgreTexture*, 6> rwTex2D=
    {
        mContext.mGBufferTargetA->getTarget(),
        mContext.mGBufferTargetB->getTarget(),
        mContext.mGBufferTargetC->getTarget(),
        mContext.mGBufferTargetD->getTarget()
    };
    descriptorData[6].mCount = rwTex2D.size();
    descriptorData[6].pName = "RWTex2D";
    descriptorData[6].descriptorType = DESCRIPTOR_TYPE_TEXTURE;
    descriptorData[6].ppTextures = (const OgreTexture**)rwTex2D.data();

    descriptorData[7].mCount = 1;
    descriptorData[7].pName = "TLAS";
    descriptorData[7].descriptorType = DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE;
    descriptorData[7].pAS = mContext.pTopAS;

    descriptorData[8].mCount = 1;
    descriptorData[8].pName = "GeometryDatas";
    descriptorData[8].descriptorType = DESCRIPTOR_TYPE_BUFFER;
    descriptorData[8].ppBuffers = &mContext.geometryBufferHandle;

  
    std::vector<OgreTexture*> tex2D;


    for (auto tex : mContext.sceneTextureList)
    {
        tex2D.push_back(tex);
    }
    descriptorData[9].mCount = tex2D.size();
    descriptorData[9].pName = "Tex2D";
    descriptorData[9].descriptorType = DESCRIPTOR_TYPE_TEXTURE;
    descriptorData[9].ppTextures = (const OgreTexture**)tex2D.data();

    std::vector<Handle<HwBufferObject>> buffers;
    buffers.push_back(mContext.geometryBufferHandle);
    buffers.push_back(mContext.geometryBufferHandle);
    for (uint32_t i = 0; i < mContext.mIndexBufferList.size(); i++)
    {
        buffers.push_back(mContext.mIndexBufferList[i]);
        buffers.push_back(mContext.mVertexBufferList[i]);
    }

    descriptorData[10].mCount = buffers.size();
    descriptorData[10].pName = "ByteAddrBuffer";
    descriptorData[10].descriptorType = DESCRIPTOR_TYPE_RW_BUFFER;
    descriptorData[10].ppBuffers = buffers.data();


    for (uint32_t i = 0; i < mContext.frameCount; i++)
    {
        BufferView globalConstBufferView;
        globalConstBufferView.buffer = mContext.mGlobalConstHandle;
        globalConstBufferView.offset = GlobalConstants::GetAlignedSizeInBytes() * i;
        descriptorData[0].mCount = 1;
        descriptorData[0].pName = "GlobalConst";
        descriptorData[0].descriptorType = DESCRIPTOR_TYPE_BUFFER_VIEW;
        descriptorData[0].pBufferView = &globalConstBufferView;

        BufferView cameraCBBufferView;
        cameraCBBufferView.buffer = mContext.mCameraBufferHandle;
        cameraCBBufferView.offset = SDFGICameraInfo::GetAlignedSizeInBytes() * i;
        descriptorData[2].mCount = 1;
        descriptorData[2].pName = "CameraCB";
        descriptorData[2].descriptorType = DESCRIPTOR_TYPE_BUFFER_VIEW;
        descriptorData[2].pBufferView = &cameraCBBufferView;

        rs->updateDescriptorSet(mGBufferZeroSets[i], 11, descriptorData);
    }
    
}