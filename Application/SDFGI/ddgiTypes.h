/*
* Copyright (c) 2019-2023, NVIDIA CORPORATION.  All rights reserved.
*
* NVIDIA CORPORATION and its licensors retain all intellectual property
* and proprietary rights in and to this software, related documentation
* and any modifications thereto.  Any use, reproduction, disclosure or
* distribution of this software and related documentation without an express
* license agreement from NVIDIA CORPORATION is strictly prohibited.
*/

#pragma once

#include <OgreHeader.h>
#include "rayTracing.h"

enum COMPOSITE_USE_FLAGS
{
    COMPOSITE_FLAG_USE_NONE = 0,
    COMPOSITE_FLAG_USE_RTAO = 0x1,
    COMPOSITE_FLAG_USE_DDGI = 0x2
};

enum COMPOSITE_SHOW_FLAGS
{
    COMPOSITE_FLAG_SHOW_NONE = 0,
    COMPOSITE_FLAG_SHOW_RTAO = 0x1,
    COMPOSITE_FLAG_SHOW_DDGI_INDIRECT = 0x2,
    COMPOSITE_FLAG_SHOW_DDGI_VOLUME_PROBES = 0x4,
    COMPOSITE_FLAG_SHOW_DDGI_VOLUME_TEXTURES = 0x8
};

enum POSTPROCESS_USE_FLAGS
{
    POSTPROCESS_FLAG_USE_NONE = 0,
    POSTPROCESS_FLAG_USE_EXPOSURE = 0x1,
    POSTPROCESS_FLAG_USE_TONEMAPPING = 0x2,
    POSTPROCESS_FLAG_USE_DITHER = 0x4,
    POSTPROCESS_FLAG_USE_GAMMA = 0x8,
};


enum class ELightType
{
    DIRECTIONAL,
    SPOT,
    POINT,
    COUNT
};

enum ERTXGIStatus
{
    OK = 0,
    ERROR_DDGI_INVALID_PROBE_COUNTS,
    ERROR_DDGI_INVALID_RESOURCE_INDICES_BUFFER,
    ERROR_DDGI_INVALID_RESOURCE_INDICES_UPLOAD_BUFFER,
    ERROR_DDGI_INVALID_CONSTANTS_BUFFER,
    ERROR_DDGI_INVALID_CONSTANTS_UPLOAD_BUFFER,
    ERROR_DDGI_INVALID_RESOURCES_DESC,
    ERROR_DDGI_MAP_FAILURE_RESOURCE_INDICES_UPLOAD_BUFFER,
    ERROR_DDGI_MAP_FAILURE_CONSTANTS_UPLOAD_BUFFER,
    ERROR_DDGI_MAP_FAILURE_VARIABILITY_READBACK_BUFFER,

    ERROR_DDGI_D3D12_INVALID_RESOURCE_DESCRIPTOR_HEAP,

    ERROR_DDGI_VK_INVALID_RESOURCE_INDICES_UPLOAD_MEMORY,
    ERROR_DDGI_VK_INVALID_CONSTANTS_UPLOAD_MEMORY,

    ERROR_DDGI_INVALID_BYTECODE_PROBE_BLENDING_IRRADIANCE,
    ERROR_DDGI_INVALID_BYTECODE_PROBE_BLENDING_DISTANCE,
    ERROR_DDGI_INVALID_BYTECODE_PROBE_RELOCATION,
    ERROR_DDGI_INVALID_BYTECODE_PROBE_RELOCATION_RESET,
    ERROR_DDGI_INVALID_BYTECODE_PROBE_CLASSIFICATION,
    ERROR_DDGI_INVALID_BYTECODE_PROBE_CLASSIFICATION_RESET,
    ERROR_DDGI_INVALID_BYTECODE_PROBE_VARIABILITY_REDUCTION,
    ERROR_DDGI_INVALID_BYTECODE_PROBE_VARIABILITY_EXTRA_REDUCTION,

    ERROR_DDGI_ALLOCATE_FAILURE_TEXTURE_PROBE_RAY_DATA,
    ERROR_DDGI_ALLOCATE_FAILURE_TEXTURE_PROBE_IRRADIANCE,
    ERROR_DDGI_ALLOCATE_FAILURE_TEXTURE_PROBE_DISTANCE,
    ERROR_DDGI_ALLOCATE_FAILURE_TEXTURE_PROBE_DATA,
    ERROR_DDGI_ALLOCATE_FAILURE_TEXTURE_PROBE_VARIABILITY,
    ERROR_DDGI_ALLOCATE_FAILURE_TEXTURE_PROBE_VARIABILITY_AVERAGE,

