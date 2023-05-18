#include "common.hlsl"
struct VertexIn
{
	float3 PosL    : POSITION;
	float4 color  : COLOR;
};

struct VertexOut
{
	float4 PosH    : SV_POSITION;
	float4 color   : COLOR;
    float4 ProjPos : POSITION;
};

VertexOut VS(VertexIn vIn)
{
	VertexOut vOut;
	float4 posW = mul(gWorld, float4(vIn.PosL, 1.0f));
	vOut.PosH = mul(gViewProj, posW);
	vOut.color = vIn.color;
	
	vOut.ProjPos = mul(gProjector, posW);
	
	
	return vOut;
}

float4 PS(VertexOut pin) : SV_Target
{
	float2 ProjTex;
	float4 TexColor = float4(1.0f, 0.0f, 0.0f, 0.0f);
	ProjTex.x =(pin.ProjPos.x/pin.ProjPos.w) * 0.5 + 0.5f;
	ProjTex.y= (pin.ProjPos.y/pin.ProjPos.w) * 0.5 + 0.5f;
	
	if (saturate(ProjTex.x) == ProjTex.x&&saturate(ProjTex.y) == ProjTex.y)
	{
	    ProjTex = mul(gTexTransform, float4(ProjTex, 0.0f, 1.0f)).xy;
		TexColor= gTextureArray[0].Sample(gsamLinearClamp, ProjTex);
	}
	
	clip(TexColor.a - 0.5f);
	return TexColor;
}
