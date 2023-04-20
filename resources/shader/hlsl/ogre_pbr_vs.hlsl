#line 1  "OgreUnifiedShader.h"
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
#line 1  "HLSL_SM4Support.hlsl"
// This file is part of the OGRE project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at https://www.ogre3d.org/licensing.

// @public-api

#if OGRE_HLSL >= 4

// SM4 separates sampler into Texture and SamplerState

#define sampler1D Sampler1D
#define sampler2D Sampler2D
#define sampler3D Sampler3D
#define samplerCUBE SamplerCube

struct Sampler1D
{
    Texture1D t;
    SamplerState s;
};
struct Sampler2D
{
    Texture2D t;
    SamplerState s;
};
struct Sampler3D
{
    Texture3D t;
    SamplerState s;
};
struct SamplerCube
{
    TextureCube t;
    SamplerState s;
};

float4 tex1D(Sampler1D s, float v) { return s.t.Sample(s.s, v); }
float4 tex2D(Sampler2D s, float2 v) { return s.t.Sample(s.s, v); }
float4 tex3D(Sampler3D s, float3 v) { return s.t.Sample(s.s, v); }
float4 texCUBE(SamplerCube s, float3 v) { return s.t.Sample(s.s, v); }
float4 texCUBElod(SamplerCube s, float4 v) { return s.t.SampleLevel(s.s, v.xyz, v.w); }

float4 tex2D(Sampler2D s, float2 v, float2 ddx, float2 ddy) { return s.t.SampleGrad(s.s, v, ddx, ddy); }
float4 tex2Dproj(Sampler2D s, float4 v) { return s.t.Sample(s.s, v.xy/v.w); }
float4 tex2Dlod(Sampler2D s, float4 v) { return s.t.SampleLevel(s.s, v.xy, v.w); }

