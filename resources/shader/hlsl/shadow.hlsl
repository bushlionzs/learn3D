//***************************************************************************************
// Shadows.hlsl by Frank Luna (C) 2015 All Rights Reserved.
//***************************************************************************************

// Include common HLSL code.
#include "common.hlsl"

VKBINDING(0, 0) ConstantBuffer<ObjectBlock> cbPerObject : register(b0, space0);
VKBINDING(1, 0) ConstantBuffer<PassBlock> cbPass : register(b1, space0);

struct VertexIn
{
	VKLOCATION(0) float3 PosL    : POSITION;
};

struct VertexOut
{
	float4 PosH    : SV_POSITION;
};

VertexOut vs(VertexIn vIn)
{
    VertexOut vOut;
	float4 posW = mul(cbPerObject.gWorld, float4(vIn.PosL, 1.0f));
    vOut.PosH = mul(cbPass.gShadowTransform, posW);
    return vOut;
}

void ps()
{
}


