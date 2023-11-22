#version 450

#include "common.glsl"


layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texcoord;
#ifdef SKINNED
    layout (location = 3) in vec3 bone_weights;
	layout (location = 4) in uvec4 bone_indices;
#endif

layout (location = 0) out vec4 outPosH;
layout (location = 1) out vec4 outShadowPosH;
layout (location = 2) out vec3 outPosW;
layout (location = 3) out vec3 outNormalW;
layout (location = 4) out vec2 outTexC;


void main() {
#ifdef SKINNED
    float weights[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
    weights[0] = bone_weights.x;
    weights[1] = bone_weights.y;
    weights[2] = bone_weights.z;
    weights[3] = 1.0f - weights[0] - weights[1] - weights[2];

    
    vec3 normalL = vec3(0.0f, 0.0f, 0.0f);
#ifdef USETANGENT
    vec3 tangentL = vec3(0.0f, 0.0f, 0.0f);
#endif
    mat4 skinMat = 
		weights[0] * cbSkinned.gBoneTransforms[bone_indices.x] + 
		weights[1] * cbSkinned.gBoneTransforms[bone_indices.y] + 
		weights[2] * cbSkinned.gBoneTransforms[bone_indices.z] + 
		weights[3] * cbSkinned.gBoneTransforms[bone_indices.w];
	gl_Position = cbPerObject.gWorldViewProj * skinMat * vec4(position, 1.0);
#else
    gl_Position = cbPerObject.gWorldViewProj * vec4(position, 1.0);
#endif
    outTexC = (cbMaterial.gTexTransform * vec4(texcoord, 0.0f, 1.0f)).xy;
	outTexC = texcoord;
	gl_Position.y = -gl_Position.y;
}

