#include "common.hlsl"

VKBINDING(0, 0) ConstantBuffer<ObjectBlock> cbPerObject : register(b0, space0);
VKBINDING(1, 0) ConstantBuffer<PassBlock> cbPass : register(b1, space0);
VKBINDING(2, 0) ConstantBuffer<MaterialBlock> cbMaterial : register(b2, space0);

Texture2D first        VKBINDING(0, 1): register(t0,space1);
Texture2D second       VKBINDING(1, 1): register(t1,space1);
Texture2D third        VKBINDING(2, 1): register(t2,space1);
Texture2D gShadowMap   VKBINDING(3, 1): register(t3,space1);
TextureCube gCubeMap   VKBINDING(4, 1): register(t4,space1);

SamplerState firstSampler       VKBINDING(5, 1): register(s0,space1);
SamplerState secondSampler      VKBINDING(6, 1): register(s1,space1);
SamplerState thirdSampler       VKBINDING(7, 1): register(s2,space1);
SamplerState shadowSampler      VKBINDING(8, 1): register(s3,space1);
SamplerState cubeSampler        VKBINDING(9, 1): register(s4,space1);

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
	float4 PosH    : SV_POSITION;
	float4 ShadowPosH : POSITION0;
    float3 PosW    : POSITION1;
    float3 NormalW : NORMAL;
#ifdef USETANGENT
	float3 TangentW : TANGENT;
#endif
	float2 TexC    : TEXCOORD;
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
	vOut.PosH = mul(cbPass.gViewProj, posW);

	
    vOut.PosW = posW.xyz;
    vOut.NormalW = mul((float3x3)cbPerObject.gWorld, vIn.NormalL);
#ifdef USETANGENT
	vOut.TangentW = mul((float3x3)cbPerObject.gWorld, vIn.TangentL);
#endif
    vOut.TexC = mul(cbMaterial.gTexTransform, float4(vIn.TexC, 0.0f, 1.0f)).xy;
	vOut.ShadowPosH = mul(cbPass.gShadowTransform, posW);
    return vOut;
}

float4 PS(VertexOut pin) : SV_Target
{
    float4 diffuseAlbedo = first.Sample(firstSampler, pin.TexC) * cbMaterial.gDiffuseAlbedo;
	//clip(diffuseAlbedo.a - 0.5f);
	return diffuseAlbedo;
}