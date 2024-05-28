#version 450
#extension GL_ARB_separate_shader_objects : enable

#include "common.glsl"

layout (location = 0) in vec3 inUV;

layout(location = 0) out vec4 outColor;

void main() {
	outColor = texture(gCubeMap, inUV);
	//outColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}