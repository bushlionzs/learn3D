#version 450 core
#extension GL_GOOGLE_include_directive : require

#include "glslBase.glsl"

STRUCT(PsInOpaque)
{
	DATA(float4, position, SV_Position);
};


#ifdef VERTEX_SHADER
layout (std430, UPDATE_FREQ_NONE, binding = 3) readonly buffer vertexDataBuffer
{
	VertexData vertexDataBuffer_data[];
};

float4 LoadVertex(uint index)
{
    return float4(vertexDataBuffer_data[index].vertexPosition, 1.0f);
}

CBUFFER(objectUniformBlock, UPDATE_FREQ_PER_DRAW, b0, binding = 0)
{
    DATA(float4x4, worldViewProjMat, None);
    DATA(uint, viewID, None);
};





void main()
{
	const uint vertexID = uint(gl_VertexIndex);
	PsInOpaque Out;

	float4 vertexPos = LoadVertex(vertexID);
	Out.position = mul(worldViewProjMat, vertexPos);

	{
		PsInOpaque out_PsInOpaque = Out;
		gl_Position = out_PsInOpaque.position;
		return;
	}
}
#endif //VERTEX_SHADER

#ifdef FRAGMENT_SHADER
layout(location = 0) out(float4) out_float4;
void main()
{
	PsInOpaque In;
	In.position = float4(float4(gl_FragCoord.xyz, 1.0f / gl_FragCoord.w));
	const uint primitiveID = uint(gl_PrimitiveID);
	float4 Out;
	Out = unpackUnorm4x8(  (((( 0 ) & 0x00000003 ) << 30 ) | (((primitiveID) & 0x3FFFFFFF ) << 0 )) );
	{
		out_float4 = Out;
		return;
	}
}
#endif //FRAGMENT_SHADER