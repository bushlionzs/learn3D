#include "Common.hlsl"


// The MIT License
// Copyright (c) 2016-2017 Mohamad Moneimne and Contributors
//
// This fragment shader defines a reference implementation for Physically Based Shading of
// a microfacet surface material defined by a glTF model.
//
// References:
// [1] Real Shading in Unreal Engine 4
//     http://blog.selfshadow.com/publications/s2013-shading-course/karis/s2013_pbs_epic_notes_v2.pdf
// [2] Physically Based Shading at Disney
//     http://blog.selfshadow.com/publications/s2012-shading-course/burley/s2012_pbs_disney_brdf_notes_v3.pdf
// [3] README.md - Environment Maps
//     https://github.com/KhronosGroup/glTF-WebGL-PBR/#environment-maps
// [4] "An Inexpensive BRDF Model for Physically based Rendering" by Christophe Schlick
//     https://www.cs.virginia.edu/~jdl/bib/appearance/analytic%20models/schlick94b.pdf



// Encapsulate the various inputs used by the various functions in the shading equation
// We store values in this struct to simplify the integration of alternative implementations
// of the shading terms, outlined in the Readme.MD Appendix.
struct PBRInfo
{
    float NdotL;                  // cos angle between normal and light direction
    float NdotV;                  // cos angle between normal and view direction
    float NdotH;                  // cos angle between normal and half vector
    float LdotH;                  // cos angle between light direction and half vector
    float VdotH;                  // cos angle between view direction and half vector
    float perceptualRoughness;    // roughness value, as authored by the model creator (input to shader)
    float metalness;              // metallic value at the surface
    float3 reflectance0;            // full reflectance color (normal incidence angle)
    float3 reflectance90;           // reflectance color at grazing angle
    float alphaRoughness;         // roughness mapped to a more linear change in the roughness (proposed by [2])
    float3 diffuseColor;            // color contribution from diffuse lighting
    float3 specularColor;           // color contribution from specular lighting
};

#define  M_PI  3.141592653
float c_MinRoughness = 0.04;

#define  albedoIndex  0
#define ambientOcclusionIndex  1
#define normalMapIndex  2
#define emissiveIndex  3
#define metalRoughnessIndex 4
#define brdfLutIndex  5
#define iblDiffuseIndex  0
#define iblSpecularIndex  1
float4 SRGBtoLINEAR(float4 srgbIn)
{
    #ifdef MANUAL_SRGB
    #ifdef SRGB_FAST_APPROXIMATION
    float3 linOut = pow(srgbIn.xyz,float3(2.2, 2.2, 2.2));
    #else //SRGB_FAST_APPROXIMATION
    float3 bLess = step(float3(0.04045),srgbIn.xyz);
    float3 linOut = mix( srgbIn.xyz/float3(12.92), pow((srgbIn.xyz+float3(0.055))/float3(1.055),float3(2.4)), bLess );
    #endif //SRGB_FAST_APPROXIMATION
    return float4(linOut,srgbIn.w);;
    #else //MANUAL_SRGB
    return srgbIn;
    #endif //MANUAL_SRGB
}



float3 NormalSampleToWorldSpace(float3 normalMapSample, float3 unitNormalW, float3 tangentW)
{
	// Uncompress each component from [0,1] to [-1,1].
	float3 normalT = 2.0f*normalMapSample - 1.0f;

	// Build orthonormal basis.
	float3 N = unitNormalW;
	float3 T = normalize(tangentW - dot(tangentW, N)*N);
	float3 B = cross(N, T);

	float3x3 TBN = float3x3(T, B, N);

	// Transform from tangent space to world space.
	float3 bumpedNormalW = mul(normalT, TBN);

	return bumpedNormalW;
}

float4 gDiffuseAlbedo = {1.0,1.0,1.0,1.0};
#ifdef USE_IBL
// Calculation of the lighting contribution from an optional Image Based Light source.
// Precomputed Environment Maps are required uniform inputs and are computed as outlined in [1].
// See our README.md on Environment Maps [3] for additional discussion.
float3 getIBLContribution(PBRInfo pbrInputs, float3 n, float3 reflection)
{
    float mipCount = 9.0; // resolution of 512x512
    float lod = (pbrInputs.perceptualRoughness * mipCount);
    // retrieve a scale and bias to F0. See [1], Figure 3
    float3 brdf = SRGBtoLINEAR(gTextureArray[brdfLutIndex].Sample(gsamLinearWrap, float2(pbrInputs.NdotV, 1.0 - pbrInputs.perceptualRoughness))).rgb;
    float3 diffuseLight = gCubeMap[iblDiffuseIndex].Sample(gsamLinearWrap, n).rgb;

    float3 specularLight = gCubeMap[iblSpecularIndex].Sample(gsamLinearWrap, reflection).rgb;

    float3 diffuse = diffuseLight * pbrInputs.diffuseColor;
    float3 specular = specularLight * (pbrInputs.specularColor * brdf.x + brdf.y);

    // For presentation, this allows us to disable IBL terms
    diffuse *= u_ScaleIBLAmbient.x;
    specular *= u_ScaleIBLAmbient.y;

    return diffuse + specular;
}
#endif

