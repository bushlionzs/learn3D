#include "common.hlsl"

struct ImGuiUniform
{
    float2 scale;
    float2 translate;
};

VKBINDING(1, 0) ConstantBuffer<ImGuiUniform> cbPass : register(b1, space0);

VKBINDING(4, 0) Texture2D first            : register(t0,space0);
VKBINDING(5, 0) SamplerState firstSampler       : register(s0,space0);

struct VertexIn
{
	VKLOCATION(0) float2 PosL    : POSITION0;
	VKLOCATION(3) float2 iTexcoord_0 : TEXCOORD0;
	VKLOCATION(2) float4 ColorL  : COLOR0;
	
};

struct VertexOut
{
	float4 PosH    : SV_POSITION;
	float4 oColor  : COLOR0;
    float2	oTexcoord_0 : TEXCOORD0;
};

VertexOut VS(VertexIn vIn)
{
	VertexOut vOut;

	vOut.PosH = float4(vIn.PosL * cbPass.scale + cbPass.translate, 0.0, 1.0);
	vOut.oColor = vIn.ColorL;
	vOut.oTexcoord_0 = vIn.iTexcoord_0;
	return vOut;
}

float4 PS(VertexOut pin) : SV_Target
{
	float4 color = first.Sample(firstSampler, pin.oTexcoord_0)* pin.oColor;
	//clip(color.a - 0.5f);
	return color;
}
