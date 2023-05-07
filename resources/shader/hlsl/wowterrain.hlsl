#include "common.hlsl"
struct VertexIn
{
	float3 PosL    : POSITION;
    float3 NormalL : NORMAL;
	float2 TexC    : TEXCOORD;
	float4 mcvv    : COLOR;
};

struct VertexOut
{
	float4 PosH    : SV_POSITION;
	float3 NormalW : NORMAL;
    float2 Texcoord0 : TEXCOORD0;
	float4 mcvv     : COLOR;
};

VertexOut vs(VertexIn vIn)
{
	VertexOut vOut;
	
	vOut.PosH = mul(gWorldViewProj, float4(vIn.PosL, 1.0f));
	vOut.NormalW = mul((float3x3) gWorld, vIn.NormalL);
	vOut.Texcoord0 = vIn.TexC;
	vOut.mcvv = vIn.mcvv;
	return vOut;
}


float4 ps(VertexOut pin) : SV_Target
{
	float4 texel_0	=	gTextureArray[0].Sample(gsamPointClamp, pin.Texcoord0);
	
	return texel_0;
}