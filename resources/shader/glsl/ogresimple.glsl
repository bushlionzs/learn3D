#version 450

#ifdef VERTEX_SHADER
#include "common.glsl"


layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 3) in vec2 texcoord;


layout (location = 0) out vec2 outTexC;


void main() {
    gl_Position = cbPerObject.gWorldViewProj * vec4(position, 1.0);
	gl_Position.y = -gl_Position.y;
	outTexC = (cbMaterial.gTexTransform * vec4(texcoord, 0.0f, 1.0f)).xy;
	outTexC = texcoord;
}
#endif //VERTEX_SHADER

#ifdef FRAGMENT_SHADER
#include "common.glsl"

layout (location = 0) in vec2 outTexC;

layout(location = 0) out vec4 outColor;

void main() {
	outColor = texture(gTextureArray[0], outTexC);

	if(outColor.a < 0.5f)
	{
	    discard;
	}
}
#endif //FRAGMENT_SHADER