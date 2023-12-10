#version 450

#ifdef VERTEX_SHADER
#include "common.glsl"


layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color_diffuse;


layout (location = 0) out vec4 color;
layout (location = 1) out vec4 ProjPos;


void main() {
    gl_Position = cbPerObject.gWorldViewProj * vec4(position, 1.0);
	gl_Position.y = -gl_Position.y;
	
	vec4 posW = cbPerObject.gWorld * vec4(position, 1.0f);
	color = color_diffuse;
	
	ProjPos = cbPerObject.gProjector * posW;
}
#endif //VERTEX_SHADER

#ifdef FRAGMENT_SHADER
#include "common.glsl"

layout (location = 0) in vec4 color;
layout (location = 1) in vec4 ProjPos;

layout(location = 0) out vec4 outColor;

void main() {
    vec2 ProjTex;
	outColor = vec4(1.0f, 0.0f, 0.0f, 0.0f);

	ProjTex.x =(ProjPos.x/ProjPos.w) * 0.5 + 0.5f;
	ProjTex.y= (ProjPos.y/ProjPos.w) * 0.5 + 0.5f;
	
	if ((ProjTex.x>= 0.0 && ProjTex.x<=1.0) && (ProjTex.y>= 0.0 && ProjTex.y<=1.0))
	{
	    vec4 tmp = cbMaterial.gTexTransform *vec4(ProjTex, 0.0f, 1.0f);
		ProjTex = tmp.xy;
		outColor = texture(gTextureArray[0], ProjTex);
	}
	
	if(outColor.a < 0.5f)
	{
	    discard;
	}
}
#endif //FRAGMENT_SHADER
