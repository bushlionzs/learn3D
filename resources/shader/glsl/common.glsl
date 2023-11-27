#ifndef NUM_DIR_LIGHTS
    #define NUM_DIR_LIGHTS 1
#endif

#ifndef NUM_POINT_LIGHTS
    #define NUM_POINT_LIGHTS 0
#endif

#ifndef NUM_SPOT_LIGHTS
    #define NUM_SPOT_LIGHTS 0
#endif

struct Light {
    vec3 Strength;
    float FalloffStart; // point/spot light only
    vec3 Direction;   // directional/spot light only
    float FalloffEnd;   // point/spot light only
    vec3 Position;    // point light only
    float SpotPower;    // spot light only
};

#define MaxLights 16

layout(binding = 0) uniform UniformBufferObject {
    mat4 gWorld;
    mat4 gProjector;
    mat4 gWorldViewProj;
} cbPerObject;

layout(binding = 1) uniform CBPASS {
    mat4 gView;
    mat4 gInvView;
    mat4 gProj;
    mat4 gInvProj;
    mat4 gViewProj;
    mat4 gInvViewProj;
	mat4 gShadowTransform;
    vec3 gEyePosW;
    uint gShadow;
    vec2 gRenderTargetSize;
    vec2 gInvRenderTargetSize;
    float gNearZ;
    float gFarZ;
    float gTotalTime;
    float gDeltaTime;
    vec4 gAmbientLight;
	Light gLights[MaxLights];
} cbPass;

layout(binding = 2) uniform CBMATERIAL {
    vec4   gDiffuseAlbedo;
    vec3   gFresnelR0;
    float  gRoughness;
    mat4   gTexScale;
	mat4   gTexTransform;
	uint   gDiffuseMapIndex;
	uint   MatPad0;
	uint   MatPad1;
	uint   MatPad2;
} cbMaterial;

#ifdef SKINNED
layout(binding = 5) uniform CBSKINNED {
    mat4 gBoneTransforms[100];
} cbSkinned;
#endif

layout (binding = 3) uniform samplerCube gCubeMap;
layout(binding = 4) uniform sampler2D gTextureArray[4];