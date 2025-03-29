#include "common.hlsl"
#include "VCTCommon.hlsl"

struct LightingConstant
{
    float4x4 InvViewProjection;
    float4x4 ShadowViewProjection;
	float4 CameraPos;
	float4 ScreenSize;
    float2 ShadowTexelSize;
    float ShadowIntensity;
    float pad0;
};

VKBINDING(0, 0) ConstantBuffer<LightingConstant> LightingConstantBuffer : register(b0, space0);

struct DirectionalLight
{
    float4 LightDirection;
    float4 LightColor;
    float LightIntensity;
    float3 pad1;
};


VKBINDING(1, 0) ConstantBuffer<DirectionalLight> DirectionalLightBuffer : register(b1, space0);

struct IlluminationFlags
{
    int useDirect;
    int useShadows;
    int useRSM;
    int useLPV;
    int useVCT;
    int useVCTDebug;
    int useDXRReflections;
    int useDXRAmbientOcclusion;
    int useSSAO;
    float rsmGIPower;
    float lpvGIPower;
    float vctGIPower;
    float dxrReflectionsBlend;
    int showOnlyAO;
};


VKBINDING(2, 0) ConstantBuffer<IlluminationFlags> IlluminationFlagsBuffer : register(b2, space0);


VKBINDING(3, 0) SamplerState BilinearSampler : register(s0);
VKBINDING(4, 0) SamplerComparisonState PcfShadowMapSampler : register(s1);

VKBINDING(5, 0) Texture2D<float4> albedoBuffer : register(t0);
VKBINDING(6, 0) Texture2D<float4> normalBuffer : register(t1);
VKBINDING(7, 0) Texture2D<float4> worldPosBuffer : register(t2);
VKBINDING(9, 0) Texture2D<float> shadowBuffer : register(t4);


VKBINDING(10, 0) Texture2D<float4> vctBuffer : register(t9);

VKBINDING(11, 0) Texture2D<float4> dxrReflectionsBuffer : register(t10);
VKBINDING(12, 0) Texture2D<float> dxrAmbientOcclusionBuffer : register(t11);

VKBINDING(13, 0) Texture2D<float> ssaoBuffer : register(t12);



struct VSInput
{
	VKLOCATION(0) float3 position : POSITION;
	VKLOCATION(3) float2 uv : TEXCOORD;
};

struct PSInput
{
    float4 position : SV_POSITION;
	float2 uv : TEXCOORD;
};

struct PSOutput
{
	float4 diffuse : SV_Target0;
};

PSInput VSMain(VSInput input)
{
	PSInput result;
    result.position = float4(input.position.xyz, 1);
    result.uv = input.uv;
    return result;
}

float sampleShadow(float2 uv, float depth)
{
    float v = shadowBuffer.SampleCmpLevelZero(PcfShadowMapSampler, uv, depth);
	if(v < 0.00001)
	{
	    return 0.0f;
	}
	
	return 1.0f;
	
}

float CalculateShadow(float3 ShadowCoord)
{   
    const float Dilation = 2.0;
    float d1 = Dilation * LightingConstantBuffer.ShadowTexelSize.x * 0.125;
    float d2 = Dilation * LightingConstantBuffer.ShadowTexelSize.x * 0.875;
    float d3 = Dilation * LightingConstantBuffer.ShadowTexelSize.x * 0.625;
    float d4 = Dilation * LightingConstantBuffer.ShadowTexelSize.x * 0.375;
	
	float v = sampleShadow(ShadowCoord.xy, ShadowCoord.z);
    float result = (
        2.0 *v +
            sampleShadow(ShadowCoord.xy + float2(-d2, d1), ShadowCoord.z) +
            sampleShadow(ShadowCoord.xy + float2(-d1, -d2), ShadowCoord.z) +
            sampleShadow(ShadowCoord.xy + float2(d2, -d1), ShadowCoord.z) +
            sampleShadow(ShadowCoord.xy + float2(d1, d2), ShadowCoord.z) +
            sampleShadow(ShadowCoord.xy + float2(-d4, d3), ShadowCoord.z) +
            sampleShadow(ShadowCoord.xy + float2(-d3, -d4), ShadowCoord.z) +
            sampleShadow(ShadowCoord.xy + float2(d4, -d3), ShadowCoord.z) +
            sampleShadow(ShadowCoord.xy + float2(d3, d4), ShadowCoord.z)
        ) / 10.0;
    
    return result * result;
}

// ===============================================================================================
// http://graphicrants.blogspot.com.au/2013/08/specular-brdf-reference.html
// ===============================================================================================

float DistributionGGX(float3 N, float3 H, float roughness)
{
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH * NdotH;

    float nom = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / max(denom, 0.001); // prevent divide by zero for roughness=0.0 and NdotH=1.0
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r * r) / 8.0;

    float nom = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySmith(float3 N, float3 V, float3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}

// ================================================================================================
// Fresnel with Schlick's approximation:
// http://blog.selfshadow.com/publications/s2013-shading-course/rad/s2013_pbs_rad_notes.pdf
// http://graphicrants.blogspot.fr/2013/08/specular-brdf-reference.html
// ================================================================================================
float3 Schlick_Fresnel(float3 f0, float cosTheta)
{
    return f0 + (1.0f - f0) * pow((1.0f - cosTheta), 5.0f);
}
float3 Schlick_Fresnel_Roughness(float cosTheta, float3 F0, float roughness)
{
    return F0 + (max(float3(1.0f - roughness, 1.0f - roughness, 1.0f - roughness), F0) - F0) * pow(1.0f - cosTheta, 5.0f);
}

