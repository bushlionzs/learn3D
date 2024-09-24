#version 450

#ifdef VERTEX_SHADER
#include "common.glsl"


layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 3) in vec2 texcoord;


layout (location = 0) out vec2 outTexC;


void main() {
    gl_Position = cbPass.gViewProj * cbPerObject.gWorld * vec4(position, 1.0);
	gl_Position.y = -gl_Position.y;
	outTexC = texcoord;
}
#endif //VERTEX_SHADER

#ifdef FRAGMENT_SHADER
#include "common.glsl"

layout (location = 0) in vec2 inTexC;

layout(location = 0) out vec4 outColor;

void main() {
	outColor = texture(first, inTexC);
    //outColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	if(outColor.a < 0.5f)
	{
	    discard;
	}
}
#endif //FRAGMENT_SHADER