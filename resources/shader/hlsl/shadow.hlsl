//***************************************************************************************
// Shadows.hlsl by Frank Luna (C) 2015 All Rights Reserved.
//***************************************************************************************

// Include common HLSL code.
#include "common.hlsl"

VKBINDING(0, 0) ConstantBuffer<ObjectBlock> cbPerObject : register(b0, space0);
VKBINDING(1, 0) ConstantBuffer<PassBlock> cbPass : register(b1, space0);

VKBINDING(2, 0) Texture2D colorMapTexture : register(t0, space0);
VKBINDING(3, 0) SamplerState colorMapSampler : register(s0, space0);

struct VertexIn
{
	VKLOCATION(0) float3 PosL    : POSITION;
	VKLOCATION(3) float2 UV : TEXCOORD0;
};

struct VertexOut
{
	VKLOCATION(0) float4 PosH : SV_POSITION;
	VKLOCATION(1) float2 UV : TEXCOORD0;
};

VertexOut vs(VertexIn vIn)
{
    VertexOut vOut;
	float4 posW = mul(cbPerObject.gWorld, float4(vIn.PosL, 1.0f));
    vOut.PosH = mul(cbPass.gShadowTransform, posW);
	vOut.UV = vIn.UV;
    return vOut;
}

void ps(VertexOut input)
{
    float alpha = colorMapTexture.Sample(colorMapSampler, input.UV).a;
	if (alpha < 0.5) {
		clip(-1);
	}
}


