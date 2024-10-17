#version 450 core
#extension GL_GOOGLE_include_directive : require
#include "glslBase.glsl"



#ifdef VERTEX_SHADER

layout (std430, UPDATE_FREQ_NONE, binding = 4) readonly buffer vertexDataBuffer
{
	VertexData vertexDataBuffer_data[];
};

layout (std430, UPDATE_FREQ_PER_FRAME, binding = 2) readonly buffer indirectDataBuffer
{
	uint indirectDataBuffer_data[];
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

float2 LoadTexCoord(uint index)
{
    return vertexDataBuffer_data[index].vertexTextureUV;
}


layout(location = 0) out(float2) out_PsInAlphaTested_texCoord;
layout(location = 1) flat out(uint) out_PsInAlphaTested_materialID;
void main()
{
	float4 vertexPos = LoadVertex(gl_VertexIndex);
	gl_Position= mul(worldViewProjMat, vertexPos);
	out_PsInAlphaTested_texCoord = LoadTexCoord(gl_VertexIndex);;
    out_PsInAlphaTested_materialID = indirectDataBuffer_data[gl_VertexIndex];;
}
#endif //VERTEX_SHADER

#ifdef FRAGMENT_SHADER

CBUFFER(PerFrameVBConstants, UPDATE_FREQ_PER_FRAME, b1, binding = 1)
{
	DATA(Transform, transform[ 5 ], None);
	DATA(CullingViewPort, cullingViewports[ 5 ], None);
	DATA(uint, numViewports, None);
};

CBUFFER(VBConstantBuffer, UPDATE_FREQ_NONE, b2, binding = 2)
{
    DATA(VBConstants, vbConstant[2], None);
};


CBUFFER(objectUniformBlock, UPDATE_FREQ_PER_DRAW, b0, binding = 0)
{
    DATA(float4x4, worldViewProjMat, None);
    DATA(uint, viewID, None);
};

RES(Tex2D(float4), diffuseMaps[ 256U ], UPDATE_FREQ_NONE, t3, binding = 6);

RES(SamplerState, nearClampSampler, UPDATE_FREQ_NONE, s0, binding = 5);

layout (std430, UPDATE_FREQ_PER_FRAME, binding = 2) readonly buffer indirectDataBuffer
{
	uint indirectDataBuffer_data[];
};

layout (std430, UPDATE_FREQ_NONE, binding = 3) readonly buffer vertexTexCoordBuffer
{
	uint vertexTexCoordBuffer_data[];
};

layout (std430, UPDATE_FREQ_NONE, binding = 4) readonly buffer vertexDataBuffer
{
	VertexData vertexPositionBuffer_data[];
};

STRUCT(PsInAlphaTested)
{
	DATA(float4, position, SV_Position);
	DATA(float2, texCoord, TEXCOORD0);
	uint materialID;
};

layout(location = 0) in(float2) In_texCoord;
layout(location = 1) flat  in(uint) In_materialID;

void main()
{
    PsInAlphaTested In;
	In.position = float4(float4(gl_FragCoord.xyz, 1.0f / gl_FragCoord.w));
	In.texCoord = In_texCoord;
	In.materialID = In_materialID;
	
	uint materialID = In.materialID;
	float4 texColor = f4(0);
#define CASE_LIST REPEAT_HUNDRED(0) REPEAT_HUNDRED(100) REPEAT_TEN(200) REPEAT_TEN(210) REPEAT_TEN(220) REPEAT_TEN(230) REPEAT_TEN(240) CASE(250) CASE(251) CASE(252) CASE(253) CASE(254) CASE(255) 
#define NonUniformResourceIndexBlock(materialID) \
    	texColor = SampleLvlTex2D(Get(diffuseMaps)[materialID], Get(nearClampSampler), In.texCoord, 0); \

#if VK_EXT_DESCRIPTOR_INDEXING_ENABLED
	NonUniformResourceIndexBlock(nonuniformEXT(materialID))
#elif VK_FEATURE_TEXTURE_ARRAY_DYNAMIC_INDEXING_ENABLED
	NonUniformResourceIndexBlock(materialID)
#else
#define CASE(id) case id: NonUniformResourceIndexBlock(id) break;
	switch(materialID) {CASE_LIST};
#undef CASE
#endif
#undef NonUniformResourceIndexBlock
#undef CASE_LIST

	clip(texColor.a < 0.5f ? -1 : 1);

	{
		return;
	}
}
#endif //FRAGMENT_SHADER