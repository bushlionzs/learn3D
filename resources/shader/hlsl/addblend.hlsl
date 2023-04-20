#include "common.hlsl"
struct VertexIn
{
	float3 PosL    : POSITION;
    float3 NormalL : NORMAL;
	float2 TexC    : TEXCOORD;
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
	vOut.oTexcoord_0 = vIn.TexC;
	return vOut;
}

float4 PS(VertexOut pin) : SV_Target
{
	float4 texel_0	=	gTextureArray[0].Sample(gsamLinearWrap, pin.oTexcoord_0);
	float4 texel_1	=	gTextureArray[1].Sample(gsamLinearWrap, pin.oTexcoord_0);
	
	clip(texel_0.a - 0.5f);
	clip(texel_1.a - 0.5f);
	float4 aa =  texel_0 + texel_1;
	aa.a = texel_1.a;
	
	return texel_1;
}
