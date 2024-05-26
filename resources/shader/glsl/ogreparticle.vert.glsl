#version 450

#include "common.glsl"


layout (location = 0) in vec3 position;
layout (location = 2) in vec4 color_diffuse;
layout (location = 3) in vec2 texcoord;

layout (location = 0) out vec4 outColor;
layout (location = 1) out vec2 outTexC;

void main() {
    gl_Position = cbPerObject.gWorldViewProj * vec4(position, 1.0);
	gl_Position.y = -gl_Position.y;
	outTexC = texcoord;
	outColor = color_diffuse;
}