#define SAMPLER1D(name, reg) \
    Texture1D name ## Tex : register(t ## reg);\
    SamplerState name ## State : register(s ## reg);\
    static Sampler1D name = {name ## Tex, name ## State}

#define SAMPLER2D(name, reg) \
    Texture2D name ## Tex : register(t ## reg);\
    SamplerState name ## State : register(s ## reg);\
    static Sampler2D name = {name ## Tex, name ## State}

#define SAMPLER3D(name, reg) \
    Texture3D name ## Tex : register(t ## reg);\
    SamplerState name ## State : register(s ## reg);\
    static Sampler3D name = {name ## Tex, name ## State}

#define SAMPLERCUBE(name, reg) \
    TextureCube name ## Tex : register(t ## reg);\
    SamplerState name ## State : register(s ## reg);\
    static SamplerCube name = {name ## Tex, name ## State}

// the following are not available in D3D9, but provided for convenience
struct Sampler2DShadow
{
    Texture2D t;
    SamplerComparisonState s;
};
struct Sampler2DArray
{
    Texture2DArray t;
    SamplerState s;
};

#define SAMPLER2DSHADOW(name, reg) \
    Texture2D name ## Tex : register(t ## reg);\
    SamplerComparisonState name ## State : register(s ## reg);\
    static Sampler2DShadow name = {name ## Tex, name ## State}

#define SAMPLER2DARRAY(name, reg) \
    Texture2DArray name ## Tex : register(t ## reg);\
    SamplerState name ## State : register(s ## reg);\
    static Sampler2DArray name = {name ## Tex, name ## State}

float tex2Dcmp(Sampler2DShadow s, float3 v) { return s.t.SampleCmpLevelZero(s.s, v.xy, v.z); }
float4 tex2DARRAY(Sampler2DArray s, float3 v) { return s.t.Sample(s.s, v); }
#else

#define SAMPLER1D(name, reg) sampler1D name : register(s ## reg)
#define SAMPLER2D(name, reg) sampler2D name : register(s ## reg)
#define SAMPLER3D(name, reg) sampler3D name : register(s ## reg)
#define SAMPLERCUBE(name, reg) samplerCUBE name : register(s ## reg)

#endif
#line 26 "OgreUnifiedShader.h"
#define vec2 float2
#define vec3 float3
#define vec4 float4
#define mat3 float3x3
#define mat4 float4x4

#define ivec2 int2
#define ivec3 int3
#define ivec4 int4

#define texture1D tex1D
#define texture2D tex2D
#define texture3D tex3D
#define texture2DArray tex2DARRAY
#define textureCube texCUBE
#define shadow2D tex2Dcmp
#define texture2DProj tex2Dproj
vec4 texture2DLod(sampler2D s, vec2 v, float lod) { return tex2Dlod(s, vec4(v.x, v.y, 0, lod)); }

#define samplerCube samplerCUBE
vec4 textureCubeLod(samplerCube s, vec3 v, float lod) { return texCUBElod(s, vec4(v.x, v.y, v.z, lod)); }

#define sampler2DShadow Sampler2DShadow

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

#if __VERSION__ == 100
mat2 transpose(mat2 m)
{
  return mat2(m[0][0], m[1][0],
              m[0][1], m[1][1]);
}

mat3 transpose(mat3 m)
{
  return mat3(m[0][0], m[1][0], m[2][0],
              m[0][1], m[1][1], m[2][1],
              m[0][2], m[1][2], m[2][2]);
}

mat4 transpose(mat4 m)
{
  return mat4(m[0][0], m[1][0], m[2][0], m[3][0],
              m[0][1], m[1][1], m[2][1], m[3][1],
              m[0][2], m[1][2], m[2][2], m[3][2],
              m[0][3], m[1][3], m[2][3], m[3][3]);
}
#endif

#if __VERSION__ > 120 || defined(OGRE_GLSLANG)
#define texture1D texture
#define texture2D texture
#define texture3D texture
#define texture2DArray texture
#define textureCube texture
#define shadow2D texture
#define shadow2DProj textureProj
#define texture2DProj textureProj
#define texture2DLod textureLod
#define textureCubeLod textureLod

#if defined(OGRE_GLSLANG) || (__VERSION__ > 150 && defined(OGRE_VERTEX_SHADER)) || __VERSION__ >= 410
#define IN(decl, loc) layout(location = loc) in decl;
#else
#define IN(decl, loc) in decl;
#endif

#if defined(OGRE_GLSLANG) || (__VERSION__ > 150 && defined(OGRE_FRAGMENT_SHADER)) || __VERSION__ >= 410
#define OUT(decl, loc) layout(location = loc) out decl;
#else
#define OUT(decl, loc) out decl;
#endif

#else

#ifdef OGRE_VERTEX_SHADER
#define IN(decl, loc) attribute decl;
#define OUT(decl, loc) varying decl;
#else
#define IN(decl, loc) varying decl;
#define OUT(decl, loc) out decl;
#endif

#endif

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
#line 103 "OgreUnifiedShader.h"

#ifndef USE_OGRE_FROM_FUTURE
#define _UNIFORM_BINDING(b)
#elif defined(VULKAN)
#define _UNIFORM_BINDING(b) layout(binding = b + 2) uniform
#elif __VERSION__ >= 420
#define _UNIFORM_BINDING(b) layout(binding = b) uniform
#else
#define _UNIFORM_BINDING(b) uniform
#endif

#define SAMPLER1D(name, reg) _UNIFORM_BINDING(reg) sampler1D name
#define SAMPLER2D(name, reg) _UNIFORM_BINDING(reg) sampler2D name
#define SAMPLER3D(name, reg) _UNIFORM_BINDING(reg) sampler3D name
#define SAMPLER2DARRAY(name, reg) _UNIFORM_BINDING(reg) sampler2DArray name
#define SAMPLERCUBE(name, reg) _UNIFORM_BINDING(reg) samplerCube name
#define SAMPLER2DSHADOW(name, reg) _UNIFORM_BINDING(reg) sampler2DShadow name

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

#line 2 "pbr-vert.glsl"

// The MIT License
// Copyright (c) 2016-2017 Mohamad Moneimne and Contributors

OGRE_UNIFORMS(
uniform mat4 u_MVPMatrix;
uniform mat4 u_ModelMatrix;
)

MAIN_PARAMETERS

IN(vec4 position, POSITION)
#ifdef HAS_NORMALS
IN(vec4 normal, NORMAL)
#endif
#ifdef HAS_TANGENTS
IN(vec4 tangent, TANGENT)
#endif
#ifdef HAS_UV
IN(vec2 uv0, TEXCOORD0)
#endif

OUT(vec3 v_Position, TEXCOORD0)
OUT(vec2 v_UV, TEXCOORD1)

#ifdef HAS_NORMALS
#ifdef HAS_TANGENTS
OUT(mat3 v_TBN, TEXCOORD2)
#else
OUT(vec3 v_Normal, TEXCOORD2)
#endif
#endif


MAIN_DECLARATION
{
  vec4 pos = mul(u_ModelMatrix, position);
  v_Position = vec3(pos.xyz) / pos.w;

  #ifdef HAS_NORMALS
  #ifdef HAS_TANGENTS
  vec3 normalW = normalize(mul(u_ModelMatrix, vec4(normal.xyz, 0.0)).xyz);
  vec3 tangentW = normalize(mul(u_ModelMatrix, vec4(tangent.xyz, 0.0)).xyz);
  vec3 bitangentW = cross(normalW, tangentW) * tangent.w;
  v_TBN = mtxFromCols(tangentW, bitangentW, normalW);
  #else // HAS_TANGENTS != 1
  v_Normal = normalize(vec3(mul(u_ModelMatrix, vec4(normal.xyz, 0.0))));
  #endif
  #endif

  #ifdef HAS_UV
  v_UV = uv0;
  #else
  v_UV = vec2(0.,0.);
  #endif

  gl_Position = mul(u_MVPMatrix, position); // needs w for proper perspective correction
}


//has_normal
//has_tangent
//has_uv
//ogre_hlsl
//ogre_vertex_shader