#version 450

#include "common.glsl"


layout (location = 0) in vec2 outTexC;
layout (location = 1) in vec2 outTexC2;
layout (location = 2) in vec2 outTexC3;


layout(location = 0) out vec4 outColor;


void main()
{
    vec4 BaseTex = texture(gTextureArray[0], outTexC);
	vec4 BaseTex2 = texture(gTextureArray[1], outTexC2);
	vec4 LightMapTex = texture(gTextureArray[2], outTexC3);
	
	vec3 BlendTexColor = mix(BaseTex.rgb, BaseTex2.rgb, BaseTex.a); 
	
	
	vec3 TexColor = LightMapTex.rgb * BlendTexColor; 
	
	outColor = vec4(TexColor, 1.0);
}