    ERROR_DDGI_D3D12_INVALID_DEVICE,
    ERROR_DDGI_D3D12_CREATE_FAILURE_PSO,
    ERROR_DDGI_D3D12_CREATE_FAILURE_ROOT_SIGNATURE,
    ERROR_DDGI_D3D12_CREATE_FAILURE_DESCRIPTORS,

    ERROR_DDGI_VK_INVALID_DEVICE,
    ERROR_DDGI_VK_INVALID_PHYSICAL_DEVICE,
    ERROR_DDGI_VK_INVALID_DESCRIPTOR_POOL,
    ERROR_DDGI_VK_CREATE_FAILURE_LAYOUTS,
    ERROR_DDGI_VK_CREATE_FAILURE_PIPELINE,
    ERROR_DDGI_VK_CREATE_FAILURE_DESCRIPTOR_SET,

    // Unmanaged Resource Mode (Application manages volume resources)
    ERROR_DDGI_INVALID_TEXTURE_PROBE_RAY_DATA,
    ERROR_DDGI_INVALID_TEXTURE_PROBE_IRRADIANCE,
    ERROR_DDGI_INVALID_TEXTURE_PROBE_DISTANCE,
    ERROR_DDGI_INVALID_TEXTURE_PROBE_DATA,
    ERROR_DDGI_INVALID_TEXTURE_PROBE_VARIABILITY,
    ERROR_DDGI_INVALID_TEXTURE_PROBE_VARIABILITY_AVERAGE,
    ERROR_DDGI_INVALID_TEXTURE_PROBE_VARIABILITY_READBACK,

    ERROR_DDGI_D3D12_INVALID_ROOT_SIGNATURE,
    ERROR_DDGI_D3D12_INVALID_DESCRIPTOR,
    ERROR_DDGI_D3D12_INVALID_PSO_PROBE_BLENDING_IRRADIANCE,
    ERROR_DDGI_D3D12_INVALID_PSO_PROBE_BLENDING_DISTANCE,
    ERROR_DDGI_D3D12_INVALID_PSO_PROBE_RELOCATION,
    ERROR_DDGI_D3D12_INVALID_PSO_PROBE_RELOCATION_RESET,
    ERROR_DDGI_D3D12_INVALID_PSO_PROBE_CLASSIFICATION,
    ERROR_DDGI_D3D12_INVALID_PSO_PROBE_CLASSIFICATION_RESET,
    ERROR_DDGI_D3D12_INVALID_PSO_PROBE_REDUCTION,
    ERROR_DDGI_D3D12_INVALID_PSO_PROBE_EXTRA_REDUCTION,

