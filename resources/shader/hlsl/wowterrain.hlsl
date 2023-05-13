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
  float3 alpha = gTextureArray[4].Sample(gsamLinearClamp, pin.Texcoord0 / 8.0).rgb;
  float a0 = alpha.r;  
  float a1 = alpha.g;
  float a2 = alpha.b;
  
  float3 t0 = gTextureArray[0].Sample(gsamLinearWrap, pin.Texcoord0).rgb;
  float3 t1 = gTextureArray[1].Sample(gsamLinearWrap, pin.Texcoord0).rgb;
  float3 t2 = gTextureArray[2].Sample(gsamLinearWrap, pin.Texcoord0).rgb;
  float3 t3 = gTextureArray[3].Sample(gsamLinearWrap, pin.Texcoord0).rgb;
  
  return float4 (t0 * (1.0 - (a0 + a1 + a2)) + t1 * a0 + t2 * a1 + t3 * a2, 1.0);
}