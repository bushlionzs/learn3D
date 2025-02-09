/* WARNING, THIS FILE WAS GENERATED, DO NOT EDIT */
#ifndef CUBEMAP_DOWNSAMPLER_RASTER_GLSL_GEN_H_RD
#define CUBEMAP_DOWNSAMPLER_RASTER_GLSL_GEN_H_RD

#include "servers/rendering/renderer_rd/shader_rd.h"

class CubemapDownsamplerRasterShaderRD : public ShaderRD {

public:

	CubemapDownsamplerRasterShaderRD() {

		static const char _vertex_code[] = {
R"<!>(
#version 450

#VERSION_DEFINES

layout(push_constant, std430) uniform Params {
	uint face_size;
	uint face_id; 
}
params;

#define M_PI 3.14159265359

void get_dir_0(out vec3 dir, in float u, in float v) {
	dir[0] = 1.0;
	dir[1] = v;
	dir[2] = -u;
}

void get_dir_1(out vec3 dir, in float u, in float v) {
	dir[0] = -1.0;
	dir[1] = v;
	dir[2] = u;
}

void get_dir_2(out vec3 dir, in float u, in float v) {
	dir[0] = u;
	dir[1] = 1.0;
	dir[2] = -v;
}

void get_dir_3(out vec3 dir, in float u, in float v) {
	dir[0] = u;
	dir[1] = -1.0;
	dir[2] = v;
}

void get_dir_4(out vec3 dir, in float u, in float v) {
	dir[0] = u;
	dir[1] = v;
	dir[2] = 1.0;
}

void get_dir_5(out vec3 dir, in float u, in float v) {
	dir[0] = -u;
	dir[1] = v;
	dir[2] = -1.0;
}

float calcWeight(float u, float v) {
	float val = u * u + v * v + 1.0;
	return val * sqrt(val);
}

layout(location = 0) out vec2 uv_interp;
/* clang-format on */

void main() {
	vec2 base_arr[3] = vec2[](vec2(-1.0, -1.0), vec2(-1.0, 3.0), vec2(3.0, -1.0));
	gl_Position = vec4(base_arr[gl_VertexIndex], 0.0, 1.0);
	uv_interp = clamp(gl_Position.xy, vec2(0.0, 0.0), vec2(1.0, 1.0)) * 2.0 * float(params.face_size); 
}

/* clang-format off */
)<!>"
		};
		static const char _fragment_code[] = {
R"<!>(
#version 450

#VERSION_DEFINES

layout(push_constant, std430) uniform Params {
	uint face_size;
	uint face_id; 
}
params;

#define M_PI 3.14159265359

void get_dir_0(out vec3 dir, in float u, in float v) {
	dir[0] = 1.0;
	dir[1] = v;
	dir[2] = -u;
}

void get_dir_1(out vec3 dir, in float u, in float v) {
	dir[0] = -1.0;
	dir[1] = v;
	dir[2] = u;
}

void get_dir_2(out vec3 dir, in float u, in float v) {
	dir[0] = u;
	dir[1] = 1.0;
	dir[2] = -v;
}

void get_dir_3(out vec3 dir, in float u, in float v) {
	dir[0] = u;
	dir[1] = -1.0;
	dir[2] = v;
}

void get_dir_4(out vec3 dir, in float u, in float v) {
	dir[0] = u;
	dir[1] = v;
	dir[2] = 1.0;
}

void get_dir_5(out vec3 dir, in float u, in float v) {
	dir[0] = -u;
	dir[1] = v;
	dir[2] = -1.0;
}

float calcWeight(float u, float v) {
	float val = u * u + v * v + 1.0;
	return val * sqrt(val);
}

layout(set = 0, binding = 0) uniform samplerCube source_cubemap;

layout(location = 0) in vec2 uv_interp;
layout(location = 0) out vec4 frag_color;
/* clang-format on */

void main() {
	
	
	float face_size = float(params.face_size);
	float inv_face_size = 1.0 / face_size;
	vec2 id = floor(uv_interp);

	float u1 = (id.x * 2.0 + 1.0 + 0.75) * inv_face_size - 1.0;
	float u0 = (id.x * 2.0 + 1.0 - 0.75) * inv_face_size - 1.0;

	float v0 = (id.y * 2.0 + 1.0 - 0.75) * -inv_face_size + 1.0;
	float v1 = (id.y * 2.0 + 1.0 + 0.75) * -inv_face_size + 1.0;

	float weights[4];
	weights[0] = calcWeight(u0, v0);
	weights[1] = calcWeight(u1, v0);
	weights[2] = calcWeight(u0, v1);
	weights[3] = calcWeight(u1, v1);

	const float wsum = 0.5 / (weights[0] + weights[1] + weights[2] + weights[3]);
	for (int i = 0; i < 4; i++) {
		weights[i] = weights[i] * wsum + .125;
	}

	vec3 dir;
	vec4 color;
	switch (params.face_id) {
		case 0:
			get_dir_0(dir, u0, v0);
			color = textureLod(source_cubemap, normalize(dir), 0.0) * weights[0];

			get_dir_0(dir, u1, v0);
			color += textureLod(source_cubemap, normalize(dir), 0.0) * weights[1];

			get_dir_0(dir, u0, v1);
			color += textureLod(source_cubemap, normalize(dir), 0.0) * weights[2];

			get_dir_0(dir, u1, v1);
			color += textureLod(source_cubemap, normalize(dir), 0.0) * weights[3];
			break;
		case 1:
			get_dir_1(dir, u0, v0);
			color = textureLod(source_cubemap, normalize(dir), 0.0) * weights[0];

			get_dir_1(dir, u1, v0);
			color += textureLod(source_cubemap, normalize(dir), 0.0) * weights[1];

			get_dir_1(dir, u0, v1);
			color += textureLod(source_cubemap, normalize(dir), 0.0) * weights[2];

			get_dir_1(dir, u1, v1);
			color += textureLod(source_cubemap, normalize(dir), 0.0) * weights[3];
			break;
		case 2:
			get_dir_2(dir, u0, v0);
			color = textureLod(source_cubemap, normalize(dir), 0.0) * weights[0];

			get_dir_2(dir, u1, v0);
			color += textureLod(source_cubemap, normalize(dir), 0.0) * weights[1];

			get_dir_2(dir, u0, v1);
			color += textureLod(source_cubemap, normalize(dir), 0.0) * weights[2];

			get_dir_2(dir, u1, v1);
			color += textureLod(source_cubemap, normalize(dir), 0.0) * weights[3];
			break;
		case 3:
			get_dir_3(dir, u0, v0);
			color = textureLod(source_cubemap, normalize(dir), 0.0) * weights[0];

			get_dir_3(dir, u1, v0);
			color += textureLod(source_cubemap, normalize(dir), 0.0) * weights[1];

			get_dir_3(dir, u0, v1);
			color += textureLod(source_cubemap, normalize(dir), 0.0) * weights[2];

			get_dir_3(dir, u1, v1);
			color += textureLod(source_cubemap, normalize(dir), 0.0) * weights[3];
			break;
		case 4:
			get_dir_4(dir, u0, v0);
			color = textureLod(source_cubemap, normalize(dir), 0.0) * weights[0];

			get_dir_4(dir, u1, v0);
			color += textureLod(source_cubemap, normalize(dir), 0.0) * weights[1];

			get_dir_4(dir, u0, v1);
			color += textureLod(source_cubemap, normalize(dir), 0.0) * weights[2];

			get_dir_4(dir, u1, v1);
			color += textureLod(source_cubemap, normalize(dir), 0.0) * weights[3];
			break;
		default:
			get_dir_5(dir, u0, v0);
			color = textureLod(source_cubemap, normalize(dir), 0.0) * weights[0];

			get_dir_5(dir, u1, v0);
			color += textureLod(source_cubemap, normalize(dir), 0.0) * weights[1];

			get_dir_5(dir, u0, v1);
			color += textureLod(source_cubemap, normalize(dir), 0.0) * weights[2];

			get_dir_5(dir, u1, v1);
			color += textureLod(source_cubemap, normalize(dir), 0.0) * weights[3];
			break;
	}
	frag_color = color;
}
)<!>"
		};
		setup(_vertex_code, _fragment_code, nullptr, "CubemapDownsamplerRasterShaderRD");
	}
};

#endif
