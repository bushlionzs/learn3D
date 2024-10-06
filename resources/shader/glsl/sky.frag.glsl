#version 450
#extension GL_ARB_separate_shader_objects : enable

#include "common.glsl"

layout (location = 0) in vec3 inUV;

layout(location = 0) out vec4 outColor;

void main() {
	vec3 texColor = texture(gCubeMap, inUV).rgb;
	outColor = vec4(texColor, 1.0f);
}