#include "common.hlsl"

VKBINDING(0, 0) ConstantBuffer<ObjectBlock> cbPerObject : register(b0, space0);
VKBINDING(1, 0) ConstantBuffer<PassBlock> cbPass : register(b1, space0);
VKBINDING(2, 0) ConstantBuffer<MaterialBlock> cbMaterial : register(b2, space0);
VKBINDING(3, 0) ConstantBuffer<cascadeBlock> cascadeInfo : register(b3, space0);

VKBINDING(0, 1) Texture2D first            : register(t0,space1);
VKBINDING(1, 1) Texture2D second           : register(t1,space1);
VKBINDING(2, 1) Texture2D third            : register(t2,space1);
VKBINDING(3, 1) Texture2DArray shadowMap   : register(t3,space1);
VKBINDING(4, 1) TextureCube cubeMap        : register(t4,space1);

VKBINDING(5, 1) SamplerState firstSampler       : register(s0,space1);
VKBINDING(6, 1) SamplerState secondSampler      : register(s1,space1);
VKBINDING(7, 1) SamplerState thirdSampler       : register(s2,space1);
VKBINDING(8, 1) SamplerState shadowMapSampler   : register(s3,space1);
VKBINDING(9, 1) SamplerState cubeSampler        : register(s4,space1);

struct VertexIn
{
	VKLOCATION(0) float3 PosL    : POSITION;
    VKLOCATION(1) float3 NormalL : NORMAL;
#ifdef USETANGENT
	float3 TangentL : TANGENT;
#endif
	VKLOCATION(3) float2 TexC    : TEXCOORD;
#ifdef SKINNED
    VKLOCATION(6) float4 BoneWeights : BLENDWEIGHT;
    VKLOCATION(5) uint4 BoneIndices  : BLENDINDICES;
#endif
};

struct VertexOut
{
	float4 Pos : SV_POSITION;
    VKLOCATION(0) float3 Normal : NORMAL0;
    VKLOCATION(1) float3 Color : COLOR0;
    VKLOCATION(2) float3 ViewPos : POSITION1;
    VKLOCATION(3) float3 WorldPos : POSITION0;
    VKLOCATION(4) float2 UV : TEXCOORD0;
};

VertexOut VS(VertexIn vIn)
{
    VertexOut vOut;
	
#ifdef SKINNED
    float weights[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
    weights[0] = vIn.BoneWeights.x;
    weights[1] = vIn.BoneWeights.y;
    weights[2] = vIn.BoneWeights.z;
    weights[3] = vIn.BoneWeights.w;
    float3 posL = float3(0.0f, 0.0f, 0.0f);
    float3 normalL = float3(0.0f, 0.0f, 0.0f);
#ifdef USETANGENT
    float3 tangentL = float3(0.0f, 0.0f, 0.0f);
#endif
    for(int i = 0; i < 4; ++i)
    {
        // Assume no nonuniform scaling when transforming normals, so 
        // that we do not have to use the inverse-transpose.

		posL += weights[i] * mul(cbSkinned.gBoneTransforms[vIn.BoneIndices[i]], float4(vIn.PosL, 1.0f)).xyz;
        normalL += weights[i] * mul((float3x3)cbSkinned.gBoneTransforms[vIn.BoneIndices[i]], vIn.NormalL);
		
#ifdef USETANGENT
        tangentL += weights[i] * mul(vIn.TangentL.xyz, (float3x3)cbSkinned.gBoneTransforms[vIn.BoneIndices[i]]);
#endif
    }

    vIn.PosL = posL;
    vIn.NormalL = normalL;
#ifdef USETANGENT
    vIn.TangentL.xyz = tangentL;
#endif
#endif

    float4 posW = mul(cbPerObject.gWorld, float4(vIn.PosL, 1.0f));
	vOut.ViewPos = mul(cbPass.gView, posW).xyz;

	
    vOut.Pos = mul(cbPass.gViewProj, posW);
    vOut.Normal = mul((float3x3)cbPerObject.gWorld, vIn.NormalL);
#ifdef USETANGENT
	vOut.TangentW = mul((float3x3)cbPerObject.gWorld, vIn.TangentL);
#endif
    vOut.UV = mul(cbMaterial.gTexTransform, float4(vIn.TexC, 0.0f, 1.0f)).xy;
	vOut.WorldPos = posW.xyz;
    return vOut;
}

static const float4x4 biasMat = float4x4(
	0.5, 0.0, 0.0, 0.5,
	0.0, 0.5, 0.0, 0.5,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 0.0, 1.0
);

#define ambient 0.1

float textureProj(float4 shadowCoord, float2 off, uint cascadeIndex)
{
    float shadow = 1.0;
	float bias = 0.01;
	if ( shadowCoord.z > -1.0 && shadowCoord.z < 1.0 )
	{		
		float dist = shadowMap.Sample(shadowMapSampler, float3(shadowCoord.xy + off, cascadeIndex)).r;
		if ( shadowCoord.w > 0.0 && dist < shadowCoord.z - bias)
		{
			shadow = ambient;
		}
	}
	return shadow;
}


float filterPCF(float4 sc, uint cascadeIndex)
{
	int3 texDim;
	shadowMap.GetDimensions(texDim.x, texDim.y, texDim.z);
	float scale = 0.75;
	float dx = scale * 1.0 / float(texDim.x);
	float dy = scale * 1.0 / float(texDim.y);

	float shadowFactor = 0.0;
	int count = 0;
	int range = 1;

	for (int x = -range; x <= range; x++)
	{
		for (int y = -range; y <= range; y++)
		{
			shadowFactor += textureProj(sc, float2(dx*x, dy*y), cascadeIndex);
			count++;
		}

	}
	return shadowFactor / count;
}

float4 PS(VertexOut input) : SV_Target
{
    float4 color = first.Sample(firstSampler, input.UV) * cbMaterial.gDiffuseAlbedo;
	if (color.a < 0.5) {
		clip(-1);
	}
	
	float shadow = 1.0f;
	if(cbPerObject.useShadow == 1)
	{
	    uint cascadeIndex = 0;
		for(uint i = 0; i < SHADOW_MAP_CASCADE_COUNT - 1; ++i) {
			if(input.ViewPos.z < cascadeInfo.cascadeSplits[i]) {
				cascadeIndex = i + 1;
			}
		}
		
		
		float4x4 lightViewProj = cascadeInfo.matrices[cascadeIndex];
		float4 shadowCoord = mul(lightViewProj, float4(input.WorldPos, 1.0));
		
		shadowCoord = mul(biasMat, shadowCoord);
		
		shadow = textureProj(shadowCoord/shadowCoord.w, float2(0.0, 0.0), cascadeIndex);
	}
	
	
	
	// Directional light
	
	float4 outFragColor;
	
	float3 N = normalize(input.Normal);
	float3 L = normalize(-cbPass.gDirLights[0].Direction);
	float3 H = normalize(L + input.ViewPos);
	float diffuse = max(dot(N, L), ambient);
	float3 lightColor = float3(1.0, 1.0, 1.0);
	outFragColor.rgb = max(lightColor * (diffuse * color.rgb), float3(0.0, 0.0, 0.0));
	outFragColor.rgb *= shadow;
	outFragColor.a = color.a;
	return outFragColor;
}