    ERROR_DDGI_VK_INVALID_DESCRIPTOR_SET,
    ERROR_DDGI_VK_INVALID_PIPELINE_LAYOUT,
    ERROR_DDGI_VK_INVALID_IMAGE_MEMORY_PROBE_RAY_DATA,
    ERROR_DDGI_VK_INVALID_IMAGE_MEMORY_PROBE_IRRADIANCE,
    ERROR_DDGI_VK_INVALID_IMAGE_MEMORY_PROBE_DISTANCE,
    ERROR_DDGI_VK_INVALID_IMAGE_MEMORY_PROBE_DATA,
    ERROR_DDGI_VK_INVALID_IMAGE_MEMORY_PROBE_VARIABILITY,
    ERROR_DDGI_VK_INVALID_IMAGE_MEMORY_PROBE_VARIABILITY_AVERAGE,
    ERROR_DDGI_VK_INVALID_IMAGE_MEMORY_PROBE_VARIABILITY_READBACK,
    ERROR_DDGI_VK_INVALID_IMAGE_VIEW_PROBE_RAY_DATA,
    ERROR_DDGI_VK_INVALID_IMAGE_VIEW_PROBE_IRRADIANCE,
    ERROR_DDGI_VK_INVALID_IMAGE_VIEW_PROBE_DISTANCE,
    ERROR_DDGI_VK_INVALID_IMAGE_VIEW_PROBE_DATA,
    ERROR_DDGI_VK_INVALID_IMAGE_VIEW_PROBE_VARIABILITY,
    ERROR_DDGI_VK_INVALID_IMAGE_VIEW_PROBE_VARIABILITY_AVERAGE,
    ERROR_DDGI_VK_INVALID_IMAGE_VIEW_PROBE_VARIABILITY_READBACK,
    ERROR_DDGI_VK_INVALID_SHADER_MODULE_PROBE_BLENDING_IRRADIANCE,
    ERROR_DDGI_VK_INVALID_SHADER_MODULE_PROBE_BLENDING_DISTANCE,
    ERROR_DDGI_VK_INVALID_SHADER_MODULE_PROBE_RELOCATION,
    ERROR_DDGI_VK_INVALID_SHADER_MODULE_PROBE_RELOCATION_RESET,
    ERROR_DDGI_VK_INVALID_SHADER_MODULE_PROBE_CLASSIFICATION,
    ERROR_DDGI_VK_INVALID_SHADER_MODULE_PROBE_CLASSIFICATION_RESET,
    ERROR_DDGI_VK_INVALID_SHADER_MODULE_PROBE_VARIABILITY_REDUCTION,
    ERROR_DDGI_VK_INVALID_SHADER_MODULE_PROBE_VARIABILITY_EXTRA_REDUCTION,
    ERROR_DDGI_VK_INVALID_PIPELINE_PROBE_BLENDING_IRRADIANCE,
    ERROR_DDGI_VK_INVALID_PIPELINE_PROBE_BLENDING_DISTANCE,
    ERROR_DDGI_VK_INVALID_PIPELINE_PROBE_RELOCATION,
    ERROR_DDGI_VK_INVALID_PIPELINE_PROBE_RELOCATION_RESET,
    ERROR_DDGI_VK_INVALID_PIPELINE_PROBE_CLASSIFICATION,
    ERROR_DDGI_VK_INVALID_PIPELINE_PROBE_CLASSIFICATION_RESET,
    ERROR_DDGI_VK_INVALID_PIPELINE_PROBE_VARIABILITY_REDUCTION,
    ERROR_DDGI_VK_INVALID_PIPELINE_PROBE_VARIABILITY_EXTRA_REDUCTION,

    // ---------------------------------------------------------------
};


#define RTXGI_PERF_MARKER_RED         Ogre::Vector3i(204, 28, 41)
#define RTXGI_PERF_MARKER_GREEN    Ogre::Vector3i(105, 148, 79)
#define RTXGI_PERF_MARKER_BLUE       Ogre::Vector3i(65, 126, 211)
#define RTXGI_PERF_MARKER_ORANGE Ogre::Vector3i(217, 122, 46)
#define RTXGI_PERF_MARKER_YELLOW  Ogre::Vector3i(217, 207, 46)
#define RTXGI_PERF_MARKER_PURPLE   Ogre::Vector3i(152, 78, 163)
#define RTXGI_PERF_MARKER_BROWN  Ogre::Vector3i(166, 86, 40)
#define RTXGI_PERF_MARKER_GREY       Ogre::Vector3i(190, 190, 190)



struct Payload
{                                         // Byte Offset
    Ogre::Vector3  albedo;                       // 12
    float   opacity;                      // 16
    Ogre::Vector3  worldPosition;                // 28
    float   metallic;                     // 32
    Ogre::Vector3  normal;                       // 44
    float   roughness;                    // 48
    Ogre::Vector3  shadingNormal;                // 60
    float   hitT;                         // 64
    uint32_t    hitKind;                      // 68
};

struct PackedPayload
{                                  // Byte Offset        Data Format
    float  hitT;                   // 0                  HitT
    Ogre::Vector3 worldPosition;          // 4               X: World Position X
                                    // 8               Y: World Position Y
                                    // 12              Z: World Position Z
    uint32_t  packed0[4];                // 16              X: 16: Albedo R          16: Albedo G
                                    //                 Y: 16: Albedo B          16: Normal X
                                    //                 Z: 16: Normal Y          16: Normal Z
                                    //                 W: 16: Metallic          16: Roughness
    Ogre::Vector3i  packed1;                // 32              X: 16: ShadingNormal X   16: ShadingNormal Y
                                    //                 Y: 16: ShadingNormal Z   16: Opacity
                                    //                 Z: 16: Hit Kind          16: Unused
                                    // 44
};