// Basic Lambertian diffuse
// Implementation from Lambert's Photometria https://archive.org/details/lambertsphotome00lambgoog
// See also [1], Equation 1
float3 diffuse(PBRInfo pbrInputs)
{
    return pbrInputs.diffuseColor / M_PI;
}

// The following equation models the Fresnel reflectance term of the spec equation (aka F())
// Implementation of fresnel from [4], Equation 15
float3 specularReflection(PBRInfo pbrInputs)
{
    return pbrInputs.reflectance0 + (pbrInputs.reflectance90 - pbrInputs.reflectance0) * pow(clamp(1.0 - pbrInputs.VdotH, 0.0, 1.0), 5.0);
}

// This calculates the specular geometric attenuation (aka G()),
// where rougher material will reflect less light back to the viewer.
// This implementation is based on [1] Equation 4, and we adopt their modifications to
// alphaRoughness as input as originally proposed in [2].
float geometricOcclusion(PBRInfo pbrInputs)
{
    float NdotL = pbrInputs.NdotL;
    float NdotV = pbrInputs.NdotV;
    float r = pbrInputs.alphaRoughness;

    float attenuationL = 2.0 * NdotL / (NdotL + sqrt(r * r + (1.0 - r * r) * (NdotL * NdotL)));
    float attenuationV = 2.0 * NdotV / (NdotV + sqrt(r * r + (1.0 - r * r) * (NdotV * NdotV)));
    return attenuationL * attenuationV;
}

// The following equation(s) model the distribution of microfacet normals across the area being drawn (aka D())
// Implementation from "Average Irregularity Representation of a Roughened Surface for Ray Reflection" by T. S. Trowbridge, and K. P. Reitz
// Follows the distribution function recommended in the SIGGRAPH 2013 course notes from EPIC Games [1], Equation 3.
float microfacetDistribution(PBRInfo pbrInputs)
{
    float roughnessSq = pbrInputs.alphaRoughness * pbrInputs.alphaRoughness;
    float f = (pbrInputs.NdotH * roughnessSq - pbrInputs.NdotH) * pbrInputs.NdotH + 1.0;
	float a = M_PI * f * f;
    return roughnessSq / a;
}

struct VertexIn
{
	float3 PosL    : POSITION;
    float3 NormalL : NORMAL;
#ifdef HAS_TANGENTS
	float3 TangentL : TANGENT;
#endif
	float2 TexC    : TEXCOORD;
};

struct VertexOut
{
	float4 PosH    : SV_POSITION;
	float4 ShadowPosH : POSITION0;
    float3 PosW    : POSITION1;
    float3 NormalW : NORMAL;
#ifdef HAS_TANGENTS
	float3 TangentW : TANGENT;
#endif
	float2 v_UV    : TEXCOORD;
};

VertexOut VS(VertexIn vIn)
{
    VertexOut vOut;
	
    float4 posW = mul(gWorld, float4(vIn.PosL, 1.0f));

    vOut.PosH = mul(gViewProj, posW);
    vOut.PosW = posW.xyz;
    vOut.NormalW = mul((float3x3) gWorld, vIn.NormalL);
#ifdef HAS_TANGENTS
	vOut.TangentW = mul((float3x3)gWorld, vIn.TangentL);
#endif
    vOut.v_UV = vIn.TexC;
	vOut.ShadowPosH = mul(gShadowTransform, posW);
	
    return vOut;
}

