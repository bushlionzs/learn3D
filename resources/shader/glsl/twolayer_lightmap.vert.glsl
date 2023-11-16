#version 450

#include "common.glsl"


layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texcoord;
layout (location = 3) in vec2 texcoord1;
layout (location = 4) in vec2 texcoord2;


layout (location = 0) out vec2 outTexC;
layout (location = 1) out vec2 outTexC2;
layout (location = 2) out vec2 outTexC3;



void main()
{
	gl_Position = cbPerObject.gWorldViewProj * vec4(position, 1.0);
	outTexC = texcoord;
	outTexC2 = texcoord1;
	outTexC3 = texcoord2;
	gl_Position.y = -gl_Position.y;
}
