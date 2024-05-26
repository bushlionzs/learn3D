#version 450

#include "common.glsl"


layout (location = 0) in vec2 outTexC;
layout (location = 1) in vec2 outTexC2;


layout(location = 0) out vec4 outColor;


void main()
{
    vec4 basetex = texture(first, outTexC);
	vec4 basetex2 = texture(second, outTexC2).rrrr;
	
	vec3 BlendColor = basetex2.rgb * basetex.rgb;
	outColor =  vec4(BlendColor, 1.0);
}
