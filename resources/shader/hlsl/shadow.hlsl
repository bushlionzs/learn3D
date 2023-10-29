//***************************************************************************************
// Shadows.hlsl by Frank Luna (C) 2015 All Rights Reserved.
//***************************************************************************************

// Include common HLSL code.
#include "common.hlsl"

struct VertexIn
{
	float3 PosL    : POSITION;
	float2 TexC    : TEXCOORD;
};

struct VertexOut
{
	float4 PosH    : SV_POSITION;
	float2 TexC    : TEXCOORD;
};

VertexOut vs(VertexIn vIn)
{
    VertexOut vOut;
    vOut.PosH = mul(gWorldViewProj, float4(vIn.PosL, 1.0f));
    vOut.TexC = vIn.TexC;
	
    return vOut;
}

float4 ps(VertexOut pin) : SV_Target
{
	//return float4(1.0, 0.0, 0.0, 1.0f);
	return float4(gShadowMap[0].Sample(gsamLinearWrap, pin.TexC).rrr, 1.0f);
}


