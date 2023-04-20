#include "Common.hlsl"

#ifndef OGRE_HLSL
#ifndef GL_ES
#if defined(USE_TEX_LOD) && __VERSION__ < 150
#extension GL_ARB_shader_texture_lod : require  
#endif
#else
#extension GL_OES_standard_derivatives : enable
#extension GL_EXT_shader_texture_lod: enable
#define textureCubeLod textureLodEXT
precision highp float;
#endif
#endif

#define USE_OGRE_FROM_FUTURE
// This file is part of the OGRE project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at https://www.ogre3d.org/licensing.

// greatly inspired by
// - shiny: https://ogrecave.github.io/shiny/defining-materials-shaders.html
// - bgfx: https://github.com/bkaradzic/bgfx/blob/master/src/bgfx_shader.sh

/// general usage:
// MAIN_PARAMETERS
// IN(vec4 vertex, POSITION)
// MAIN_DECLARATION
// {
//     GLSL code here
// }

/// configuration
// use macros that will be default with Ogre 14
// #define USE_OGRE_FROM_FUTURE

// @public-api

#if defined(OGRE_HLSL) || defined(OGRE_CG)
// HLSL
// This file is part of the OGRE project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at https://www.ogre3d.org/licensing.

// @public-api

#define vec2 float2
#define vec3 float3
#define vec4 float4
#define mat3 float3x3
#define mat4 float4x4

#define ivec2 int2
#define ivec3 int3
#define ivec4 int4


#define mix lerp
#define fract frac

float mod(float _a, float _b) { return _a - _b * floor(_a / _b); }
vec2  mod(vec2  _a, vec2  _b) { return _a - _b * floor(_a / _b); }
vec3  mod(vec3  _a, vec3  _b) { return _a - _b * floor(_a / _b); }
vec4  mod(vec4  _a, vec4  _b) { return _a - _b * floor(_a / _b); }

vec2 vec2_splat(float x) { return vec2(x, x); }
vec3 vec3_splat(float x) { return vec3(x, x, x); }
vec4 vec4_splat(float x) { return vec4(x, x, x, x); }

mat4 mtxFromRows(vec4 a, vec4 b, vec4 c, vec4 d)
{
    return mat4(a, b, c, d);
}

mat3 mtxFromRows(vec3 a, vec3 b, vec3 c)
{
    return mat3(a, b, c);
}

mat3 mtxFromCols(vec3 a, vec3 b, vec3 c)
{
    return transpose(mat3(a, b, c));
}

#define STATIC static

#define OGRE_UNIFORMS_BEGIN
#define OGRE_UNIFORMS_END

#define MAIN_PARAMETERS void main(

#ifdef OGRE_VERTEX_SHADER
#define MAIN_DECLARATION out float4 gl_Position : POSITION)
#else
#define MAIN_DECLARATION in float4 gl_FragCoord : POSITION, out float4 gl_FragColor : COLOR)
#endif

#define IN(decl, sem) in decl : sem,
#define OUT(decl, sem) out decl : sem,
#elif defined(OGRE_METAL)
#define vec2 float2
#define vec3 float3
#define vec4 float4
#define mat3 metal::float3x3
#define mat4 metal::float4x4

#define IN(decl, sem) decl [[ attribute(sem) ]];
#else
// GLSL
#line 1  "GLSL_GL3Support.glsl"
// This file is part of the OGRE project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at https://www.ogre3d.org/licensing.

// @public-api





#if defined(OGRE_FRAGMENT_SHADER) && (defined(OGRE_GLSLANG) || (__VERSION__ > 130))
#define gl_FragColor FragColor
OUT(vec4 FragColor, 0)
#endif

#ifdef VULKAN

#ifdef OGRE_VERTEX_SHADER
#define OGRE_UNIFORMS_BEGIN layout(binding = 0, row_major) uniform OgreUniforms {
#else
#define OGRE_UNIFORMS_BEGIN layout(binding = 1, row_major) uniform OgreUniforms {
#endif

#define OGRE_UNIFORMS_END };

#else

#define OGRE_UNIFORMS_BEGIN
#define OGRE_UNIFORMS_END

#endif

#ifndef USE_OGRE_FROM_FUTURE
#define _UNIFORM_BINDING(b)
#elif defined(VULKAN)
#define _UNIFORM_BINDING(b) layout(binding = b + 2) uniform
#elif __VERSION__ >= 420
#define _UNIFORM_BINDING(b) layout(binding = b) uniform
#else
#define _UNIFORM_BINDING(b) uniform
#endif


