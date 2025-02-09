/* WARNING, THIS FILE WAS GENERATED, DO NOT EDIT */
#ifndef SPECULAR_MERGE_GLSL_GEN_H_RD
#define SPECULAR_MERGE_GLSL_GEN_H_RD

#include "servers/rendering/renderer_rd/shader_rd.h"

class SpecularMergeShaderRD : public ShaderRD {

public:

	SpecularMergeShaderRD() {

		static const char _vertex_code[] = {
R"<!>(
#version 450

#VERSION_DEFINES

#if defined(USE_MULTIVIEW) && defined(has_VK_KHR_multiview)
#extension GL_EXT_multiview : enable
#endif

#ifdef USE_MULTIVIEW
#ifdef has_VK_KHR_multiview
#define ViewIndex gl_ViewIndex
#else 

#define ViewIndex 0
#endif 
#else 

#define ViewIndex 0
#endif 

#ifdef USE_MULTIVIEW
layout(location = 0) out vec3 uv_interp;
#else 
layout(location = 0) out vec2 uv_interp;
#endif 

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

#if defined(USE_MULTIVIEW) && defined(has_VK_KHR_multiview)
#extension GL_EXT_multiview : enable
#endif

#ifdef USE_MULTIVIEW
#ifdef has_VK_KHR_multiview
#define ViewIndex gl_ViewIndex
#else 

#define ViewIndex 0
#endif 
#else 

#define ViewIndex 0
#endif 

#ifdef USE_MULTIVIEW
layout(location = 0) in vec3 uv_interp;
#else 
layout(location = 0) in vec2 uv_interp;
#endif 

#ifdef USE_MULTIVIEW
layout(set = 0, binding = 0) uniform sampler2DArray specular;
#else 
layout(set = 0, binding = 0) uniform sampler2D specular;
#endif 

#ifdef MODE_SSR

#ifdef USE_MULTIVIEW
layout(set = 1, binding = 0) uniform sampler2DArray ssr;
#else 
layout(set = 1, binding = 0) uniform sampler2D ssr;
#endif 

#endif

#ifdef MODE_MERGE

#ifdef USE_MULTIVIEW
layout(set = 2, binding = 0) uniform sampler2DArray diffuse;
#else 
layout(set = 2, binding = 0) uniform sampler2D diffuse;
#endif 

#endif

layout(location = 0) out vec4 frag_color;

void main() {
	frag_color.rgb = texture(specular, uv_interp).rgb;
	frag_color.a = 0.0;
#ifdef MODE_SSR

	vec4 ssr_color = texture(ssr, uv_interp);
	frag_color.rgb = mix(frag_color.rgb, ssr_color.rgb, ssr_color.a);
#endif

#ifdef MODE_MERGE
	frag_color += texture(diffuse, uv_interp);
#endif
	
}
)<!>"
		};
		setup(_vertex_code, _fragment_code, nullptr, "SpecularMergeShaderRD");
	}
};

#endif
