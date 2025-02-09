/* WARNING, THIS FILE WAS GENERATED, DO NOT EDIT */
#ifndef BLIT_GLSL_GEN_H_RD
#define BLIT_GLSL_GEN_H_RD

#include "servers/rendering/renderer_rd/shader_rd.h"

class BlitShaderRD : public ShaderRD {

public:

	BlitShaderRD() {

		static const char _vertex_code[] = {
R"<!>(
#version 450

#VERSION_DEFINES

layout(push_constant, std140) uniform Pos {
	vec4 src_rect;
	vec4 dst_rect;

	vec2 eye_center;
	float k1;
	float k2;

	float upscale;
	float aspect_ratio;
	uint layer;
	uint pad1;
}
data;

layout(location = 0) out vec2 uv;

void main() {
	vec2 base_arr[4] = vec2[](vec2(0.0, 0.0), vec2(0.0, 1.0), vec2(1.0, 1.0), vec2(1.0, 0.0));
	uv = data.src_rect.xy + base_arr[gl_VertexIndex] * data.src_rect.zw;
	vec2 vtx = data.dst_rect.xy + base_arr[gl_VertexIndex] * data.dst_rect.zw;
	gl_Position = vec4(vtx * 2.0 - 1.0, 0.0, 1.0);
}

)<!>"
		};
		static const char _fragment_code[] = {
R"<!>(
#version 450

#VERSION_DEFINES

layout(push_constant, std140) uniform Pos {
	vec4 src_rect;
	vec4 dst_rect;

	vec2 eye_center;
	float k1;
	float k2;

	float upscale;
	float aspect_ratio;
	uint layer;
	bool convert_to_srgb;
}
data;

layout(location = 0) in vec2 uv;

layout(location = 0) out vec4 color;

#ifdef USE_LAYER
layout(binding = 0) uniform sampler2DArray src_rt;
#else
layout(binding = 0) uniform sampler2D src_rt;
#endif

vec3 linear_to_srgb(vec3 color) {
	
	color = clamp(color, vec3(0.0), vec3(1.0));
	const vec3 a = vec3(0.055f);
	return mix((vec3(1.0f) + a) * pow(color.rgb, vec3(1.0f / 2.4f)) - a, 12.92f * color.rgb, lessThan(color.rgb, vec3(0.0031308f)));
}

void main() {
#ifdef APPLY_LENS_DISTORTION
	vec2 coords = uv * 2.0 - 1.0;
	vec2 offset = coords - data.eye_center;

	
	offset.y /= data.aspect_ratio;

	
	vec2 offset_sq = offset * offset;
	float radius_sq = offset_sq.x + offset_sq.y;
	float radius_s4 = radius_sq * radius_sq;
	float distortion_scale = 1.0 + (data.k1 * radius_sq) + (data.k2 * radius_s4);
	offset *= distortion_scale;

	
	offset.y *= data.aspect_ratio;

	
	coords = offset + data.eye_center;
	coords /= data.upscale;

	
	if (coords.x < -1.0 || coords.y < -1.0 || coords.x > 1.0 || coords.y > 1.0) {
		color = vec4(0.0, 0.0, 0.0, 1.0);
	} else {
		
		coords = (coords + vec2(1.0)) / vec2(2.0);
		color = texture(src_rt, vec3(coords, data.layer));
	}
#elif defined(USE_LAYER)
	color = texture(src_rt, vec3(uv, data.layer));
#else
	color = texture(src_rt, uv);
#endif

	if (data.convert_to_srgb) {
		color.rgb = linear_to_srgb(color.rgb); 
	}
}
)<!>"
		};
		setup(_vertex_code, _fragment_code, nullptr, "BlitShaderRD");
	}
};

#endif
