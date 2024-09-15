#version 450
#define float2 vec2
#define float3 vec3
#define float4 vec4
#define float3x3 mat3
#define lerp mix
#ifdef VERTEX_SHADER
#include "common.glsl"

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 3) in vec2 texcoord;
layout (location = 4) in vec3 tangent;


layout (location = 0) out vec3 outWorldPos;
layout (location = 1) out vec3 outNormal;
layout (location = 2) out vec3 outTagent;
layout (location = 3) out vec2 outUV0;
layout (location = 4) out vec2 outUV1;
layout (location = 5) out vec4 outColor0;



void main()
{	
    outWorldPos = (cbPerObject.gWorld * float4(position, 1.0f)).xyz;
	outWorldPos.y = -outWorldPos.y;
    outNormal = normalize(mat3(cbPerObject.gWorld) * normal);
    outUV0 = texcoord;
	gl_Position = cbPass.gProj * cbPass.gView * float4(outWorldPos, 1.0f);
}

#endif //VERTEX_SHADER

#ifdef FRAGMENT_SHADER
#include "common.glsl"
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

#define  M_PI  3.141592653589793
#define c_MinRoughness  0.04


vec4 SRGBtoLINEAR(vec4 srgbIn)
{
	#define MANUAL_SRGB 1
	#ifdef MANUAL_SRGB
	#ifdef SRGB_FAST_APPROXIMATION
	vec3 linOut = pow(srgbIn.xyz,vec3(2.2));
	#else //SRGB_FAST_APPROXIMATION
	vec3 bLess = step(vec3(0.04045),srgbIn.xyz);
	vec3 linOut = mix( srgbIn.xyz/vec3(12.92), pow((srgbIn.xyz+vec3(0.055))/vec3(1.055),vec3(2.4)), bLess );
	#endif //SRGB_FAST_APPROXIMATION
	return vec4(linOut,srgbIn.w);;
	#else //MANUAL_SRGB
	return srgbIn;
	#endif //MANUAL_SRGB
}



vec3 getNormal(float3 worldPos, float3 normal, float2 uv)
{
	// Perturb normal, see http://www.thetenthplanet.de/archives/1180
	vec3 tangentNormal = texture(normal_pbr, uv).xyz * 2.0 - 1.0;

	vec3 q1 = dFdx(worldPos);
	vec3 q2 = dFdy(worldPos);
	vec2 st1 = dFdx(uv);
	vec2 st2 = dFdy(uv);

	vec3 N = normalize(normal);
	vec3 T = normalize(q1 * st2.t - q2 * st1.t);
	vec3 B = -normalize(cross(N, T));
	mat3 TBN = mat3(T, B, N);

	return normalize(TBN * tangentNormal);
}


vec3 Uncharted2Tonemap(vec3 color)
{
	float A = 0.15;
	float B = 0.50;
	float C = 0.10;
	float D = 0.20;
	float E = 0.02;
	float F = 0.30;
	float W = 11.2;
	return ((color*(A*color+C*B)+D*E)/(color*(A*color+B)+D*F))-E/F;
}

vec4 tonemap(vec4 color)
{
    float exposure = 4.5f;
	float gamma = 2.2f;
	vec3 outcol = Uncharted2Tonemap(color.rgb * exposure);
	outcol = outcol * (1.0f / Uncharted2Tonemap(vec3(11.2f)));	
	return vec4(pow(outcol, vec3(1.0f / gamma)), color.a);
}

