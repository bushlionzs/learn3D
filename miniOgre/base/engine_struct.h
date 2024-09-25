#pragma once
#define OGRE_STREAM_TEMP_SIZE 128
#include <OgreHeader.h>
enum RenderListType
{
    RenderListType_Opaque = 0,
    RenderListType_Transparent
};

class EngineRenderList
{
public:
    std::vector<Ogre::Renderable*> mOpaqueList;
    std::vector<Ogre::Renderable*> mTransparentList;
};

class CubeMatrix
{
public:
    Ogre::Matrix4 view;
    Ogre::Matrix4 proj;
};

class TransformInfo
{
public:
    Ogre::Vector3 translate;
    Ogre::Quaternion rotate;
    Ogre::Vector3 scale;
};

class RawData
{
public:
    const char* mData;
    uint32_t mDataSize;
    uint32_t mDataStride;
};

class IndexDataView
{
public:
    uint32_t mIndexCount;
    uint32_t mIndexLocation;
    uint32_t mBaseVertexLocation;
};

class RawDataView
{
public:
    uint32_t mVertexStart;
    uint32_t mVertexCount;
};

typedef struct 
{
    unsigned int vertexIndex;
    unsigned short boneIndex;
    Real weight;

} VertexBoneAssignment;

typedef union ClearValue
{
    struct
    {
        float r;
        float g;
        float b;
        float a;
    };
    struct
    {
        float    depth;
        uint32_t stencil;
    };
} ClearValue;

typedef struct BindRenderTargetDesc
{
    Ogre::RenderTarget* renderTarget;
    ClearValue clearColour;
} BindRenderTargetDesc;

typedef struct BindDepthTargetDesc
{
    Ogre::RenderTarget* depthStencil;
    ClearValue      clearValue;
} BindDepthTargetDesc;

enum
{
    MAX_INSTANCE_EXTENSIONS = 64,
    MAX_DEVICE_EXTENSIONS = 64,
    /// Max number of GPUs in SLI or Cross-Fire
    MAX_LINKED_GPUS = 4,
    /// Max number of GPUs in unlinked mode
    MAX_UNLINKED_GPUS = 4,
    /// Max number of GPus for either linked or unlinked mode. must update WindowsBase::setupPlatformUI accordingly
    MAX_MULTIPLE_GPUS = 4,
    MAX_RENDER_TARGET_ATTACHMENTS = 8,
    MAX_VERTEX_BINDINGS = 15,
    MAX_VERTEX_ATTRIBS = 15,
    MAX_RESOURCE_NAME_LENGTH = 256,
    MAX_SEMANTIC_NAME_LENGTH = 128,
    MAX_DEBUG_NAME_LENGTH = 128,
    MAX_MIP_LEVELS = 0xFFFFFFFF,
    MAX_SWAPCHAIN_IMAGES = 3,
    MAX_GPU_VENDOR_STRING_LENGTH = 256, // max size for GPUVendorPreset strings
    MAX_SAMPLE_LOCATIONS = 16,
};

struct RenderPassInfo
{
    uint32_t renderTargetCount = 1;
    BindRenderTargetDesc renderTargets[MAX_RENDER_TARGET_ATTACHMENTS];
    BindDepthTargetDesc  depthTarget;
    Ogre::Matrix4 lightViewProj;
    Ogre::OgreTexture* shadowMap = nullptr;
    Ogre::ICamera* cam = nullptr;
    bool shadowPass = false;
};

class SkinnedData
{
public:
    float boneWeight[4];
    uint32_t boneIndices[4];
};


enum EngineType
{
    EngineType_Dx11 = 0,
    EngineType_Dx12,
    EngineType_Vulkan,
    EngineType_VulkanRaytracing,
    EngineType_Count
};
