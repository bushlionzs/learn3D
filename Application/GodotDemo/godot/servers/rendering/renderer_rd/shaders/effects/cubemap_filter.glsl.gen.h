/* WARNING, THIS FILE WAS GENERATED, DO NOT EDIT */
#ifndef CUBEMAP_FILTER_GLSL_GEN_H_RD
#define CUBEMAP_FILTER_GLSL_GEN_H_RD

#include "servers/rendering/renderer_rd/shader_rd.h"

class CubemapFilterShaderRD : public ShaderRD {

public:

	CubemapFilterShaderRD() {

		static const char _compute_code[] = {
R"<!>(
#version 450

#VERSION_DEFINES

#define GROUP_SIZE 64

layout(local_size_x = GROUP_SIZE, local_size_y = 1, local_size_z = 1) in;

layout(set = 0, binding = 0) uniform samplerCube source_cubemap;
layout(rgba16f, set = 2, binding = 0) uniform restrict writeonly imageCube dest_cubemap0;
layout(rgba16f, set = 2, binding = 1) uniform restrict writeonly imageCube dest_cubemap1;
layout(rgba16f, set = 2, binding = 2) uniform restrict writeonly imageCube dest_cubemap2;
layout(rgba16f, set = 2, binding = 3) uniform restrict writeonly imageCube dest_cubemap3;
layout(rgba16f, set = 2, binding = 4) uniform restrict writeonly imageCube dest_cubemap4;
layout(rgba16f, set = 2, binding = 5) uniform restrict writeonly imageCube dest_cubemap5;
layout(rgba16f, set = 2, binding = 6) uniform restrict writeonly imageCube dest_cubemap6;

#ifdef USE_HIGH_QUALITY
#define NUM_TAPS 32
#else
#define NUM_TAPS 8
#endif

#define BASE_RESOLUTION 128

#ifdef USE_HIGH_QUALITY
layout(set = 1, binding = 0, std430) buffer restrict readonly Data {
	vec4[7][5][3][24] coeffs;
}
data;
#else
layout(set = 1, binding = 0, std430) buffer restrict readonly Data {
	vec4[7][5][6] coeffs;
}
data;
#endif

void get_dir(out vec3 dir, in vec2 uv, in uint face) {
	switch (face) {
		case 0:
			dir = vec3(1.0, uv[1], -uv[0]);
			break;
		case 1:
			dir = vec3(-1.0, uv[1], uv[0]);
			break;
		case 2:
			dir = vec3(uv[0], 1.0, -uv[1]);
			break;
		case 3:
			dir = vec3(uv[0], -1.0, uv[1]);
			break;
		case 4:
			dir = vec3(uv[0], uv[1], 1.0);
			break;
		default:
			dir = vec3(-uv[0], uv[1], -1.0);
			break;
	}
}

void main() {
	
	
	
	
	
	
	
	uvec3 id = gl_GlobalInvocationID;

	
#ifndef USE_TEXTURE_ARRAY
	
	int mip_level = 0;
	if (id.x < (128 * 128)) {
		mip_level = 0;
	} else if (id.x < (128 * 128 + 64 * 64)) {
		mip_level = 1;
		id.x -= (128 * 128);
	} else if (id.x < (128 * 128 + 64 * 64 + 32 * 32)) {
		mip_level = 2;
		id.x -= (128 * 128 + 64 * 64);
	} else if (id.x < (128 * 128 + 64 * 64 + 32 * 32 + 16 * 16)) {
		mip_level = 3;
		id.x -= (128 * 128 + 64 * 64 + 32 * 32);
	} else if (id.x < (128 * 128 + 64 * 64 + 32 * 32 + 16 * 16 + 8 * 8)) {
		mip_level = 4;
		id.x -= (128 * 128 + 64 * 64 + 32 * 32 + 16 * 16);
	} else if (id.x < (128 * 128 + 64 * 64 + 32 * 32 + 16 * 16 + 8 * 8 + 4 * 4)) {
		mip_level = 5;
		id.x -= (128 * 128 + 64 * 64 + 32 * 32 + 16 * 16 + 8 * 8);
	} else if (id.x < (128 * 128 + 64 * 64 + 32 * 32 + 16 * 16 + 8 * 8 + 4 * 4 + 2 * 2)) {
		mip_level = 6;
		id.x -= (128 * 128 + 64 * 64 + 32 * 32 + 16 * 16 + 8 * 8 + 4 * 4);
	} else {
		return;
	}
	int res = BASE_RESOLUTION >> mip_level;
#else 
	int res = BASE_RESOLUTION;
	int mip_level = int(id.x / (BASE_RESOLUTION * BASE_RESOLUTION));
	id.x -= mip_level * BASE_RESOLUTION * BASE_RESOLUTION;
#endif

	
	vec3 dir, adir, frameZ;
	{
		id.z = id.y;
		id.y = id.x / res;
		id.x -= id.y * res;

		vec2 uv;
		uv.x = (float(id.x) * 2.0 + 1.0) / float(res) - 1.0;
		uv.y = -(float(id.y) * 2.0 + 1.0) / float(res) + 1.0;

		get_dir(dir, uv, id.z);
		frameZ = normalize(dir);

		adir = abs(dir);
	}

	
	vec4 color = vec4(0.0);
	for (int axis = 0; axis < 3; axis++) {
		const int otherAxis0 = 1 - (axis & 1) - (axis >> 1);
		const int otherAxis1 = 2 - (axis >> 1);

		float frameweight = (max(adir[otherAxis0], adir[otherAxis1]) - .75) / .25;
		if (frameweight > 0.0) {
			
			vec3 UpVector;
			switch (axis) {
				case 0:
					UpVector = vec3(1, 0, 0);
					break;
				case 1:
					UpVector = vec3(0, 1, 0);
					break;
				default:
					UpVector = vec3(0, 0, 1);
					break;
			}

			vec3 frameX = normalize(cross(UpVector, frameZ));
			vec3 frameY = cross(frameZ, frameX);

			
			float Nx = dir[otherAxis0];
			float Ny = dir[otherAxis1];
			float Nz = adir[axis];

			float NmaxXY = max(abs(Ny), abs(Nx));
			Nx /= NmaxXY;
			Ny /= NmaxXY;

			float theta;
			if (Ny < Nx) {
				if (Ny <= -0.999)
					theta = Nx;
				else
					theta = Ny;
			} else {
				if (Ny >= 0.999)
					theta = -Nx;
				else
					theta = -Ny;
			}

			float phi;
			if (Nz <= -0.999)
				phi = -NmaxXY;
			else if (Nz >= 0.999)
				phi = NmaxXY;
			else
				phi = Nz;

			float theta2 = theta * theta;
			float phi2 = phi * phi;

			
			for (int iSuperTap = 0; iSuperTap < NUM_TAPS / 4; iSuperTap++) {
				const int index = (NUM_TAPS / 4) * axis + iSuperTap;

#ifdef USE_HIGH_QUALITY
				vec4 coeffsDir0[3];
				vec4 coeffsDir1[3];
				vec4 coeffsDir2[3];
				vec4 coeffsLevel[3];
				vec4 coeffsWeight[3];

				for (int iCoeff = 0; iCoeff < 3; iCoeff++) {
					coeffsDir0[iCoeff] = data.coeffs[mip_level][0][iCoeff][index];
					coeffsDir1[iCoeff] = data.coeffs[mip_level][1][iCoeff][index];
					coeffsDir2[iCoeff] = data.coeffs[mip_level][2][iCoeff][index];
					coeffsLevel[iCoeff] = data.coeffs[mip_level][3][iCoeff][index];
					coeffsWeight[iCoeff] = data.coeffs[mip_level][4][iCoeff][index];
				}

				for (int iSubTap = 0; iSubTap < 4; iSubTap++) {
					
					vec3 sample_dir = frameX * (coeffsDir0[0][iSubTap] + coeffsDir0[1][iSubTap] * theta2 + coeffsDir0[2][iSubTap] * phi2) + frameY * (coeffsDir1[0][iSubTap] + coeffsDir1[1][iSubTap] * theta2 + coeffsDir1[2][iSubTap] * phi2) + frameZ * (coeffsDir2[0][iSubTap] + coeffsDir2[1][iSubTap] * theta2 + coeffsDir2[2][iSubTap] * phi2);

					float sample_level = coeffsLevel[0][iSubTap] + coeffsLevel[1][iSubTap] * theta2 + coeffsLevel[2][iSubTap] * phi2;

					float sample_weight = coeffsWeight[0][iSubTap] + coeffsWeight[1][iSubTap] * theta2 + coeffsWeight[2][iSubTap] * phi2;
#else
				vec4 coeffsDir0 = data.coeffs[mip_level][0][index];
				vec4 coeffsDir1 = data.coeffs[mip_level][1][index];
				vec4 coeffsDir2 = data.coeffs[mip_level][2][index];
				vec4 coeffsLevel = data.coeffs[mip_level][3][index];
				vec4 coeffsWeight = data.coeffs[mip_level][4][index];

				for (int iSubTap = 0; iSubTap < 4; iSubTap++) {
					
					vec3 sample_dir = frameX * coeffsDir0[iSubTap] + frameY * coeffsDir1[iSubTap] + frameZ * coeffsDir2[iSubTap];

					float sample_level = coeffsLevel[iSubTap];

					float sample_weight = coeffsWeight[iSubTap];
#endif

					sample_weight *= frameweight;

					
					sample_dir /= max(abs(sample_dir[0]), max(abs(sample_dir[1]), abs(sample_dir[2])));
					sample_level += 0.75 * log2(dot(sample_dir, sample_dir));
#ifndef USE_TEXTURE_ARRAY
					sample_level += float(mip_level) / 6.0; 
#endif
					
					color.xyz += textureLod(source_cubemap, normalize(sample_dir), sample_level).xyz * sample_weight;
					color.w += sample_weight;
				}
			}
		}
	}
	color /= color.w;

	
	color.xyz = max(vec3(0.0), color.xyz);
	color.w = 1.0;
#ifdef USE_TEXTURE_ARRAY
	id.xy *= uvec2(2, 2);
#endif

	switch (mip_level) {
		case 0:
			imageStore(dest_cubemap0, ivec3(id), color);
#ifdef USE_TEXTURE_ARRAY
			imageStore(dest_cubemap0, ivec3(id) + ivec3(1.0, 0.0, 0.0), color);
			imageStore(dest_cubemap0, ivec3(id) + ivec3(0.0, 1.0, 0.0), color);
			imageStore(dest_cubemap0, ivec3(id) + ivec3(1.0, 1.0, 0.0), color);
#endif
			break;
		case 1:
			imageStore(dest_cubemap1, ivec3(id), color);
#ifdef USE_TEXTURE_ARRAY
			imageStore(dest_cubemap1, ivec3(id) + ivec3(1.0, 0.0, 0.0), color);
			imageStore(dest_cubemap1, ivec3(id) + ivec3(0.0, 1.0, 0.0), color);
			imageStore(dest_cubemap1, ivec3(id) + ivec3(1.0, 1.0, 0.0), color);
#endif
			break;
		case 2:
			imageStore(dest_cubemap2, ivec3(id), color);
#ifdef USE_TEXTURE_ARRAY
			imageStore(dest_cubemap2, ivec3(id) + ivec3(1.0, 0.0, 0.0), color);
			imageStore(dest_cubemap2, ivec3(id) + ivec3(0.0, 1.0, 0.0), color);
			imageStore(dest_cubemap2, ivec3(id) + ivec3(1.0, 1.0, 0.0), color);
#endif
			break;
		case 3:
			imageStore(dest_cubemap3, ivec3(id), color);
#ifdef USE_TEXTURE_ARRAY
			imageStore(dest_cubemap3, ivec3(id) + ivec3(1.0, 0.0, 0.0), color);
			imageStore(dest_cubemap3, ivec3(id) + ivec3(0.0, 1.0, 0.0), color);
			imageStore(dest_cubemap3, ivec3(id) + ivec3(1.0, 1.0, 0.0), color);
#endif
			break;
		case 4:
			imageStore(dest_cubemap4, ivec3(id), color);
#ifdef USE_TEXTURE_ARRAY
			imageStore(dest_cubemap4, ivec3(id) + ivec3(1.0, 0.0, 0.0), color);
			imageStore(dest_cubemap4, ivec3(id) + ivec3(0.0, 1.0, 0.0), color);
			imageStore(dest_cubemap4, ivec3(id) + ivec3(1.0, 1.0, 0.0), color);
#endif
			break;
		case 5:
			imageStore(dest_cubemap5, ivec3(id), color);
#ifdef USE_TEXTURE_ARRAY
			imageStore(dest_cubemap5, ivec3(id) + ivec3(1.0, 0.0, 0.0), color);
			imageStore(dest_cubemap5, ivec3(id) + ivec3(0.0, 1.0, 0.0), color);
			imageStore(dest_cubemap5, ivec3(id) + ivec3(1.0, 1.0, 0.0), color);
#endif
			break;
		default:
			imageStore(dest_cubemap6, ivec3(id), color);
#ifdef USE_TEXTURE_ARRAY
			imageStore(dest_cubemap6, ivec3(id) + ivec3(1.0, 0.0, 0.0), color);
			imageStore(dest_cubemap6, ivec3(id) + ivec3(0.0, 1.0, 0.0), color);
			imageStore(dest_cubemap6, ivec3(id) + ivec3(1.0, 1.0, 0.0), color);
#endif
			break;
	}
}
)<!>"
		};
		setup(nullptr, nullptr, _compute_code, "CubemapFilterShaderRD");
	}
};

#endif
