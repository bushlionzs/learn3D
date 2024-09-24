#version 450
#extension GL_ARB_separate_shader_objects : enable

#include "common.glsl"

layout (location = 0) in vec3 inUV;

layout(location = 0) out vec4 outColor;

void main() {
    vec3 aa = vec3(0.15427, 0.01148, -0.5);
	vec3 texColor = texture(gCubeMap, inUV).rgb;
	texColor = texColor / (texColor + vec3(1.0f, 1.0f, 1.0f));
	outColor = vec4(texColor, 1.0f);
}