struct ProbeVisualizationPayload
{
    float  hitT;
    Ogre::Vector3 worldPosition;
    int    instanceIndex;
    uint32_t   volumeIndex;
    uint32_t   instanceOffset;
};

struct MinimalPayload
{
    Ogre::Vector3 radiance;
    float  hitT;
};

struct Vertex
{
    Ogre::Vector3 position;
    Ogre::Vector3 normal;
    Ogre::Vector4 tangent;     // w stores bitangent direction
    Ogre::Vector2 uv0;
};

struct GeometryData
{
    Ogre::Matrix4 m;
    uint32_t vertexOffset;
    uint32_t indexOffset;
    uint32_t padding[14];
};

struct SDFGICameraInfo
{
    Ogre::Vector3 position;
    float  aspect;
    Ogre::Vector3 up;
    float  fov;
    Ogre::Vector3 right;
    float  tanHalfFovY;
    Ogre::Vector3 forward;
    float  pad0;
    Ogre::Vector2 resolution;
    float  pad1;
};

struct SDFGILight
{
    uint32_t    type;                // 0: directional, 1: spot, 2: point (don't really need type on gpu with implicit placement)
    Ogre::Vector3  direction;           // Directional / Spot
    float   power;
    Ogre::Vector3  position;            // Spot / Point
    float   radius;              // Spot / Point
    Ogre::Vector3  color;
    float   umbraAngle;          // Spot
    float   penumbraAngle;       // Spot
    Ogre::Vector2  pad0;
};

struct SDFDIMaterial
{
    Ogre::Vector3 albedo;                  // RGB [0-1]
    float  opacity;                 // [0-1]
    Ogre::Vector3 emissiveColor;           // RGB [0-1]
    float  roughness;               // [0-1]
    float  metallic;                // [0-1]
    int    alphaMode;               // 0: Opaque, 1: Blend, 2: Masked
    float  alphaCutoff;             // [0-1]
    int    doubleSided;             // 0: false, 1: true
    int    albedoTexIdx;            // RGBA [0-1]
    int    roughnessMetallicTexIdx; // R: Occlusion, G: Roughness, B: Metallic
    int    normalTexIdx;            // Tangent space XYZ
    int    emissiveTexIdx;          // RGB [0-1]
};

struct AppConsts
{
    uint32_t   frameNumber;    // updated every frame, used for random number generation
    Ogre::Vector3 skyRadiance;

    uint32_t data[4] = {};
    static uint32_t GetNum32BitValues() { return 4; }
    static uint32_t GetSizeInBytes() { return GetNum32BitValues() * 4; }
    static uint32_t GetAlignedNum32BitValues() { return 4; }
    static uint32_t GetAlignedSizeInBytes() { return GetAlignedNum32BitValues() * 4; }
    uint32_t* GetData()
    {
        data[0] = frameNumber;
        data[1] = *(uint32_t*)&skyRadiance.x;
        data[2] = *(uint32_t*)&skyRadiance.y;
        data[3] = *(uint32_t*)&skyRadiance.z;
        return data;
    }
};

struct PathTraceConsts
{
    float rayNormalBias;
    float rayViewBias;
    uint32_t  numBounces;
    uint32_t  samplesPerPixel;

    uint32_t data[4];
    static uint32_t GetNum32BitValues() { return 4; }
    static uint32_t GetSizeInBytes() { return GetNum32BitValues() * 4; }
    static uint32_t GetAlignedNum32BitValues() { return 4; }
    static uint32_t GetAlignedSizeInBytes() { return GetAlignedNum32BitValues() * 4; }
    uint32_t* GetData()
    {
        data[0] = *(uint32_t*)&rayNormalBias;
        data[1] = *(uint32_t*)&rayViewBias;
        data[2] = numBounces;
        data[3] = samplesPerPixel;
        return data;
    }

    // Pack the progressive accumulation bool into the last bit of numBounces
    void SetProgressive(bool value)
    {
        numBounces |= ((uint32_t)value << 31);
    }

    // Pack the SER bool into the second-to-last bit of samplesPerPixel
    void SetShaderExecutionReordering(bool value)
    {
        samplesPerPixel |= ((uint32_t)value << 30);
    }

