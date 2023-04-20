#include "OgreHeader.h"
#include "gltf_helper.h"
#include "tiny_gltf.h"

int GetFormatSize(int id)
{
    switch (id)
    {
    case TINYGLTF_COMPONENT_TYPE_BYTE: return 1;
    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE: return 1;
    case TINYGLTF_COMPONENT_TYPE_SHORT: return 2;
    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT: return 2;
    case TINYGLTF_COMPONENT_TYPE_INT: return 4;
    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT: return 4;
    case TINYGLTF_COMPONENT_TYPE_FLOAT: return 4;
    case TINYGLTF_COMPONENT_TYPE_DOUBLE: return 8;
    }

    assert(false);
    return -1;
}

VertexElementType GetEngineFormat(int id)
{
    switch (id)
    {
        //case TINYGLTF_COMPONENT_TYPE_BYTE: return 1;
        //case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE: return 1;
    case TINYGLTF_COMPONENT_TYPE_SHORT: return VET_SHORT2;
    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT: return VET_USHORT2;
    case TINYGLTF_COMPONENT_TYPE_INT: return VET_INT4;
    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT: return VET_UINT4;
    case TINYGLTF_COMPONENT_TYPE_FLOAT: return VET_FLOAT3;
    }

    assert(false);
    return VET_SHORT2;
}

VertexElementSemantic GetEngineSemantic(const std::string& semantic)
{
    static std::unordered_map<std::string, VertexElementSemantic> semanticMap =
    {
        {"POSITION", VES_POSITION},
        {"NORMAL", VES_NORMAL},
        {"TEXCOORD_0", VES_TEXTURE_COORDINATES},
        {"JOINTS_0", VES_BLEND_INDICES},
        {"WEIGHTS_0", VES_BLEND_WEIGHTS}
    };

    auto itor = semanticMap.find(semantic);

    if (itor == semanticMap.end())
    {
        assert(false);
    }

    return itor->second;
}

int GetTypeSize(int type)
{
    switch (type)
    {
    case TINYGLTF_TYPE_VEC2:   return 2;
    case TINYGLTF_TYPE_VEC3:   return 3;
    case TINYGLTF_TYPE_VEC4:   return 4;
    case TINYGLTF_TYPE_MAT2:   return 4;
    case TINYGLTF_TYPE_MAT3:   return 9;
    case TINYGLTF_TYPE_MAT4:   return 16;
    case TINYGLTF_TYPE_SCALAR: return 1;
    }
    assert(false);
    return 0;
}

int GetComponentTypeSize(int componentType)
{
    switch (componentType)
    {
    case TINYGLTF_COMPONENT_TYPE_BYTE: return 1;
    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE: return 1;
    case TINYGLTF_COMPONENT_TYPE_SHORT: return 2;
    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT: return 2;
    case TINYGLTF_COMPONENT_TYPE_INT: return 4;
    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT: return 4;
    case TINYGLTF_COMPONENT_TYPE_FLOAT: return 4;
    }

    assert(false);
    return 0;
}

