#version 450


#include "common.glsl"


layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 3) in vec2 texcoord;


layout (location = 0) out vec3 outUV;


void main() {
	vec4 posW = cbPerObject.gWorld * vec4(position, 1.0f);
	posW.xyz -= cbPass.gEyePosW;
	
	gl_Position = cbPass.gViewProj * vec4(posW.xyz, 1.0);
	outUV = position;
}