float3 u_LightDirection = {100.0f, 100.0f, 100.0f};
float3 u_LightColor = {1.0,1.0,1.0};
float4 PS(VertexOut pin) : SV_Target
{
    // Metallic and Roughness material properties are packed together
    // In glTF, these factors can be specified by fixed scalar values
    // or from a metallic-roughness map
    float perceptualRoughness = u_MetallicRoughnessValues.y;
    float metallic = u_MetallicRoughnessValues.x;
#ifdef HAS_METALROUGHNESSMAP
    // Roughness is stored in the 'g' channel, metallic is stored in the 'b' channel.
    // This layout intentionally reserves the 'r' channel for (optional) occlusion map data
    float4 mrSample = gTextureArray[metalRoughnessIndex].Sample(gsamLinearWrap, pin.v_UV);
    perceptualRoughness = mrSample.g * perceptualRoughness;
    metallic = mrSample.b * metallic;
#endif
    perceptualRoughness = clamp(perceptualRoughness, c_MinRoughness, 1.0);
    metallic = clamp(metallic, 0.0, 1.0);

    PBRInfo pbrInputs;

    // Roughness is authored as perceptual roughness; as is convention,
    // convert to material roughness by squaring the perceptual roughness [2].
    pbrInputs.alphaRoughness = perceptualRoughness * perceptualRoughness;

    // The albedo may be defined from a base texture or a flat color
#ifdef HAS_BASECOLORMAP
    float4 baseColorSource = gTextureArray[albedoIndex].Sample(gsamLinearWrap, pin.v_UV);
    float4 baseColor = SRGBtoLINEAR(baseColorSource) * u_BaseColorFactor;
#else
    float4 baseColor = u_BaseColorFactor;
#endif

    float3 f0 = float3(0.04, 0.04, 0.04);
    float3 diffuseColor = baseColor.rgb * (float3(1.0, 1.0, 1.0) - f0);
    diffuseColor *= 1.0 - metallic;
    float3 specularColor = lerp(f0, baseColor.rgb, metallic);

    // Compute reflectance.
    float reflectance = max(max(specularColor.r, specularColor.g), specularColor.b);

    // For typical incident reflectance range (between 4% to 100%) set the grazing reflectance to 100% for typical fresnel effect.
    // For very low reflectance range on highly diffuse objects (below 4%), incrementally reduce grazing reflecance to 0%.
    float reflectance90 = clamp(reflectance * 25.0, 0.0, 1.0);

    pbrInputs.reflectance0 = specularColor.rgb;
    pbrInputs.reflectance90 = float3(1.0, 1.0, 1.0) * reflectance90;

    pbrInputs.perceptualRoughness = perceptualRoughness;
    pbrInputs.metalness = metallic;
    pbrInputs.diffuseColor = diffuseColor;
    pbrInputs.specularColor = specularColor;

    float3 normalColor = gTextureArray[normalMapIndex].Sample(gsamAnisotropicWrap, pin.v_UV);
	
    float3 n = NormalSampleToWorldSpace(normalColor, pin.NormalW, pin.TangentW);
    float3 v = normalize(gEyePosW - pin.PosW);        // Vector from surface point to camera
    float3 l = normalize(u_LightDirection);             // Vector from surface point to light
    float3 h = normalize(l+v);                          // Half vector between both l and v
    float3 reflection = -normalize(reflect(v, n));
    reflection.z *= -1.0;

    pbrInputs.NdotL = clamp(dot(n, l), 0.001, 1.0);
    pbrInputs.NdotV = abs(dot(n, v)) + 0.001;
    pbrInputs.NdotH = clamp(dot(n, h), 0.0, 1.0);
    pbrInputs.LdotH = clamp(dot(l, h), 0.0, 1.0);
    pbrInputs.VdotH = clamp(dot(v, h), 0.0, 1.0);

    // Calculate the shading terms for the microfacet specular shading model
    float3 F = specularReflection(pbrInputs);
    float G = geometricOcclusion(pbrInputs);
    float D = microfacetDistribution(pbrInputs);

    // Calculation of analytical lighting contribution
    float3 diffuseContrib = (1.0 - F) * diffuse(pbrInputs);
    float3 specContrib = F * G * D / (4.0 * pbrInputs.NdotL * pbrInputs.NdotV);
    float3 color = pbrInputs.NdotL * u_LightColor * (diffuseContrib + specContrib);
	
    // Calculate lighting contribution from image based lighting source (IBL)
#ifdef USE_IBL
	float3 ibl = getIBLContribution(pbrInputs, n, reflection);
    color += ibl;
#endif
    // Apply optional PBR terms for additional (optional) shading
#ifdef HAS_OCCLUSIONMAP
	float ao = gTextureArray[ambientOcclusionIndex].Sample(gsamAnisotropicWrap, pin.v_UV).r;
    color = lerp(color, color * ao, u_OcclusionStrength);
#endif

#ifdef HAS_EMISSIVEMAP
	float3 emissive = gTextureArray[emissiveIndex].Sample(gsamAnisotropicWrap, pin.v_UV).rgb * u_EmissiveFactor;
    color += emissive;
#endif

    return float4(pow(color,float3(1.0/2.2, 1.0/2.2, 1.0/2.2)), baseColor.a);
}
