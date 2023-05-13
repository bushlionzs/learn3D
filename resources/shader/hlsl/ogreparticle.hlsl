#include "common.hlsl"
struct VertexIn
{
	float3 PosL    : POSITION;
	float2 iTexcoord_0 : TEXCOORD0;
	float4 color  : COLOR;
};

struct VertexOut
{
	float4 PosH    : SV_POSITION;
	float4 color  : COLOR;
    float2	oTexcoord_0 : TEXCOORD0;
};

VertexOut VS(VertexIn vIn)
{
	VertexOut vOut;
	
	vOut.PosH = mul(gWorldViewProj, float4(vIn.PosL, 1.0f));
	vOut.oTexcoord_0 = vIn.iTexcoord_0;
	vOut.color = vIn.color;
	return vOut;
}

float4 PS(VertexOut pin) : SV_Target
{
	float4 texel_0	=	gTextureArray[0].Sample(gsamLinearClamp, pin.oTexcoord_0);
	clip(texel_0.a - 0.3f);
	float4 outcolor = texel_0 * pin.color;
	outcolor.a = texel_0.a;
	return outcolor;
}
