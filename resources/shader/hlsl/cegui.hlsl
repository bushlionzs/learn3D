#include "common.hlsl"
struct VertexIn
{
	float3 PosL    : POSITION;
	float4 ColorL  : COLOR0;
	float2 iTexcoord_0 : TEXCOORD0;
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
	
	vOut.PosH = mul(gWorldViewProj, float4(vIn.PosL, 1.0f));
	vOut.oColor = vIn.ColorL;
	vOut.oTexcoord_0 = vIn.iTexcoord_0;
	return vOut;
}

float4 PS(VertexOut pin) : SV_Target
{
	float4 color	=	gTextureArray[0].Sample(gsamLinearWrap, pin.oTexcoord_0) * pin.oColor;
	clip(color.a - 0.5f);
	return color;
}