// ================================================================================================
// Cook-Torrence BRDF
float3 DirectSpecularBRDF(float3 normalWS, float3 lightDir, float3 viewDir, float roughness, float3 F0)
{
    float3 halfVec = normalize(viewDir + lightDir);
    // Cook-Torrance BRDF
    float NDF = DistributionGGX(normalWS, halfVec, roughness);
    float G = GeometrySmith(normalWS, viewDir, lightDir, roughness);
    float3 F = Schlick_Fresnel(F0, max(dot(halfVec, viewDir), 0.0));
           
    float3 nominator = NDF * G * F;
    float denominator = 4 * max(dot(normalWS, viewDir), 0.0) * max(dot(normalWS, lightDir), 0.0);
    float3 specular = nominator / max(denominator, 0.001); // prevent divide by zero for NdotV=0.0 or NdotL=0.0
       
    return specular;
}

float3 DirectDiffuseBRDF(float3 diffuseAlbedo, float3 lightDir, float3 viewDir, float3 F0, float metallic)
{
    float3 halfVec = normalize(viewDir + lightDir);
   
    float3 F = Schlick_Fresnel(F0, max(dot(halfVec, viewDir), 0.0));
    float3 kS = F;
    // for energy conservation, the diffuse and specular light can't
    // be above 1.0 (unless the surface emits light); to preserve this
    // relationship the diffuse component (kD) should equal 1.0 - kS.
    float3 kD = float3(1.0f, 1.0f, 1.0f) - kS;
    // multiply kD by the inverse metalness such that only non-metals 
    // have diffuse lighting, or a linear blend if partly metal (pure metals
    // have no diffuse light).
    kD *= (float3(1.0f, 1.0f, 1.0f) - metallic);
    
    return (diffuseAlbedo * kD) / PI;
}
PSOutput PSMain(PSInput input)
{
	PSOutput output = (PSOutput)0;
    float2 inPos = input.position.xy;    
    
    float3 normal = normalize(normalBuffer[inPos].rgb);
    float4 albedo = albedoBuffer[inPos];
    float4 worldPos = worldPosBuffer[inPos];
    
    if (!any(albedo))
    {
        output.diffuse = float4(0.9f, 0.9f, 0.9f, 1.0f);
        return output;
    }
    
    float3 indirectLighting = float3(0.0f, 0.0f, 0.0f);
    float3 directLighting = float3(0.0f, 0.0f, 0.0f);
    
    float ao = 1.0f;
    
    float3 reflectionsDXR = dxrReflectionsBuffer[inPos].rgb;
    
    
    //VCT
    if (IlluminationFlagsBuffer.useVCT)
    {
        uint gWidth = 0;
        uint gHeight = 0;
        albedoBuffer.GetDimensions(gWidth, gHeight);
        float4 vct = vctBuffer.Sample(BilinearSampler, inPos * float2(1.0f / gWidth, 1.0f / gHeight));
        
        //indirectLighting += vct.rgb * IlluminationFlagsBuffer.vctGIPower;
        if (!IlluminationFlagsBuffer.useVCTDebug)
            ao = 1.0f - vct.a;
    }  
    
    if (IlluminationFlagsBuffer.useSSAO)
    {
        float ssao = ssaoBuffer[inPos];
        ao = 1.0f - ssao;
    }
    
    if (IlluminationFlagsBuffer.useDXRAmbientOcclusion)
    {
        float rtao = dxrAmbientOcclusionBuffer[inPos];
        ao = rtao;
    }
    
    float shadow = 1.0f;
	
	static const float4x4 biasMat = float4x4(
	0.5, 0.0, 0.0, 0.5,
	0.0, 0.5, 0.0, 0.5,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 0.0, 1.0 );
	
    if (IlluminationFlagsBuffer.useShadows)
    {
        float4 lightSpacePos = mul(LightingConstantBuffer.ShadowViewProjection, worldPos);
		//lightSpacePos = mul(biasMat, lightSpacePos);
        float4 shadowcoord = lightSpacePos / lightSpacePos.w;
        //shadowcoord.rg = shadowcoord.rg * float2(0.5f, -0.5f) + float2(0.5f, 0.5f);
        shadow = CalculateShadow(shadowcoord.rgb);
    }
    
    if (IlluminationFlagsBuffer.useDirect)
    {
        float3 viewDir = normalize(LightingConstantBuffer.CameraPos.xyz - worldPos.xyz);

        float3 lightDir = DirectionalLightBuffer.LightDirection.xyz;
        float3 lightColor = DirectionalLightBuffer.LightColor.xyz;
        float lightIntensity = DirectionalLightBuffer.LightIntensity;
        float NdotL = saturate(dot(normal.xyz, lightDir));
            
        float roughness = albedo.a;
        float metalness = (roughness > 0.0f) ? 0.7f : 0.0f;
        float3 F0 = float3(0.04, 0.04, 0.04);
        F0 = lerp(F0, albedo.rgb, metalness);
        
        float3 direct = DirectDiffuseBRDF(albedo.rgb, lightDir, viewDir, F0, metalness) + DirectSpecularBRDF(normal.xyz, lightDir, viewDir, 1.0f - roughness, F0);
        
        directLighting = max(direct, 0.0f) * NdotL * lightIntensity * lightColor;
    }
    
    output.diffuse.rgb = ao * indirectLighting + (directLighting + (IlluminationFlagsBuffer.useDXRReflections ? lerp(reflectionsDXR, directLighting * albedo.a, IlluminationFlagsBuffer.dxrReflectionsBlend) : 0.0f)) * shadow;;
    output.diffuse.rgb = saturate(output.diffuse.rgb);
    if (IlluminationFlagsBuffer.showOnlyAO)
        output.diffuse.rgb = float3(ao.xxx);
    
    return output;
}
