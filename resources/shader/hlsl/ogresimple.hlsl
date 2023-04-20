#include "common.hlsl"
struct VertexIn
{
	float3 PosL    : POSITION;
	float2 iTexcoord_0 : TEXCOORD0;
};

struct VertexOut
{
	float4 PosH    : SV_POSITION;
    float2	oTexcoord_0 : TEXCOORD0;
};

VertexOut VS(VertexIn vIn)
{
	VertexOut vOut;
	
	vOut.PosH = mul(gWorldViewProj, float4(vIn.PosL, 1.0f));
	vOut.oTexcoord_0.x = 1 - vIn.iTexcoord_0.x;
	vOut.oTexcoord_0.y = vIn.iTexcoord_0.y;
	vOut.oTexcoord_0 = vIn.iTexcoord_0;
	return vOut;
}

float4 PS(VertexOut pin) : SV_Target
{
	float3 texel_0	=	gTextureArray[0].Sample(gsamLinearWrap, pin.oTexcoord_0);
	return float4(texel_0, 1.0f);
}
