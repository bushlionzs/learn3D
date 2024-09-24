#version 450
#extension GL_ARB_separate_shader_objects : enable

#include "common.glsl"

layout (location = 0) in vec4 inPosH;
layout (location = 1) in vec4 inShadowPosH;
layout (location = 2) in vec3 inPosW;
layout (location = 3) in vec3 inNormalW;
layout (location = 4) in vec2 inTexC;

layout(location = 0) out vec4 outColor;

void main() {
    outColor = texture(first, inTexC);
	if(outColor.a < 0.5f)
	{
	    discard;
	}

	//vec3 shadowFactor = vec3(0.0f, 1.0f, 1.0f);
	//shadowFactor[0] = CalcShadowFactor(inShadowPosH, gShadowMap, 1024);
	//outColor = shadowFactor * outColor
}