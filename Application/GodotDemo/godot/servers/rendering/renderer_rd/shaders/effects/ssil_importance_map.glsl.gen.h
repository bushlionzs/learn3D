/* WARNING, THIS FILE WAS GENERATED, DO NOT EDIT */
#ifndef SSIL_IMPORTANCE_MAP_GLSL_GEN_H_RD
#define SSIL_IMPORTANCE_MAP_GLSL_GEN_H_RD

#include "servers/rendering/renderer_rd/shader_rd.h"

class SsilImportanceMapShaderRD : public ShaderRD {

public:

	SsilImportanceMapShaderRD() {

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
	float pad;
}
params;

void main() {
	
	ivec2 ssC = ivec2(gl_GlobalInvocationID.xy);

#ifdef GENERATE_MAP
	
	uvec2 base_position = ssC * 2;

	float avg = 0.0;
	float minV = 1.0;
	float maxV = 0.0;
	for (int i = 0; i < 4; i++) {
		vec3 value_a = texelFetch(source_texture, ivec3(base_position, i), 0).rgb * params.intensity;
		vec3 value_b = texelFetch(source_texture, ivec3(base_position, i) + ivec3(0, 1, 0), 0).rgb * params.intensity;
		vec3 value_c = texelFetch(source_texture, ivec3(base_position, i) + ivec3(1, 0, 0), 0).rgb * params.intensity;
		vec3 value_d = texelFetch(source_texture, ivec3(base_position, i) + ivec3(1, 1, 0), 0).rgb * params.intensity;

		
		float a = dot(value_a, vec3(0.2125, 0.7154, 0.0721));
		float b = dot(value_b, vec3(0.2125, 0.7154, 0.0721));
		float c = dot(value_c, vec3(0.2125, 0.7154, 0.0721));
		float d = dot(value_d, vec3(0.2125, 0.7154, 0.0721));

		maxV = max(maxV, max(max(a, b), max(c, d)));
		minV = min(minV, min(min(a, b), min(c, d)));
	}

	float min_max_diff = maxV - minV;

	imageStore(dest_image, ssC, vec4(pow(clamp(min_max_diff * 2.0, 0.0, 1.0), 0.6)));
#endif

#ifdef PROCESS_MAPA
	vec2 uv = (vec2(ssC) + 0.5) * params.half_screen_pixel_size * 2.0;

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
		setup(nullptr, nullptr, _compute_code, "SsilImportanceMapShaderRD");
	}
};

#endif