    // Pack the AA bool into the last bit of samplesPerPixel
    void SetAntialiasing(bool value)
    {
        samplesPerPixel |= ((uint32_t)value << 31);
    }
};

struct LightingConsts
{
    uint32_t hasDirectionalLight;   // -1: no directional light
    uint32_t numPointLights;        // point lights start at index 1
    uint32_t numSpotLights;         // spot lights start at 1 + numPointLights
    uint32_t lightingPad0;

    uint32_t data[3] = {};
    static uint32_t GetNum32BitValues() { return 3; }
    static uint32_t GetSizeInBytes() { return GetNum32BitValues() * 4; }
    static uint32_t GetAlignedNum32BitValues() { return 4; }
    static uint32_t GetAlignedSizeInBytes() { return GetAlignedNum32BitValues() * 4; }
    uint32_t* GetData()
    {
        data[0] = hasDirectionalLight;
        data[1] = numPointLights;
        data[2] = numSpotLights;
        //data[3] = 0; // empty, for alignment
        return data;
    }
};

struct RTAOConsts
{
    float rayLength;
    float rayNormalBias;
    float rayViewBias;
    float power;
    float filterDistanceSigma;
    float filterDepthSigma;
    uint32_t  filterBufferWidth;
    uint32_t  filterBufferHeight;
    float filterDistKernel0;
    float filterDistKernel1;
    float filterDistKernel2;
    float filterDistKernel3;
    float filterDistKernel4;
    float filterDistKernel5;

    uint32_t data[14] = {};
    static uint32_t GetNum32BitValues() { return 14; }
    static uint32_t GetSizeInBytes() { return GetNum32BitValues() * 4; }
    static uint32_t GetAlignedNum32BitValues() { return 16; }
    static uint32_t GetAlignedSizeInBytes() { return GetAlignedNum32BitValues() * 4; }
    uint32_t* GetData()
    {
        data[0]  = *(uint32_t*)&rayLength;
        data[1]  = *(uint32_t*)&rayNormalBias;
        data[2]  = *(uint32_t*)&rayViewBias;
        data[3]  = *(uint32_t*)&power;
        data[4]  = *(uint32_t*)&filterDistanceSigma;
        data[5]  = *(uint32_t*)&filterDepthSigma;
        data[6]  = filterBufferWidth;
        data[7]  = filterBufferHeight;
        data[8]  = *(uint32_t*)&filterDistKernel0;
        data[9]  = *(uint32_t*)&filterDistKernel1;
        data[10] = *(uint32_t*)&filterDistKernel2;
        data[11] = *(uint32_t*)&filterDistKernel3;
        data[12] = *(uint32_t*)&filterDistKernel4;
        data[13] = *(uint32_t*)&filterDistKernel5;
        //data[14] = 0; // empty, for alignment
        //data[15] = 0; // empty, for alignment
        return data;
    }
};

struct CompositeConsts
{
    uint32_t useFlags;
    uint32_t showFlags;

    uint32_t data[2];
    static uint32_t GetNum32BitValues() { return 4; }
    static uint32_t GetSizeInBytes() { return GetNum32BitValues() * 4; }
    static uint32_t GetAlignedNum32BitValues() { return 4; }
    static uint32_t GetAlignedSizeInBytes() { return GetAlignedNum32BitValues() * 4; }
    uint32_t* GetData()
    {
        data[0] = useFlags;
        data[1] = showFlags;
        //data[2] = 0; // empty, for alignment
        //data[3] = 0; // empty, for alignment;
        return data;
    }
};

struct PostProcessConsts
{
    uint32_t  useFlags;
    float exposure;

    uint32_t data[2];
    static uint32_t GetNum32BitValues() { return 2; }
    static uint32_t GetSizeInBytes() { return GetNum32BitValues() * 4; }
    static uint32_t GetAlignedNum32BitValues() { return 4; }
    static uint32_t GetAlignedSizeInBytes() { return GetAlignedNum32BitValues() * 4; }
    uint32_t* GetData()
    {
        data[0] = useFlags;
        data[1] = *(uint32_t*)&exposure;
        //data[2] = 0; // empty, alignment padding
        //data[3] = 0; // empty, alignment padding
        return data;
    }
};

