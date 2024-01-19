#pragma once
#define OGRE_STREAM_TEMP_SIZE 128

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

typedef struct VertexBoneAssignment_s
{
    unsigned int vertexIndex;
    unsigned short boneIndex;
    Real weight;

} VertexBoneAssignment;

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
    EngineType_Count
};

enum ShaderType
{
    ShaderType_Vertex = 0,
    ShaderType_Frag = 1,
    ShaderType_Count
};