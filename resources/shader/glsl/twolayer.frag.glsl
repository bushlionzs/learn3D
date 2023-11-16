#version 450

#include "common.glsl"


layout (location = 0) in vec2 outTexC;
layout (location = 1) in vec2 outTexC2;

layout(location = 0) out vec4 outColor;

void main()
{
    vec4 basetex = texture(gTextureArray[0], outTexC);
	vec4 basetex2 = texture(gTextureArray[1], outTexC2);
	
	vec3 TexColor = mix(basetex.rgb, basetex2.rgb, basetex.a);
	outColor =  vec4(TexColor, 1.0);
	gl_Position.y = -gl_Position.y;
}