struct DDGIVisConsts
{
    // Probe Visualization
    uint32_t  instanceOffset;   // Offset of the current volume's sphere instances in the acceleration structure's TLAS instances
    uint32_t  probeType;        // 0: irradiance | 1: distance
    float probeRadius;      // world-space value
    float distanceDivisor;  // divisor that normalizes the displayed distance values

    // Probe Textures Visualization
    float rayDataTextureScale;
    float irradianceTextureScale;
    float distanceTextureScale;
    float probeDataTextureScale;
    float probeVariabilityTextureScale;
    float probeVariabilityTextureThreshold;

    uint32_t data[10];
    static uint32_t GetNum32BitValues() { return 10; }
    static uint32_t GetSizeInBytes() { return GetNum32BitValues() * 4; }
    static uint32_t GetAlignedNum32BitValues() { return 12; }
    static uint32_t GetAlignedSizeInBytes() { return GetAlignedNum32BitValues() * 4; }
    uint32_t* GetData()
    {
        data[0] = instanceOffset;
        data[1] = probeType;
        data[2] = *(uint32_t*)&probeRadius;
        data[3] = *(uint32_t*)&distanceDivisor;
        data[4] = *(uint32_t*)&rayDataTextureScale;
        data[5] = *(uint32_t*)&irradianceTextureScale;
        data[6] = *(uint32_t*)&distanceTextureScale;
        data[7] = *(uint32_t*)&probeDataTextureScale;
        data[8] = *(uint32_t*)&probeVariabilityTextureScale;
        data[9] = *(uint32_t*)&probeVariabilityTextureThreshold;
        //data[10/11] = 0; // empty, alignment padding

        return data;
    }
};

struct GlobalConstants             // Added directly to the Root Signature (D3D12) or VkPipelineLayout Push Constants (Vulkan)
{
    AppConsts         app;         //  4 32-bit values,  16 bytes
    PathTraceConsts   pt;          //  4 32-bit values,  16 bytes
    LightingConsts    lights;      //  4 32-bit values,  16 bytes
    RTAOConsts        rtao;        // 16 32-bit values,  64 bytes
    CompositeConsts   composite;   //  4 32-bit values,  16 bytes
    PostProcessConsts post;        //  4 32-bit values,  16 bytes
    DDGIVisConsts     ddgivis;     // 12 32-bit values,  48 bytes
                                    // 48 32-bit values, 192 bytes

    static uint32_t GetNum32BitValues()
    {
        return (AppConsts::GetNum32BitValues() +
            PathTraceConsts::GetNum32BitValues() +
            LightingConsts::GetNum32BitValues() +
            RTAOConsts::GetNum32BitValues() +
            CompositeConsts::GetNum32BitValues() +
            PostProcessConsts::GetNum32BitValues() +
            DDGIVisConsts::GetNum32BitValues());
    }

    static uint32_t GetSizeInBytes()
    {
        return (AppConsts::GetSizeInBytes() +
            PathTraceConsts::GetSizeInBytes() +
            LightingConsts::GetSizeInBytes() +
            RTAOConsts::GetSizeInBytes() +
            CompositeConsts::GetSizeInBytes() +
            PostProcessConsts::GetSizeInBytes() +
            DDGIVisConsts::GetSizeInBytes());
    }

    static uint32_t GetAlignedNum32BitValues()
    {
        return (AppConsts::GetAlignedNum32BitValues() +
            PathTraceConsts::GetAlignedNum32BitValues() +
            LightingConsts::GetAlignedNum32BitValues() +
            RTAOConsts::GetAlignedNum32BitValues() +
            CompositeConsts::GetAlignedNum32BitValues() +
            PostProcessConsts::GetAlignedNum32BitValues() +
            DDGIVisConsts::GetAlignedNum32BitValues());
    }

    static uint32_t GetAlignedSizeInBytes()
    {
        return (AppConsts::GetAlignedSizeInBytes() +
            PathTraceConsts::GetAlignedSizeInBytes() +
            LightingConsts::GetAlignedSizeInBytes() +
            RTAOConsts::GetAlignedSizeInBytes() +
            CompositeConsts::GetAlignedSizeInBytes() +
            PostProcessConsts::GetAlignedSizeInBytes() +
            DDGIVisConsts::GetAlignedSizeInBytes());
    }

};