#ifdef USE_IBL
// Calculation of the lighting contribution from an optional Image Based Light source.
// Precomputed Environment Maps are required uniform inputs and are computed as outlined in [1].
// See our README.md on Environment Maps [3] for additional discussion.
float3 getIBLContribution(PBRInfo pbrInputs, float3 n, float3 reflection)
{
    float mipCount = 10.0; // resolution of 512x512
    float lod = (pbrInputs.perceptualRoughness * mipCount);
    // retrieve a scale and bias to F0. See [1], Figure 3
    float3 brdf = SRGBtoLINEAR(texture(brdflut, float2(pbrInputs.NdotV, 1.0 - pbrInputs.perceptualRoughness))).rgb;
    float3 diffuseLight = SRGBtoLINEAR(tonemap(texture(irradiance, n))).rgb;

    float3 specularLight = SRGBtoLINEAR(tonemap(textureLod(prefiltered, reflection, lod))).rgb;

    float3 diffuse = diffuseLight * pbrInputs.diffuseColor;
    float3 specular = specularLight * (pbrInputs.specularColor * brdf.x + brdf.y);

    // For presentation, this allows us to disable IBL terms
    diffuse *= pbrMaterial.u_ScaleIBLAmbient.x;
    specular *= pbrMaterial.u_ScaleIBLAmbient.y;

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

layout (location = 0) in vec3 inWorldPos;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec3 inTagent;
layout (location = 3) in vec2 inUV0;
layout (location = 4) in vec2 inUV1;
layout (location = 5) in vec4 inColor0;

layout (location = 0) out vec4 outColor;

void main()
{
    // Metallic and Roughness material properties are packed together
    // In glTF, these factors can be specified by fixed scalar values
    // or from a metallic-roughness map
	
    float perceptualRoughness = pbrMaterial.u_MetallicRoughnessValues.y;
    float metallic = pbrMaterial.u_MetallicRoughnessValues.x;
#ifdef HAS_METALROUGHNESSMAP
    // Roughness is stored in the 'g' channel, metallic is stored in the 'b' channel.
    // This layout intentionally reserves the 'r' channel for (optional) occlusion map data
    float4 mrSample = texture(metal_roughness_pbr, inUV0);
	metallic = mrSample.b * metallic;
    perceptualRoughness = mrSample.g * perceptualRoughness;
    
#endif
    perceptualRoughness = clamp(perceptualRoughness, c_MinRoughness, 1.0);
    metallic = clamp(metallic, 0.0, 1.0);

    PBRInfo pbrInputs;

    // Roughness is authored as perceptual roughness; as is convention,
    // convert to material roughness by squaring the perceptual roughness [2].
    pbrInputs.alphaRoughness = perceptualRoughness * perceptualRoughness;

    // The albedo may be defined from a base texture or a flat color
#ifdef HAS_BASECOLORMAP
    float4 baseColorSource = texture(albedo_pbr, inUV0);
    float4 baseColor = SRGBtoLINEAR(baseColorSource) * pbrMaterial.u_BaseColorFactor;
#else
    float4 baseColor = pbrMaterial.u_BaseColorFactor;
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

    //float3 normalColor = texture(normal_pbr, inUV0).xyz;
	
    //float3 n = NormalSampleToWorldSpace(normalColor, inNormal, inTagent, inWorldPos, inUV0);
	
	float3 n = getNormal(inWorldPos, inNormal, inUV0);
	n.y *= -1.0f;
    float3 v = normalize(cbPass.gEyePosW - inWorldPos);        // Vector from surface point to camera
	float3 u_LightDirection = {0.73994, -0.64279, 0.19827};
    float3 l = normalize(u_LightDirection);             // Vector from surface point to light
    float3 h = normalize(l+v);                          // Half vector between both l and v
    float3 reflection = normalize(reflect(-v, n));

    pbrInputs.NdotL = clamp(dot(n, l), 0.001, 1.0);
    pbrInputs.NdotV = clamp(abs(dot(n, v)), 0.001, 1.0);
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
	float3 middle = diffuseContrib + specContrib;
	float3 u_LightColor = {1.0,1.0,1.0};
    float3 color = pbrInputs.NdotL *  u_LightColor * middle;
    // Calculate lighting contribution from image based lighting source (IBL)
#ifdef USE_IBL
	float3 ibl = getIBLContribution(pbrInputs, n, reflection);
    color += ibl;
#endif
    // Apply optional PBR terms for additional (optional) shading
#ifdef HAS_OCCLUSIONMAP
	float ao = texture(ao_pbr, inUV0).r;
    color = lerp(color, color * ao, pbrMaterial.u_OcclusionStrength);
#endif

#ifdef HAS_EMISSIVEMAP
	float3 emissive = texture(emissive_pbr,inUV0).rgb * pbrMaterial.u_EmissiveFactor;
    color += emissive;
#endif
    //color = ibl;
    outColor =  float4(pow(color,float3(1.0/2.2, 1.0/2.2, 1.0/2.2)), baseColor.a);
}

#endif //FRAGMENT_SHADER