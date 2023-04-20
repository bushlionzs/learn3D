Texture2D gTexture: register(t0);
SamplerState gsamPointWrap        : register(s0);
SamplerState gsamPointClamp       : register(s1);
SamplerState gsamLinearWrap       : register(s2);
SamplerState gsamLinearClamp      : register(s3);
SamplerState gsamAnisotropicWrap  : register(s4);
SamplerState gsamAnisotropicClamp : register(s5);
SamplerComparisonState gsamShadow : register(s6);
cbuffer cbPerObject : register(b0)
{
    float4x4 gWorld;
	float4x4 gWorldInvTranspose;
	float4x4 gWorldViewProj;
};

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

VertexOut vs(VertexIn vIn)
{
	VertexOut vOut;
	
	vOut.PosH = mul(gWorldViewProj, float4(vIn.PosL, 1.0f));
	vOut.oTexcoord_0 = vIn.iTexcoord_0;
	return vOut;
}

float4 ps(VertexOut pin) : SV_Target
{
	//return float4(1.0f, 0.0f, 0.0f, 1.0f);
	//return gTexture.Sample(gsamLinearClamp, float3(pin.oTexcoord_0, 0.0f));
	return gTexture.Sample(gsamLinearClamp, pin.oTexcoord_0);
}
