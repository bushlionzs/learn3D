/* WARNING, THIS FILE WAS GENERATED, DO NOT EDIT */
#ifndef LUMINANCE_REDUCE_RASTER_GLSL_GEN_H_RD
#define LUMINANCE_REDUCE_RASTER_GLSL_GEN_H_RD

#include "servers/rendering/renderer_rd/shader_rd.h"

class LuminanceReduceRasterShaderRD : public ShaderRD {

public:

	LuminanceReduceRasterShaderRD() {

		static const char _vertex_code[] = {
R"<!>(
#version 450

#VERSION_DEFINES


layout(push_constant, std430) uniform PushConstant {
	ivec2 source_size;
	ivec2 dest_size;

	float exposure_adjust;
	float min_luminance;
	float max_luminance;
	uint pad1;
}
settings;

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


layout(push_constant, std430) uniform PushConstant {
	ivec2 source_size;
	ivec2 dest_size;

	float exposure_adjust;
	float min_luminance;
	float max_luminance;
	uint pad1;
}
settings;

layout(location = 0) in vec2 uv_interp;
/* clang-format on */

layout(set = 0, binding = 0) uniform sampler2D source_exposure;

#ifdef FINAL_PASS
layout(set = 1, binding = 0) uniform sampler2D prev_luminance;
#endif

layout(location = 0) out highp float luminance;

void main() {
	ivec2 dest_pos = ivec2(uv_interp * settings.dest_size);
	ivec2 src_pos = ivec2(uv_interp * settings.source_size);

	ivec2 next_pos = (dest_pos + ivec2(1)) * settings.source_size / settings.dest_size;
	next_pos = max(next_pos, src_pos + ivec2(1)); 

	highp vec3 source_color = vec3(0.0);
	for (int i = src_pos.x; i < next_pos.x; i++) {
		for (int j = src_pos.y; j < next_pos.y; j++) {
			source_color += texelFetch(source_exposure, ivec2(i, j), 0).rgb;
		}
	}

	source_color /= float((next_pos.x - src_pos.x) * (next_pos.y - src_pos.y));

#ifdef FIRST_PASS
	luminance = max(source_color.r, max(source_color.g, source_color.b));

	
	
	
#else
	luminance = source_color.r;
#endif

#ifdef FINAL_PASS
	
	luminance = clamp(luminance, settings.min_luminance, settings.max_luminance);

	
	highp float prev_lum = texelFetch(prev_luminance, ivec2(0, 0), 0).r; 
	luminance = prev_lum + (luminance - prev_lum) * clamp(settings.exposure_adjust, 0.0, 1.0);
#endif
}
)<!>"
		};
		setup(_vertex_code, _fragment_code, nullptr, "LuminanceReduceRasterShaderRD");
	}
};

#endif
