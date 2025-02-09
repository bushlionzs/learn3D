/* WARNING, THIS FILE WAS GENERATED, DO NOT EDIT */
#ifndef SHADOW_FRUSTUM_GLSL_GEN_H_RD
#define SHADOW_FRUSTUM_GLSL_GEN_H_RD

#include "servers/rendering/renderer_rd/shader_rd.h"

class ShadowFrustumShaderRD : public ShaderRD {

public:

	ShadowFrustumShaderRD() {

		static const char _vertex_code[] = {
R"<!>(
#version 450

#VERSION_DEFINES

/* clang-format on */

layout(push_constant, std430) uniform Info {
	mat4 mvp;
	vec4 color;
}
info;

layout(location = 0) in vec3 vertex_attrib;

void main() {
	vec4 vertex = info.mvp * vec4(vertex_attrib, 1.0);
	vertex.xyz /= vertex.w;
	gl_Position = vec4(vertex.xy, 0.0, 1.0);
}

/* clang-format off */
)<!>"
		};
		static const char _fragment_code[] = {
R"<!>(
#version 450

#VERSION_DEFINES

layout(push_constant, std430) uniform Info {
	mat4 mvp;
	vec4 color;
}
info;

layout(location = 0) out vec4 frag_color;

void main() {
	frag_color = info.color;
}
)<!>"
		};
		setup(_vertex_code, _fragment_code, nullptr, "ShadowFrustumShaderRD");
	}
};

#endif
