/* WARNING, THIS FILE WAS GENERATED, DO NOT EDIT */
#ifndef CUBEMAP_FILTER_RASTER_GLSL_GEN_H_RD
#define CUBEMAP_FILTER_RASTER_GLSL_GEN_H_RD

#include "servers/rendering/renderer_rd/shader_rd.h"

class CubemapFilterRasterShaderRD : public ShaderRD {

public:

	CubemapFilterRasterShaderRD() {

		static const char _vertex_code[] = {
R"<!>(
#version 450

#VERSION_DEFINES

layout(push_constant, std430) uniform Params {
	int mip_level;
	uint face_id;
}
params;

layout(location = 0) out vec2 uv_interp;
/* clang-format on */

void main() {
	vec2 base_arr[3] = vec2[](vec2(-1.0, -1.0), vec2(-1.0, 3.0), vec2(3.0, -1.0));
	gl_Position = vec4(base_arr[gl_VertexIndex], 0.0, 1.0);
	uv_interp = clamp(gl_Position.xy, vec2(0.0, 0.0), vec2(1.0, 1.0)) * 2.0; 
}

/* clang-format off */
)<!>"
		};
		static const char _fragment_code[] = {
R"<!>(
#version 450

#VERSION_DEFINES

layout(push_constant, std430) uniform Params {
	int mip_level;
	uint face_id;
}
params;

layout(set = 0, binding = 0) uniform samplerCube source_cubemap;

layout(location = 0) in vec2 uv_interp;
layout(location = 0) out vec4 frag_color;

/* clang-format on */

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
	
	vec3 dir, adir, frameZ;
	{
		vec2 uv;
		uv.x = uv_interp.x;
		uv.y = 1.0 - uv_interp.y;
		uv = uv * 2.0 - 1.0;

		get_dir(dir, uv, params.face_id);
		frameZ = normalize(dir);

		adir = abs(dir);
	}

	
	
	int mip_level = 0;

	if (params.mip_level < 0) {
		
		frag_color.rgb = textureLod(source_cubemap, frameZ, 0.0).rgb;
		frag_color.a = 1.0;
		return;
	} else if (params.mip_level > 6) {
		
		mip_level = 6;
	} else {
		mip_level = params.mip_level;
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
					
					color.xyz += textureLod(source_cubemap, normalize(sample_dir), sample_level).xyz * sample_weight;
					color.w += sample_weight;
				}
			}
		}
	}
	color /= color.w;

	
	color.xyz = max(vec3(0.0), color.xyz);
	color.w = 1.0;

	frag_color = color;
}
)<!>"
		};
		setup(_vertex_code, _fragment_code, nullptr, "CubemapFilterRasterShaderRD");
	}
};

#endif
