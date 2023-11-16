#version 450

#include "common.glsl"


layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texcoord;

layout (location = 0) out vec2 outTexC;


void main()
{
	gl_Position = cbPerObject.gWorldViewProj * vec4(position, 1.0);
	outTexC = texcoord;
	gl_Position.y = -gl_Position.y;
}
