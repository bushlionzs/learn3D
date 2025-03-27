#include "common.hlsl"

VKBINDING(0, 0) ConstantBuffer<ObjectBlock> cbPerObject : register(b0, space0);
VKBINDING(1, 0) ConstantBuffer<PassBlock> cbPass : register(b1, space0);

struct VSInput
{
    float3 position : POSITION;
};


float4 VS(VSInput input) : SV_Position
{
    float4 result;   
    result = mul(cbPerObject.gWorld, float4(input.position.xyz, 1));
    result = mul(cbPass.gViewProj, result);
    result.z *= result.w;

    return result;
}


void PS()
{
}
