#version 450

#ifdef VERTEX_SHADER

#include "common.glsl"


layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 3) in vec2 texcoord;

layout (location = 0) out vec4 outPosW;
layout (location = 1) out vec2 outUV;

void main() {	
    outPosW = cbPerObject.gWorld * vec4(position, 1.0);
	outUV = texcoord;
	gl_Position = cbPass.gViewProj * outPosW;
	gl_Position.y = -gl_Position.y;
}

#endif //VERTEX_SHADER

#ifdef GEOMETRY_SHADER

layout(triangles) in;
layout(triangle_strip, max_vertices = 6) out;

layout (location = 0) in vec4 inPosW[];
layout (location = 1) in vec2 inUV[];

layout (location = 0) out vec4 outPosW;
layout (location = 1) out vec2 outUV;
void main(){
    for (int i = 0; i < 3; ++i)
	{
	   vec4 pos = gl_in[i].gl_Position;
	   outUV  = inUV[i];
	   gl_Position = pos;
	   EmitVertex();
	}
	
	EndPrimitive();
	for (int i = 0; i < 3; ++i)
	{
	   vec4 pos = gl_in[i].gl_Position;
	   outUV  = inUV[i];
	   pos.x += 3.5f;
	   gl_Position = pos;
	   EmitVertex();
	}
	
	EndPrimitive();
}
#endif //GEOMETRY_SHADER
#ifdef FRAGMENT_SHADER
#include "common.glsl"

layout (location = 0) in vec4 inPosH;
layout (location = 1) in vec2 inUV;

layout(location = 0) out vec4 outColor;

void main() {
    outColor = texture(first, inUV);
}
   
#endif //FRAGMENT_SHADER


