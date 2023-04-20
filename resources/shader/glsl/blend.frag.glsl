#version 450
#extension GL_ARB_separate_shader_objects : enable

#include "common.glsl"

layout (location = 0) in vec2 outTexC;

layout(location = 0) out vec4 outColor;

void main() {
    vec4 tex1 = texture(gTextureArray[0], outTexC);
	vec4 tex2 = texture(gTextureArray[1], outTexC);
	
	outColor = tex1 * 0.5 + tex2 * 0.5;
}