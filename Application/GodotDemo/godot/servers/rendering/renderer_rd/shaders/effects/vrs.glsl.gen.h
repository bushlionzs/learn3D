/* WARNING, THIS FILE WAS GENERATED, DO NOT EDIT */
#ifndef VRS_GLSL_GEN_H_RD
#define VRS_GLSL_GEN_H_RD

#include "servers/rendering/renderer_rd/shader_rd.h"

class VrsShaderRD : public ShaderRD {

public:

	VrsShaderRD() {

		static const char _vertex_code[] = {
R"<!>(
#version 450

#VERSION_DEFINES

#ifdef USE_MULTIVIEW
#ifdef has_VK_KHR_multiview
#extension GL_EXT_multiview : enable
#define ViewIndex gl_ViewIndex
#else 
#define ViewIndex 0
#endif 
#endif 

#ifdef USE_MULTIVIEW
layout(location = 0) out vec3 uv_interp;
#else
layout(location = 0) out vec2 uv_interp;
#endif

layout(push_constant, std430) uniform Params {
	float max_texel_factor;
	float res1;
	float res2;
	float res3;
}
params;

void main() {
	vec2 base_arr[3] = vec2[](vec2(-1.0, -1.0), vec2(-1.0, 3.0), vec2(3.0, -1.0));
	gl_Position = vec4(base_arr[gl_VertexIndex], 0.0, 1.0);
	uv_interp.xy = clamp(gl_Position.xy, vec2(0.0, 0.0), vec2(1.0, 1.0)) * 2.0; 
#ifdef USE_MULTIVIEW
	uv_interp.z = ViewIndex;
#endif
}

)<!>"
		};
		static const char _fragment_code[] = {
R"<!>(
#version 450

#VERSION_DEFINES

#ifdef USE_MULTIVIEW
#ifdef has_VK_KHR_multiview
#extension GL_EXT_multiview : enable
#define ViewIndex gl_ViewIndex
#else 
#define ViewIndex 0
#endif 
#endif 

#ifdef USE_MULTIVIEW
layout(location = 0) in vec3 uv_interp;
layout(set = 0, binding = 0) uniform sampler2DArray source_color;
#else /* USE_MULTIVIEW */
layout(location = 0) in vec2 uv_interp;
layout(set = 0, binding = 0) uniform sampler2D source_color;
#endif /* USE_MULTIVIEW */

layout(location = 0) out uint frag_color;

layout(push_constant, std430) uniform Params {
	float max_texel_factor;
	float res1;
	float res2;
	float res3;
}
params;

void main() {
#ifdef USE_MULTIVIEW
	vec3 uv = uv_interp;
#else
	vec2 uv = uv_interp;
#endif

	
	vec4 color = textureLod(source_color, uv, 0.0);

	
	color.r = clamp(floor(color.r * params.max_texel_factor + 0.1), 0.0, params.max_texel_factor);
	color.g = clamp(floor(color.g * params.max_texel_factor + 0.1), 0.0, params.max_texel_factor);

	
	if (color.r < (color.g - 1.0)) {
		color.r = color.g - 1.0;
	}
	if (color.g < (color.r - 1.0)) {
		color.g = color.r - 1.0;
	}

	
	frag_color = int(color.r + 0.1) << 2;
	frag_color += int(color.g + 0.1);
}
)<!>"
		};
		setup(_vertex_code, _fragment_code, nullptr, "VrsShaderRD");
	}
};

#endif