// Returns dxgi format based on tinygltf type
DXGI_FORMAT GetFormat(int type, int id)
{
    if (type == TINYGLTF_TYPE_SCALAR)
    {
        switch (id)
        {
        case TINYGLTF_COMPONENT_TYPE_BYTE: return DXGI_FORMAT_R8_SINT;
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE: return DXGI_FORMAT_R8_UINT;
        case TINYGLTF_COMPONENT_TYPE_SHORT: return DXGI_FORMAT_R16_SINT;
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT: return DXGI_FORMAT_R16_UINT;
        case TINYGLTF_COMPONENT_TYPE_INT: return DXGI_FORMAT_R32_SINT;
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT: return DXGI_FORMAT_R32_UINT;
        case TINYGLTF_COMPONENT_TYPE_FLOAT: return DXGI_FORMAT_R32_FLOAT;
        }
    }
    else if (type == TINYGLTF_TYPE_VEC2)
    {
        switch (id)
        {
        case TINYGLTF_COMPONENT_TYPE_BYTE: return DXGI_FORMAT_R8G8_SINT;
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE: return DXGI_FORMAT_R8G8_UINT;
        case TINYGLTF_COMPONENT_TYPE_SHORT: return DXGI_FORMAT_R16G16_SINT;
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT: return DXGI_FORMAT_R16G16_UINT;
        case TINYGLTF_COMPONENT_TYPE_INT: return DXGI_FORMAT_R32G32_SINT;
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT: return DXGI_FORMAT_R32G32_UINT;
        case TINYGLTF_COMPONENT_TYPE_FLOAT: return DXGI_FORMAT_R32G32_FLOAT;
        }
    }
    else if (type == TINYGLTF_TYPE_VEC3)
    {
        switch (id)
        {
        case TINYGLTF_COMPONENT_TYPE_BYTE: return DXGI_FORMAT_UNKNOWN; //(BYTE)
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE: return DXGI_FORMAT_UNKNOWN; //(UNSIGNED_BYTE)1
        case TINYGLTF_COMPONENT_TYPE_SHORT: return DXGI_FORMAT_UNKNOWN; //(SHORT)2
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT: return DXGI_FORMAT_UNKNOWN; //(UNSIGNED_SHORT)2
        case TINYGLTF_COMPONENT_TYPE_INT: return DXGI_FORMAT_R32G32B32_SINT; //(SIGNED_INT)4
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT: return DXGI_FORMAT_R32G32B32_UINT; //(UNSIGNED_INT)4
        case TINYGLTF_COMPONENT_TYPE_FLOAT: return DXGI_FORMAT_R32G32B32_FLOAT; //(FLOAT)
        }
    }
    else if (type == TINYGLTF_TYPE_VEC4)
    {
        switch (id)
        {
        case TINYGLTF_COMPONENT_TYPE_BYTE: return DXGI_FORMAT_R8G8B8A8_SINT; //(BYTE)
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE: return DXGI_FORMAT_R8G8B8A8_UINT; //(UNSIGNED_BYTE)1
        case TINYGLTF_COMPONENT_TYPE_SHORT: return DXGI_FORMAT_R16G16B16A16_SINT; //(SHORT)2
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT: return DXGI_FORMAT_R16G16B16A16_UINT; //(UNSIGNED_SHORT)2
        case TINYGLTF_COMPONENT_TYPE_INT: return DXGI_FORMAT_R32G32B32A32_SINT; //(SIGNED_INT)4
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT: return DXGI_FORMAT_R32G32B32A32_UINT; //(UNSIGNED_INT)4
        case TINYGLTF_COMPONENT_TYPE_FLOAT: return DXGI_FORMAT_R32G32B32A32_FLOAT; //(FLOAT)
        }
    }
    assert(false);
    return DXGI_FORMAT_UNKNOWN;
}

int GetStrideFromFormat(int type, int id)
{
    if (type == TINYGLTF_TYPE_SCALAR)
    {
        switch (id)
        {
        case TINYGLTF_COMPONENT_TYPE_BYTE: return 1;
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE: return 1;
        case TINYGLTF_COMPONENT_TYPE_SHORT: return 2;
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT: return 2;
        case TINYGLTF_COMPONENT_TYPE_INT: return 4;
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT: return 4;
        case TINYGLTF_COMPONENT_TYPE_FLOAT: return 4;
        }
    }
    else if (type == TINYGLTF_TYPE_VEC2)
    {
        switch (id)
        {
        case TINYGLTF_COMPONENT_TYPE_BYTE: return 2;
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE: return 2;
        case TINYGLTF_COMPONENT_TYPE_SHORT: return 4;
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT: return 4;
        case TINYGLTF_COMPONENT_TYPE_INT: return 8;
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT: return 8;
        case TINYGLTF_COMPONENT_TYPE_FLOAT: return 8;
        }
    }
    else if (type == TINYGLTF_TYPE_VEC3)
    {
        switch (id)
        {
        case TINYGLTF_COMPONENT_TYPE_BYTE: return 4; //(BYTE)
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE: return 4; //(UNSIGNED_BYTE)1
        case TINYGLTF_COMPONENT_TYPE_SHORT: return 4; //(SHORT)2
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT: return 4; //(UNSIGNED_SHORT)2
        case TINYGLTF_COMPONENT_TYPE_INT: return 12; //(SIGNED_INT)4
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT: return 12; //(UNSIGNED_INT)4
        case TINYGLTF_COMPONENT_TYPE_FLOAT: return 12; //(FLOAT)
        }
    }
    else if (type == TINYGLTF_TYPE_VEC4)
    {
        switch (id)
        {
        case TINYGLTF_COMPONENT_TYPE_BYTE: return 4; //(BYTE)
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE: return 4; //(UNSIGNED_BYTE)1
        case TINYGLTF_COMPONENT_TYPE_SHORT: return 8; //(SHORT)2
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT: return 8; //(UNSIGNED_SHORT)2
        case TINYGLTF_COMPONENT_TYPE_INT: return 16; //(SIGNED_INT)4
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT: return 16; //(UNSIGNED_INT)4
        case TINYGLTF_COMPONENT_TYPE_FLOAT: return 16; //(FLOAT)
        }
    }


    assert(false);
    return 0;
}