#define saturate(x) clamp(x, 0.0, 1.0)
#define mul(a, b) ((a) * (b))

#define vec2_splat vec2
#define vec3_splat vec3
#define vec4_splat vec4

mat4 mtxFromRows(vec4 a, vec4 b, vec4 c, vec4 d)
{
    return transpose(mat4(a, b, c, d));
}

mat3 mtxFromRows(vec3 a, vec3 b, vec3 c)
{
    return transpose(mat3(a, b, c));
}

mat3 mtxFromCols(vec3 a, vec3 b, vec3 c)
{
    return mat3(a, b, c);
}

#define STATIC

#define MAIN_PARAMETERS
#define MAIN_DECLARATION void main()

#endif

#if !defined(OGRE_HLSL) && !defined(OGRE_CG)
// semantics as aliases for attribute locations
#define POSITION    0
#define BLENDWEIGHT 1
#define NORMAL      2
#define COLOR0      3
#define COLOR1      4
#define COLOR COLOR0
#define FOG         5
#define BLENDINDICES 7
#define TEXCOORD0   8
#define TEXCOORD1   9
#define TEXCOORD2  10
#define TEXCOORD3  11
#define TEXCOORD4  12
#define TEXCOORD5  13
#define TEXCOORD6  14
#define TEXCOORD7  15
#define TANGENT    14
#endif

#define OGRE_UNIFORMS(params) OGRE_UNIFORMS_BEGIN params OGRE_UNIFORMS_END

// GL_EXT_shader_explicit_arithmetic_types polyfill
#ifdef OGRE_GLSLES
#define float32_t highp float
#define f32vec2 highp vec2
#define f32vec3 highp vec3
#define f32vec4 highp vec4
#else
#define float32_t float
#define f32vec2 vec2
#define f32vec3 vec3
#define f32vec4 vec4
#endif

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
    vec3 reflectance0;            // full reflectance color (normal incidence angle)
    vec3 reflectance90;           // reflectance color at grazing angle
    float alphaRoughness;         // roughness mapped to a more linear change in the roughness (proposed by [2])
    vec3 diffuseColor;            // color contribution from diffuse lighting
    vec3 specularColor;           // color contribution from specular lighting
};

STATIC const float M_PI = 3.141592653589793;
STATIC const float c_MinRoughness = 0.04;

