#include "common.hlsl"

VKBINDING(0, 0) ConstantBuffer<ObjectBlock> cbPerObject : register(b0, space0);
VKBINDING(1, 0) ConstantBuffer<PassBlock> cbPass : register(b1, space0);
VKBINDING(2, 0) ConstantBuffer<ObjMaterialBlock> objMaterial : register(b2, space0);

Texture2D diffuse_tex          VKBINDING(0, 1): register(t0,space1);
Texture2D normal_tex           VKBINDING(1, 1): register(t1,space1);
Texture2D specular_tex         VKBINDING(2, 1): register(t2,space1);
Texture2D emissive_tex         VKBINDING(3, 1): register(t3,space1);
Texture2D opacity_tex          VKBINDING(4, 1): register(t4,space1);

SamplerState diffuseSampler    VKBINDING(5, 1): register(s0,space1);
SamplerState normalSampler     VKBINDING(6, 1): register(s2,space1);
SamplerState specularSampler   VKBINDING(7, 1): register(s3,space1);
SamplerState emissiveSampler   VKBINDING(8, 1): register(s4,space1);
SamplerState opacitySampler    VKBINDING(9, 1): register(s5,space1);

#define OPACITY_THRESHOLD 0.1

float packShininess(float shininess)
{
    return shininess / 255.0; // assumed 255.0 to be the max possible shininess value
}

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
	float3 outNormal: NORMAL;
	float3 tangentW: TANGENT;
    float3 bitangentW: BINORMAL;
	float2 outUV: TEXCOORD;
};

VertexOut VS(VertexIn vIn) 
{
    VertexOut Out;
    float4 outWorldPos = mul(cbPerObject.gWorld , float4(vIn.position, 1.0));
    Out.PosH = mul(cbPass.gViewProj , outWorldPos);    
    Out.outNormal = mul((float3x3)cbPerObject.gWorld , vIn.normal);
	Out.tangentW = mul((float3x3)cbPerObject.gWorld , vIn.tangentW);
	Out.bitangentW = mul((float3x3)cbPerObject.gWorld , vIn.bitangentW);
    Out.outUV = vIn.texUV;
	return Out;
}


struct PSOutput
{
	float3 out_diffuse : SV_Target0;
	float3 out_normal : SV_Target1;
	float4 out_specular : SV_Target2;
	float3 out_emission : SV_Target3;
};

PSOutput PS(VertexOut In)
{
	PSOutput Out;
	
	if (objMaterial.u_hasOpacityMap > 0 && texture(opacity_tex, In.outUV).r < OPACITY_THRESHOLD)
        discard;
        
    Out.out_emission = objMaterial.u_emissionColor;
    
    if (objMaterial.u_hasEmissionMap > 0)
    {
        Out.out_emission += texture(objMaterial.emissive_tex, In.outUV).rgb;
        Out.out_emission = clamp(Out.out_emission, 0.0, 1.0);
    }

    Out.out_diffuse = objMaterial.u_color.rgb;
    
    if (objMaterial.u_hasDiffuseTexture > 0)
    {
        Out.out_diffuse = texture(objMaterial.diffuse_tex, In.outUV).rgb;
    }
    
    Out.out_specular.rgb = u_specularColor;
    Out.out_specular.a = packShininess(u_shininess);
    Out.out_normal = normalize(In.normal);
    
    if (objMaterial.u_hasNormalMap > 0)
    {
        float3 normalSample = texture(objMaterial.normal_tex, In.outUV).rgb;
        normalSample = 2.0 * normalSample - 1.0;
        
        float3 tangent = normalize(In.tangentW);
        float3 bitangent = normalize(In.bitangentW);
        Out.out_normal = normalize(normalSample.x * tangent + normalSample.y * bitangent + normalSample.z * out_normal);
    }
    
    if (objMaterial.u_hasSpecularMap > 0)
    {
        out_specular.rgb = texture(u_specularMap0, In.outUV).rgb;
    }
	
    out_normal = packNormal(out_normal);
	
	return Out;
}