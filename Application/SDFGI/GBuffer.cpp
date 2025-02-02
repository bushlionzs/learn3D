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
    rs->pushGroupMarker("GBuffer", Ogre::Vector3i(0.0, 0.0, 1.0f));
    rs->bindPipeline(mProgramHandle, setlist.data(), setlist.size());
    rs->traceRay(mProgramHandle, ogreConfig.width, ogreConfig.height, 1);
    rs->popGroupMarker();
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

    mGBufferZeroSet = rs->createDescriptorSet(mProgramHandle, 0);
    mGBufferFirstSet = rs->createDescriptorSet(mProgramHandle, 1);
    mGBufferThirdSet = rs->createDescriptorSet(mProgramHandle, 3);

    setlist.push_back(mGBufferZeroSet);
    setlist.push_back(mGBufferFirstSet);
    setlist.push_back(mGBufferThirdSet);

    return true;
}

void GBuffer::updateDescriptorSet()
{
    DescriptorData descriptorData[16];

    descriptorData[0].mCount = 1;
    descriptorData[0].pName = "GlobalConst";
    descriptorData[0].descriptorType = DESCRIPTOR_TYPE_SAMPLER;
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

    auto* rs = Ogre::Root::getSingleton().getRenderSystem();
    rs->updateDescriptorSet(mGBufferZeroSet, 9, descriptorData);


    std::vector<OgreTexture*> tex2D;
    //tex2D.push_back(nullptr);
    //tex2D.push_back(nullptr);

    for (auto tex : mContext.sceneTextureList)
    {
        tex2D.push_back(tex);
    }
    descriptorData[0].mCount = tex2D.size();
    descriptorData[0].pName = "Tex2D";
    descriptorData[0].descriptorType = DESCRIPTOR_TYPE_TEXTURE;
    descriptorData[0].ppTextures = (const OgreTexture**)tex2D.data();
    rs->updateDescriptorSet(mGBufferFirstSet, 1, descriptorData);

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

    rs->updateDescriptorSet(mGBufferThirdSet, 1, descriptorData);
}