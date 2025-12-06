#pragma once
#include "ddgiTypes.h"
#include "DDGIRootConstants.h"
#include "DDGIVolume.h"
#include "pass.h"
#include "Configs.h"
class DDGIVolume;
struct SDFGIContext
{
    AccelerationStructure* pBottomAS;
    AccelerationStructure* pTopAS;

    Ogre::Entity* pEntity;

    std::vector<SDFDIMaterial> materialList;
    Handle<HwBufferObject> materialBufferHandle;
    std::vector<GeometryData> geometryNodes;
    Handle<HwBufferObject> geometryBufferHandle;
    std::vector<Handle<HwBufferObject>> mIndexBufferList;
    std::vector<Handle<HwBufferObject>> mVertexBufferList;
    std::vector<OgreTexture*> sceneTextureList;

    GlobalConstants mGlobalConstants;
    Handle<HwBufferObject> mGlobalConstHandle;
    DDGIRootConstants mDDGI;
    Handle<HwBufferObject> mDDGIHandle;

    Handle<HwSampler> mSamplerHandle[3];

    SDFGICameraInfo mSDFGICameraInfo;
    Handle<HwBufferObject> mCameraBufferHandle;
    std::vector<SDFGILight> mlights;
    Handle<HwBufferObject> mLightBufferHandle; //Light
    std::vector<DDGIVolumeResourceIndices> mVolumeResourceIndices;
    std::vector<Handle<HwBufferObject>> mDDGIVolumeResourceIndicesHandles;

    std::vector<DDGIVolumeDescGPUPacked> mVolumeDescGPUPacked;
    std::vector<Handle<HwBufferObject>> mDDGIVolumeDescGPUPackedHandles;

    Ogre::RenderTarget* mGBufferTargetA;
    Ogre::RenderTarget* mGBufferTargetB;
    Ogre::RenderTarget* mGBufferTargetC;
    Ogre::RenderTarget* mGBufferTargetD;
    Ogre::RenderTarget* mIndirectTarget;

    Handle<HwBufferObject> mVolumeConstantsHandle;

    std::vector<DDGIVolumeDesc> volumeDescs;
    std::vector<DDGIVolume*> volumes;

    Configs::Config mConfig;

    uint32_t frameCount;
};

#define RTXGI_COORDINATE_SYSTEM_LEFT 0
#define RTXGI_COORDINATE_SYSTEM_LEFT_Z_UP 1
#define RTXGI_COORDINATE_SYSTEM_RIGHT 2
#define RTXGI_COORDINATE_SYSTEM_RIGHT_Z_UP 3

#define RTXGI_BINDLESS_TYPE_RESOURCE_ARRAYS 0
#define RTXGI_DDGI_BLEND_SHARED_MEMORY 1
#define RTXGI_DDGI_BINDLESS_RESOURCES 1
#define RTXGI_DDGI_RESOURCE_MANAGEMENT 0
#define RTXGI_COORDINATE_SYSTEM 2
#define RTXGI_DDGI_SHADER_REFLECTION 0 
#define RTXGI_DDGI_DEBUG_PROBE_INDEXING 0 
#define RTXGI_DDGI_DEBUG_OCTAHEDRAL_INDEXING 0
#define RTXGI_DDGI_DEBUG_BORDER_COPY_INDEXING 0

#define SAFE_DELETE(x) { if(x) delete x; x = NULL; }

void addMacro(RaytracingShaderInfo& shaderInfo, std::string first, std::string second);

void addMacro(ShaderInfo& shaderInfo, std::string first, std::string second);