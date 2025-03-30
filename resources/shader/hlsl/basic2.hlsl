#include "common.hlsl"

VKBINDING(0, 0) ConstantBuffer<ObjectBlock> cbPerObject : register(b0, space0);
VKBINDING(1, 0) ConstantBuffer<PassBlock> cbPass : register(b1, space0);
VKBINDING(2, 0) ConstantBuffer<MaterialBlock> cbMaterial : register(b2, space0);

VKBINDING(3, 1) Texture2D shadowMap : register(t1,space1);
VKBINDING(4, 1) SamplerState shadowMapSampler : register(s1, space1);

struct VertexIn
{
	VKLOCATION(0) float3 Pos    : POSITION;
    VKLOCATION(1) float3 Normal : NORMAL;

};

struct VertexOut
{
	float4 Pos : SV_POSITION;
	VKLOCATION(0) float3 Normal : NORMAL0;
	VKLOCATION(1) float3 Color : COLOR0;
	VKLOCATION(2) float3 ViewVec : TEXCOORD1;
	VKLOCATION(3) float3 LightVec : TEXCOORD2;
	VKLOCATION(4) float4 worldPos : TEXCOORD3;
};

	
VertexOut VS(VertexIn input)
{
    VertexOut output;
	
    float4 posW = mul(cbPerObject.gWorld, float4(input.Pos, 1.0f));
	output.Pos = mul(cbPass.gViewProj, posW);
	
    
	output.Normal = mul((float3x3)cbPerObject.gWorld, input.Normal);
	
	float3 lightPos = cbPass.gDirLights[0].Position;
    output.LightVec = normalize(lightPos - input.Pos);
    output.ViewVec = -posW.xyz;
	
	output.worldPos = mul(cbPerObject.gWorld, float4(input.Pos, 1.0));
	
	
	output.Color = cbMaterial.gDiffuseAlbedo.rgb;
    return output;
}

#define ambient 0.1

float textureProj(float4 shadowCoord, float2 off)
{
    float shadow = 1.0;
	if ( shadowCoord.z > -1.0 && shadowCoord.z < 1.0 )
	{		
		float dist = shadowMap.Sample( shadowMapSampler, shadowCoord.xy + off ).r;
		if ( shadowCoord.w > 0.0 && dist < shadowCoord.z )
		{
			shadow = ambient;
		}
	}
	return shadow;
}


float filterPCF(float4 sc)
{
	int2 texDim;
	shadowMap.GetDimensions(texDim.x, texDim.y);
	float scale = 1.5;
	float dx = scale * 1.0 / float(texDim.x);
	float dy = scale * 1.0 / float(texDim.y);

	float shadowFactor = 0.0;
	int count = 0;
	int range = 1;

	for (int x = -range; x <= range; x++)
	{
		for (int y = -range; y <= range; y++)
		{
			shadowFactor += textureProj(sc, float2(dx*x, dy*y));
			count++;
		}

	}
	return shadowFactor / count;
}

float4 PS(VertexOut input) : SV_Target
{
    float4x4 lightViewProj = cbPass.gDirLights[0].lightViewProject;
    float4 lightSpacePos = mul(lightViewProj, input.worldPos);
	float4 shadowcoord = lightSpacePos / lightSpacePos.w;
	shadowcoord.rg = shadowcoord.rg * float2(0.5f, -0.5f) + float2(0.5f, 0.5f);
    float shadow = filterPCF(shadowcoord);
	float3 N = normalize(input.Normal);
	float3 L = normalize(input.LightVec);
	//L = normalize(cbPass.gDirLights[0].Direction);
	float3 V = normalize(input.ViewVec);
	float3 R = normalize(-reflect(L, N));
	float3 diffuse = max(dot(N, L), ambient) * input.Color;

	return float4(diffuse * shadow, 1.0);
}