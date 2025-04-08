// Defaults for number of lights.
#ifndef MAX_NUM_DIR_LIGHTS
    #define MAX_NUM_DIR_LIGHTS 1
#endif

#ifndef NUM_POINT_LIGHTS
    #define NUM_POINT_LIGHTS 0
#endif

#ifndef NUM_SPOT_LIGHTS
    #define NUM_SPOT_LIGHTS 0
#endif

#include "LightingUtil.hlsl"

#ifdef VULKAN
#define VKBINDING(r,s) [[vk::binding(r, s)]]
#define VKLOCATION(l) [[vk::location(l)]]
#else
#define VKBINDING(r,s)
#define VKLOCATION(l)
#endif



// Constant data that varies per frame.

struct ObjectBlock
{
    float4x4 gWorld;
	float4x4 gProjector;
	float4 diffuseColor;
	uint useShadow;
	uint haveTexture;
	uint padding[2];
};


struct PassBlock
{
    column_major float4x4 gView;
    column_major float4x4 gInvView;
    column_major float4x4 gProj;
    column_major float4x4 gInvProj;
    column_major float4x4 gViewProj;
    column_major float4x4 gInvViewProj;
	column_major float4x4 gShadowTransform;
    float3 gEyePosW;
    uint gShadow;
    float2 gRenderTargetSize;
    float2 gInvRenderTargetSize;
    float gNearZ;
    float gFarZ;
    float gTotalTime;
    float gDeltaTime;
    Light gDirLights[MAX_NUM_DIR_LIGHTS];
	uint numDirLights;
};



struct PbrMaterialBlock
{
    float2 u_MetallicRoughnessValues;
	float u_OcclusionStrength;
	uint alphaMode;
    float3 u_EmissiveFactor;
	float alpha_mask_cutoff;
	float4 u_BaseColorFactor;
	float4 u_ScaleIBLAmbient;
    uint debugRenderMode;
	uint hasAlbedoMap;
	uint hasEmissiveMap;
    uint hasNormalMap;
    uint hasMetalRoughNessMap;
	uint hasMetalMap;
	uint hasRoughNessMap;
	uint hasOcclusionMap;
	uint hasIBL;
};

struct ObjMaterialBlock
{
	uint u_hasDiffuseTexture;
	uint u_hasNormalMap;
	uint u_hasSpecularMap;
	uint u_hasOpacityMap;
	uint u_hasEmissionMap;
	uint u_shininess;
	float2 u_clipmapResolution;
	float4 u_emissionColor;
	float4 u_specularColor;
	float4 u_color;
};

struct MaterialBlock
{
    float4   gDiffuseAlbedo;
    float3   gFresnelR0;
    float    gRoughness;
    column_major float4x4 gTexScale;
	column_major float4x4 gTexTransform;
	uint     gDiffuseMapIndex;
	uint     MatPad0;
	uint     MatPad1;
	uint     MatPad2;
};


struct SkinBlock
{
    float4x4 gBoneTransforms[200];
};

#define SHADOW_MAP_CASCADE_COUNT 4
struct cascadeBlock
{
    float4x4 matrices[SHADOW_MAP_CASCADE_COUNT];
	float4 cascadeSplits;
};



