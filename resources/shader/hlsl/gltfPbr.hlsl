
#define PI 3.1415926

cbuffer WorldView : register(b0)
{
    matrix MVP;
};

cbuffer CB1 : register(b1)
{
    matrix WorldMat;
    matrix NormalMat;
    float4 baseColor;
    float3 emissiveFactor;
    float  metallicFactor;
    float3 cameraPos;
    float  roughnessFactor;
};

struct VS_INPUT
{
    float3 Normal  : NORMAL;
    float3 Pos     : POSITION;
#if HAS_TANGENT
    float4 Tangent : TANGENT0;
#endif
#ifdef BASECOLOR_TEX
    float2 Tex     : TEXCOORD0;
#endif
};

struct PS_INPUT
{
    float4 Pos       : SV_POSITION;
    float4 WorldPos  : POSITION0;
#ifdef BASECOLOR_TEX
    float2 Tex       : TEXCOORD0;
#endif

    float3 Normal    : NORMAL;

#ifdef HAS_TANGENT
    float3 Tangent   : TANGENT;
    float3 Bitangent : BINORMAL;
#endif
};

#ifdef BASECOLOR_TEX
Texture2D baseColorTex  : register(t0);
#endif

#ifdef ROUGHNESSMETALLIC_TEX
Texture2D roughnessTex  : register(t1);
#endif

#ifdef NORMAL_TEX
Texture2D normalTex     : register(t2);
#endif

#ifdef EMISSIVE_TEX
Texture2D emissiveTex   : register(t3);
#endif

#ifdef BASECOLOR_TEX
SamplerState samLinear  : register(s0);
#endif

PS_INPUT mainVS(VS_INPUT input)
{
    PS_INPUT output = (PS_INPUT)0;

    output.Pos = mul(MVP, float4(input.Pos, 1.0));
    output.WorldPos = mul(WorldMat, float4(input.Pos, 1.0));
    output.Normal = normalize(mul(NormalMat, float4(input.Normal, 0)).xyz);

#ifdef BASECOLOR_TEX
    output.Tex = input.Tex;
#endif

#ifdef HAS_TANGENT
    output.Tangent = normalize(mul(NormalMat, float4(input.Tangent.xyz, 0)).xyz);
    output.Bitangent = cross(output.Normal, output.Tangent) * input.Tangent.w;
#endif

    return output;
}

//BRDF Functions From https://github.com/google/filament/blob/main/shaders/src/brdf.fs

// http://citeseerx.ist.psu.edu/viewdoc/download;jsessionid=35A58EDADCAC2BF3A46AC602C7122A06?doi=10.1.1.50.2297&rep=rep1&type=pdf
// Schlick approximation of the Cook-Torrence Fresnel
// Factor which defines the ratio of light reflected by each microfacet
float3 fresnel(float3 f0, float VdotH)
{
    return f0 + (1.0 - f0) * pow(clamp(1.0 - VdotH, 0.0, 1.0), 5.0);
}

// Geometric Occlusion
// Smith Joint GGX
// Geometrical attenuation coefficient which expresses the ration of light that is not self-obstructed by the surface
// Heitz 2014, "Understanding the Masking-Shadowing Function in Microfacet-Based BRDFs"
float V_GGX(float NdotL, float NdotV, float roughness)
{
    float a2 = roughness * roughness;

    float GGXV = NdotL * sqrt(NdotV * NdotV * (1.0 - a2) + a2);
    float GGXL = NdotV * sqrt(NdotL * NdotL * (1.0 - a2) + a2);
    float GGX = GGXV + GGXL;

    float returnVal = 0.5 / GGX;
    return saturate(returnVal);
}

// Normal Distribution
// Trowbridge-Reitz GGX
// Distribution of facets oriented in H direction
float D_GGX(float NdotH, float roughness)
{
    float a2 = roughness * roughness;
    float f = (NdotH * NdotH) * (a2 - 1.0) + 1.0;
    return a2 / (PI * f * f);
}

// Lambertian Diffuse
float3 lambertian(float3 diffuseColor)
{
    return diffuseColor / PI;
}

float3 calcPbrBRDF(float3 diffuseColor, float roughness, float metallic, float3 f0, float VdotH, float NdotL, float NdotV, float NdotH)
{
    roughness = roughness * roughness;
    // calculate specular terms
    float3 F = fresnel(f0, VdotH);
    float Vis = V_GGX(NdotL, NdotV, roughness);
    float D = D_GGX(NdotH, roughness);

    float3 specular = F * Vis * D;
    float3 diffuse = lambertian(diffuseColor) * (1.0 - metallic);

    return NdotL * (diffuse + specular);
}

float4 mainPS(PS_INPUT input) : SV_TARGET
{
    float3 light = normalize(float3(00.0, 3.0, -3.0));
    float roughness = 0.0;
    float metallic = 0.0;
    float3 color = float3(1.0, 1.0, 1.0);
    float lightIntensity = PI;
    float3 f0 = float3(0.04, 0.04, 0.04);

#if BASECOLOR_TEX
    color = baseColor.rgb * baseColorTex.Sample(samLinear, input.Tex.xy).rgb;
#else
    color = baseColor.rgb;
#endif

#if NORMAL_TEX
    float3 normal = normalTex.Sample(samLinear, input.Tex.xy).rgb;
#else
    float3 normal = normalize(input.Normal);
#endif

#ifdef ROUGHNESSMETALLIC_TEX
    // roghness is in the g channel
    float4 matSample = roughnessTex.Sample(samLinear, input.Tex.xy);
    roughness = matSample.g * roughnessFactor;
    metallic = matSample.b * metallicFactor;
#if HAS_OCCLUSION
    color = color * matSample.r;
#endif
#else
    roughness = roughnessFactor;
    metallic = metallicFactor;
#endif
    f0 = lerp(f0, baseColor.rgb, metallic);

    float3 v = normalize(cameraPos - input.WorldPos.xyz);
#if HAS_TANGENT
    float3 n = normalTex.Sample(samLinear, input.Tex.xy).xyz;
    n = n * 2.0 - 1.0;
    float3x3 tbn = float3x3(input.Tangent, input.Bitangent, input.Normal);
    //n = normalize(n.x * input.Tangent - n.y * input.Bitangent + n.z * input.Normal);
    n = mul(transpose(tbn), n);
#else
    float3 n = normalize(input.Normal);
#endif
    float3 l = normalize(light);
    float3 h = normalize(l + v);

    float NdotL = clamp(dot(n, l), 0, 1);
    float VdotH = clamp(dot(v, h), 0, 1);
    float NdotV = clamp(dot(n, v), 0, 1);
    float NdotH = clamp(dot(n, h), 0, 1);

    float3 pbrColor = lightIntensity * calcPbrBRDF(color, roughness, metallic, f0, VdotH, NdotL, NdotV, NdotH);

#ifdef EMISSIVE_TEX
    pbrColor += emissiveFactor * emissiveTex.Sample(samLinear, input.Tex.xy).rgb;
#endif

    // HDR tonemapping
    //pbrColor = pbrColor / (pbrColor + float3(1.0, 1.0, 1.0));
    // gamma correct
    pbrColor = pow(abs(pbrColor), (1.0 / 2.2));

    return float4(pbrColor, 1.0f);
    //float3 diffuse = saturate(dot(normal, light)) * color;
    //return float4(diffuse, 1.0f);
    //return float4(color, 1.0f);
}