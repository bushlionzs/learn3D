/* WARNING, THIS FILE WAS GENERATED, DO NOT EDIT */
#ifndef CUBEMAP_ROUGHNESS_GLSL_GEN_H_RD
#define CUBEMAP_ROUGHNESS_GLSL_GEN_H_RD

#include "servers/rendering/renderer_rd/shader_rd.h"

class CubemapRoughnessShaderRD : public ShaderRD {

public:

	CubemapRoughnessShaderRD() {

		static const char _compute_code[] = {
R"<!>(
#version 450

#VERSION_DEFINES

#define GROUP_SIZE 8

layout(local_size_x = GROUP_SIZE, local_size_y = GROUP_SIZE, local_size_z = 1) in;

layout(set = 0, binding = 0) uniform samplerCube source_cube;

layout(rgba16f, set = 1, binding = 0) uniform restrict writeonly imageCube dest_cubemap;

#define M_PI 3.14159265359

layout(push_constant, std430) uniform Params {
	uint face_id;
	uint sample_count;
	float roughness;
	bool use_direct_write;
	float face_size;
}
params;

vec3 texelCoordToVec(vec2 uv, uint faceID) {
	mat3 faceUvVectors[6];

	
	faceUvVectors[1][0] = vec3(0.0, 0.0, 1.0); 
	faceUvVectors[1][1] = vec3(0.0, -1.0, 0.0); 
	faceUvVectors[1][2] = vec3(-1.0, 0.0, 0.0); 

	
	faceUvVectors[0][0] = vec3(0.0, 0.0, -1.0); 
	faceUvVectors[0][1] = vec3(0.0, -1.0, 0.0); 
	faceUvVectors[0][2] = vec3(1.0, 0.0, 0.0); 

	
	faceUvVectors[3][0] = vec3(1.0, 0.0, 0.0); 
	faceUvVectors[3][1] = vec3(0.0, 0.0, -1.0); 
	faceUvVectors[3][2] = vec3(0.0, -1.0, 0.0); 

	
	faceUvVectors[2][0] = vec3(1.0, 0.0, 0.0); 
	faceUvVectors[2][1] = vec3(0.0, 0.0, 1.0); 
	faceUvVectors[2][2] = vec3(0.0, 1.0, 0.0); 

	
	faceUvVectors[5][0] = vec3(-1.0, 0.0, 0.0); 
	faceUvVectors[5][1] = vec3(0.0, -1.0, 0.0); 
	faceUvVectors[5][2] = vec3(0.0, 0.0, -1.0); 

	
	faceUvVectors[4][0] = vec3(1.0, 0.0, 0.0); 
	faceUvVectors[4][1] = vec3(0.0, -1.0, 0.0); 
	faceUvVectors[4][2] = vec3(0.0, 0.0, 1.0); 

	
	vec3 result = (faceUvVectors[faceID][0] * uv.x) + (faceUvVectors[faceID][1] * uv.y) + faceUvVectors[faceID][2];
	return normalize(result);
}

vec3 ImportanceSampleGGX(vec2 xi, float roughness4) {
	
	float Phi = 2.0 * M_PI * xi.x;
	float CosTheta = sqrt((1.0 - xi.y) / (1.0 + (roughness4 - 1.0) * xi.y));
	float SinTheta = sqrt(1.0 - CosTheta * CosTheta);

	
	vec3 H;
	H.x = SinTheta * cos(Phi);
	H.y = SinTheta * sin(Phi);
	H.z = CosTheta;

	return H;
}

float DistributionGGX(float NdotH, float roughness4) {
	float NdotH2 = NdotH * NdotH;
	float denom = (NdotH2 * (roughness4 - 1.0) + 1.0);
	denom = M_PI * denom * denom;

	return roughness4 / denom;
}

float radicalInverse_VdC(uint bits) {
	bits = (bits << 16u) | (bits >> 16u);
	bits = ((bits & 0x55555555u) << 1u) | ((bits & 0xAAAAAAAAu) >> 1u);
	bits = ((bits & 0x33333333u) << 2u) | ((bits & 0xCCCCCCCCu) >> 2u);
	bits = ((bits & 0x0F0F0F0Fu) << 4u) | ((bits & 0xF0F0F0F0u) >> 4u);
	bits = ((bits & 0x00FF00FFu) << 8u) | ((bits & 0xFF00FF00u) >> 8u);
	return float(bits) * 2.3283064365386963e-10; 
}

vec2 Hammersley(uint i, uint N) {
	return vec2(float(i) / float(N), radicalInverse_VdC(i));
}

void main() {
	uvec3 id = gl_GlobalInvocationID;
	id.z += params.face_id;

	vec2 uv = ((vec2(id.xy) * 2.0 + 1.0) / (params.face_size) - 1.0);
	vec3 N = texelCoordToVec(uv, id.z);

	if (params.use_direct_write) {
		imageStore(dest_cubemap, ivec3(id), vec4(texture(source_cube, N).rgb, 1.0));
	} else {
		vec4 sum = vec4(0.0, 0.0, 0.0, 0.0);

		float solid_angle_texel = 4.0 * M_PI / (6.0 * params.face_size * params.face_size);
		float roughness2 = params.roughness * params.roughness;
		float roughness4 = roughness2 * roughness2;
		vec3 UpVector = abs(N.z) < 0.999 ? vec3(0.0, 0.0, 1.0) : vec3(1.0, 0.0, 0.0);
		mat3 T;
		T[0] = normalize(cross(UpVector, N));
		T[1] = cross(N, T[0]);
		T[2] = N;

		for (uint sampleNum = 0u; sampleNum < params.sample_count; sampleNum++) {
			vec2 xi = Hammersley(sampleNum, params.sample_count);

			vec3 H = T * ImportanceSampleGGX(xi, roughness4);
			float NdotH = dot(N, H);
			vec3 L = (2.0 * NdotH * H - N);

			float ndotl = clamp(dot(N, L), 0.0, 1.0);

			if (ndotl > 0.0) {
				float D = DistributionGGX(NdotH, roughness4);
				float pdf = D * NdotH / (4.0 * NdotH) + 0.0001;

				float solid_angle_sample = 1.0 / (float(params.sample_count) * pdf + 0.0001);

				float mipLevel = params.roughness == 0.0 ? 0.0 : 0.5 * log2(solid_angle_sample / solid_angle_texel);

				sum.rgb += textureLod(source_cube, L, mipLevel).rgb * ndotl;
				sum.a += ndotl;
			}
		}
		sum /= sum.a;

		imageStore(dest_cubemap, ivec3(id), vec4(sum.rgb, 1.0));
	}
}
)<!>"
		};
		setup(nullptr, nullptr, _compute_code, "CubemapRoughnessShaderRD");
	}
};

#endif