vec4 SRGBtoLINEAR(vec4 srgbIn)
{
    #ifdef MANUAL_SRGB
    #ifdef SRGB_FAST_APPROXIMATION
    vec3 linOut = pow(srgbIn.xyz,vec3(2.2, 2.2, 2.2));
    #else //SRGB_FAST_APPROXIMATION
    vec3 bLess = step(vec3(0.04045),srgbIn.xyz);
    vec3 linOut = mix( srgbIn.xyz/vec3(12.92), pow((srgbIn.xyz+vec3(0.055))/vec3(1.055),vec3(2.4)), bLess );
    #endif //SRGB_FAST_APPROXIMATION
    return vec4(linOut,srgbIn.w);;
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
vec3 getIBLContribution(PBRInfo pbrInputs, vec3 n, vec3 reflection)
{
    return float3(1.0,1.0,1.0);
}
#endif

// Basic Lambertian diffuse
// Implementation from Lambert's Photometria https://archive.org/details/lambertsphotome00lambgoog
// See also [1], Equation 1
vec3 diffuse(PBRInfo pbrInputs)
{
    return pbrInputs.diffuseColor / M_PI;
}

// The following equation models the Fresnel reflectance term of the spec equation (aka F())
// Implementation of fresnel from [4], Equation 15
vec3 specularReflection(PBRInfo pbrInputs)
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
    return roughnessSq / (M_PI * f * f);
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
	
    float4 posW = mul(float4(vIn.PosL, 1.0f), gWorld);

    vOut.PosH = mul(posW, gViewProj);
    vOut.PosW = posW.xyz;
    vOut.NormalW = mul(vIn.NormalL, (float3x3) gWorldInvTranspose);
#ifdef HAS_TANGENTS
	vOut.TangentW = mul(vIn.TangentL, (float3x3)gWorld);
#endif
	float4 texC = mul(float4(vIn.TexC, 0.0f, 1.0f), gTexScale);
    vOut.v_UV = mul(texC, gTexTransform).xy;
	vOut.ShadowPosH = mul(posW, gShadowTransform);
	
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
    vec4 mrSample = gTextureArray[mMetalRoughnessIndex].Sample(gsamAnisotropicWrap, pin.v_UV) * gDiffuseAlbedo;
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
    vec4 baseColorSource = gTextureArray[mAlbedoIndex].Sample(gsamAnisotropicWrap, pin.v_UV) * gDiffuseAlbedo;
    vec4 baseColor = SRGBtoLINEAR(baseColorSource) * u_BaseColorFactor;
#else
    vec4 baseColor = u_BaseColorFactor;
#endif

    vec3 f0 = vec3(0.04, 0.04, 0.04);
    vec3 diffuseColor = baseColor.rgb * (vec3(1.0, 1.0, 1.0) - f0);
    diffuseColor *= 1.0 - metallic;
    vec3 specularColor = mix(f0, baseColor.rgb, metallic);

    // Compute reflectance.
    float reflectance = max(max(specularColor.r, specularColor.g), specularColor.b);

    // For typical incident reflectance range (between 4% to 100%) set the grazing reflectance to 100% for typical fresnel effect.
    // For very low reflectance range on highly diffuse objects (below 4%), incrementally reduce grazing reflecance to 0%.
    float reflectance90 = clamp(reflectance * 25.0, 0.0, 1.0);

    pbrInputs.reflectance0 = specularColor.rgb;
    pbrInputs.reflectance90 = vec3(1.0, 1.0, 1.0) * reflectance90;

    pbrInputs.perceptualRoughness = perceptualRoughness;
    pbrInputs.metalness = metallic;
    pbrInputs.diffuseColor = diffuseColor;
    pbrInputs.specularColor = specularColor;

    vec3 normalColor = gTextureArray[mNormalMapIndex].Sample(gsamAnisotropicWrap, pin.v_UV);
	
    vec3 n = NormalSampleToWorldSpace(normalColor, pin.NormalW, pin.TangentW);
    vec3 v = normalize(gEyePosW - pin.PosW);        // Vector from surface point to camera
    vec3 l = normalize(u_LightDirection);             // Vector from surface point to light
    vec3 h = normalize(l+v);                          // Half vector between both l and v
    vec3 reflection = -normalize(reflect(v, n));
    reflection.z *= -1.0;

    pbrInputs.NdotL = clamp(dot(n, l), 0.001, 1.0);
    pbrInputs.NdotV = abs(dot(n, v)) + 0.001;
    pbrInputs.NdotH = clamp(dot(n, h), 0.0, 1.0);
    pbrInputs.LdotH = clamp(dot(l, h), 0.0, 1.0);
    pbrInputs.VdotH = clamp(dot(v, h), 0.0, 1.0);

    // Calculate the shading terms for the microfacet specular shading model
    vec3 F = specularReflection(pbrInputs);
    float G = geometricOcclusion(pbrInputs);
    float D = microfacetDistribution(pbrInputs);

    // Calculation of analytical lighting contribution
    vec3 diffuseContrib = (1.0 - F) * diffuse(pbrInputs);
    vec3 specContrib = F * G * D / (4.0 * pbrInputs.NdotL * pbrInputs.NdotV);
    vec3 color = pbrInputs.NdotL * u_LightColor * (diffuseContrib + specContrib);

    // Calculate lighting contribution from image based lighting source (IBL)
#ifdef USE_IBL
    //color += getIBLContribution(pbrInputs, n, reflection);
#endif

    // Apply optional PBR terms for additional (optional) shading
#ifdef HAS_OCCLUSIONMAP
	float ao = gTextureArray[mAmbientOcclusionIndex].Sample(gsamAnisotropicWrap, pin.v_UV).r;
    color = mix(color, color * ao, u_OcclusionStrength);
#endif

#ifdef HAS_EMISSIVEMAP
	vec3 emissive = gTextureArray[mEmissiveIndex].Sample(gsamAnisotropicWrap, pin.v_UV).rgb * u_EmissiveFactor;
    color += emissive;
#endif

    return vec4(pow(color,vec3(1.0/2.2, 1.0/2.2, 1.0/2.2)), baseColor.a);
}
