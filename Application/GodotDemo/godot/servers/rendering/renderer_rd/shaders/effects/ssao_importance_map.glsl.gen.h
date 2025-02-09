/* WARNING, THIS FILE WAS GENERATED, DO NOT EDIT */
#ifndef SSAO_IMPORTANCE_MAP_GLSL_GEN_H_RD
#define SSAO_IMPORTANCE_MAP_GLSL_GEN_H_RD

#include "servers/rendering/renderer_rd/shader_rd.h"

class SsaoImportanceMapShaderRD : public ShaderRD {

public:

	SsaoImportanceMapShaderRD() {

		static const char _compute_code[] = {
R"<!>(
#version 450

#VERSION_DEFINES

layout(local_size_x = 8, local_size_y = 8, local_size_z = 1) in;

#ifdef GENERATE_MAP
layout(set = 0, binding = 0) uniform sampler2DArray source_texture;
#else
layout(set = 0, binding = 0) uniform sampler2D source_importance;
#endif
layout(r8, set = 1, binding = 0) uniform restrict writeonly image2D dest_image;

#ifdef PROCESS_MAPB
layout(set = 2, binding = 0, std430) buffer Counter {
	uint sum;
}
counter;
#endif

layout(push_constant, std430) uniform Params {
	vec2 half_screen_pixel_size;
	float intensity;
	float power;
}
params;

void main() {
	
	ivec2 ssC = ivec2(gl_GlobalInvocationID.xy);

#ifdef GENERATE_MAP
	
	uvec2 base_position = ssC * 2;

	vec2 base_uv = (vec2(base_position) + vec2(0.5f, 0.5f)) * params.half_screen_pixel_size;

	float minV = 1.0;
	float maxV = 0.0;
	for (int i = 0; i < 4; i++) {
		vec4 vals = textureGather(source_texture, vec3(base_uv, i));

		
		vals = params.intensity * vals;

		vals = 1 - vals;

		vals = pow(clamp(vals, 0.0, 1.0), vec4(params.power));

		maxV = max(maxV, max(max(vals.x, vals.y), max(vals.z, vals.w)));
		minV = min(minV, min(min(vals.x, vals.y), min(vals.z, vals.w)));
	}

	float min_max_diff = maxV - minV;

	imageStore(dest_image, ssC, vec4(pow(clamp(min_max_diff * 2.0, 0.0, 1.0), 0.8)));
#endif

#ifdef PROCESS_MAPA
	vec2 uv = (vec2(ssC) + 0.5f) * params.half_screen_pixel_size * 2.0;

	float center = textureLod(source_importance, uv, 0.0).x;

	vec2 half_pixel = params.half_screen_pixel_size;

	vec4 vals;
	vals.x = textureLod(source_importance, uv + vec2(-half_pixel.x * 3, -half_pixel.y), 0.0).x;
	vals.y = textureLod(source_importance, uv + vec2(+half_pixel.x, -half_pixel.y * 3), 0.0).x;
	vals.z = textureLod(source_importance, uv + vec2(+half_pixel.x * 3, +half_pixel.y), 0.0).x;
	vals.w = textureLod(source_importance, uv + vec2(-half_pixel.x, +half_pixel.y * 3), 0.0).x;

	float avg = dot(vals, vec4(0.25, 0.25, 0.25, 0.25));

	imageStore(dest_image, ssC, vec4(avg));
#endif

#ifdef PROCESS_MAPB
	vec2 uv = (vec2(ssC) + 0.5f) * params.half_screen_pixel_size * 2.0;

	float center = textureLod(source_importance, uv, 0.0).x;

	vec2 half_pixel = params.half_screen_pixel_size;

	vec4 vals;
	vals.x = textureLod(source_importance, uv + vec2(-half_pixel.x, -half_pixel.y * 3), 0.0).x;
	vals.y = textureLod(source_importance, uv + vec2(+half_pixel.x * 3, -half_pixel.y), 0.0).x;
	vals.z = textureLod(source_importance, uv + vec2(+half_pixel.x, +half_pixel.y * 3), 0.0).x;
	vals.w = textureLod(source_importance, uv + vec2(-half_pixel.x * 3, +half_pixel.y), 0.0).x;

	float avg = dot(vals, vec4(0.25, 0.25, 0.25, 0.25));

	imageStore(dest_image, ssC, vec4(avg));

	
	uint sum = uint(clamp(avg, 0.0, 1.0) * 255.0 + 0.5);

	
	if (((ssC.x % 3) + (ssC.y % 3)) == 0) {
		atomicAdd(counter.sum, sum);
	}
#endif
}
)<!>"
		};
		setup(nullptr, nullptr, _compute_code, "SsaoImportanceMapShaderRD");
	}
};

#endif
