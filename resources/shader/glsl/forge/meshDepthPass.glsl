#version 450 core
#extension GL_GOOGLE_include_directive : require
#include "glslBase.glsl"
#ifdef VERTEX_SHADER

layout (std430, UPDATE_FREQ_NONE, binding = 4) readonly buffer vertexDataBuffer
{
	VertexData vertexDataBuffer_data[];
};

CBUFFER(objectUniformBlock, UPDATE_FREQ_PER_DRAW, b0, binding = 0)
{
    DATA(float4x4, worldViewProjMat, None);
    DATA(uint, viewID, None);
};

float4 LoadVertex(uint index)
{
    return float4(vertexDataBuffer_data[index].vertexPosition, 1.0f);
}

void main()
{
	float4 vertexPos = LoadVertex(gl_VertexIndex);
	gl_Position= mul(worldViewProjMat, vertexPos);
}
#endif //VERTEX_SHADER

#ifdef FRAGMENT_SHADER
void main()
{

}
#endif //FRAGMENT_SHADER