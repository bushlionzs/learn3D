
#include "common.hlsl"

VKBINDING(0, 0) ConstantBuffer<ObjectBlock> cbPerObject : register(b0, space0);
VKBINDING(1, 0) ConstantBuffer<PassBlock> cbPass : register(b1, space0);
VKBINDING(2, 0) ConstantBuffer<MaterialBlock> cbMaterial : register(b2, space0);

struct VertexIn
{
	VKLOCATION(0) float3 position : POSITION;
    VKLOCATION(1) float3 normal   : NORMAL;
	VKLOCATION(9) float3 tangentW: TANGENT;
    VKLOCATION(8) float3 bitangentW: BINORMAL;
	VKLOCATION(3) float2 texUV    : TEXCOORD;
};



struct VertexOut
{
	float4 PosH    : SV_POSITION;
	float4 outWorldPos : POSITION;
	float3 outNormal: NORMAL;
	float2 outUV: TEXCOORD;
};

VertexOut VS(VertexIn vIn) 
{
    VertexOut Out;
    Out.outWorldPos = mul(cbPerObject.gWorld , float4(vIn.position, 1.0));
    Out.PosH = mul(cbPass.gViewProj , Out.outWorldPos);    
    Out.outNormal = mul((float3x3)cbPerObject.gWorld , vIn.normal);
    Out.outUV = vIn.texUV;
	return Out;
}


struct PSOutput
{
	float4 color : SV_Target0;
	float4 normal : SV_Target1;
	float4 worldpos : SV_Target2;
};

PSOutput PS(VertexOut pin)
{
	PSOutput Out;
	//Out.color = first.Sample(firstSampler, pin.outUV);
    Out.color = cbPerObject.diffuseColor;
	Out.normal = float4(pin.outNormal, 1.0f);
    Out.worldpos = pin.outWorldPos;
	return Out;
}