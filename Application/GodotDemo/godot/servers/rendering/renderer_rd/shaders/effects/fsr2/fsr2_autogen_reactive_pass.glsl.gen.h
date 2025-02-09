/* WARNING, THIS FILE WAS GENERATED, DO NOT EDIT */
#ifndef FSR2_AUTOGEN_REACTIVE_PASS_GLSL_GEN_H_RD
#define FSR2_AUTOGEN_REACTIVE_PASS_GLSL_GEN_H_RD

#include "servers/rendering/renderer_rd/shader_rd.h"

class Fsr2AutogenReactivePassShaderRD : public ShaderRD {

public:

	Fsr2AutogenReactivePassShaderRD() {

		static const char _compute_code[] = {
R"<!>(
#version 450

#VERSION_DEFINES

vec2 derive_motion_vector(vec2 uv, float depth, mat4 reprojection_matrix) {
	vec4 previous_pos_ndc = reprojection_matrix * vec4(uv * 2.0f - 1.0f, depth * 2.0f - 1.0f, 1.0f);
	return 0.5f + (previous_pos_ndc.xy / previous_pos_ndc.w) * 0.5f - uv;
}

#define FFX_FSR2_OPTION_GODOT_DERIVE_INVALID_MOTION_VECTORS_FUNCTION(i, j, k) derive_motion_vector(i, j, k)























#extension GL_GOOGLE_include_directive : require
#extension GL_EXT_samplerless_texture_functions : require

#define FSR2_BIND_SRV_INPUT_OPAQUE_ONLY                     0
#define FSR2_BIND_SRV_INPUT_COLOR                           1
#define FSR2_BIND_UAV_AUTOREACTIVE                          2
#define FSR2_BIND_CB_REACTIVE                               3
#define FSR2_BIND_CB_FSR2                                   4










































#ifndef FFX_FSR2_RESOURCES_H
#define FFX_FSR2_RESOURCES_H

#if defined(FFX_CPU) || defined(FFX_GPU)
#define FFX_FSR2_RESOURCE_IDENTIFIER_NULL                                           0
#define FFX_FSR2_RESOURCE_IDENTIFIER_INPUT_OPAQUE_ONLY                              1
#define FFX_FSR2_RESOURCE_IDENTIFIER_INPUT_COLOR                                    2
#define FFX_FSR2_RESOURCE_IDENTIFIER_INPUT_MOTION_VECTORS                           3
#define FFX_FSR2_RESOURCE_IDENTIFIER_INPUT_DEPTH                                    4
#define FFX_FSR2_RESOURCE_IDENTIFIER_INPUT_EXPOSURE                                 5
#define FFX_FSR2_RESOURCE_IDENTIFIER_INPUT_REACTIVE_MASK                            6
#define FFX_FSR2_RESOURCE_IDENTIFIER_INPUT_TRANSPARENCY_AND_COMPOSITION_MASK        7
#define FFX_FSR2_RESOURCE_IDENTIFIER_RECONSTRUCTED_PREVIOUS_NEAREST_DEPTH           8
#define FFX_FSR2_RESOURCE_IDENTIFIER_DILATED_MOTION_VECTORS                         9
#define FFX_FSR2_RESOURCE_IDENTIFIER_DILATED_DEPTH                                  10
#define FFX_FSR2_RESOURCE_IDENTIFIER_INTERNAL_UPSCALED_COLOR                        11
#define FFX_FSR2_RESOURCE_IDENTIFIER_LOCK_STATUS                                    12
#define FFX_FSR2_RESOURCE_IDENTIFIER_NEW_LOCKS                                      13
#define FFX_FSR2_RESOURCE_IDENTIFIER_PREPARED_INPUT_COLOR                           14
#define FFX_FSR2_RESOURCE_IDENTIFIER_LUMA_HISTORY                                   15
#define FFX_FSR2_RESOURCE_IDENTIFIER_DEBUG_OUTPUT                                   16
#define FFX_FSR2_RESOURCE_IDENTIFIER_LANCZOS_LUT                                    17
#define FFX_FSR2_RESOURCE_IDENTIFIER_SPD_ATOMIC_COUNT                               18
#define FFX_FSR2_RESOURCE_IDENTIFIER_UPSCALED_OUTPUT                                19
#define FFX_FSR2_RESOURCE_IDENTIFIER_RCAS_INPUT                                     20
#define FFX_FSR2_RESOURCE_IDENTIFIER_LOCK_STATUS_1                                  21
#define FFX_FSR2_RESOURCE_IDENTIFIER_LOCK_STATUS_2                                  22
#define FFX_FSR2_RESOURCE_IDENTIFIER_INTERNAL_UPSCALED_COLOR_1                      23
#define FFX_FSR2_RESOURCE_IDENTIFIER_INTERNAL_UPSCALED_COLOR_2                      24
#define FFX_FSR2_RESOURCE_IDENTIFIER_INTERNAL_DEFAULT_REACTIVITY                    25
#define FFX_FSR2_RESOURCE_IDENTIFIER_INTERNAL_DEFAULT_TRANSPARENCY_AND_COMPOSITION  26
#define FFX_FSR2_RESOURCE_IDENTITIER_UPSAMPLE_MAXIMUM_BIAS_LUT                      27
#define FFX_FSR2_RESOURCE_IDENTIFIER_DILATED_REACTIVE_MASKS                         28
#define FFX_FSR2_RESOURCE_IDENTIFIER_SCENE_LUMINANCE                                29 
#define FFX_FSR2_RESOURCE_IDENTIFIER_SCENE_LUMINANCE_MIPMAP_0                       29
#define FFX_FSR2_RESOURCE_IDENTIFIER_SCENE_LUMINANCE_MIPMAP_1                       30
#define FFX_FSR2_RESOURCE_IDENTIFIER_SCENE_LUMINANCE_MIPMAP_2                       31
#define FFX_FSR2_RESOURCE_IDENTIFIER_SCENE_LUMINANCE_MIPMAP_3                       32
#define FFX_FSR2_RESOURCE_IDENTIFIER_SCENE_LUMINANCE_MIPMAP_4                       33
#define FFX_FSR2_RESOURCE_IDENTIFIER_SCENE_LUMINANCE_MIPMAP_5                       34
#define FFX_FSR2_RESOURCE_IDENTIFIER_SCENE_LUMINANCE_MIPMAP_6                       35
#define FFX_FSR2_RESOURCE_IDENTIFIER_SCENE_LUMINANCE_MIPMAP_7                       36
#define FFX_FSR2_RESOURCE_IDENTIFIER_SCENE_LUMINANCE_MIPMAP_8                       37
#define FFX_FSR2_RESOURCE_IDENTIFIER_SCENE_LUMINANCE_MIPMAP_9                       38
#define FFX_FSR2_RESOURCE_IDENTIFIER_SCENE_LUMINANCE_MIPMAP_10                      39
#define FFX_FSR2_RESOURCE_IDENTIFIER_SCENE_LUMINANCE_MIPMAP_11                      40
#define FFX_FSR2_RESOURCE_IDENTIFIER_SCENE_LUMINANCE_MIPMAP_12                      41
#define FFX_FSR2_RESOURCE_IDENTIFIER_INTERNAL_DEFAULT_EXPOSURE                      42
#define FFX_FSR2_RESOURCE_IDENTIFIER_AUTO_EXPOSURE                                  43
#define FFX_FSR2_RESOURCE_IDENTIFIER_AUTOREACTIVE                                   44
#define FFX_FSR2_RESOURCE_IDENTIFIER_AUTOCOMPOSITION                                45

#define FFX_FSR2_RESOURCE_IDENTIFIER_PREV_PRE_ALPHA_COLOR                           46
#define FFX_FSR2_RESOURCE_IDENTIFIER_PREV_POST_ALPHA_COLOR                          47
#define FFX_FSR2_RESOURCE_IDENTIFIER_PREV_PRE_ALPHA_COLOR_1                         48
#define FFX_FSR2_RESOURCE_IDENTIFIER_PREV_POST_ALPHA_COLOR_1                        49
#define FFX_FSR2_RESOURCE_IDENTIFIER_PREV_PRE_ALPHA_COLOR_2                         50
#define FFX_FSR2_RESOURCE_IDENTIFIER_PREV_POST_ALPHA_COLOR_2                        51
#define FFX_FSR2_RESOURCE_IDENTIFIER_PREVIOUS_DILATED_MOTION_VECTORS                52
#define FFX_FSR2_RESOURCE_IDENTIFIER_INTERNAL_DILATED_MOTION_VECTORS_1              53
#define FFX_FSR2_RESOURCE_IDENTIFIER_INTERNAL_DILATED_MOTION_VECTORS_2              54
#define FFX_FSR2_RESOURCE_IDENTIFIER_LUMA_HISTORY_1                                 55
#define FFX_FSR2_RESOURCE_IDENTIFIER_LUMA_HISTORY_2                                 56
#define FFX_FSR2_RESOURCE_IDENTIFIER_LOCK_INPUT_LUMA                                57


#define FFX_FSR2_RESOURCE_IDENTIFIER_SCENE_LUMINANCE_MIPMAP_SHADING_CHANGE          FFX_FSR2_RESOURCE_IDENTIFIER_SCENE_LUMINANCE_MIPMAP_4
#define FFX_FSR2_SHADING_CHANGE_MIP_LEVEL                                           (FFX_FSR2_RESOURCE_IDENTIFIER_SCENE_LUMINANCE_MIPMAP_SHADING_CHANGE - FFX_FSR2_RESOURCE_IDENTIFIER_SCENE_LUMINANCE)

#define FFX_FSR2_RESOURCE_IDENTIFIER_COUNT                                          58

#define FFX_FSR2_CONSTANTBUFFER_IDENTIFIER_FSR2                                     0
#define FFX_FSR2_CONSTANTBUFFER_IDENTIFIER_SPD                                      1
#define FFX_FSR2_CONSTANTBUFFER_IDENTIFIER_RCAS                                     2
#define FFX_FSR2_CONSTANTBUFFER_IDENTIFIER_GENREACTIVE                              3

#define FFX_FSR2_AUTOREACTIVEFLAGS_APPLY_TONEMAP                                    1
#define FFX_FSR2_AUTOREACTIVEFLAGS_APPLY_INVERSETONEMAP                             2
#define FFX_FSR2_AUTOREACTIVEFLAGS_APPLY_THRESHOLD                                  4
#define FFX_FSR2_AUTOREACTIVEFLAGS_USE_COMPONENTS_MAX                               8

#endif 

#endif 

#if defined(FFX_GPU)





























#if !defined(FFX_CORE_H)
#define FFX_CORE_H





















#ifndef FFX_COMMON_TYPES_H
#define FFX_COMMON_TYPES_H

#if defined(FFX_CPU)
#define FFX_PARAMETER_IN
#define FFX_PARAMETER_OUT
#define FFX_PARAMETER_INOUT
#elif defined(FFX_HLSL)
#define FFX_PARAMETER_IN        in
#define FFX_PARAMETER_OUT       out
#define FFX_PARAMETER_INOUT     inout
#elif defined(FFX_GLSL)
#define FFX_PARAMETER_IN        in
#define FFX_PARAMETER_OUT       out
#define FFX_PARAMETER_INOUT     inout
#endif 

#if defined(FFX_CPU)



typedef bool FfxBoolean;




typedef uint8_t FfxUInt8;




typedef uint16_t FfxUInt16;




typedef uint32_t FfxUInt32;




typedef uint64_t FfxUInt64;




typedef int8_t FfxInt8;




typedef int16_t FfxInt16;




typedef int32_t FfxInt32;




typedef int64_t FfxInt64;




typedef float FfxFloat32;




typedef float FfxFloat32x2[2];




typedef float FfxFloat32x3[3];




typedef float FfxFloat32x4[4];




typedef uint32_t FfxUInt32x2[2];




typedef uint32_t FfxUInt32x3[3];




typedef uint32_t FfxUInt32x4[4];
#endif 

#if defined(FFX_HLSL)



typedef bool FfxBoolean;

#if FFX_HLSL_6_2
typedef float32_t   FfxFloat32;
typedef float32_t2  FfxFloat32x2;
typedef float32_t3  FfxFloat32x3;
typedef float32_t4  FfxFloat32x4;




typedef uint32_t    FfxUInt32;
typedef uint32_t2   FfxUInt32x2;
typedef uint32_t3   FfxUInt32x3;
typedef uint32_t4   FfxUInt32x4;
typedef int32_t     FfxInt32;
typedef int32_t2    FfxInt32x2;
typedef int32_t3    FfxInt32x3;
typedef int32_t4    FfxInt32x4;
#else
#define FfxFloat32   float
#define FfxFloat32x2 float2
#define FfxFloat32x3 float3
#define FfxFloat32x4 float4




typedef uint        FfxUInt32;
typedef uint2       FfxUInt32x2;
typedef uint3       FfxUInt32x3;
typedef uint4       FfxUInt32x4;
typedef int         FfxInt32;
typedef int2        FfxInt32x2;
typedef int3        FfxInt32x3;
typedef int4        FfxInt32x4;
#endif 

#if FFX_HALF
#if FFX_HLSL_6_2
typedef float16_t   FfxFloat16;
typedef float16_t2  FfxFloat16x2;
typedef float16_t3  FfxFloat16x3;
typedef float16_t4  FfxFloat16x4;




typedef uint16_t    FfxUInt16;
typedef uint16_t2   FfxUInt16x2;
typedef uint16_t3   FfxUInt16x3;
typedef uint16_t4   FfxUInt16x4;




typedef int16_t     FfxInt16;
typedef int16_t2    FfxInt16x2;
typedef int16_t3    FfxInt16x3;
typedef int16_t4    FfxInt16x4;
#else
typedef min16float  FfxFloat16;
typedef min16float2 FfxFloat16x2;
typedef min16float3 FfxFloat16x3;
typedef min16float4 FfxFloat16x4;




typedef min16uint   FfxUInt16;
typedef min16uint2  FfxUInt16x2;
typedef min16uint3  FfxUInt16x3;
typedef min16uint4  FfxUInt16x4;




typedef min16int    FfxInt16;
typedef min16int2   FfxInt16x2;
typedef min16int3   FfxInt16x3;
typedef min16int4   FfxInt16x4;
#endif  
#endif 
#endif 

#if defined(FFX_GLSL)



#define FfxBoolean   bool
#define FfxFloat32   float
#define FfxFloat32x2 vec2
#define FfxFloat32x3 vec3
#define FfxFloat32x4 vec4
#define FfxUInt32    uint
#define FfxUInt32x2  uvec2
#define FfxUInt32x3  uvec3
#define FfxUInt32x4  uvec4
#define FfxInt32     int
#define FfxInt32x2   ivec2
#define FfxInt32x3   ivec3
#define FfxInt32x4   ivec4
#if FFX_HALF
#define FfxFloat16   float16_t
#define FfxFloat16x2 f16vec2
#define FfxFloat16x3 f16vec3
#define FfxFloat16x4 f16vec4
#define FfxUInt16    uint16_t
#define FfxUInt16x2  u16vec2
#define FfxUInt16x3  u16vec3
#define FfxUInt16x4  u16vec4
#define FfxInt16     int16_t
#define FfxInt16x2   i16vec2
#define FfxInt16x3   i16vec3
#define FfxInt16x4   i16vec4
#endif 
#endif 





#if FFX_HALF

#if FFX_HLSL_6_2

#define FFX_MIN16_SCALAR( TypeName, BaseComponentType )           typedef BaseComponentType##16_t TypeName;
#define FFX_MIN16_VECTOR( TypeName, BaseComponentType, COL )      typedef vector<BaseComponentType##16_t, COL> TypeName;
#define FFX_MIN16_MATRIX( TypeName, BaseComponentType, ROW, COL ) typedef matrix<BaseComponentType##16_t, ROW, COL> TypeName;

#define FFX_16BIT_SCALAR( TypeName, BaseComponentType )           typedef BaseComponentType##16_t TypeName;
#define FFX_16BIT_VECTOR( TypeName, BaseComponentType, COL )      typedef vector<BaseComponentType##16_t, COL> TypeName;
#define FFX_16BIT_MATRIX( TypeName, BaseComponentType, ROW, COL ) typedef matrix<BaseComponentType##16_t, ROW, COL> TypeName;

#else 

#define FFX_MIN16_SCALAR( TypeName, BaseComponentType )           typedef min16##BaseComponentType TypeName;
#define FFX_MIN16_VECTOR( TypeName, BaseComponentType, COL )      typedef vector<min16##BaseComponentType, COL> TypeName;
#define FFX_MIN16_MATRIX( TypeName, BaseComponentType, ROW, COL ) typedef matrix<min16##BaseComponentType, ROW, COL> TypeName;

#define FFX_16BIT_SCALAR( TypeName, BaseComponentType )           FFX_MIN16_SCALAR( TypeName, BaseComponentType );
#define FFX_16BIT_VECTOR( TypeName, BaseComponentType, COL )      FFX_MIN16_VECTOR( TypeName, BaseComponentType, COL );
#define FFX_16BIT_MATRIX( TypeName, BaseComponentType, ROW, COL ) FFX_MIN16_MATRIX( TypeName, BaseComponentType, ROW, COL );

#endif 

#else 

#define FFX_MIN16_SCALAR( TypeName, BaseComponentType )           typedef BaseComponentType TypeName;
#define FFX_MIN16_VECTOR( TypeName, BaseComponentType, COL )      typedef vector<BaseComponentType, COL> TypeName;
#define FFX_MIN16_MATRIX( TypeName, BaseComponentType, ROW, COL ) typedef matrix<BaseComponentType, ROW, COL> TypeName;

#define FFX_16BIT_SCALAR( TypeName, BaseComponentType )           typedef BaseComponentType TypeName;
#define FFX_16BIT_VECTOR( TypeName, BaseComponentType, COL )      typedef vector<BaseComponentType, COL> TypeName;
#define FFX_16BIT_MATRIX( TypeName, BaseComponentType, ROW, COL ) typedef matrix<BaseComponentType, ROW, COL> TypeName;

#endif 

#if defined(FFX_GPU)

#if defined(FFX_HLSL)
FFX_MIN16_SCALAR( FFX_MIN16_F , float );
FFX_MIN16_VECTOR( FFX_MIN16_F2, float, 2 );
FFX_MIN16_VECTOR( FFX_MIN16_F3, float, 3 );
FFX_MIN16_VECTOR( FFX_MIN16_F4, float, 4 );

FFX_MIN16_SCALAR( FFX_MIN16_I,  int );
FFX_MIN16_VECTOR( FFX_MIN16_I2, int, 2 );
FFX_MIN16_VECTOR( FFX_MIN16_I3, int, 3 );
FFX_MIN16_VECTOR( FFX_MIN16_I4, int, 4 );

FFX_MIN16_SCALAR( FFX_MIN16_U,  uint );
FFX_MIN16_VECTOR( FFX_MIN16_U2, uint, 2 );
FFX_MIN16_VECTOR( FFX_MIN16_U3, uint, 3 );
FFX_MIN16_VECTOR( FFX_MIN16_U4, uint, 4 );

FFX_16BIT_SCALAR( FFX_F16_t , float );
FFX_16BIT_VECTOR( FFX_F16_t2, float, 2 );
FFX_16BIT_VECTOR( FFX_F16_t3, float, 3 );
FFX_16BIT_VECTOR( FFX_F16_t4, float, 4 );

FFX_16BIT_SCALAR( FFX_I16_t,  int );
FFX_16BIT_VECTOR( FFX_I16_t2, int, 2 );
FFX_16BIT_VECTOR( FFX_I16_t3, int, 3 );
FFX_16BIT_VECTOR( FFX_I16_t4, int, 4 );

FFX_16BIT_SCALAR( FFX_U16_t,  uint );
FFX_16BIT_VECTOR( FFX_U16_t2, uint, 2 );
FFX_16BIT_VECTOR( FFX_U16_t3, uint, 3 );
FFX_16BIT_VECTOR( FFX_U16_t4, uint, 4 );

#define TYPEDEF_MIN16_TYPES(Prefix)           \
typedef FFX_MIN16_F     Prefix##_F;           \
typedef FFX_MIN16_F2    Prefix##_F2;          \
typedef FFX_MIN16_F3    Prefix##_F3;          \
typedef FFX_MIN16_F4    Prefix##_F4;          \
typedef FFX_MIN16_I     Prefix##_I;           \
typedef FFX_MIN16_I2    Prefix##_I2;          \
typedef FFX_MIN16_I3    Prefix##_I3;          \
typedef FFX_MIN16_I4    Prefix##_I4;          \
typedef FFX_MIN16_U     Prefix##_U;           \
typedef FFX_MIN16_U2    Prefix##_U2;          \
typedef FFX_MIN16_U3    Prefix##_U3;          \
typedef FFX_MIN16_U4    Prefix##_U4;

#define TYPEDEF_16BIT_TYPES(Prefix)           \
typedef FFX_16BIT_F     Prefix##_F;           \
typedef FFX_16BIT_F2    Prefix##_F2;          \
typedef FFX_16BIT_F3    Prefix##_F3;          \
typedef FFX_16BIT_F4    Prefix##_F4;          \
typedef FFX_16BIT_I     Prefix##_I;           \
typedef FFX_16BIT_I2    Prefix##_I2;          \
typedef FFX_16BIT_I3    Prefix##_I3;          \
typedef FFX_16BIT_I4    Prefix##_I4;          \
typedef FFX_16BIT_U     Prefix##_U;           \
typedef FFX_16BIT_U2    Prefix##_U2;          \
typedef FFX_16BIT_U3    Prefix##_U3;          \
typedef FFX_16BIT_U4    Prefix##_U4;

#define TYPEDEF_FULL_PRECISION_TYPES(Prefix)  \
typedef FfxFloat32      Prefix##_F;           \
typedef FfxFloat32x2    Prefix##_F2;          \
typedef FfxFloat32x3    Prefix##_F3;          \
typedef FfxFloat32x4    Prefix##_F4;          \
typedef FfxInt32        Prefix##_I;           \
typedef FfxInt32x2      Prefix##_I2;          \
typedef FfxInt32x3      Prefix##_I3;          \
typedef FfxInt32x4      Prefix##_I4;          \
typedef FfxUInt32       Prefix##_U;           \
typedef FfxUInt32x2     Prefix##_U2;          \
typedef FfxUInt32x3     Prefix##_U3;          \
typedef FfxUInt32x4     Prefix##_U4;
#endif 

#if defined(FFX_GLSL)

#if FFX_HALF

#define  FFX_MIN16_F  float16_t
#define  FFX_MIN16_F2 f16vec2
#define  FFX_MIN16_F3 f16vec3
#define  FFX_MIN16_F4 f16vec4

#define  FFX_MIN16_I  int16_t
#define  FFX_MIN16_I2 i16vec2
#define  FFX_MIN16_I3 i16vec3
#define  FFX_MIN16_I4 i16vec4

#define  FFX_MIN16_U  uint16_t
#define  FFX_MIN16_U2 u16vec2
#define  FFX_MIN16_U3 u16vec3
#define  FFX_MIN16_U4 u16vec4

#define FFX_16BIT_F  float16_t
#define FFX_16BIT_F2 f16vec2
#define FFX_16BIT_F3 f16vec3
#define FFX_16BIT_F4 f16vec4
)<!>" R"<!>(
#define FFX_16BIT_I  int16_t
#define FFX_16BIT_I2 i16vec2
#define FFX_16BIT_I3 i16vec3
#define FFX_16BIT_I4 i16vec4

#define FFX_16BIT_U  uint16_t
#define FFX_16BIT_U2 u16vec2
#define FFX_16BIT_U3 u16vec3
#define FFX_16BIT_U4 u16vec4

#else 

#define  FFX_MIN16_F  float
#define  FFX_MIN16_F2 vec2
#define  FFX_MIN16_F3 vec3
#define  FFX_MIN16_F4 vec4

#define  FFX_MIN16_I  int
#define  FFX_MIN16_I2 ivec2
#define  FFX_MIN16_I3 ivec3
#define  FFX_MIN16_I4 ivec4

#define  FFX_MIN16_U  uint
#define  FFX_MIN16_U2 uvec2
#define  FFX_MIN16_U3 uvec3
#define  FFX_MIN16_U4 uvec4

#define FFX_16BIT_F  float
#define FFX_16BIT_F2 vec2
#define FFX_16BIT_F3 vec3
#define FFX_16BIT_F4 vec4

#define FFX_16BIT_I  int
#define FFX_16BIT_I2 ivec2
#define FFX_16BIT_I3 ivec3
#define FFX_16BIT_I4 ivec4

#define FFX_16BIT_U  uint
#define FFX_16BIT_U2 uvec2
#define FFX_16BIT_U3 uvec3
#define FFX_16BIT_U4 uvec4

#endif 

#endif 

#endif 
#endif 

#if defined(FFX_CPU)
























#define FFX_TRUE (1)




#define FFX_FALSE (0)
 
#if !defined(FFX_STATIC)



#define FFX_STATIC static
#endif 

#ifdef __clang__
#pragma clang diagnostic ignored "-Wunused-variable"
#endif









FFX_STATIC FfxUInt32 ffxAsUInt32(FfxFloat32 x)
{
    union
    {
        FfxFloat32 f;
        FfxUInt32  u;
    } bits;

    bits.f = x;
    return bits.u;
}

FFX_STATIC FfxFloat32 ffxDot2(FfxFloat32x2 a, FfxFloat32x2 b)
{
    return a[0] * b[0] + a[1] * b[1];
}

FFX_STATIC FfxFloat32 ffxDot3(FfxFloat32x3 a, FfxFloat32x3 b)
{
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

FFX_STATIC FfxFloat32 ffxDot4(FfxFloat32x4 a, FfxFloat32x4 b)
{
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
}
















FFX_STATIC FfxFloat32 ffxLerp(FfxFloat32 x, FfxFloat32 y, FfxFloat32 t)
{
    return y * t + (-x * t + x);
}









FFX_STATIC FfxFloat32 ffxReciprocal(FfxFloat32 a)
{
    return 1.0f / a;
}









FFX_STATIC FfxFloat32 ffxSqrt(FfxFloat32 x)
{
    return sqrt(x);
}

FFX_STATIC FfxUInt32 AShrSU1(FfxUInt32 a, FfxUInt32 b)
{
    return FfxUInt32(FfxInt32(a) >> FfxInt32(b));
}











FFX_STATIC FfxFloat32 ffxFract(FfxFloat32 a)
{
    return a - floor(a);
}









FFX_STATIC FfxFloat32 rsqrt(FfxFloat32 a)
{
    return ffxReciprocal(ffxSqrt(a));
}

FFX_STATIC FfxFloat32 ffxMin(FfxFloat32 x, FfxFloat32 y)
{
    return x < y ? x : y;
}

FFX_STATIC FfxUInt32 ffxMin(FfxUInt32 x, FfxUInt32 y)
{
    return x < y ? x : y;
}

FFX_STATIC FfxFloat32 ffxMax(FfxFloat32 x, FfxFloat32 y)
{
    return x > y ? x : y;
}

FFX_STATIC FfxUInt32 ffxMax(FfxUInt32 x, FfxUInt32 y)
{
    return x > y ? x : y;
}









FFX_STATIC FfxFloat32 ffxSaturate(FfxFloat32 a)
{
    return ffxMin(1.0f, ffxMax(0.0f, a));
}




FFX_STATIC void opAAddOneF3(FfxFloat32x3 d, FfxFloat32x3 a, FfxFloat32 b)
{
    d[0] = a[0] + b;
    d[1] = a[1] + b;
    d[2] = a[2] + b;
    return;
}

FFX_STATIC void opACpyF3(FfxFloat32x3 d, FfxFloat32x3 a)
{
    d[0] = a[0];
    d[1] = a[1];
    d[2] = a[2];
    return;
}

FFX_STATIC void opAMulF3(FfxFloat32x3 d, FfxFloat32x3 a, FfxFloat32x3 b)
{
    d[0] = a[0] * b[0];
    d[1] = a[1] * b[1];
    d[2] = a[2] * b[2];
    return;
}

FFX_STATIC void opAMulOneF3(FfxFloat32x3 d, FfxFloat32x3 a, FfxFloat32 b)
{
    d[0] = a[0] * b;
    d[1] = a[1] * b;
    d[2] = a[2] * b;
    return;
}

FFX_STATIC void opARcpF3(FfxFloat32x3 d, FfxFloat32x3 a)
{
    d[0] = ffxReciprocal(a[0]);
    d[1] = ffxReciprocal(a[1]);
    d[2] = ffxReciprocal(a[2]);
    return;
}

















FFX_STATIC FfxUInt32 f32tof16(FfxFloat32 f)
{
    static FfxUInt16 base[512] = {
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0100, 0x0200, 0x0400,
        0x0800, 0x0c00, 0x1000, 0x1400, 0x1800, 0x1c00, 0x2000, 0x2400, 0x2800, 0x2c00, 0x3000, 0x3400, 0x3800, 0x3c00, 0x4000, 0x4400, 0x4800, 0x4c00, 0x5000,
        0x5400, 0x5800, 0x5c00, 0x6000, 0x6400, 0x6800, 0x6c00, 0x7000, 0x7400, 0x7800, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff,
        0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff,
        0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff,
        0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff,
        0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff,
        0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff,
        0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
        0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
        0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
        0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
        0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
        0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8001, 0x8002,
        0x8004, 0x8008, 0x8010, 0x8020, 0x8040, 0x8080, 0x8100, 0x8200, 0x8400, 0x8800, 0x8c00, 0x9000, 0x9400, 0x9800, 0x9c00, 0xa000, 0xa400, 0xa800, 0xac00,
        0xb000, 0xb400, 0xb800, 0xbc00, 0xc000, 0xc400, 0xc800, 0xcc00, 0xd000, 0xd400, 0xd800, 0xdc00, 0xe000, 0xe400, 0xe800, 0xec00, 0xf000, 0xf400, 0xf800,
        0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff,
        0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff,
        0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff,
        0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff,
        0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff,
        0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff
    };
    
    static FfxUInt8 shift[512] = {
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x17, 0x16, 0x15, 0x14, 0x13, 0x12, 0x11, 0x10, 0x0f, 0x0e, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d,
        0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x17, 0x16, 0x15, 0x14, 0x13, 0x12, 0x11, 0x10, 0x0f, 0x0e, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d,
        0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18
    };

    union
    {
        FfxFloat32      f;
        FfxUInt32 u;
    } bits;

    bits.f       = f;
    FfxUInt32 u = bits.u;
    FfxUInt32 i = u >> 23;
    return (FfxUInt32)(base[i]) + ((u & 0x7fffff) >> shift[i]);
}













FFX_STATIC FfxUInt32 packHalf2x16(FfxFloat32x2 a)
{
    return f32tof16(a[0]) + (f32tof16(a[1]) << 16);
}
#endif // #if defined(FFX_CPU)

#if defined(FFX_GLSL) && defined(FFX_GPU)
























#define FFX_GROUPSHARED shared




#define FFX_GROUP_MEMORY_BARRIER() barrier()




#define FFX_STATIC




#define FFX_UNROLL




#define FFX_GREATER_THAN(x, y) greaterThan(x, y)




#define FFX_GREATER_THAN_EQUAL(x, y) greaterThanEqual(x, y)




#define FFX_LESS_THAN(x, y) lessThan(x, y)




#define FFX_LESS_THAN_EQUAL(x, y) lessThanEqual(x, y)




#define FFX_EQUAL(x, y) equal(x, y)




#define FFX_NOT_EQUAL(x, y) notEqual(x, y)




#define FFX_BROADCAST_FLOAT32(x)   FfxFloat32(x)




#define FFX_BROADCAST_FLOAT32X2(x) FfxFloat32x2(FfxFloat32(x))




#define FFX_BROADCAST_FLOAT32X3(x) FfxFloat32x3(FfxFloat32(x))




#define FFX_BROADCAST_FLOAT32X4(x) FfxFloat32x4(FfxFloat32(x))




#define FFX_BROADCAST_UINT32(x)   FfxUInt32(x)




#define FFX_BROADCAST_UINT32X2(x) FfxUInt32x2(FfxUInt32(x))




#define FFX_BROADCAST_UINT32X3(x) FfxUInt32x3(FfxUInt32(x))




#define FFX_BROADCAST_UINT32X4(x) FfxUInt32x4(FfxUInt32(x))




#define FFX_BROADCAST_INT32(x)   FfxInt32(x)




#define FFX_BROADCAST_INT32X2(x) FfxInt32x2(FfxInt32(x))




#define FFX_BROADCAST_INT32X3(x) FfxInt32x3(FfxInt32(x))




#define FFX_BROADCAST_INT32X4(x) FfxInt32x4(FfxInt32(x))




#define FFX_BROADCAST_MIN_FLOAT16(x)   FFX_MIN16_F(x)




#define FFX_BROADCAST_MIN_FLOAT16X2(x) FFX_MIN16_F2(FFX_MIN16_F(x))




#define FFX_BROADCAST_MIN_FLOAT16X3(x) FFX_MIN16_F3(FFX_MIN16_F(x))




#define FFX_BROADCAST_MIN_FLOAT16X4(x) FFX_MIN16_F4(FFX_MIN16_F(x))




#define FFX_BROADCAST_MIN_UINT16(x)   FFX_MIN16_U(x)




#define FFX_BROADCAST_MIN_UINT16X2(x) FFX_MIN16_U2(FFX_MIN16_U(x))




#define FFX_BROADCAST_MIN_UINT16X3(x) FFX_MIN16_U3(FFX_MIN16_U(x))




#define FFX_BROADCAST_MIN_UINT16X4(x) FFX_MIN16_U4(FFX_MIN16_U(x))




#define FFX_BROADCAST_MIN_INT16(x)   FFX_MIN16_I(x)




#define FFX_BROADCAST_MIN_INT16X2(x) FFX_MIN16_I2(FFX_MIN16_I(x))




#define FFX_BROADCAST_MIN_INT16X3(x) FFX_MIN16_I3(FFX_MIN16_I(x))




#define FFX_BROADCAST_MIN_INT16X4(x) FFX_MIN16_I4(FFX_MIN16_I(x))

#if !defined(FFX_SKIP_EXT)
#if FFX_HALF
    #extension GL_EXT_shader_16bit_storage : require
    #extension GL_EXT_shader_explicit_arithmetic_types : require
#endif 

#if defined(FFX_LONG)
    #extension GL_ARB_gpu_shader_int64 : require
    #extension GL_NV_shader_atomic_int64 : require
#endif 

#if defined(FFX_WAVE)
    #extension GL_KHR_shader_subgroup_arithmetic : require
    #extension GL_KHR_shader_subgroup_ballot : require
    #extension GL_KHR_shader_subgroup_quad : require
    #extension GL_KHR_shader_subgroup_shuffle : require
#endif 
#endif 


FfxFloat32   ffxSqrt(FfxFloat32 x);
FfxFloat32x2 ffxSqrt(FfxFloat32x2 x);
FfxFloat32x3 ffxSqrt(FfxFloat32x3 x);
FfxFloat32x4 ffxSqrt(FfxFloat32x4 x);









FfxFloat32 ffxAsFloat(FfxUInt32 x)
{
    return uintBitsToFloat(x);
}









FfxFloat32x2 ffxAsFloat(FfxUInt32x2 x)
{
    return uintBitsToFloat(x);
}









FfxFloat32x3 ffxAsFloat(FfxUInt32x3 x)
{
    return uintBitsToFloat(x);
}









FfxFloat32x4 ffxAsFloat(FfxUInt32x4 x)
{
    return uintBitsToFloat(x);
}









FfxUInt32 ffxAsUInt32(FfxFloat32 x)
{
    return floatBitsToUint(x);
}









FfxUInt32x2 ffxAsUInt32(FfxFloat32x2 x)
{
    return floatBitsToUint(x);
}









FfxUInt32x3 ffxAsUInt32(FfxFloat32x3 x)
{
    return floatBitsToUint(x);
}









FfxUInt32x4 ffxAsUInt32(FfxFloat32x4 x)
{
    return floatBitsToUint(x);
}









FfxUInt32 f32tof16(FfxFloat32 value)
{
    return packHalf2x16(FfxFloat32x2(value, 0.0));
}









FfxFloat32x2 ffxBroadcast2(FfxFloat32 value)
{
    return FfxFloat32x2(value, value);
}









FfxFloat32x3 ffxBroadcast3(FfxFloat32 value)
{
    return FfxFloat32x3(value, value, value);
}









FfxFloat32x4 ffxBroadcast4(FfxFloat32 value)
{
    return FfxFloat32x4(value, value, value, value);
}









FfxInt32x2 ffxBroadcast2(FfxInt32 value)
{
    return FfxInt32x2(value, value);
}









FfxInt32x3 ffxBroadcast3(FfxInt32 value)
{
    return FfxInt32x3(value, value, value);
}









FfxInt32x4 ffxBroadcast4(FfxInt32 value)
{
    return FfxInt32x4(value, value, value, value);
}









FfxUInt32x2 ffxBroadcast2(FfxUInt32 value)
{
    return FfxUInt32x2(value, value);
}









FfxUInt32x3 ffxBroadcast3(FfxUInt32 value)
{
    return FfxUInt32x3(value, value, value);
}









FfxUInt32x4 ffxBroadcast4(FfxUInt32 value)
{
    return FfxUInt32x4(value, value, value, value);
}




FfxUInt32 bitfieldExtract(FfxUInt32 src, FfxUInt32 off, FfxUInt32 bits)
{
    return bitfieldExtract(src, FfxInt32(off), FfxInt32(bits));
}




FfxUInt32 bitfieldInsert(FfxUInt32 src, FfxUInt32 ins, FfxUInt32 mask)
{
    return (ins & mask) | (src & (~mask));
}





FfxUInt32 bitfieldInsertMask(FfxUInt32 src, FfxUInt32 ins, FfxUInt32 bits)
{
    return bitfieldInsert(src, ins, 0, FfxInt32(bits));
}
)<!>" R"<!>(















FfxFloat32 ffxLerp(FfxFloat32 x, FfxFloat32 y, FfxFloat32 t)
{
    return mix(x, y, t);
}
















FfxFloat32x2 ffxLerp(FfxFloat32x2 x, FfxFloat32x2 y, FfxFloat32 t)
{
    return mix(x, y, t);
}
















FfxFloat32x2 ffxLerp(FfxFloat32x2 x, FfxFloat32x2 y, FfxFloat32x2 t)
{
    return mix(x, y, t);
}
















FfxFloat32x3 ffxLerp(FfxFloat32x3 x, FfxFloat32x3 y, FfxFloat32 t)
{
    return mix(x, y, t);
}
















FfxFloat32x3 ffxLerp(FfxFloat32x3 x, FfxFloat32x3 y, FfxFloat32x3 t)
{
    return mix(x, y, t);
}
















FfxFloat32x4 ffxLerp(FfxFloat32x4 x, FfxFloat32x4 y, FfxFloat32 t)
{
    return mix(x, y, t);
}
















FfxFloat32x4 ffxLerp(FfxFloat32x4 x, FfxFloat32x4 y, FfxFloat32x4 t)
{
    return mix(x, y, t);
}














FfxFloat32 ffxMax3(FfxFloat32 x, FfxFloat32 y, FfxFloat32 z)
{
    return max(x, max(y, z));
}














FfxFloat32x2 ffxMax3(FfxFloat32x2 x, FfxFloat32x2 y, FfxFloat32x2 z)
{
    return max(x, max(y, z));
}














FfxFloat32x3 ffxMax3(FfxFloat32x3 x, FfxFloat32x3 y, FfxFloat32x3 z)
{
    return max(x, max(y, z));
}














FfxFloat32x4 ffxMax3(FfxFloat32x4 x, FfxFloat32x4 y, FfxFloat32x4 z)
{
    return max(x, max(y, z));
}














FfxUInt32 ffxMax3(FfxUInt32 x, FfxUInt32 y, FfxUInt32 z)
{
    return max(x, max(y, z));
}














FfxUInt32x2 ffxMax3(FfxUInt32x2 x, FfxUInt32x2 y, FfxUInt32x2 z)
{
    return max(x, max(y, z));
}














FfxUInt32x3 ffxMax3(FfxUInt32x3 x, FfxUInt32x3 y, FfxUInt32x3 z)
{
    return max(x, max(y, z));
}














FfxUInt32x4 ffxMax3(FfxUInt32x4 x, FfxUInt32x4 y, FfxUInt32x4 z)
{
    return max(x, max(y, z));
}














FfxFloat32 ffxMed3(FfxFloat32 x, FfxFloat32 y, FfxFloat32 z)
{
    return max(min(x, y), min(max(x, y), z));
}














FfxFloat32x2 ffxMed3(FfxFloat32x2 x, FfxFloat32x2 y, FfxFloat32x2 z)
{
    return max(min(x, y), min(max(x, y), z));
}














FfxFloat32x3 ffxMed3(FfxFloat32x3 x, FfxFloat32x3 y, FfxFloat32x3 z)
{
    return max(min(x, y), min(max(x, y), z));
}














FfxFloat32x4 ffxMed3(FfxFloat32x4 x, FfxFloat32x4 y, FfxFloat32x4 z)
{
    return max(min(x, y), min(max(x, y), z));
}














FfxInt32 ffxMed3(FfxInt32 x, FfxInt32 y, FfxInt32 z)
{
    return max(min(x, y), min(max(x, y), z));
}














FfxInt32x2 ffxMed3(FfxInt32x2 x, FfxInt32x2 y, FfxInt32x2 z)
{
    return max(min(x, y), min(max(x, y), z));
}














FfxInt32x3 ffxMed3(FfxInt32x3 x, FfxInt32x3 y, FfxInt32x3 z)
{
    return max(min(x, y), min(max(x, y), z));
}














FfxInt32x4 ffxMed3(FfxInt32x4 x, FfxInt32x4 y, FfxInt32x4 z)
{
    return max(min(x, y), min(max(x, y), z));
}















FfxFloat32 ffxMin3(FfxFloat32 x, FfxFloat32 y, FfxFloat32 z)
{
    return min(x, min(y, z));
}














FfxFloat32x2 ffxMin3(FfxFloat32x2 x, FfxFloat32x2 y, FfxFloat32x2 z)
{
    return min(x, min(y, z));
}














FfxFloat32x3 ffxMin3(FfxFloat32x3 x, FfxFloat32x3 y, FfxFloat32x3 z)
{
    return min(x, min(y, z));
}














FfxFloat32x4 ffxMin3(FfxFloat32x4 x, FfxFloat32x4 y, FfxFloat32x4 z)
{
    return min(x, min(y, z));
}














FfxUInt32 ffxMin3(FfxUInt32 x, FfxUInt32 y, FfxUInt32 z)
{
    return min(x, min(y, z));
}














FfxUInt32x2 ffxMin3(FfxUInt32x2 x, FfxUInt32x2 y, FfxUInt32x2 z)
{
    return min(x, min(y, z));
}














FfxUInt32x3 ffxMin3(FfxUInt32x3 x, FfxUInt32x3 y, FfxUInt32x3 z)
{
    return min(x, min(y, z));
}














FfxUInt32x4 ffxMin3(FfxUInt32x4 x, FfxUInt32x4 y, FfxUInt32x4 z)
{
    return min(x, min(y, z));
}











FfxFloat32 rcp(FfxFloat32 x)
{
    return FfxFloat32(1.0) / x;
}











FfxFloat32x2 rcp(FfxFloat32x2 x)
{
    return ffxBroadcast2(1.0) / x;
}











FfxFloat32x3 rcp(FfxFloat32x3 x)
{
    return ffxBroadcast3(1.0) / x;
}











FfxFloat32x4 rcp(FfxFloat32x4 x)
{
    return ffxBroadcast4(1.0) / x;
}











FfxFloat32 rsqrt(FfxFloat32 x)
{
    return FfxFloat32(1.0) / ffxSqrt(x);
}











FfxFloat32x2 rsqrt(FfxFloat32x2 x)
{
    return ffxBroadcast2(1.0) / ffxSqrt(x);
}











FfxFloat32x3 rsqrt(FfxFloat32x3 x)
{
    return ffxBroadcast3(1.0) / ffxSqrt(x);
}











FfxFloat32x4 rsqrt(FfxFloat32x4 x)
{
    return ffxBroadcast4(1.0) / ffxSqrt(x);
}









FfxFloat32 ffxSaturate(FfxFloat32 x)
{
    return clamp(x, FfxFloat32(0.0), FfxFloat32(1.0));
}









FfxFloat32x2 ffxSaturate(FfxFloat32x2 x)
{
    return clamp(x, ffxBroadcast2(0.0), ffxBroadcast2(1.0));
}









FfxFloat32x3 ffxSaturate(FfxFloat32x3 x)
{
    return clamp(x, ffxBroadcast3(0.0), ffxBroadcast3(1.0));
}









FfxFloat32x4 ffxSaturate(FfxFloat32x4 x)
{
    return clamp(x, ffxBroadcast4(0.0), ffxBroadcast4(1.0));
}















FfxFloat32 ffxFract(FfxFloat32 x)
{
    return fract(x);
}















FfxFloat32x2 ffxFract(FfxFloat32x2 x)
{
    return fract(x);
}















FfxFloat32x3 ffxFract(FfxFloat32x3 x)
{
    return fract(x);
}















FfxFloat32x4 ffxFract(FfxFloat32x4 x)
{
    return fract(x);
}

FfxUInt32 AShrSU1(FfxUInt32 a, FfxUInt32 b)
{
    return FfxUInt32(FfxInt32(a) >> FfxInt32(b));
}

#if FFX_HALF

#define FFX_UINT32_TO_FLOAT16X2(x) unpackFloat2x16(FfxUInt32(x))

FfxFloat16x4 ffxUint32x2ToFloat16x4(FfxUInt32x2 x)
{
    return FfxFloat16x4(unpackFloat2x16(x.x), unpackFloat2x16(x.y));
}
#define FFX_UINT32X2_TO_FLOAT16X4(x) ffxUint32x2ToFloat16x4(FfxUInt32x2(x))
#define FFX_UINT32_TO_UINT16X2(x) unpackUint2x16(FfxUInt32(x))
#define FFX_UINT32X2_TO_UINT16X4(x) unpackUint4x16(pack64(FfxUInt32x2(x)))

#define FFX_FLOAT16X2_TO_UINT32(x) packFloat2x16(FfxFloat16x2(x))
FfxUInt32x2 ffxFloat16x4ToUint32x2(FfxFloat16x4 x)
{
    return FfxUInt32x2(packFloat2x16(x.xy), packFloat2x16(x.zw));
}
#define FFX_FLOAT16X4_TO_UINT32X2(x) ffxFloat16x4ToUint32x2(FfxFloat16x4(x))
#define FFX_UINT16X2_TO_UINT32(x) packUint2x16(FfxUInt16x2(x))
#define FFX_UINT16X4_TO_UINT32X2(x) unpack32(packUint4x16(FfxUInt16x4(x)))

#define FFX_TO_UINT16(x) halfBitsToUint16(FfxFloat16(x))
#define FFX_TO_UINT16X2(x) halfBitsToUint16(FfxFloat16x2(x))
#define FFX_TO_UINT16X3(x) halfBitsToUint16(FfxFloat16x3(x))
#define FFX_TO_UINT16X4(x) halfBitsToUint16(FfxFloat16x4(x))

#define FFX_TO_FLOAT16(x) uint16BitsToHalf(FfxUInt16(x))
#define FFX_TO_FLOAT16X2(x) uint16BitsToHalf(FfxUInt16x2(x))
#define FFX_TO_FLOAT16X3(x) uint16BitsToHalf(FfxUInt16x3(x))
#define FFX_TO_FLOAT16X4(x) uint16BitsToHalf(FfxUInt16x4(x))

FfxFloat16 ffxBroadcastFloat16(FfxFloat16 a)
{
    return FfxFloat16(a);
}
FfxFloat16x2 ffxBroadcastFloat16x2(FfxFloat16 a)
{
    return FfxFloat16x2(a, a);
}
FfxFloat16x3 ffxBroadcastFloat16x3(FfxFloat16 a)
{
    return FfxFloat16x3(a, a, a);
}
FfxFloat16x4 ffxBroadcastFloat16x4(FfxFloat16 a)
{
    return FfxFloat16x4(a, a, a, a);
}
#define FFX_BROADCAST_FLOAT16(a)   FfxFloat16(a)
#define FFX_BROADCAST_FLOAT16X2(a) FfxFloat16x2(FfxFloat16(a))
#define FFX_BROADCAST_FLOAT16X3(a) FfxFloat16x3(FfxFloat16(a))
#define FFX_BROADCAST_FLOAT16X4(a) FfxFloat16x4(FfxFloat16(a))

FfxInt16 ffxBroadcastInt16(FfxInt16 a)
{
    return FfxInt16(a);
}
FfxInt16x2 ffxBroadcastInt16x2(FfxInt16 a)
{
    return FfxInt16x2(a, a);
}
FfxInt16x3 ffxBroadcastInt16x3(FfxInt16 a)
{
    return FfxInt16x3(a, a, a);
}
FfxInt16x4 ffxBroadcastInt16x4(FfxInt16 a)
{
    return FfxInt16x4(a, a, a, a);
}
#define FFX_BROADCAST_INT16(a)   FfxInt16(a)
#define FFX_BROADCAST_INT16X2(a) FfxInt16x2(FfxInt16(a))
#define FFX_BROADCAST_INT16X3(a) FfxInt16x3(FfxInt16(a))
#define FFX_BROADCAST_INT16X4(a) FfxInt16x4(FfxInt16(a))

FfxUInt16 ffxBroadcastUInt16(FfxUInt16 a)
{
    return FfxUInt16(a);
}
FfxUInt16x2 ffxBroadcastUInt16x2(FfxUInt16 a)
{
    return FfxUInt16x2(a, a);
}
FfxUInt16x3 ffxBroadcastUInt16x3(FfxUInt16 a)
{
    return FfxUInt16x3(a, a, a);
}
FfxUInt16x4 ffxBroadcastUInt16x4(FfxUInt16 a)
{
    return FfxUInt16x4(a, a, a, a);
}
#define FFX_BROADCAST_UINT16(a)   FfxUInt16(a)
#define FFX_BROADCAST_UINT16X2(a) FfxUInt16x2(FfxUInt16(a))
#define FFX_BROADCAST_UINT16X3(a) FfxUInt16x3(FfxUInt16(a))
#define FFX_BROADCAST_UINT16X4(a) FfxUInt16x4(FfxUInt16(a))

FfxUInt16 ffxAbsHalf(FfxUInt16 a)
{
    return FfxUInt16(abs(FfxInt16(a)));
}
FfxUInt16x2 ffxAbsHalf(FfxUInt16x2 a)
{
    return FfxUInt16x2(abs(FfxInt16x2(a)));
}
FfxUInt16x3 ffxAbsHalf(FfxUInt16x3 a)
{
    return FfxUInt16x3(abs(FfxInt16x3(a)));
}
FfxUInt16x4 ffxAbsHalf(FfxUInt16x4 a)
{
    return FfxUInt16x4(abs(FfxInt16x4(a)));
}

FfxFloat16 ffxClampHalf(FfxFloat16 x, FfxFloat16 n, FfxFloat16 m)
{
    return clamp(x, n, m);
}
FfxFloat16x2 ffxClampHalf(FfxFloat16x2 x, FfxFloat16x2 n, FfxFloat16x2 m)
{
    return clamp(x, n, m);
}
FfxFloat16x3 ffxClampHalf(FfxFloat16x3 x, FfxFloat16x3 n, FfxFloat16x3 m)
{
    return clamp(x, n, m);
}
FfxFloat16x4 ffxClampHalf(FfxFloat16x4 x, FfxFloat16x4 n, FfxFloat16x4 m)
{
    return clamp(x, n, m);
}

FfxFloat16 ffxFract(FfxFloat16 x)
{
    return fract(x);
}
FfxFloat16x2 ffxFract(FfxFloat16x2 x)
{
    return fract(x);
}
FfxFloat16x3 ffxFract(FfxFloat16x3 x)
{
    return fract(x);
}
FfxFloat16x4 ffxFract(FfxFloat16x4 x)
{
    return fract(x);
}

FfxFloat16 ffxLerp(FfxFloat16 x, FfxFloat16 y, FfxFloat16 a)
{
    return mix(x, y, a);
}
FfxFloat16x2 ffxLerp(FfxFloat16x2 x, FfxFloat16x2 y, FfxFloat16 a)
{
    return mix(x, y, a);
}
FfxFloat16x2 ffxLerp(FfxFloat16x2 x, FfxFloat16x2 y, FfxFloat16x2 a)
{
    return mix(x, y, a);
}
FfxFloat16x3 ffxLerp(FfxFloat16x3 x, FfxFloat16x3 y, FfxFloat16x3 a)
{
    return mix(x, y, a);
}
FfxFloat16x3 ffxLerp(FfxFloat16x3 x, FfxFloat16x3 y, FfxFloat16 a)
{
    return mix(x, y, a);
}
FfxFloat16x4 ffxLerp(FfxFloat16x4 x, FfxFloat16x4 y, FfxFloat16 a)
{
    return mix(x, y, a);
}
FfxFloat16x4 ffxLerp(FfxFloat16x4 x, FfxFloat16x4 y, FfxFloat16x4 a)
{
    return mix(x, y, a);
}


FfxFloat16 ffxMed3Half(FfxFloat16 x, FfxFloat16 y, FfxFloat16 z)
{
    return max(min(x, y), min(max(x, y), z));
}
FfxFloat16x2 ffxMed3Half(FfxFloat16x2 x, FfxFloat16x2 y, FfxFloat16x2 z)
{
    return max(min(x, y), min(max(x, y), z));
}
FfxFloat16x3 ffxMed3Half(FfxFloat16x3 x, FfxFloat16x3 y, FfxFloat16x3 z)
{
    return max(min(x, y), min(max(x, y), z));
}
FfxFloat16x4 ffxMed3Half(FfxFloat16x4 x, FfxFloat16x4 y, FfxFloat16x4 z)
{
    return max(min(x, y), min(max(x, y), z));
}
FfxInt16 ffxMed3Half(FfxInt16 x, FfxInt16 y, FfxInt16 z)
{
    return max(min(x, y), min(max(x, y), z));
}
FfxInt16x2 ffxMed3Half(FfxInt16x2 x, FfxInt16x2 y, FfxInt16x2 z)
{
    return max(min(x, y), min(max(x, y), z));
}
FfxInt16x3 ffxMed3Half(FfxInt16x3 x, FfxInt16x3 y, FfxInt16x3 z)
{
    return max(min(x, y), min(max(x, y), z));
}
FfxInt16x4 ffxMed3Half(FfxInt16x4 x, FfxInt16x4 y, FfxInt16x4 z)
{
    return max(min(x, y), min(max(x, y), z));
}


FfxFloat16 ffxMax3Half(FfxFloat16 x, FfxFloat16 y, FfxFloat16 z)
{
    return max(x, max(y, z));
}
FfxFloat16x2 ffxMax3Half(FfxFloat16x2 x, FfxFloat16x2 y, FfxFloat16x2 z)
{
    return max(x, max(y, z));
}
FfxFloat16x3 ffxMax3Half(FfxFloat16x3 x, FfxFloat16x3 y, FfxFloat16x3 z)
{
    return max(x, max(y, z));
}
FfxFloat16x4 ffxMax3Half(FfxFloat16x4 x, FfxFloat16x4 y, FfxFloat16x4 z)
{
    return max(x, max(y, z));
}


FfxFloat16 ffxMin3Half(FfxFloat16 x, FfxFloat16 y, FfxFloat16 z)
{
    return min(x, min(y, z));
}
FfxFloat16x2 ffxMin3Half(FfxFloat16x2 x, FfxFloat16x2 y, FfxFloat16x2 z)
{
    return min(x, min(y, z));
}
FfxFloat16x3 ffxMin3Half(FfxFloat16x3 x, FfxFloat16x3 y, FfxFloat16x3 z)
{
    return min(x, min(y, z));
}
FfxFloat16x4 ffxMin3Half(FfxFloat16x4 x, FfxFloat16x4 y, FfxFloat16x4 z)
{
    return min(x, min(y, z));
}

FfxFloat16 ffxReciprocalHalf(FfxFloat16 x)
{
    return FFX_BROADCAST_FLOAT16(1.0) / x;
}
FfxFloat16x2 ffxReciprocalHalf(FfxFloat16x2 x)
{
    return FFX_BROADCAST_FLOAT16X2(1.0) / x;
}
FfxFloat16x3 ffxReciprocalHalf(FfxFloat16x3 x)
{
    return FFX_BROADCAST_FLOAT16X3(1.0) / x;
}
FfxFloat16x4 ffxReciprocalHalf(FfxFloat16x4 x)
{
    return FFX_BROADCAST_FLOAT16X4(1.0) / x;
}

FfxFloat16 ffxReciprocalSquareRootHalf(FfxFloat16 x)
{
    return FFX_BROADCAST_FLOAT16(1.0) / sqrt(x);
}
FfxFloat16x2 ffxReciprocalSquareRootHalf(FfxFloat16x2 x)
{
    return FFX_BROADCAST_FLOAT16X2(1.0) / sqrt(x);
}
FfxFloat16x3 ffxReciprocalSquareRootHalf(FfxFloat16x3 x)
{
    return FFX_BROADCAST_FLOAT16X3(1.0) / sqrt(x);
}
FfxFloat16x4 ffxReciprocalSquareRootHalf(FfxFloat16x4 x)
{
    return FFX_BROADCAST_FLOAT16X4(1.0) / sqrt(x);
}

FfxFloat16 ffxSaturate(FfxFloat16 x)
{
    return clamp(x, FFX_BROADCAST_FLOAT16(0.0), FFX_BROADCAST_FLOAT16(1.0));
}
FfxFloat16x2 ffxSaturate(FfxFloat16x2 x)
{
    return clamp(x, FFX_BROADCAST_FLOAT16X2(0.0), FFX_BROADCAST_FLOAT16X2(1.0));
}
FfxFloat16x3 ffxSaturate(FfxFloat16x3 x)
{
    return clamp(x, FFX_BROADCAST_FLOAT16X3(0.0), FFX_BROADCAST_FLOAT16X3(1.0));
}
FfxFloat16x4 ffxSaturate(FfxFloat16x4 x)
{
    return clamp(x, FFX_BROADCAST_FLOAT16X4(0.0), FFX_BROADCAST_FLOAT16X4(1.0));
}

FfxUInt16 ffxBitShiftRightHalf(FfxUInt16 a, FfxUInt16 b)
{
    return FfxUInt16(FfxInt16(a) >> FfxInt16(b));
}
FfxUInt16x2 ffxBitShiftRightHalf(FfxUInt16x2 a, FfxUInt16x2 b)
{
    return FfxUInt16x2(FfxInt16x2(a) >> FfxInt16x2(b));
}
FfxUInt16x3 ffxBitShiftRightHalf(FfxUInt16x3 a, FfxUInt16x3 b)
{
    return FfxUInt16x3(FfxInt16x3(a) >> FfxInt16x3(b));
}
FfxUInt16x4 ffxBitShiftRightHalf(FfxUInt16x4 a, FfxUInt16x4 b)
{
    return FfxUInt16x4(FfxInt16x4(a) >> FfxInt16x4(b));
}
#endif 

#if defined(FFX_WAVE)

FfxFloat32 AWaveXorF1(FfxFloat32 v, FfxUInt32 x)
{
    return subgroupShuffleXor(v, x);
}
FfxFloat32x2 AWaveXorF2(FfxFloat32x2 v, FfxUInt32 x)
{
    return subgroupShuffleXor(v, x);
}
FfxFloat32x3 AWaveXorF3(FfxFloat32x3 v, FfxUInt32 x)
{
    return subgroupShuffleXor(v, x);
}
FfxFloat32x4 AWaveXorF4(FfxFloat32x4 v, FfxUInt32 x)
{
    return subgroupShuffleXor(v, x);
}
FfxUInt32 AWaveXorU1(FfxUInt32 v, FfxUInt32 x)
{
    return subgroupShuffleXor(v, x);
}
FfxUInt32x2 AWaveXorU2(FfxUInt32x2 v, FfxUInt32 x)
{
    return subgroupShuffleXor(v, x);
}
FfxUInt32x3 AWaveXorU3(FfxUInt32x3 v, FfxUInt32 x)
{
    return subgroupShuffleXor(v, x);
}
FfxUInt32x4 AWaveXorU4(FfxUInt32x4 v, FfxUInt32 x)
{
    return subgroupShuffleXor(v, x);
}


#if FFX_HALF
FfxFloat16x2 ffxWaveXorFloat16x2(FfxFloat16x2 v, FfxUInt32 x)
{
    return FFX_UINT32_TO_FLOAT16X2(subgroupShuffleXor(FFX_FLOAT16X2_TO_UINT32(v), x));
}
FfxFloat16x4 ffxWaveXorFloat16x4(FfxFloat16x4 v, FfxUInt32 x)
{
    return FFX_UINT32X2_TO_FLOAT16X4(subgroupShuffleXor(FFX_FLOAT16X4_TO_UINT32X2(v), x));
}
FfxUInt16x2 ffxWaveXorUint16x2(FfxUInt16x2 v, FfxUInt32 x)
{
    return FFX_UINT32_TO_UINT16X2(subgroupShuffleXor(FFX_UINT16X2_TO_UINT32(v), x));
}
FfxUInt16x4 ffxWaveXorUint16x4(FfxUInt16x4 v, FfxUInt32 x)
{
    return FFX_UINT32X2_TO_UINT16X4(subgroupShuffleXor(FFX_UINT16X4_TO_UINT32X2(v), x));
}
#endif 
#endif 
#endif // #if defined(FFX_GLSL) && defined(FFX_GPU)

#if defined(FFX_HLSL) && defined(FFX_GPU)
























#define FFX_GROUPSHARED groupshared




#define FFX_GROUP_MEMORY_BARRIER GroupMemoryBarrierWithGroupSync




#define FFX_STATIC static




#define FFX_UNROLL [unroll]




#define FFX_GREATER_THAN(x, y) x > y




#define FFX_GREATER_THAN_EQUAL(x, y) x >= y




#define FFX_LESS_THAN(x, y) x < y




#define FFX_LESS_THAN_EQUAL(x, y) x <= y




#define FFX_EQUAL(x, y) x == y




#define FFX_NOT_EQUAL(x, y) x != y




#define FFX_BROADCAST_FLOAT32(x) FfxFloat32(x)




#define FFX_BROADCAST_FLOAT32X2(x) FfxFloat32(x)




#define FFX_BROADCAST_FLOAT32X3(x) FfxFloat32(x)




#define FFX_BROADCAST_FLOAT32X4(x) FfxFloat32(x)




#define FFX_BROADCAST_UINT32(x) FfxUInt32(x)




#define FFX_BROADCAST_UINT32X2(x) FfxUInt32(x)




#define FFX_BROADCAST_UINT32X3(x) FfxUInt32(x)




#define FFX_BROADCAST_UINT32X4(x) FfxUInt32(x)




#define FFX_BROADCAST_INT32(x) FfxInt32(x)




#define FFX_BROADCAST_INT32X2(x) FfxInt32(x)




#define FFX_BROADCAST_INT32X3(x) FfxInt32(x)




#define FFX_BROADCAST_INT32X4(x) FfxInt32(x)




#define FFX_BROADCAST_MIN_FLOAT16(a)   FFX_MIN16_F(a)




#define FFX_BROADCAST_MIN_FLOAT16X2(a) FFX_MIN16_F(a)




#define FFX_BROADCAST_MIN_FLOAT16X3(a) FFX_MIN16_F(a)




#define FFX_BROADCAST_MIN_FLOAT16X4(a) FFX_MIN16_F(a)




#define FFX_BROADCAST_MIN_UINT16(a)   FFX_MIN16_U(a)




#define FFX_BROADCAST_MIN_UINT16X2(a) FFX_MIN16_U(a)




#define FFX_BROADCAST_MIN_UINT16X3(a) FFX_MIN16_U(a)




#define FFX_BROADCAST_MIN_UINT16X4(a) FFX_MIN16_U(a)



)<!>" R"<!>(
#define FFX_BROADCAST_MIN_INT16(a)   FFX_MIN16_I(a)




#define FFX_BROADCAST_MIN_INT16X2(a) FFX_MIN16_I(a)




#define FFX_BROADCAST_MIN_INT16X3(a) FFX_MIN16_I(a)




#define FFX_BROADCAST_MIN_INT16X4(a) FFX_MIN16_I(a)













FfxUInt32 packHalf2x16(FfxFloat32x2 value)
{
    return f32tof16(value.x) | (f32tof16(value.y) << 16);
}









FfxFloat32x2 ffxBroadcast2(FfxFloat32 value)
{
    return FfxFloat32x2(value, value);
}









FfxFloat32x3 ffxBroadcast3(FfxFloat32 value)
{
    return FfxFloat32x3(value, value, value);
}









FfxFloat32x4 ffxBroadcast4(FfxFloat32 value)
{
    return FfxFloat32x4(value, value, value, value);
}









FfxInt32x2 ffxBroadcast2(FfxInt32 value)
{
    return FfxInt32x2(value, value);
}









FfxUInt32x3 ffxBroadcast3(FfxInt32 value)
{
    return FfxUInt32x3(value, value, value);
}









FfxInt32x4 ffxBroadcast4(FfxInt32 value)
{
    return FfxInt32x4(value, value, value, value);
}









FfxUInt32x2 ffxBroadcast2(FfxUInt32 value)
{
    return FfxUInt32x2(value, value);
}









FfxUInt32x3 ffxBroadcast3(FfxUInt32 value)
{
    return FfxUInt32x3(value, value, value);
}









FfxUInt32x4 ffxBroadcast4(FfxUInt32 value)
{
    return FfxUInt32x4(value, value, value, value);
}

FfxUInt32 bitfieldExtract(FfxUInt32 src, FfxUInt32 off, FfxUInt32 bits)
{
    FfxUInt32 mask = (1u << bits) - 1;
    return (src >> off) & mask;
}

FfxUInt32 bitfieldInsert(FfxUInt32 src, FfxUInt32 ins, FfxUInt32 mask)
{
    return (ins & mask) | (src & (~mask));
}

FfxUInt32 bitfieldInsertMask(FfxUInt32 src, FfxUInt32 ins, FfxUInt32 bits)
{
    FfxUInt32 mask = (1u << bits) - 1;
    return (ins & mask) | (src & (~mask));
}









FfxUInt32 ffxAsUInt32(FfxFloat32 x)
{
    return asuint(x);
}









FfxUInt32x2 ffxAsUInt32(FfxFloat32x2 x)
{
    return asuint(x);
}









FfxUInt32x3 ffxAsUInt32(FfxFloat32x3 x)
{
    return asuint(x);
}









FfxUInt32x4 ffxAsUInt32(FfxFloat32x4 x)
{
    return asuint(x);
}









FfxFloat32 ffxAsFloat(FfxUInt32 x)
{
    return asfloat(x);
}









FfxFloat32x2 ffxAsFloat(FfxUInt32x2 x)
{
    return asfloat(x);
}









FfxFloat32x3 ffxAsFloat(FfxUInt32x3 x)
{
    return asfloat(x);
}









FfxFloat32x4 ffxAsFloat(FfxUInt32x4 x)
{
    return asfloat(x);
}
















FfxFloat32 ffxLerp(FfxFloat32 x, FfxFloat32 y, FfxFloat32 t)
{
    return lerp(x, y, t);
}
















FfxFloat32x2 ffxLerp(FfxFloat32x2 x, FfxFloat32x2 y, FfxFloat32 t)
{
    return lerp(x, y, t);
}
















FfxFloat32x2 ffxLerp(FfxFloat32x2 x, FfxFloat32x2 y, FfxFloat32x2 t)
{
    return lerp(x, y, t);
}
















FfxFloat32x3 ffxLerp(FfxFloat32x3 x, FfxFloat32x3 y, FfxFloat32 t)
{
    return lerp(x, y, t);
}
















FfxFloat32x3 ffxLerp(FfxFloat32x3 x, FfxFloat32x3 y, FfxFloat32x3 t)
{
    return lerp(x, y, t);
}
















FfxFloat32x4 ffxLerp(FfxFloat32x4 x, FfxFloat32x4 y, FfxFloat32 t)
{
    return lerp(x, y, t);
}
















FfxFloat32x4 ffxLerp(FfxFloat32x4 x, FfxFloat32x4 y, FfxFloat32x4 t)
{
    return lerp(x, y, t);
}









FfxFloat32 ffxSaturate(FfxFloat32 x)
{
    return saturate(x);
}









FfxFloat32x2 ffxSaturate(FfxFloat32x2 x)
{
    return saturate(x);
}









FfxFloat32x3 ffxSaturate(FfxFloat32x3 x)
{
    return saturate(x);
}









FfxFloat32x4 ffxSaturate(FfxFloat32x4 x)
{
    return saturate(x);
}















FfxFloat32 ffxFract(FfxFloat32 x)
{
    return x - floor(x);
}















FfxFloat32x2 ffxFract(FfxFloat32x2 x)
{
    return x - floor(x);
}















FfxFloat32x3 ffxFract(FfxFloat32x3 x)
{
    return x - floor(x);
}















FfxFloat32x4 ffxFract(FfxFloat32x4 x)
{
    return x - floor(x);
}













FfxFloat32 ffxMax3(FfxFloat32 x, FfxFloat32 y, FfxFloat32 z)
{
    return max(x, max(y, z));
}













FfxFloat32x2 ffxMax3(FfxFloat32x2 x, FfxFloat32x2 y, FfxFloat32x2 z)
{
    return max(x, max(y, z));
}













FfxFloat32x3 ffxMax3(FfxFloat32x3 x, FfxFloat32x3 y, FfxFloat32x3 z)
{
    return max(x, max(y, z));
}













FfxFloat32x4 ffxMax3(FfxFloat32x4 x, FfxFloat32x4 y, FfxFloat32x4 z)
{
    return max(x, max(y, z));
}













FfxUInt32 ffxMax3(FfxUInt32 x, FfxUInt32 y, FfxUInt32 z)
{
    return max(x, max(y, z));
}













FfxUInt32x2 ffxMax3(FfxUInt32x2 x, FfxUInt32x2 y, FfxUInt32x2 z)
{
    return max(x, max(y, z));
}













FfxUInt32x3 ffxMax3(FfxUInt32x3 x, FfxUInt32x3 y, FfxUInt32x3 z)
{
    return max(x, max(y, z));
}













FfxUInt32x4 ffxMax3(FfxUInt32x4 x, FfxUInt32x4 y, FfxUInt32x4 z)
{
    return max(x, max(y, z));
}













FfxFloat32 ffxMed3(FfxFloat32 x, FfxFloat32 y, FfxFloat32 z)
{
    return max(min(x, y), min(max(x, y), z));
}













FfxFloat32x2 ffxMed3(FfxFloat32x2 x, FfxFloat32x2 y, FfxFloat32x2 z)
{
    return max(min(x, y), min(max(x, y), z));
}













FfxFloat32x3 ffxMed3(FfxFloat32x3 x, FfxFloat32x3 y, FfxFloat32x3 z)
{
    return max(min(x, y), min(max(x, y), z));
}













FfxFloat32x4 ffxMed3(FfxFloat32x4 x, FfxFloat32x4 y, FfxFloat32x4 z)
{
    return max(min(x, y), min(max(x, y), z));
}













FfxInt32 ffxMed3(FfxInt32 x, FfxInt32 y, FfxInt32 z)
{
    return max(min(x, y), min(max(x, y), z));
    
    
}













FfxInt32x2 ffxMed3(FfxInt32x2 x, FfxInt32x2 y, FfxInt32x2 z)
{
    return max(min(x, y), min(max(x, y), z));
    
    
}













FfxInt32x3 ffxMed3(FfxInt32x3 x, FfxInt32x3 y, FfxInt32x3 z)
{
    return max(min(x, y), min(max(x, y), z));
}













FfxInt32x4 ffxMed3(FfxInt32x4 x, FfxInt32x4 y, FfxInt32x4 z)
{
    return max(min(x, y), min(max(x, y), z));
}













FfxFloat32 ffxMin3(FfxFloat32 x, FfxFloat32 y, FfxFloat32 z)
{
    return min(x, min(y, z));
}













FfxFloat32x2 ffxMin3(FfxFloat32x2 x, FfxFloat32x2 y, FfxFloat32x2 z)
{
    return min(x, min(y, z));
}













FfxFloat32x3 ffxMin3(FfxFloat32x3 x, FfxFloat32x3 y, FfxFloat32x3 z)
{
    return min(x, min(y, z));
}













FfxFloat32x4 ffxMin3(FfxFloat32x4 x, FfxFloat32x4 y, FfxFloat32x4 z)
{
    return min(x, min(y, z));
}













FfxUInt32 ffxMin3(FfxUInt32 x, FfxUInt32 y, FfxUInt32 z)
{
    return min(x, min(y, z));
}













FfxUInt32x2 ffxMin3(FfxUInt32x2 x, FfxUInt32x2 y, FfxUInt32x2 z)
{
    return min(x, min(y, z));
}













FfxUInt32x3 ffxMin3(FfxUInt32x3 x, FfxUInt32x3 y, FfxUInt32x3 z)
{
    return min(x, min(y, z));
}













FfxUInt32x4 ffxMin3(FfxUInt32x4 x, FfxUInt32x4 y, FfxUInt32x4 z)
{
    return min(x, min(y, z));
}


FfxUInt32 AShrSU1(FfxUInt32 a, FfxUInt32 b)
{
    return FfxUInt32(FfxInt32(a) >> FfxInt32(b));
}




#if FFX_HALF




FFX_MIN16_F2 ffxUint32ToFloat16x2(FfxUInt32 x)
{
	FfxFloat32x2 t = f16tof32(FfxUInt32x2(x & 0xFFFF, x >> 16));
	return FFX_MIN16_F2(t);
}
FFX_MIN16_F4 ffxUint32x2ToFloat16x4(FfxUInt32x2 x)
{
	return FFX_MIN16_F4(ffxUint32ToFloat16x2(x.x), ffxUint32ToFloat16x2(x.y));
}
FFX_MIN16_U2 ffxUint32ToUint16x2(FfxUInt32 x)
{
	FfxUInt32x2 t = FfxUInt32x2(x & 0xFFFF, x >> 16);
	return FFX_MIN16_U2(t);
}
FFX_MIN16_U4 ffxUint32x2ToUint16x4(FfxUInt32x2 x)
{
	return FFX_MIN16_U4(ffxUint32ToUint16x2(x.x), ffxUint32ToUint16x2(x.y));
}
#define FFX_UINT32_TO_FLOAT16X2(x) ffxUint32ToFloat16x2(FfxUInt32(x))
#define FFX_UINT32X2_TO_FLOAT16X4(x) ffxUint32x2ToFloat16x4(FfxUInt32x2(x))
#define FFX_UINT32_TO_UINT16X2(x) ffxUint32ToUint16x2(FfxUInt32(x))
#define FFX_UINT32X2_TO_UINT16X4(x) ffxUint32x2ToUint16x4(FfxUInt32x2(x))

FfxUInt32 FFX_MIN16_F2ToUint32(FFX_MIN16_F2 x)
{
	return f32tof16(x.x) + (f32tof16(x.y) << 16);
}
FfxUInt32x2 FFX_MIN16_F4ToUint32x2(FFX_MIN16_F4 x)
{
	return FfxUInt32x2(FFX_MIN16_F2ToUint32(x.xy), FFX_MIN16_F2ToUint32(x.zw));
}
FfxUInt32 FFX_MIN16_U2ToUint32(FFX_MIN16_U2 x)
{
	return FfxUInt32(x.x) + (FfxUInt32(x.y) << 16);
}
FfxUInt32x2 FFX_MIN16_U4ToUint32x2(FFX_MIN16_U4 x)
{
	return FfxUInt32x2(FFX_MIN16_U2ToUint32(x.xy), FFX_MIN16_U2ToUint32(x.zw));
}
#define FFX_FLOAT16X2_TO_UINT32(x) FFX_MIN16_F2ToUint32(FFX_MIN16_F2(x))
#define FFX_FLOAT16X4_TO_UINT32X2(x) FFX_MIN16_F4ToUint32x2(FFX_MIN16_F4(x))
#define FFX_UINT16X2_TO_UINT32(x) FFX_MIN16_U2ToUint32(FFX_MIN16_U2(x))
#define FFX_UINT16X4_TO_UINT32X2(x) FFX_MIN16_U4ToUint32x2(FFX_MIN16_U4(x))

#if defined(FFX_HLSL_6_2) && !defined(FFX_NO_16_BIT_CAST)
#define FFX_TO_UINT16(x) asuint16(x)
#define FFX_TO_UINT16X2(x) asuint16(x)
#define FFX_TO_UINT16X3(x) asuint16(x)
#define FFX_TO_UINT16X4(x) asuint16(x)
#else
#define FFX_TO_UINT16(a) FFX_MIN16_U(f32tof16(FfxFloat32(a)))
#define FFX_TO_UINT16X2(a) FFX_MIN16_U2(FFX_TO_UINT16((a).x), FFX_TO_UINT16((a).y))
#define FFX_TO_UINT16X3(a) FFX_MIN16_U3(FFX_TO_UINT16((a).x), FFX_TO_UINT16((a).y), FFX_TO_UINT16((a).z))
#define FFX_TO_UINT16X4(a) FFX_MIN16_U4(FFX_TO_UINT16((a).x), FFX_TO_UINT16((a).y), FFX_TO_UINT16((a).z), FFX_TO_UINT16((a).w))
#endif 

#if defined(FFX_HLSL_6_2) && !defined(FFX_NO_16_BIT_CAST)
#define FFX_TO_FLOAT16(x) asfloat16(x)
#define FFX_TO_FLOAT16X2(x) asfloat16(x)
#define FFX_TO_FLOAT16X3(x) asfloat16(x)
#define FFX_TO_FLOAT16X4(x) asfloat16(x)
#else
#define FFX_TO_FLOAT16(a) FFX_MIN16_F(f16tof32(FfxUInt32(a)))
#define FFX_TO_FLOAT16X2(a) FFX_MIN16_F2(FFX_TO_FLOAT16((a).x), FFX_TO_FLOAT16((a).y))
#define FFX_TO_FLOAT16X3(a) FFX_MIN16_F3(FFX_TO_FLOAT16((a).x), FFX_TO_FLOAT16((a).y), FFX_TO_FLOAT16((a).z))
#define FFX_TO_FLOAT16X4(a) FFX_MIN16_F4(FFX_TO_FLOAT16((a).x), FFX_TO_FLOAT16((a).y), FFX_TO_FLOAT16((a).z), FFX_TO_FLOAT16((a).w))
#endif 


#define FFX_BROADCAST_FLOAT16(a)   FFX_MIN16_F(a)
#define FFX_BROADCAST_FLOAT16X2(a) FFX_MIN16_F(a)
#define FFX_BROADCAST_FLOAT16X3(a) FFX_MIN16_F(a)
#define FFX_BROADCAST_FLOAT16X4(a) FFX_MIN16_F(a)


#define FFX_BROADCAST_INT16(a)   FFX_MIN16_I(a)
#define FFX_BROADCAST_INT16X2(a) FFX_MIN16_I(a)
#define FFX_BROADCAST_INT16X3(a) FFX_MIN16_I(a)
#define FFX_BROADCAST_INT16X4(a) FFX_MIN16_I(a)


#define FFX_BROADCAST_UINT16(a)   FFX_MIN16_U(a)
#define FFX_BROADCAST_UINT16X2(a) FFX_MIN16_U(a)
#define FFX_BROADCAST_UINT16X3(a) FFX_MIN16_U(a)
#define FFX_BROADCAST_UINT16X4(a) FFX_MIN16_U(a)


FFX_MIN16_U ffxAbsHalf(FFX_MIN16_U a)
{
	return FFX_MIN16_U(abs(FFX_MIN16_I(a)));
}
FFX_MIN16_U2 ffxAbsHalf(FFX_MIN16_U2 a)
{
	return FFX_MIN16_U2(abs(FFX_MIN16_I2(a)));
}
FFX_MIN16_U3 ffxAbsHalf(FFX_MIN16_U3 a)
{
	return FFX_MIN16_U3(abs(FFX_MIN16_I3(a)));
}
FFX_MIN16_U4 ffxAbsHalf(FFX_MIN16_U4 a)
{
	return FFX_MIN16_U4(abs(FFX_MIN16_I4(a)));
}

FFX_MIN16_F ffxClampHalf(FFX_MIN16_F x, FFX_MIN16_F n, FFX_MIN16_F m)
{
	return max(n, min(x, m));
}
FFX_MIN16_F2 ffxClampHalf(FFX_MIN16_F2 x, FFX_MIN16_F2 n, FFX_MIN16_F2 m)
{
	return max(n, min(x, m));
}
FFX_MIN16_F3 ffxClampHalf(FFX_MIN16_F3 x, FFX_MIN16_F3 n, FFX_MIN16_F3 m)
{
	return max(n, min(x, m));
}
FFX_MIN16_F4 ffxClampHalf(FFX_MIN16_F4 x, FFX_MIN16_F4 n, FFX_MIN16_F4 m)
{
	return max(n, min(x, m));
}


FFX_MIN16_F ffxFract(FFX_MIN16_F x)
{
	return x - floor(x);
}
FFX_MIN16_F2 ffxFract(FFX_MIN16_F2 x)
{
	return x - floor(x);
}
FFX_MIN16_F3 ffxFract(FFX_MIN16_F3 x)
{
	return x - floor(x);
}
FFX_MIN16_F4 ffxFract(FFX_MIN16_F4 x)
{
	return x - floor(x);
}

FFX_MIN16_F ffxLerp(FFX_MIN16_F x, FFX_MIN16_F y, FFX_MIN16_F a)
{
	return lerp(x, y, a);
}
FFX_MIN16_F2 ffxLerp(FFX_MIN16_F2 x, FFX_MIN16_F2 y, FFX_MIN16_F a)
{
	return lerp(x, y, a);
}
FFX_MIN16_F2 ffxLerp(FFX_MIN16_F2 x, FFX_MIN16_F2 y, FFX_MIN16_F2 a)
{
	return lerp(x, y, a);
}
FFX_MIN16_F3 ffxLerp(FFX_MIN16_F3 x, FFX_MIN16_F3 y, FFX_MIN16_F a)
{
	return lerp(x, y, a);
}
FFX_MIN16_F3 ffxLerp(FFX_MIN16_F3 x, FFX_MIN16_F3 y, FFX_MIN16_F3 a)
{
	return lerp(x, y, a);
}
FFX_MIN16_F4 ffxLerp(FFX_MIN16_F4 x, FFX_MIN16_F4 y, FFX_MIN16_F a)
{
	return lerp(x, y, a);
}
FFX_MIN16_F4 ffxLerp(FFX_MIN16_F4 x, FFX_MIN16_F4 y, FFX_MIN16_F4 a)
{
	return lerp(x, y, a);
}

FFX_MIN16_F ffxMax3Half(FFX_MIN16_F x, FFX_MIN16_F y, FFX_MIN16_F z)
{
	return max(x, max(y, z));
}
FFX_MIN16_F2 ffxMax3Half(FFX_MIN16_F2 x, FFX_MIN16_F2 y, FFX_MIN16_F2 z)
{
	return max(x, max(y, z));
}
FFX_MIN16_F3 ffxMax3Half(FFX_MIN16_F3 x, FFX_MIN16_F3 y, FFX_MIN16_F3 z)
{
	return max(x, max(y, z));
}
FFX_MIN16_F4 ffxMax3Half(FFX_MIN16_F4 x, FFX_MIN16_F4 y, FFX_MIN16_F4 z)
{
	return max(x, max(y, z));
}

FFX_MIN16_F ffxMin3Half(FFX_MIN16_F x, FFX_MIN16_F y, FFX_MIN16_F z)
{
	return min(x, min(y, z));
}
FFX_MIN16_F2 ffxMin3Half(FFX_MIN16_F2 x, FFX_MIN16_F2 y, FFX_MIN16_F2 z)
{
	return min(x, min(y, z));
}
FFX_MIN16_F3 ffxMin3Half(FFX_MIN16_F3 x, FFX_MIN16_F3 y, FFX_MIN16_F3 z)
{
	return min(x, min(y, z));
}
FFX_MIN16_F4 ffxMin3Half(FFX_MIN16_F4 x, FFX_MIN16_F4 y, FFX_MIN16_F4 z)
{
	return min(x, min(y, z));
}

FFX_MIN16_F ffxMed3Half(FFX_MIN16_F x, FFX_MIN16_F y, FFX_MIN16_F z)
{
    return max(min(x, y), min(max(x, y), z));
}
FFX_MIN16_F2 ffxMed3Half(FFX_MIN16_F2 x, FFX_MIN16_F2 y, FFX_MIN16_F2 z)
{
    return max(min(x, y), min(max(x, y), z));
}
FFX_MIN16_F3 ffxMed3Half(FFX_MIN16_F3 x, FFX_MIN16_F3 y, FFX_MIN16_F3 z)
{
    return max(min(x, y), min(max(x, y), z));
}
FFX_MIN16_F4 ffxMed3Half(FFX_MIN16_F4 x, FFX_MIN16_F4 y, FFX_MIN16_F4 z)
{
    return max(min(x, y), min(max(x, y), z));
}

FFX_MIN16_I ffxMed3Half(FFX_MIN16_I x, FFX_MIN16_I y, FFX_MIN16_I z)
{
    return max(min(x, y), min(max(x, y), z));
}
FFX_MIN16_I2 ffxMed3Half(FFX_MIN16_I2 x, FFX_MIN16_I2 y, FFX_MIN16_I2 z)
{
    return max(min(x, y), min(max(x, y), z));
}
FFX_MIN16_I3 ffxMed3Half(FFX_MIN16_I3 x, FFX_MIN16_I3 y, FFX_MIN16_I3 z)
{
    return max(min(x, y), min(max(x, y), z));
}
FFX_MIN16_I4 ffxMed3Half(FFX_MIN16_I4 x, FFX_MIN16_I4 y, FFX_MIN16_I4 z)
{
    return max(min(x, y), min(max(x, y), z));
}

FFX_MIN16_F ffxReciprocalHalf(FFX_MIN16_F x)
{
	return rcp(x);
}
FFX_MIN16_F2 ffxReciprocalHalf(FFX_MIN16_F2 x)
{
	return rcp(x);
}
FFX_MIN16_F3 ffxReciprocalHalf(FFX_MIN16_F3 x)
{
	return rcp(x);
}
FFX_MIN16_F4 ffxReciprocalHalf(FFX_MIN16_F4 x)
{
	return rcp(x);
}

FFX_MIN16_F ffxReciprocalSquareRootHalf(FFX_MIN16_F x)
{
	return rsqrt(x);
}
FFX_MIN16_F2 ffxReciprocalSquareRootHalf(FFX_MIN16_F2 x)
{
	return rsqrt(x);
}
FFX_MIN16_F3 ffxReciprocalSquareRootHalf(FFX_MIN16_F3 x)
{
	return rsqrt(x);
}
FFX_MIN16_F4 ffxReciprocalSquareRootHalf(FFX_MIN16_F4 x)
{
	return rsqrt(x);
}

FFX_MIN16_F ffxSaturate(FFX_MIN16_F x)
{
	return saturate(x);
}
FFX_MIN16_F2 ffxSaturate(FFX_MIN16_F2 x)
{
	return saturate(x);
}
FFX_MIN16_F3 ffxSaturate(FFX_MIN16_F3 x)
{
	return saturate(x);
}
FFX_MIN16_F4 ffxSaturate(FFX_MIN16_F4 x)
{
	return saturate(x);
}

FFX_MIN16_U ffxBitShiftRightHalf(FFX_MIN16_U a, FFX_MIN16_U b)
{
	return FFX_MIN16_U(FFX_MIN16_I(a) >> FFX_MIN16_I(b));
}
FFX_MIN16_U2 ffxBitShiftRightHalf(FFX_MIN16_U2 a, FFX_MIN16_U2 b)
{
	return FFX_MIN16_U2(FFX_MIN16_I2(a) >> FFX_MIN16_I2(b));
}
FFX_MIN16_U3 ffxBitShiftRightHalf(FFX_MIN16_U3 a, FFX_MIN16_U3 b)
{
	return FFX_MIN16_U3(FFX_MIN16_I3(a) >> FFX_MIN16_I3(b));
}
FFX_MIN16_U4 ffxBitShiftRightHalf(FFX_MIN16_U4 a, FFX_MIN16_U4 b)
{
	return FFX_MIN16_U4(FFX_MIN16_I4(a) >> FFX_MIN16_I4(b));
}
#endif 




#if defined(FFX_WAVE)

FfxFloat32 AWaveXorF1(FfxFloat32 v, FfxUInt32 x)
{
    return WaveReadLaneAt(v, WaveGetLaneIndex() ^ x);
}
FfxFloat32x2 AWaveXorF2(FfxFloat32x2 v, FfxUInt32 x)
{
    return WaveReadLaneAt(v, WaveGetLaneIndex() ^ x);
}
FfxFloat32x3 AWaveXorF3(FfxFloat32x3 v, FfxUInt32 x)
{
    return WaveReadLaneAt(v, WaveGetLaneIndex() ^ x);
}
FfxFloat32x4 AWaveXorF4(FfxFloat32x4 v, FfxUInt32 x)
{
    return WaveReadLaneAt(v, WaveGetLaneIndex() ^ x);
}
FfxUInt32 AWaveXorU1(FfxUInt32 v, FfxUInt32 x)
{
    return WaveReadLaneAt(v, WaveGetLaneIndex() ^ x);
}
FfxUInt32x2 AWaveXorU1(FfxUInt32x2 v, FfxUInt32 x)
{
    return WaveReadLaneAt(v, WaveGetLaneIndex() ^ x);
}
FfxUInt32x3 AWaveXorU1(FfxUInt32x3 v, FfxUInt32 x)
{
    return WaveReadLaneAt(v, WaveGetLaneIndex() ^ x);
}
FfxUInt32x4 AWaveXorU1(FfxUInt32x4 v, FfxUInt32 x)
{
    return WaveReadLaneAt(v, WaveGetLaneIndex() ^ x);
}
)<!>" R"<!>(
#if FFX_HALF
FfxFloat16x2 ffxWaveXorFloat16x2(FfxFloat16x2 v, FfxUInt32 x)
{
    return FFX_UINT32_TO_FLOAT16X2(WaveReadLaneAt(FFX_FLOAT16X2_TO_UINT32(v), WaveGetLaneIndex() ^ x));
}
FfxFloat16x4 ffxWaveXorFloat16x4(FfxFloat16x4 v, FfxUInt32 x)
{
    return FFX_UINT32X2_TO_FLOAT16X4(WaveReadLaneAt(FFX_FLOAT16X4_TO_UINT32X2(v), WaveGetLaneIndex() ^ x));
}
FfxUInt16x2 ffxWaveXorUint16x2(FfxUInt16x2 v, FfxUInt32 x)
{
    return FFX_UINT32_TO_UINT16X2(WaveReadLaneAt(FFX_UINT16X2_TO_UINT32(v), WaveGetLaneIndex() ^ x));
}
FfxUInt16x4 ffxWaveXorUint16x4(FfxUInt16x4 v, FfxUInt32 x)
{
    return AW4_FFX_UINT32(WaveReadLaneAt(FFX_UINT32_AW4(v), WaveGetLaneIndex() ^ x));
}
#endif 
#endif 
#endif // #if defined(FFX_HLSL) && defined(FFX_GPU)

#if defined(FFX_GPU)
























#define FFX_TRUE (true)




#define FFX_FALSE (false)




#define FFX_POSITIVE_INFINITY_FLOAT ffxAsFloat(0x7f800000u)




#define FFX_NEGATIVE_INFINITY_FLOAT ffxAsFloat(0xff800000u)




#define FFX_PI  (3.14159)










FfxFloat32 ffxReciprocal(FfxFloat32 value)
{
    return rcp(value);
}









FfxFloat32x2 ffxReciprocal(FfxFloat32x2 value)
{
    return rcp(value);
}









FfxFloat32x3 ffxReciprocal(FfxFloat32x3 value)
{
    return rcp(value);
}









FfxFloat32x4 ffxReciprocal(FfxFloat32x4 value)
{
    return rcp(value);
}










FfxFloat32 ffxMin(FfxFloat32 x, FfxFloat32 y)
{
    return min(x, y);
}










FfxFloat32x2 ffxMin(FfxFloat32x2 x, FfxFloat32x2 y)
{
    return min(x, y);
}










FfxFloat32x3 ffxMin(FfxFloat32x3 x, FfxFloat32x3 y)
{
    return min(x, y);
}










FfxFloat32x4 ffxMin(FfxFloat32x4 x, FfxFloat32x4 y)
{
    return min(x, y);
}










FfxInt32 ffxMin(FfxInt32 x, FfxInt32 y)
{
    return min(x, y);
}










FfxInt32x2 ffxMin(FfxInt32x2 x, FfxInt32x2 y)
{
    return min(x, y);
}










FfxInt32x3 ffxMin(FfxInt32x3 x, FfxInt32x3 y)
{
    return min(x, y);
}










FfxInt32x4 ffxMin(FfxInt32x4 x, FfxInt32x4 y)
{
    return min(x, y);
}










FfxUInt32 ffxMin(FfxUInt32 x, FfxUInt32 y)
{
    return min(x, y);
}










FfxUInt32x2 ffxMin(FfxUInt32x2 x, FfxUInt32x2 y)
{
    return min(x, y);
}










FfxUInt32x3 ffxMin(FfxUInt32x3 x, FfxUInt32x3 y)
{
    return min(x, y);
}










FfxUInt32x4 ffxMin(FfxUInt32x4 x, FfxUInt32x4 y)
{
    return min(x, y);
}










FfxFloat32 ffxMax(FfxFloat32 x, FfxFloat32 y)
{
    return max(x, y);
}










FfxFloat32x2 ffxMax(FfxFloat32x2 x, FfxFloat32x2 y)
{
    return max(x, y);
}










FfxFloat32x3 ffxMax(FfxFloat32x3 x, FfxFloat32x3 y)
{
    return max(x, y);
}










FfxFloat32x4 ffxMax(FfxFloat32x4 x, FfxFloat32x4 y)
{
    return max(x, y);
}










FfxInt32 ffxMax(FfxInt32 x, FfxInt32 y)
{
    return max(x, y);
}










FfxInt32x2 ffxMax(FfxInt32x2 x, FfxInt32x2 y)
{
    return max(x, y);
}










FfxInt32x3 ffxMax(FfxInt32x3 x, FfxInt32x3 y)
{
    return max(x, y);
}










FfxInt32x4 ffxMax(FfxInt32x4 x, FfxInt32x4 y)
{
    return max(x, y);
}










FfxUInt32 ffxMax(FfxUInt32 x, FfxUInt32 y)
{
    return max(x, y);
}










FfxUInt32x2 ffxMax(FfxUInt32x2 x, FfxUInt32x2 y)
{
    return max(x, y);
}










FfxUInt32x3 ffxMax(FfxUInt32x3 x, FfxUInt32x3 y)
{
    return max(x, y);
}










FfxUInt32x4 ffxMax(FfxUInt32x4 x, FfxUInt32x4 y)
{
    return max(x, y);
}










FfxFloat32 ffxPow(FfxFloat32 x, FfxFloat32 y)
{
    return pow(x, y);
}










FfxFloat32x2 ffxPow(FfxFloat32x2 x, FfxFloat32x2 y)
{
    return pow(x, y);
}










FfxFloat32x3 ffxPow(FfxFloat32x3 x, FfxFloat32x3 y)
{
    return pow(x, y);
}










FfxFloat32x4 ffxPow(FfxFloat32x4 x, FfxFloat32x4 y)
{
    return pow(x, y);
}









FfxFloat32 ffxSqrt(FfxFloat32 x)
{
    return sqrt(x);
}









FfxFloat32x2 ffxSqrt(FfxFloat32x2 x)
{
    return sqrt(x);
}









FfxFloat32x3 ffxSqrt(FfxFloat32x3 x)
{
    return sqrt(x);
}









FfxFloat32x4 ffxSqrt(FfxFloat32x4 x)
{
    return sqrt(x);
}










FfxFloat32 ffxCopySignBit(FfxFloat32 d, FfxFloat32 s)
{
    return ffxAsFloat(ffxAsUInt32(d) | (ffxAsUInt32(s) & FfxUInt32(0x80000000u)));
}










FfxFloat32x2 ffxCopySignBit(FfxFloat32x2 d, FfxFloat32x2 s)
{
    return ffxAsFloat(ffxAsUInt32(d) | (ffxAsUInt32(s) & ffxBroadcast2(0x80000000u)));
}










FfxFloat32x3 ffxCopySignBit(FfxFloat32x3 d, FfxFloat32x3 s)
{
    return ffxAsFloat(ffxAsUInt32(d) | (ffxAsUInt32(s) & ffxBroadcast3(0x80000000u)));
}










FfxFloat32x4 ffxCopySignBit(FfxFloat32x4 d, FfxFloat32x4 s)
{
    return ffxAsFloat(ffxAsUInt32(d) | (ffxAsUInt32(s) & ffxBroadcast4(0x80000000u)));
}



















FfxFloat32 ffxIsSigned(FfxFloat32 m)
{
    return ffxSaturate(m * FfxFloat32(FFX_NEGATIVE_INFINITY_FLOAT));
}



















FfxFloat32x2 ffxIsSigned(FfxFloat32x2 m)
{
    return ffxSaturate(m * ffxBroadcast2(FFX_NEGATIVE_INFINITY_FLOAT));
}



















FfxFloat32x3 ffxIsSigned(FfxFloat32x3 m)
{
    return ffxSaturate(m * ffxBroadcast3(FFX_NEGATIVE_INFINITY_FLOAT));
}



















FfxFloat32x4 ffxIsSigned(FfxFloat32x4 m)
{
    return ffxSaturate(m * ffxBroadcast4(FFX_NEGATIVE_INFINITY_FLOAT));
}














FfxFloat32 ffxIsGreaterThanZero(FfxFloat32 m)
{
    return ffxSaturate(m * FfxFloat32(FFX_POSITIVE_INFINITY_FLOAT));
}














FfxFloat32x2 ffxIsGreaterThanZero(FfxFloat32x2 m)
{
    return ffxSaturate(m * ffxBroadcast2(FFX_POSITIVE_INFINITY_FLOAT));
}














FfxFloat32x3 ffxIsGreaterThanZero(FfxFloat32x3 m)
{
    return ffxSaturate(m * ffxBroadcast3(FFX_POSITIVE_INFINITY_FLOAT));
}














FfxFloat32x4 ffxIsGreaterThanZero(FfxFloat32x4 m)
{
    return ffxSaturate(m * ffxBroadcast4(FFX_POSITIVE_INFINITY_FLOAT));
}
















FfxUInt32 ffxFloatToSortableInteger(FfxUInt32 value)
{
    return value ^ ((AShrSU1(value, FfxUInt32(31))) | FfxUInt32(0x80000000));
}













FfxUInt32 ffxSortableIntegerToFloat(FfxUInt32 value)
{
    return value ^ ((~AShrSU1(value, FfxUInt32(31))) | FfxUInt32(0x80000000));
}















FfxFloat32 ffxApproximateSqrt(FfxFloat32 a)
{
    return ffxAsFloat((ffxAsUInt32(a) >> FfxUInt32(1)) + FfxUInt32(0x1fbc4639));
}















FfxFloat32 ffxApproximateReciprocal(FfxFloat32 a)
{
    return ffxAsFloat(FfxUInt32(0x7ef07ebb) - ffxAsUInt32(a));
}















FfxFloat32 ffxApproximateReciprocalMedium(FfxFloat32 value)
{
    FfxFloat32 b = ffxAsFloat(FfxUInt32(0x7ef19fff) - ffxAsUInt32(value));
    return b * (-b * value + FfxFloat32(2.0));
}















FfxFloat32 ffxApproximateReciprocalSquareRoot(FfxFloat32 a)
{
    return ffxAsFloat(FfxUInt32(0x5f347d74) - (ffxAsUInt32(a) >> FfxUInt32(1)));
}















FfxFloat32x2 ffxApproximateSqrt(FfxFloat32x2 a)
{
    return ffxAsFloat((ffxAsUInt32(a) >> ffxBroadcast2(1u)) + ffxBroadcast2(0x1fbc4639u));
}















FfxFloat32x2 ffxApproximateReciprocal(FfxFloat32x2 a)
{
    return ffxAsFloat(ffxBroadcast2(0x7ef07ebbu) - ffxAsUInt32(a));
}















FfxFloat32x2 ffxApproximateReciprocalMedium(FfxFloat32x2 a)
{
    FfxFloat32x2 b = ffxAsFloat(ffxBroadcast2(0x7ef19fffu) - ffxAsUInt32(a));
    return b * (-b * a + ffxBroadcast2(2.0f));
}















FfxFloat32x2 ffxApproximateReciprocalSquareRoot(FfxFloat32x2 a)
{
    return ffxAsFloat(ffxBroadcast2(0x5f347d74u) - (ffxAsUInt32(a) >> ffxBroadcast2(1u)));
}















FfxFloat32x3 ffxApproximateSqrt(FfxFloat32x3 a)
{
    return ffxAsFloat((ffxAsUInt32(a) >> ffxBroadcast3(1u)) + ffxBroadcast3(0x1fbc4639u));
}















FfxFloat32x3 ffxApproximateReciprocal(FfxFloat32x3 a)
{
    return ffxAsFloat(ffxBroadcast3(0x7ef07ebbu) - ffxAsUInt32(a));
}















FfxFloat32x3 ffxApproximateReciprocalMedium(FfxFloat32x3 a)
{
    FfxFloat32x3 b = ffxAsFloat(ffxBroadcast3(0x7ef19fffu) - ffxAsUInt32(a));
    return b * (-b * a + ffxBroadcast3(2.0f));
}















FfxFloat32x3 ffxApproximateReciprocalSquareRoot(FfxFloat32x3 a)
{
    return ffxAsFloat(ffxBroadcast3(0x5f347d74u) - (ffxAsUInt32(a) >> ffxBroadcast3(1u)));
}















FfxFloat32x4 ffxApproximateSqrt(FfxFloat32x4 a)
{
    return ffxAsFloat((ffxAsUInt32(a) >> ffxBroadcast4(1u)) + ffxBroadcast4(0x1fbc4639u));
}















FfxFloat32x4 ffxApproximateReciprocal(FfxFloat32x4 a)
{
    return ffxAsFloat(ffxBroadcast4(0x7ef07ebbu) - ffxAsUInt32(a));
}















FfxFloat32x4 ffxApproximateReciprocalMedium(FfxFloat32x4 a)
{
    FfxFloat32x4 b = ffxAsFloat(ffxBroadcast4(0x7ef19fffu) - ffxAsUInt32(a));
    return b * (-b * a + ffxBroadcast4(2.0f));
}















FfxFloat32x4 ffxApproximateReciprocalSquareRoot(FfxFloat32x4 a)
{
    return ffxAsFloat(ffxBroadcast4(0x5f347d74u) - (ffxAsUInt32(a) >> ffxBroadcast4(1u)));
}










FfxFloat32 ffxDot2(FfxFloat32x2 a, FfxFloat32x2 b)
{
    return dot(a, b);
}










FfxFloat32 ffxDot3(FfxFloat32x3 a, FfxFloat32x3 b)
{
    return dot(a, b);
}










FfxFloat32 ffxDot4(FfxFloat32x4 a, FfxFloat32x4 b)
{
    return dot(a, b);
}














FfxFloat32 ffxApproximatePQToGamma2Medium(FfxFloat32 a)
{
    return a * a * a * a;
}













FfxFloat32 ffxApproximatePQToLinear(FfxFloat32 a)
{
    return a * a * a * a * a * a * a * a;
}













FfxFloat32 ffxApproximateGamma2ToPQ(FfxFloat32 a)
{
    return ffxAsFloat((ffxAsUInt32(a) >> FfxUInt32(2)) + FfxUInt32(0x2F9A4E46));
}













FfxFloat32 ffxApproximateGamma2ToPQMedium(FfxFloat32 a)
{
    FfxFloat32 b  = ffxAsFloat((ffxAsUInt32(a) >> FfxUInt32(2)) + FfxUInt32(0x2F9A4E46));
    FfxFloat32 b4 = b * b * b * b;
    return b - b * (b4 - a) / (FfxFloat32(4.0) * b4);
}













FfxFloat32 ffxApproximateGamma2ToPQHigh(FfxFloat32 a)
{
    return ffxSqrt(ffxSqrt(a));
}













FfxFloat32 ffxApproximateLinearToPQ(FfxFloat32 a)
{
    return ffxAsFloat((ffxAsUInt32(a) >> FfxUInt32(3)) + FfxUInt32(0x378D8723));
}













FfxFloat32 ffxApproximateLinearToPQMedium(FfxFloat32 a)
{
    FfxFloat32 b  = ffxAsFloat((ffxAsUInt32(a) >> FfxUInt32(3)) + FfxUInt32(0x378D8723));
    FfxFloat32 b8 = b * b * b * b * b * b * b * b;
    return b - b * (b8 - a) / (FfxFloat32(8.0) * b8);
}













FfxFloat32 ffxApproximateLinearToPQHigh(FfxFloat32 a)
{
    return ffxSqrt(ffxSqrt(ffxSqrt(a)));
}













FfxFloat32x2 ffxApproximatePQToGamma2Medium(FfxFloat32x2 a)
{
    return a * a * a * a;
}













FfxFloat32x2 ffxApproximatePQToLinear(FfxFloat32x2 a)
{
    return a * a * a * a * a * a * a * a;
}













FfxFloat32x2 ffxApproximateGamma2ToPQ(FfxFloat32x2 a)
{
    return ffxAsFloat((ffxAsUInt32(a) >> ffxBroadcast2(2u)) + ffxBroadcast2(0x2F9A4E46u));
}













FfxFloat32x2 ffxApproximateGamma2ToPQMedium(FfxFloat32x2 a)
{
    FfxFloat32x2 b  = ffxAsFloat((ffxAsUInt32(a) >> ffxBroadcast2(2u)) + ffxBroadcast2(0x2F9A4E46u));
    FfxFloat32x2 b4 = b * b * b * b;
    return b - b * (b4 - a) / (FfxFloat32(4.0) * b4);
}













FfxFloat32x2 ffxApproximateGamma2ToPQHigh(FfxFloat32x2 a)
{
    return ffxSqrt(ffxSqrt(a));
}













FfxFloat32x2 ffxApproximateLinearToPQ(FfxFloat32x2 a)
{
    return ffxAsFloat((ffxAsUInt32(a) >> ffxBroadcast2(3u)) + ffxBroadcast2(0x378D8723u));
}













FfxFloat32x2 ffxApproximateLinearToPQMedium(FfxFloat32x2 a)
{
    FfxFloat32x2 b  = ffxAsFloat((ffxAsUInt32(a) >> ffxBroadcast2(3u)) + ffxBroadcast2(0x378D8723u));
    FfxFloat32x2 b8 = b * b * b * b * b * b * b * b;
    return b - b * (b8 - a) / (FfxFloat32(8.0) * b8);
}













FfxFloat32x2 ffxApproximateLinearToPQHigh(FfxFloat32x2 a)
{
    return ffxSqrt(ffxSqrt(ffxSqrt(a)));
}













FfxFloat32x3 ffxApproximatePQToGamma2Medium(FfxFloat32x3 a)
{
    return a * a * a * a;
}













FfxFloat32x3 ffxApproximatePQToLinear(FfxFloat32x3 a)
{
    return a * a * a * a * a * a * a * a;
}













FfxFloat32x3 ffxApproximateGamma2ToPQ(FfxFloat32x3 a)
{
    return ffxAsFloat((ffxAsUInt32(a) >> ffxBroadcast3(2u)) + ffxBroadcast3(0x2F9A4E46u));
}













FfxFloat32x3 ffxApproximateGamma2ToPQMedium(FfxFloat32x3 a)
{
    FfxFloat32x3 b  = ffxAsFloat((ffxAsUInt32(a) >> ffxBroadcast3(2u)) + ffxBroadcast3(0x2F9A4E46u));
    FfxFloat32x3 b4 = b * b * b * b;
    return b - b * (b4 - a) / (FfxFloat32(4.0) * b4);
}













FfxFloat32x3 ffxApproximateGamma2ToPQHigh(FfxFloat32x3 a)
{
    return ffxSqrt(ffxSqrt(a));
}













FfxFloat32x3 ffxApproximateLinearToPQ(FfxFloat32x3 a)
{
    return ffxAsFloat((ffxAsUInt32(a) >> ffxBroadcast3(3u)) + ffxBroadcast3(0x378D8723u));
}













FfxFloat32x3 ffxApproximateLinearToPQMedium(FfxFloat32x3 a)
{
    FfxFloat32x3 b  = ffxAsFloat((ffxAsUInt32(a) >> ffxBroadcast3(3u)) + ffxBroadcast3(0x378D8723u));
    FfxFloat32x3 b8 = b * b * b * b * b * b * b * b;
    return b - b * (b8 - a) / (FfxFloat32(8.0) * b8);
}













FfxFloat32x3 ffxApproximateLinearToPQHigh(FfxFloat32x3 a)
{
    return ffxSqrt(ffxSqrt(ffxSqrt(a)));
}













FfxFloat32x4 ffxApproximatePQToGamma2Medium(FfxFloat32x4 a)
{
    return a * a * a * a;
}













FfxFloat32x4 ffxApproximatePQToLinear(FfxFloat32x4 a)
{
    return a * a * a * a * a * a * a * a;
}













FfxFloat32x4 ffxApproximateGamma2ToPQ(FfxFloat32x4 a)
{
    return ffxAsFloat((ffxAsUInt32(a) >> ffxBroadcast4(2u)) + ffxBroadcast4(0x2F9A4E46u));
}













FfxFloat32x4 ffxApproximateGamma2ToPQMedium(FfxFloat32x4 a)
{
    FfxFloat32x4 b  = ffxAsFloat((ffxAsUInt32(a) >> ffxBroadcast4(2u)) + ffxBroadcast4(0x2F9A4E46u));
    FfxFloat32x4 b4 = b * b * b * b * b * b * b * b;
    return b - b * (b4 - a) / (FfxFloat32(4.0) * b4);
}













FfxFloat32x4 ffxApproximateGamma2ToPQHigh(FfxFloat32x4 a)
{
    return ffxSqrt(ffxSqrt(a));
}













FfxFloat32x4 ffxApproximateLinearToPQ(FfxFloat32x4 a)
{
    return ffxAsFloat((ffxAsUInt32(a) >> ffxBroadcast4(3u)) + ffxBroadcast4(0x378D8723u));
}













FfxFloat32x4 ffxApproximateLinearToPQMedium(FfxFloat32x4 a)
{
    FfxFloat32x4 b  = ffxAsFloat((ffxAsUInt32(a) >> ffxBroadcast4(3u)) + ffxBroadcast4(0x378D8723u));
    FfxFloat32x4 b8 = b * b * b * b * b * b * b * b;
    return b - b * (b8 - a) / (FfxFloat32(8.0) * b8);
}













FfxFloat32x4 ffxApproximateLinearToPQHigh(FfxFloat32x4 a)
{
    return ffxSqrt(ffxSqrt(ffxSqrt(a)));
}










FfxFloat32 ffxParabolicSin(FfxFloat32 value)
{
    return value * abs(value) - value;
}










FfxFloat32x2 ffxParabolicSin(FfxFloat32x2 x)
{
    return x * abs(x) - x;
}










FfxFloat32 ffxParabolicCos(FfxFloat32 x)
{
    x = ffxFract(x * FfxFloat32(0.5) + FfxFloat32(0.75));
    x = x * FfxFloat32(2.0) - FfxFloat32(1.0);
    return ffxParabolicSin(x);
}










FfxFloat32x2 ffxParabolicCos(FfxFloat32x2 x)
{
    x = ffxFract(x * ffxBroadcast2(0.5f) + ffxBroadcast2(0.75f));
    x = x * ffxBroadcast2(2.0f) - ffxBroadcast2(1.0f);
    return ffxParabolicSin(x);
}










FfxFloat32x2 ffxParabolicSinCos(FfxFloat32 x)
{
    FfxFloat32 y = ffxFract(x * FfxFloat32(0.5) + FfxFloat32(0.75));
    y = y * FfxFloat32(2.0) - FfxFloat32(1.0);
    return ffxParabolicSin(FfxFloat32x2(x, y));
}










FfxUInt32 ffxZeroOneAnd(FfxUInt32 x, FfxUInt32 y)
{
    return min(x, y);
}










FfxUInt32x2 ffxZeroOneAnd(FfxUInt32x2 x, FfxUInt32x2 y)
{
    return min(x, y);
}










FfxUInt32x3 ffxZeroOneAnd(FfxUInt32x3 x, FfxUInt32x3 y)
{
    return min(x, y);
}










FfxUInt32x4 ffxZeroOneAnd(FfxUInt32x4 x, FfxUInt32x4 y)
{
    return min(x, y);
}










FfxUInt32 ffxZeroOneAnd(FfxUInt32 x)
{
    return x ^ FfxUInt32(1);
}










FfxUInt32x2 ffxZeroOneAnd(FfxUInt32x2 x)
{
    return x ^ ffxBroadcast2(1u);
}










FfxUInt32x3 ffxZeroOneAnd(FfxUInt32x3 x)
{
    return x ^ ffxBroadcast3(1u);
}










FfxUInt32x4 ffxZeroOneAnd(FfxUInt32x4 x)
{
    return x ^ ffxBroadcast4(1u);
}










FfxUInt32 ffxZeroOneOr(FfxUInt32 x, FfxUInt32 y)
{
    return max(x, y);
}










FfxUInt32x2 ffxZeroOneOr(FfxUInt32x2 x, FfxUInt32x2 y)
{
    return max(x, y);
}










FfxUInt32x3 ffxZeroOneOr(FfxUInt32x3 x, FfxUInt32x3 y)
{
    return max(x, y);
}










FfxUInt32x4 ffxZeroOneOr(FfxUInt32x4 x, FfxUInt32x4 y)
{
    return max(x, y);
}









FfxUInt32 ffxZeroOneAndToU1(FfxFloat32 x)
{
    return FfxUInt32(FfxFloat32(1.0) - x);
}









FfxUInt32x2 ffxZeroOneAndToU2(FfxFloat32x2 x)
{
    return FfxUInt32x2(ffxBroadcast2(1.0) - x);
}









FfxUInt32x3 ffxZeroOneAndToU3(FfxFloat32x3 x)
{
    return FfxUInt32x3(ffxBroadcast3(1.0) - x);
}








)<!>" R"<!>(
FfxUInt32x4 ffxZeroOneAndToU4(FfxFloat32x4 x)
{
    return FfxUInt32x4(ffxBroadcast4(1.0) - x);
}












FfxFloat32 ffxZeroOneAndOr(FfxFloat32 x, FfxFloat32 y, FfxFloat32 z)
{
    return ffxSaturate(x * y + z);
}












FfxFloat32x2 ffxZeroOneAndOr(FfxFloat32x2 x, FfxFloat32x2 y, FfxFloat32x2 z)
{
    return ffxSaturate(x * y + z);
}












FfxFloat32x3 ffxZeroOneAndOr(FfxFloat32x3 x, FfxFloat32x3 y, FfxFloat32x3 z)
{
    return ffxSaturate(x * y + z);
}












FfxFloat32x4 ffxZeroOneAndOr(FfxFloat32x4 x, FfxFloat32x4 y, FfxFloat32x4 z)
{
    return ffxSaturate(x * y + z);
}









FfxFloat32 ffxZeroOneIsGreaterThanZero(FfxFloat32 x)
{
    return ffxSaturate(x * FfxFloat32(FFX_POSITIVE_INFINITY_FLOAT));
}









FfxFloat32x2 ffxZeroOneIsGreaterThanZero(FfxFloat32x2 x)
{
    return ffxSaturate(x * ffxBroadcast2(FFX_POSITIVE_INFINITY_FLOAT));
}









FfxFloat32x3 ffxZeroOneIsGreaterThanZero(FfxFloat32x3 x)
{
    return ffxSaturate(x * ffxBroadcast3(FFX_POSITIVE_INFINITY_FLOAT));
}









FfxFloat32x4 ffxZeroOneIsGreaterThanZero(FfxFloat32x4 x)
{
    return ffxSaturate(x * ffxBroadcast4(FFX_POSITIVE_INFINITY_FLOAT));
}









FfxFloat32 ffxZeroOneAnd(FfxFloat32 x)
{
    return FfxFloat32(1.0) - x;
}









FfxFloat32x2 ffxZeroOneAnd(FfxFloat32x2 x)
{
    return ffxBroadcast2(1.0) - x;
}









FfxFloat32x3 ffxZeroOneAnd(FfxFloat32x3 x)
{
    return ffxBroadcast3(1.0) - x;
}









FfxFloat32x4 ffxZeroOneAnd(FfxFloat32x4 x)
{
    return ffxBroadcast4(1.0) - x;
}










FfxFloat32 ffxZeroOneOr(FfxFloat32 x, FfxFloat32 y)
{
    return max(x, y);
}










FfxFloat32x2 ffxZeroOneOr(FfxFloat32x2 x, FfxFloat32x2 y)
{
    return max(x, y);
}










FfxFloat32x3 ffxZeroOneOr(FfxFloat32x3 x, FfxFloat32x3 y)
{
    return max(x, y);
}










FfxFloat32x4 ffxZeroOneOr(FfxFloat32x4 x, FfxFloat32x4 y)
{
    return max(x, y);
}











FfxFloat32 ffxZeroOneSelect(FfxFloat32 x, FfxFloat32 y, FfxFloat32 z)
{
    FfxFloat32 r = (-x) * z + z;
    return x * y + r;
}











FfxFloat32x2 ffxZeroOneSelect(FfxFloat32x2 x, FfxFloat32x2 y, FfxFloat32x2 z)
{
    FfxFloat32x2 r = (-x) * z + z;
    return x * y + r;
}











FfxFloat32x3 ffxZeroOneSelect(FfxFloat32x3 x, FfxFloat32x3 y, FfxFloat32x3 z)
{
    FfxFloat32x3 r = (-x) * z + z;
    return x * y + r;
}











FfxFloat32x4 ffxZeroOneSelect(FfxFloat32x4 x, FfxFloat32x4 y, FfxFloat32x4 z)
{
    FfxFloat32x4 r = (-x) * z + z;
    return x * y + r;
}









FfxFloat32 ffxZeroOneIsSigned(FfxFloat32 x)
{
    return ffxSaturate(x * FfxFloat32(FFX_NEGATIVE_INFINITY_FLOAT));
}









FfxFloat32x2 ffxZeroOneIsSigned(FfxFloat32x2 x)
{
    return ffxSaturate(x * ffxBroadcast2(FFX_NEGATIVE_INFINITY_FLOAT));
}









FfxFloat32x3 ffxZeroOneIsSigned(FfxFloat32x3 x)
{
    return ffxSaturate(x * ffxBroadcast3(FFX_NEGATIVE_INFINITY_FLOAT));
}









FfxFloat32x4 ffxZeroOneIsSigned(FfxFloat32x4 x)
{
    return ffxSaturate(x * ffxBroadcast4(FFX_NEGATIVE_INFINITY_FLOAT));
}















FfxFloat32 ffxRec709FromLinear(FfxFloat32 color)
{
    FfxFloat32x3 j = FfxFloat32x3(0.018 * 4.5, 4.5, 0.45);
    FfxFloat32x2 k = FfxFloat32x2(1.099, -0.099);
    return clamp(j.x, color * j.y, pow(color, j.z) * k.x + k.y);
}















FfxFloat32x2 ffxRec709FromLinear(FfxFloat32x2 color)
{
    FfxFloat32x3 j = FfxFloat32x3(0.018 * 4.5, 4.5, 0.45);
    FfxFloat32x2 k = FfxFloat32x2(1.099, -0.099);
    return clamp(j.xx, color * j.yy, pow(color, j.zz) * k.xx + k.yy);
}















FfxFloat32x3 ffxRec709FromLinear(FfxFloat32x3 color)
{
    FfxFloat32x3 j = FfxFloat32x3(0.018 * 4.5, 4.5, 0.45);
    FfxFloat32x2 k = FfxFloat32x2(1.099, -0.099);
    return clamp(j.xxx, color * j.yyy, pow(color, j.zzz) * k.xxx + k.yyy);
}














FfxFloat32 ffxGammaFromLinear(FfxFloat32 color, FfxFloat32 rcpX)
{
    return pow(color, FfxFloat32(rcpX));
}














FfxFloat32x2 ffxGammaFromLinear(FfxFloat32x2 color, FfxFloat32 rcpX)
{
    return pow(color, ffxBroadcast2(rcpX));
}














FfxFloat32x3 ffxGammaFromLinear(FfxFloat32x3 color, FfxFloat32 rcpX)
{
    return pow(color, ffxBroadcast3(rcpX));
}









FfxFloat32 ffxPQToLinear(FfxFloat32 x)
{
    FfxFloat32 p = pow(x, FfxFloat32(0.159302));
    return pow((FfxFloat32(0.835938) + FfxFloat32(18.8516) * p) / (FfxFloat32(1.0) + FfxFloat32(18.6875) * p), FfxFloat32(78.8438));
}









FfxFloat32x2 ffxPQToLinear(FfxFloat32x2 x)
{
    FfxFloat32x2 p = pow(x, ffxBroadcast2(0.159302));
    return pow((ffxBroadcast2(0.835938) + ffxBroadcast2(18.8516) * p) / (ffxBroadcast2(1.0) + ffxBroadcast2(18.6875) * p), ffxBroadcast2(78.8438));
}









FfxFloat32x3 ffxPQToLinear(FfxFloat32x3 x)
{
    FfxFloat32x3 p = pow(x, ffxBroadcast3(0.159302));
    return pow((ffxBroadcast3(0.835938) + ffxBroadcast3(18.8516) * p) / (ffxBroadcast3(1.0) + ffxBroadcast3(18.6875) * p), ffxBroadcast3(78.8438));
}









FfxFloat32 ffxSrgbToLinear(FfxFloat32 color)
{
    FfxFloat32x3 j = FfxFloat32x3(0.0031308 * 12.92, 12.92, 1.0 / 2.4);
    FfxFloat32x2 k = FfxFloat32x2(1.055, -0.055);
    return clamp(j.x, color * j.y, pow(color, j.z) * k.x + k.y);
}









FfxFloat32x2 ffxSrgbToLinear(FfxFloat32x2 color)
{
    FfxFloat32x3 j = FfxFloat32x3(0.0031308 * 12.92, 12.92, 1.0 / 2.4);
    FfxFloat32x2 k = FfxFloat32x2(1.055, -0.055);
    return clamp(j.xx, color * j.yy, pow(color, j.zz) * k.xx + k.yy);
}









FfxFloat32x3 ffxSrgbToLinear(FfxFloat32x3 color)
{
    FfxFloat32x3 j = FfxFloat32x3(0.0031308 * 12.92, 12.92, 1.0 / 2.4);
    FfxFloat32x2 k = FfxFloat32x2(1.055, -0.055);
    return clamp(j.xxx, color * j.yyy, pow(color, j.zzz) * k.xxx + k.yyy);
}









FfxFloat32 ffxLinearFromRec709(FfxFloat32 color)
{
    FfxFloat32x3 j = FfxFloat32x3(0.081 / 4.5, 1.0 / 4.5, 1.0 / 0.45);
    FfxFloat32x2 k = FfxFloat32x2(1.0 / 1.099, 0.099 / 1.099);
    return ffxZeroOneSelect(ffxZeroOneIsSigned(color - j.x), color * j.y, pow(color * k.x + k.y, j.z));
}









FfxFloat32x2 ffxLinearFromRec709(FfxFloat32x2 color)
{
    FfxFloat32x3 j = FfxFloat32x3(0.081 / 4.5, 1.0 / 4.5, 1.0 / 0.45);
    FfxFloat32x2 k = FfxFloat32x2(1.0 / 1.099, 0.099 / 1.099);
    return ffxZeroOneSelect(ffxZeroOneIsSigned(color - j.xx), color * j.yy, pow(color * k.xx + k.yy, j.zz));
}









FfxFloat32x3 ffxLinearFromRec709(FfxFloat32x3 color)
{
    FfxFloat32x3 j = FfxFloat32x3(0.081 / 4.5, 1.0 / 4.5, 1.0 / 0.45);
    FfxFloat32x2 k = FfxFloat32x2(1.0 / 1.099, 0.099 / 1.099);
    return ffxZeroOneSelect(ffxZeroOneIsSigned(color - j.xxx), color * j.yyy, pow(color * k.xxx + k.yyy, j.zzz));
}












FfxFloat32 ffxLinearFromGamma(FfxFloat32 color, FfxFloat32 power)
{
    return pow(color, FfxFloat32(power));
}












FfxFloat32x2 ffxLinearFromGamma(FfxFloat32x2 color, FfxFloat32 power)
{
    return pow(color, ffxBroadcast2(power));
}












FfxFloat32x3 ffxLinearFromGamma(FfxFloat32x3 color, FfxFloat32 power)
{
    return pow(color, ffxBroadcast3(power));
}











FfxFloat32 ffxLinearFromPQ(FfxFloat32 x)
{
    FfxFloat32 p = pow(x, FfxFloat32(0.0126833));
    return pow(ffxSaturate(p - FfxFloat32(0.835938)) / (FfxFloat32(18.8516) - FfxFloat32(18.6875) * p), FfxFloat32(6.27739));
}











FfxFloat32x2 ffxLinearFromPQ(FfxFloat32x2 x)
{
    FfxFloat32x2 p = pow(x, ffxBroadcast2(0.0126833));
    return pow(ffxSaturate(p - ffxBroadcast2(0.835938)) / (ffxBroadcast2(18.8516) - ffxBroadcast2(18.6875) * p), ffxBroadcast2(6.27739));
}











FfxFloat32x3 ffxLinearFromPQ(FfxFloat32x3 x)
{
    FfxFloat32x3 p = pow(x, ffxBroadcast3(0.0126833));
    return pow(ffxSaturate(p - ffxBroadcast3(0.835938)) / (ffxBroadcast3(18.8516) - ffxBroadcast3(18.6875) * p), ffxBroadcast3(6.27739));
}











FfxFloat32 ffxLinearFromSrgb(FfxFloat32 color)
{
    FfxFloat32x3 j = FfxFloat32x3(0.04045 / 12.92, 1.0 / 12.92, 2.4);
    FfxFloat32x2 k = FfxFloat32x2(1.0 / 1.055, 0.055 / 1.055);
    return ffxZeroOneSelect(ffxZeroOneIsSigned(color - j.x), color * j.y, pow(color * k.x + k.y, j.z));
}











FfxFloat32x2 ffxLinearFromSrgb(FfxFloat32x2 color)
{
    FfxFloat32x3 j = FfxFloat32x3(0.04045 / 12.92, 1.0 / 12.92, 2.4);
    FfxFloat32x2 k = FfxFloat32x2(1.0 / 1.055, 0.055 / 1.055);
    return ffxZeroOneSelect(ffxZeroOneIsSigned(color - j.xx), color * j.yy, pow(color * k.xx + k.yy, j.zz));
}











FfxFloat32x3 ffxLinearFromSrgb(FfxFloat32x3 color)
{
    FfxFloat32x3 j = FfxFloat32x3(0.04045 / 12.92, 1.0 / 12.92, 2.4);
    FfxFloat32x2 k = FfxFloat32x2(1.0 / 1.055, 0.055 / 1.055);
    return ffxZeroOneSelect(ffxZeroOneIsSigned(color - j.xxx), color * j.yyy, pow(color * k.xxx + k.yyy, j.zzz));
}














FfxUInt32x2 ffxRemapForQuad(FfxUInt32 a)
{
    return FfxUInt32x2(bitfieldExtract(a, 1u, 3u), bitfieldInsertMask(bitfieldExtract(a, 3u, 3u), a, 1u));
}




















FfxUInt32x2 ffxRemapForWaveReduction(FfxUInt32 a)
{
    return FfxUInt32x2(bitfieldInsertMask(bitfieldExtract(a, 2u, 3u), a, 1u), bitfieldInsertMask(bitfieldExtract(a, 3u, 3u), bitfieldExtract(a, 1u, 2u), 2u));
}





















#if FFX_HALF
#if FFX_HLSL_6_2



#define FFX_POSITIVE_INFINITY_HALF FFX_TO_FLOAT16((uint16_t)0x7c00u)




#define FFX_NEGATIVE_INFINITY_HALF FFX_TO_FLOAT16((uint16_t)0xfc00u)
#else



#define FFX_POSITIVE_INFINITY_HALF FFX_TO_FLOAT16(0x7c00u)




#define FFX_NEGATIVE_INFINITY_HALF FFX_TO_FLOAT16(0xfc00u)
#endif 










FfxFloat16 ffxMin(FfxFloat16 x, FfxFloat16 y)
{
    return min(x, y);
}










FfxFloat16x2 ffxMin(FfxFloat16x2 x, FfxFloat16x2 y)
{
    return min(x, y);
}










FfxFloat16x3 ffxMin(FfxFloat16x3 x, FfxFloat16x3 y)
{
    return min(x, y);
}










FfxFloat16x4 ffxMin(FfxFloat16x4 x, FfxFloat16x4 y)
{
    return min(x, y);
}










FfxInt16 ffxMin(FfxInt16 x, FfxInt16 y)
{
    return min(x, y);
}










FfxInt16x2 ffxMin(FfxInt16x2 x, FfxInt16x2 y)
{
    return min(x, y);
}










FfxInt16x3 ffxMin(FfxInt16x3 x, FfxInt16x3 y)
{
    return min(x, y);
}










FfxInt16x4 ffxMin(FfxInt16x4 x, FfxInt16x4 y)
{
    return min(x, y);
}










FfxUInt16 ffxMin(FfxUInt16 x, FfxUInt16 y)
{
    return min(x, y);
}










FfxUInt16x2 ffxMin(FfxUInt16x2 x, FfxUInt16x2 y)
{
    return min(x, y);
}










FfxUInt16x3 ffxMin(FfxUInt16x3 x, FfxUInt16x3 y)
{
    return min(x, y);
}










FfxUInt16x4 ffxMin(FfxUInt16x4 x, FfxUInt16x4 y)
{
    return min(x, y);
}










FfxFloat16 ffxMax(FfxFloat16 x, FfxFloat16 y)
{
    return max(x, y);
}










FfxFloat16x2 ffxMax(FfxFloat16x2 x, FfxFloat16x2 y)
{
    return max(x, y);
}










FfxFloat16x3 ffxMax(FfxFloat16x3 x, FfxFloat16x3 y)
{
    return max(x, y);
}










FfxFloat16x4 ffxMax(FfxFloat16x4 x, FfxFloat16x4 y)
{
    return max(x, y);
}










FfxInt16 ffxMax(FfxInt16 x, FfxInt16 y)
{
    return max(x, y);
}










FfxInt16x2 ffxMax(FfxInt16x2 x, FfxInt16x2 y)
{
    return max(x, y);
}










FfxInt16x3 ffxMax(FfxInt16x3 x, FfxInt16x3 y)
{
    return max(x, y);
}










FfxInt16x4 ffxMax(FfxInt16x4 x, FfxInt16x4 y)
{
    return max(x, y);
}










FfxUInt16 ffxMax(FfxUInt16 x, FfxUInt16 y)
{
    return max(x, y);
}










FfxUInt16x2 ffxMax(FfxUInt16x2 x, FfxUInt16x2 y)
{
    return max(x, y);
}










FfxUInt16x3 ffxMax(FfxUInt16x3 x, FfxUInt16x3 y)
{
    return max(x, y);
}










FfxUInt16x4 ffxMax(FfxUInt16x4 x, FfxUInt16x4 y)
{
    return max(x, y);
}










FfxFloat16 ffxPow(FfxFloat16 x, FfxFloat16 y)
{
    return pow(x, y);
}










FfxFloat16x2 ffxPow(FfxFloat16x2 x, FfxFloat16x2 y)
{
    return pow(x, y);
}










FfxFloat16x3 ffxPow(FfxFloat16x3 x, FfxFloat16x3 y)
{
    return pow(x, y);
}










FfxFloat16x4 ffxPow(FfxFloat16x4 x, FfxFloat16x4 y)
{
    return pow(x, y);
}









FfxFloat16 ffxSqrt(FfxFloat16 x)
{
    return sqrt(x);
}









FfxFloat16x2 ffxSqrt(FfxFloat16x2 x)
{
    return sqrt(x);
}









FfxFloat16x3 ffxSqrt(FfxFloat16x3 x)
{
    return sqrt(x);
}









FfxFloat16x4 ffxSqrt(FfxFloat16x4 x)
{
    return sqrt(x);
}










FfxFloat16 ffxCopySignBitHalf(FfxFloat16 d, FfxFloat16 s)
{
    return FFX_TO_FLOAT16(FFX_TO_UINT16(d) | (FFX_TO_UINT16(s) & FFX_BROADCAST_UINT16(0x8000u)));
}










FfxFloat16x2 ffxCopySignBitHalf(FfxFloat16x2 d, FfxFloat16x2 s)
{
    return FFX_TO_FLOAT16X2(FFX_TO_UINT16X2(d) | (FFX_TO_UINT16X2(s) & FFX_BROADCAST_UINT16X2(0x8000u)));
}










FfxFloat16x3 ffxCopySignBitHalf(FfxFloat16x3 d, FfxFloat16x3 s)
{
    return FFX_TO_FLOAT16X3(FFX_TO_UINT16X3(d) | (FFX_TO_UINT16X3(s) & FFX_BROADCAST_UINT16X3(0x8000u)));
}










FfxFloat16x4 ffxCopySignBitHalf(FfxFloat16x4 d, FfxFloat16x4 s)
{
    return FFX_TO_FLOAT16X4(FFX_TO_UINT16X4(d) | (FFX_TO_UINT16X4(s) & FFX_BROADCAST_UINT16X4(0x8000u)));
}



















FfxFloat16 ffxIsSignedHalf(FfxFloat16 m)
{
    return ffxSaturate(m * FFX_BROADCAST_FLOAT16(FFX_NEGATIVE_INFINITY_HALF));
}



















FfxFloat16x2 ffxIsSignedHalf(FfxFloat16x2 m)
{
    return ffxSaturate(m * FFX_BROADCAST_FLOAT16X2(FFX_NEGATIVE_INFINITY_HALF));
}



















FfxFloat16x3 ffxIsSignedHalf(FfxFloat16x3 m)
{
    return ffxSaturate(m * FFX_BROADCAST_FLOAT16X3(FFX_NEGATIVE_INFINITY_HALF));
}



















FfxFloat16x4 ffxIsSignedHalf(FfxFloat16x4 m)
{
    return ffxSaturate(m * FFX_BROADCAST_FLOAT16X4(FFX_NEGATIVE_INFINITY_HALF));
}














FfxFloat16 ffxIsGreaterThanZeroHalf(FfxFloat16 m)
{
    return ffxSaturate(m * FFX_BROADCAST_FLOAT16(FFX_POSITIVE_INFINITY_HALF));
}














FfxFloat16x2 ffxIsGreaterThanZeroHalf(FfxFloat16x2 m)
{
    return ffxSaturate(m * FFX_BROADCAST_FLOAT16X2(FFX_POSITIVE_INFINITY_HALF));
}














FfxFloat16x3 ffxIsGreaterThanZeroHalf(FfxFloat16x3 m)
{
    return ffxSaturate(m * FFX_BROADCAST_FLOAT16X3(FFX_POSITIVE_INFINITY_HALF));
}














FfxFloat16x4 ffxIsGreaterThanZeroHalf(FfxFloat16x4 m)
{
    return ffxSaturate(m * FFX_BROADCAST_FLOAT16X4(FFX_POSITIVE_INFINITY_HALF));
}
















FfxUInt16 ffxFloatToSortableIntegerHalf(FfxUInt16 x)
{
    return x ^ ((ffxBitShiftRightHalf(x, FFX_BROADCAST_UINT16(15))) | FFX_BROADCAST_UINT16(0x8000));
}













FfxUInt16 ffxSortableIntegerToFloatHalf(FfxUInt16 x)
{
    return x ^ ((~ffxBitShiftRightHalf(x, FFX_BROADCAST_UINT16(15))) | FFX_BROADCAST_UINT16(0x8000));
}
















FfxUInt16x2 ffxFloatToSortableIntegerHalf(FfxUInt16x2 x)
{
    return x ^ ((ffxBitShiftRightHalf(x, FFX_BROADCAST_UINT16X2(15))) | FFX_BROADCAST_UINT16X2(0x8000));
}













FfxUInt16x2 ffxSortableIntegerToFloatHalf(FfxUInt16x2 x)
{
    return x ^ ((~ffxBitShiftRightHalf(x, FFX_BROADCAST_UINT16X2(15))) | FFX_BROADCAST_UINT16X2(0x8000));
}












FfxUInt32 ffxPackBytesZeroY0ZeroX0(FfxUInt32x2 i)
{
    return ((i.x) & 0xffu) | ((i.y << 16) & 0xff0000u);
}












FfxUInt32 ffxPackBytesZeroY1ZeroX1(FfxUInt32x2 i)
{
    return ((i.x >> 8) & 0xffu) | ((i.y << 8) & 0xff0000u);
}












FfxUInt32 ffxPackBytesZeroY2ZeroX2(FfxUInt32x2 i)
{
    return ((i.x >> 16) & 0xffu) | ((i.y) & 0xff0000u);
}












FfxUInt32 ffxPackBytesZeroY3ZeroX3(FfxUInt32x2 i)
{
    return ((i.x >> 24) & 0xffu) | ((i.y >> 8) & 0xff0000u);
}












FfxUInt32 ffxPackBytesY3Y2Y1X0(FfxUInt32x2 i)
{
    return ((i.x) & 0x000000ffu) | (i.y & 0xffffff00u);
}












FfxUInt32 ffxPackBytesY3Y2Y1X2(FfxUInt32x2 i)
{
    return ((i.x >> 16) & 0x000000ffu) | (i.y & 0xffffff00u);
}












FfxUInt32 ffxPackBytesY3Y2X0Y0(FfxUInt32x2 i)
{
    return ((i.x << 8) & 0x0000ff00u) | (i.y & 0xffff00ffu);
}












FfxUInt32 ffxPackBytesY3Y2X2Y0(FfxUInt32x2 i)
{
    return ((i.x >> 8) & 0x0000ff00u) | (i.y & 0xffff00ffu);
}












FfxUInt32 ffxPackBytesY3X0Y1Y0(FfxUInt32x2 i)
{
    return ((i.x << 16) & 0x00ff0000u) | (i.y & 0xff00ffffu);
}












FfxUInt32 ffxPackBytesY3X2Y1Y0(FfxUInt32x2 i)
{
    return ((i.x) & 0x00ff0000u) | (i.y & 0xff00ffffu);
}












FfxUInt32 ffxPackBytesX0Y2Y1Y0(FfxUInt32x2 i)
{
    return ((i.x << 24) & 0xff000000u) | (i.y & 0x00ffffffu);
}












FfxUInt32 ffxPackBytesX2Y2Y1Y0(FfxUInt32x2 i)
{
    return ((i.x << 8) & 0xff000000u) | (i.y & 0x00ffffffu);
}












FfxUInt32 ffxPackBytesY2X2Y0X0(FfxUInt32x2 i)
{
    return ((i.x) & 0x00ff00ffu) | ((i.y << 8) & 0xff00ff00u);
}












FfxUInt32 ffxPackBytesY2Y0X2X0(FfxUInt32x2 i)
{
    return (((i.x) & 0xffu) | ((i.x >> 8) & 0xff00u) | ((i.y << 16) & 0xff0000u) | ((i.y << 8) & 0xff000000u));
}








)<!>" R"<!>(

FfxUInt16x2 ffxPackX0Y0X1Y1UnsignedToUint16x2(FfxFloat16x2 x, FfxFloat16x2 y)
{
    x *= FFX_BROADCAST_FLOAT16X2(1.0 / 32768.0);
    y *= FFX_BROADCAST_FLOAT16X2(1.0 / 32768.0);
    return FFX_UINT32_TO_UINT16X2(ffxPackBytesY2X2Y0X0(FfxUInt32x2(FFX_UINT16X2_TO_UINT32(FFX_TO_UINT16X2(x)), FFX_UINT16X2_TO_UINT32(FFX_TO_UINT16X2(y)))));
}



















FfxUInt32x2 ffxPermuteUByte0Float16x2ToUint2(FfxUInt32x2 d, FfxFloat16x2 i)
{
    FfxUInt32 b = FFX_UINT16X2_TO_UINT32(FFX_TO_UINT16X2(i * FFX_BROADCAST_FLOAT16X2(1.0 / 32768.0)));
    return FfxUInt32x2(ffxPackBytesY3Y2Y1X0(FfxUInt32x2(d.x, b)), ffxPackBytesY3Y2Y1X2(FfxUInt32x2(d.y, b)));
}



















FfxUInt32x2 ffxPermuteUByte1Float16x2ToUint2(FfxUInt32x2 d, FfxFloat16x2 i)
{
    FfxUInt32 b = FFX_UINT16X2_TO_UINT32(FFX_TO_UINT16X2(i * FFX_BROADCAST_FLOAT16X2(1.0 / 32768.0)));
    return FfxUInt32x2(ffxPackBytesY3Y2X0Y0(FfxUInt32x2(d.x, b)), ffxPackBytesY3Y2X2Y0(FfxUInt32x2(d.y, b)));
}



















FfxUInt32x2 ffxPermuteUByte2Float16x2ToUint2(FfxUInt32x2 d, FfxFloat16x2 i)
{
    FfxUInt32 b = FFX_UINT16X2_TO_UINT32(FFX_TO_UINT16X2(i * FFX_BROADCAST_FLOAT16X2(1.0 / 32768.0)));
    return FfxUInt32x2(ffxPackBytesY3X0Y1Y0(FfxUInt32x2(d.x, b)), ffxPackBytesY3X2Y1Y0(FfxUInt32x2(d.y, b)));
}



















FfxUInt32x2 ffxPermuteUByte3Float16x2ToUint2(FfxUInt32x2 d, FfxFloat16x2 i)
{
    FfxUInt32 b = FFX_UINT16X2_TO_UINT32(FFX_TO_UINT16X2(i * FFX_BROADCAST_FLOAT16X2(1.0 / 32768.0)));
    return FfxUInt32x2(ffxPackBytesX0Y2Y1Y0(FfxUInt32x2(d.x, b)), ffxPackBytesX2Y2Y1Y0(FfxUInt32x2(d.y, b)));
}









FfxFloat16x2 ffxPermuteUByte0Uint2ToFloat16x2(FfxUInt32x2 i)
{
    return FFX_TO_FLOAT16X2(FFX_UINT32_TO_UINT16X2(ffxPackBytesZeroY0ZeroX0(i))) * FFX_BROADCAST_FLOAT16X2(32768.0);
}









FfxFloat16x2 ffxPermuteUByte1Uint2ToFloat16x2(FfxUInt32x2 i)
{
    return FFX_TO_FLOAT16X2(FFX_UINT32_TO_UINT16X2(ffxPackBytesZeroY1ZeroX1(i))) * FFX_BROADCAST_FLOAT16X2(32768.0);
}









FfxFloat16x2 ffxPermuteUByte2Uint2ToFloat16x2(FfxUInt32x2 i)
{
    return FFX_TO_FLOAT16X2(FFX_UINT32_TO_UINT16X2(ffxPackBytesZeroY2ZeroX2(i))) * FFX_BROADCAST_FLOAT16X2(32768.0);
}









FfxFloat16x2 ffxPermuteUByte3Uint2ToFloat16x2(FfxUInt32x2 i)
{
    return FFX_TO_FLOAT16X2(FFX_UINT32_TO_UINT16X2(ffxPackBytesZeroY3ZeroX3(i))) * FFX_BROADCAST_FLOAT16X2(32768.0);
}










FfxUInt16x2 ffxPackX0Y0X1Y1SignedToUint16x2(FfxFloat16x2 x, FfxFloat16x2 y)
{
    x = x * FFX_BROADCAST_FLOAT16X2(1.0 / 32768.0) + FFX_BROADCAST_FLOAT16X2(0.25 / 32768.0);
    y = y * FFX_BROADCAST_FLOAT16X2(1.0 / 32768.0) + FFX_BROADCAST_FLOAT16X2(0.25 / 32768.0);
    return FFX_UINT32_TO_UINT16X2(ffxPackBytesY2X2Y0X0(FfxUInt32x2(FFX_UINT16X2_TO_UINT32(FFX_TO_UINT16X2(x)), FFX_UINT16X2_TO_UINT32(FFX_TO_UINT16X2(y)))));
}













FfxUInt32x2 ffxPermuteSByte0Float16x2ToUint2(FfxUInt32x2 d, FfxFloat16x2 i)
{
    FfxUInt32 b = FFX_UINT16X2_TO_UINT32(FFX_TO_UINT16X2(i * FFX_BROADCAST_FLOAT16X2(1.0 / 32768.0) + FFX_BROADCAST_FLOAT16X2(0.25 / 32768.0)));
    return FfxUInt32x2(ffxPackBytesY3Y2Y1X0(FfxUInt32x2(d.x, b)), ffxPackBytesY3Y2Y1X2(FfxUInt32x2(d.y, b)));
}













FfxUInt32x2 ffxPermuteSByte1Float16x2ToUint2(FfxUInt32x2 d, FfxFloat16x2 i)
{
    FfxUInt32 b = FFX_UINT16X2_TO_UINT32(FFX_TO_UINT16X2(i * FFX_BROADCAST_FLOAT16X2(1.0 / 32768.0) + FFX_BROADCAST_FLOAT16X2(0.25 / 32768.0)));
    return FfxUInt32x2(ffxPackBytesY3Y2X0Y0(FfxUInt32x2(d.x, b)), ffxPackBytesY3Y2X2Y0(FfxUInt32x2(d.y, b)));
}













FfxUInt32x2 ffxPermuteSByte2Float16x2ToUint2(FfxUInt32x2 d, FfxFloat16x2 i)
{
    FfxUInt32 b = FFX_UINT16X2_TO_UINT32(FFX_TO_UINT16X2(i * FFX_BROADCAST_FLOAT16X2(1.0 / 32768.0) + FFX_BROADCAST_FLOAT16X2(0.25 / 32768.0)));
    return FfxUInt32x2(ffxPackBytesY3X0Y1Y0(FfxUInt32x2(d.x, b)), ffxPackBytesY3X2Y1Y0(FfxUInt32x2(d.y, b)));
}













FfxUInt32x2 ffxPermuteSByte3Float16x2ToUint2(FfxUInt32x2 d, FfxFloat16x2 i)
{
    FfxUInt32 b = FFX_UINT16X2_TO_UINT32(FFX_TO_UINT16X2(i * FFX_BROADCAST_FLOAT16X2(1.0 / 32768.0) + FFX_BROADCAST_FLOAT16X2(0.25 / 32768.0)));
    return FfxUInt32x2(ffxPackBytesX0Y2Y1Y0(FfxUInt32x2(d.x, b)), ffxPackBytesX2Y2Y1Y0(FfxUInt32x2(d.y, b)));
}
















FfxUInt32x2 ffxPermuteZeroBasedSByte0Float16x2ToUint2(FfxUInt32x2 d, FfxFloat16x2 i)
{
    FfxUInt32 b = FFX_UINT16X2_TO_UINT32(FFX_TO_UINT16X2(i * FFX_BROADCAST_FLOAT16X2(1.0 / 32768.0) + FFX_BROADCAST_FLOAT16X2(0.25 / 32768.0))) ^ 0x00800080u;
    return FfxUInt32x2(ffxPackBytesY3Y2Y1X0(FfxUInt32x2(d.x, b)), ffxPackBytesY3Y2Y1X2(FfxUInt32x2(d.y, b)));
}
















FfxUInt32x2 ffxPermuteZeroBasedSByte1Float16x2ToUint2(FfxUInt32x2 d, FfxFloat16x2 i)
{
    FfxUInt32 b = FFX_UINT16X2_TO_UINT32(FFX_TO_UINT16X2(i * FFX_BROADCAST_FLOAT16X2(1.0 / 32768.0) + FFX_BROADCAST_FLOAT16X2(0.25 / 32768.0))) ^ 0x00800080u;
    return FfxUInt32x2(ffxPackBytesY3Y2X0Y0(FfxUInt32x2(d.x, b)), ffxPackBytesY3Y2X2Y0(FfxUInt32x2(d.y, b)));
}
















FfxUInt32x2 ffxPermuteZeroBasedSByte2Float16x2ToUint2(FfxUInt32x2 d, FfxFloat16x2 i)
{
    FfxUInt32 b = FFX_UINT16X2_TO_UINT32(FFX_TO_UINT16X2(i * FFX_BROADCAST_FLOAT16X2(1.0 / 32768.0) + FFX_BROADCAST_FLOAT16X2(0.25 / 32768.0))) ^ 0x00800080u;
    return FfxUInt32x2(ffxPackBytesY3X0Y1Y0(FfxUInt32x2(d.x, b)), ffxPackBytesY3X2Y1Y0(FfxUInt32x2(d.y, b)));
}
















FfxUInt32x2 ffxPermuteZeroBasedSByte3Float16x2ToUint2(FfxUInt32x2 d, FfxFloat16x2 i)
{
    FfxUInt32 b = FFX_UINT16X2_TO_UINT32(FFX_TO_UINT16X2(i * FFX_BROADCAST_FLOAT16X2(1.0 / 32768.0) + FFX_BROADCAST_FLOAT16X2(0.25 / 32768.0))) ^ 0x00800080u;
    return FfxUInt32x2(ffxPackBytesX0Y2Y1Y0(FfxUInt32x2(d.x, b)), ffxPackBytesX2Y2Y1Y0(FfxUInt32x2(d.y, b)));
}











FfxFloat16x2 ffxPermuteSByte0Uint2ToFloat16x2(FfxUInt32x2 i)
{
    return FFX_TO_FLOAT16X2(FFX_UINT32_TO_UINT16X2(ffxPackBytesZeroY0ZeroX0(i))) * FFX_BROADCAST_FLOAT16X2(32768.0) - FFX_BROADCAST_FLOAT16X2(0.25);
}











FfxFloat16x2 ffxPermuteSByte1Uint2ToFloat16x2(FfxUInt32x2 i)
{
    return FFX_TO_FLOAT16X2(FFX_UINT32_TO_UINT16X2(ffxPackBytesZeroY1ZeroX1(i))) * FFX_BROADCAST_FLOAT16X2(32768.0) - FFX_BROADCAST_FLOAT16X2(0.25);
}











FfxFloat16x2 ffxPermuteSByte2Uint2ToFloat16x2(FfxUInt32x2 i)
{
    return FFX_TO_FLOAT16X2(FFX_UINT32_TO_UINT16X2(ffxPackBytesZeroY2ZeroX2(i))) * FFX_BROADCAST_FLOAT16X2(32768.0) - FFX_BROADCAST_FLOAT16X2(0.25);
}











FfxFloat16x2 ffxPermuteSByte3Uint2ToFloat16x2(FfxUInt32x2 i)
{
    return FFX_TO_FLOAT16X2(FFX_UINT32_TO_UINT16X2(ffxPackBytesZeroY3ZeroX3(i))) * FFX_BROADCAST_FLOAT16X2(32768.0) - FFX_BROADCAST_FLOAT16X2(0.25);
}











FfxFloat16x2 ffxPermuteZeroBasedSByte0Uint2ToFloat16x2(FfxUInt32x2 i)
{
    return FFX_TO_FLOAT16X2(FFX_UINT32_TO_UINT16X2(ffxPackBytesZeroY0ZeroX0(i) ^ 0x00800080u)) * FFX_BROADCAST_FLOAT16X2(32768.0) - FFX_BROADCAST_FLOAT16X2(0.25);
}











FfxFloat16x2 ffxPermuteZeroBasedSByte1Uint2ToFloat16x2(FfxUInt32x2 i)
{
    return FFX_TO_FLOAT16X2(FFX_UINT32_TO_UINT16X2(ffxPackBytesZeroY1ZeroX1(i) ^ 0x00800080u)) * FFX_BROADCAST_FLOAT16X2(32768.0) - FFX_BROADCAST_FLOAT16X2(0.25);
}











FfxFloat16x2 ffxPermuteZeroBasedSByte2Uint2ToFloat16x2(FfxUInt32x2 i)
{
    return FFX_TO_FLOAT16X2(FFX_UINT32_TO_UINT16X2(ffxPackBytesZeroY2ZeroX2(i) ^ 0x00800080u)) * FFX_BROADCAST_FLOAT16X2(32768.0) - FFX_BROADCAST_FLOAT16X2(0.25);
}











FfxFloat16x2 ffxPermuteZeroBasedSByte3Uint2ToFloat16x2(FfxUInt32x2 i)
{
    return FFX_TO_FLOAT16X2(FFX_UINT32_TO_UINT16X2(ffxPackBytesZeroY3ZeroX3(i) ^ 0x00800080u)) * FFX_BROADCAST_FLOAT16X2(32768.0) - FFX_BROADCAST_FLOAT16X2(0.25);
}















FfxFloat16 ffxApproximateSqrtHalf(FfxFloat16 a)
{
    return FFX_TO_FLOAT16((FFX_TO_UINT16(a) >> FFX_BROADCAST_UINT16(1)) + FFX_BROADCAST_UINT16(0x1de2));
}















FfxFloat16x2 ffxApproximateSqrtHalf(FfxFloat16x2 a)
{
    return FFX_TO_FLOAT16X2((FFX_TO_UINT16X2(a) >> FFX_BROADCAST_UINT16X2(1)) + FFX_BROADCAST_UINT16X2(0x1de2));
}















FfxFloat16x3 ffxApproximateSqrtHalf(FfxFloat16x3 a)
{
    return FFX_TO_FLOAT16X3((FFX_TO_UINT16X3(a) >> FFX_BROADCAST_UINT16X3(1)) + FFX_BROADCAST_UINT16X3(0x1de2));
}















FfxFloat16 ffxApproximateReciprocalHalf(FfxFloat16 a)
{
    return FFX_TO_FLOAT16(FFX_BROADCAST_UINT16(0x7784) - FFX_TO_UINT16(a));
}















FfxFloat16x2 ffxApproximateReciprocalHalf(FfxFloat16x2 a)
{
    return FFX_TO_FLOAT16X2(FFX_BROADCAST_UINT16X2(0x7784) - FFX_TO_UINT16X2(a));
}















FfxFloat16x3 ffxApproximateReciprocalHalf(FfxFloat16x3 a)
{
    return FFX_TO_FLOAT16X3(FFX_BROADCAST_UINT16X3(0x7784) - FFX_TO_UINT16X3(a));
}















FfxFloat16x4 ffxApproximateReciprocalHalf(FfxFloat16x4 a)
{
    return FFX_TO_FLOAT16X4(FFX_BROADCAST_UINT16X4(0x7784) - FFX_TO_UINT16X4(a));
}















FfxFloat16 ffxApproximateReciprocalMediumHalf(FfxFloat16 a)
{
    FfxFloat16 b = FFX_TO_FLOAT16(FFX_BROADCAST_UINT16(0x778d) - FFX_TO_UINT16(a));
    return b * (-b * a + FFX_BROADCAST_FLOAT16(2.0));
}















FfxFloat16x2 ffxApproximateReciprocalMediumHalf(FfxFloat16x2 a)
{
    FfxFloat16x2 b = FFX_TO_FLOAT16X2(FFX_BROADCAST_UINT16X2(0x778d) - FFX_TO_UINT16X2(a));
    return b * (-b * a + FFX_BROADCAST_FLOAT16X2(2.0));
}















FfxFloat16x3 ffxApproximateReciprocalMediumHalf(FfxFloat16x3 a)
{
    FfxFloat16x3 b = FFX_TO_FLOAT16X3(FFX_BROADCAST_UINT16X3(0x778d) - FFX_TO_UINT16X3(a));
    return b * (-b * a + FFX_BROADCAST_FLOAT16X3(2.0));
}















FfxFloat16x4 ffxApproximateReciprocalMediumHalf(FfxFloat16x4 a)
{
    FfxFloat16x4 b = FFX_TO_FLOAT16X4(FFX_BROADCAST_UINT16X4(0x778d) - FFX_TO_UINT16X4(a));
    return b * (-b * a + FFX_BROADCAST_FLOAT16X4(2.0));
}















FfxFloat16 ffxApproximateReciprocalSquareRootHalf(FfxFloat16 a)
{
    return FFX_TO_FLOAT16(FFX_BROADCAST_UINT16(0x59a3) - (FFX_TO_UINT16(a) >> FFX_BROADCAST_UINT16(1)));
}















FfxFloat16x2 ffxApproximateReciprocalSquareRootHalf(FfxFloat16x2 a)
{
    return FFX_TO_FLOAT16X2(FFX_BROADCAST_UINT16X2(0x59a3) - (FFX_TO_UINT16X2(a) >> FFX_BROADCAST_UINT16X2(1)));
}















FfxFloat16x3 ffxApproximateReciprocalSquareRootHalf(FfxFloat16x3 a)
{
    return FFX_TO_FLOAT16X3(FFX_BROADCAST_UINT16X3(0x59a3) - (FFX_TO_UINT16X3(a) >> FFX_BROADCAST_UINT16X3(1)));
}















FfxFloat16x4 ffxApproximateReciprocalSquareRootHalf(FfxFloat16x4 a)
{
    return FFX_TO_FLOAT16X4(FFX_BROADCAST_UINT16X4(0x59a3) - (FFX_TO_UINT16X4(a) >> FFX_BROADCAST_UINT16X4(1)));
}










FfxFloat16 ffxParabolicSinHalf(FfxFloat16 x)
{
    return x * abs(x) - x;
}










FfxFloat16x2 ffxParabolicSinHalf(FfxFloat16x2 x)
{
    return x * abs(x) - x;
}










FfxFloat16 ffxParabolicCosHalf(FfxFloat16 x)
{
    x = ffxFract(x * FFX_BROADCAST_FLOAT16(0.5) + FFX_BROADCAST_FLOAT16(0.75));
    x = x * FFX_BROADCAST_FLOAT16(2.0) - FFX_BROADCAST_FLOAT16(1.0);
    return ffxParabolicSinHalf(x);
}










FfxFloat16x2 ffxParabolicCosHalf(FfxFloat16x2 x)
{
    x = ffxFract(x * FFX_BROADCAST_FLOAT16X2(0.5) + FFX_BROADCAST_FLOAT16X2(0.75));
    x = x * FFX_BROADCAST_FLOAT16X2(2.0) - FFX_BROADCAST_FLOAT16X2(1.0);
    return ffxParabolicSinHalf(x);
}










FfxFloat16x2 ffxParabolicSinCosHalf(FfxFloat16 x)
{
    FfxFloat16 y = ffxFract(x * FFX_BROADCAST_FLOAT16(0.5) + FFX_BROADCAST_FLOAT16(0.75));
    y     = y * FFX_BROADCAST_FLOAT16(2.0) - FFX_BROADCAST_FLOAT16(1.0);
    return ffxParabolicSinHalf(FfxFloat16x2(x, y));
}










FfxUInt16 ffxZeroOneAndHalf(FfxUInt16 x, FfxUInt16 y)
{
    return min(x, y);
}










FfxUInt16x2 ffxZeroOneAndHalf(FfxUInt16x2 x, FfxUInt16x2 y)
{
    return min(x, y);
}










FfxUInt16x3 ffxZeroOneAndHalf(FfxUInt16x3 x, FfxUInt16x3 y)
{
    return min(x, y);
}










FfxUInt16x4 ffxZeroOneAndHalf(FfxUInt16x4 x, FfxUInt16x4 y)
{
    return min(x, y);
}










FfxUInt16 ffxZeroOneNotHalf(FfxUInt16 x)
{
    return x ^ FFX_BROADCAST_UINT16(1);
}










FfxUInt16x2 ffxZeroOneNotHalf(FfxUInt16x2 x)
{
    return x ^ FFX_BROADCAST_UINT16X2(1);
}










FfxUInt16x3 ffxZeroOneNotHalf(FfxUInt16x3 x)
{
    return x ^ FFX_BROADCAST_UINT16X3(1);
}










FfxUInt16x4 ffxZeroOneNotHalf(FfxUInt16x4 x)
{
    return x ^ FFX_BROADCAST_UINT16X4(1);
}










FfxUInt16 ffxZeroOneOrHalf(FfxUInt16 x, FfxUInt16 y)
{
    return max(x, y);
}










FfxUInt16x2 ffxZeroOneOrHalf(FfxUInt16x2 x, FfxUInt16x2 y)
{
    return max(x, y);
}










FfxUInt16x3 ffxZeroOneOrHalf(FfxUInt16x3 x, FfxUInt16x3 y)
{
    return max(x, y);
}










FfxUInt16x4 ffxZeroOneOrHalf(FfxUInt16x4 x, FfxUInt16x4 y)
{
    return max(x, y);
}









FfxUInt16 ffxZeroOneFloat16ToUint16(FfxFloat16 x)
{
    return FFX_TO_UINT16(x * FFX_TO_FLOAT16(FFX_TO_UINT16(1)));
}









FfxUInt16x2 ffxZeroOneFloat16x2ToUint16x2(FfxFloat16x2 x)
{
    return FFX_TO_UINT16X2(x * FFX_TO_FLOAT16X2(FfxUInt16x2(1, 1)));
}









FfxUInt16x3 ffxZeroOneFloat16x3ToUint16x3(FfxFloat16x3 x)
{
    return FFX_TO_UINT16X3(x * FFX_TO_FLOAT16X3(FfxUInt16x3(1, 1, 1)));
}









FfxUInt16x4 ffxZeroOneFloat16x4ToUint16x4(FfxFloat16x4 x)
{
    return FFX_TO_UINT16X4(x * FFX_TO_FLOAT16X4(FfxUInt16x4(1, 1, 1, 1)));
}









FfxFloat16 ffxZeroOneUint16ToFloat16(FfxUInt16 x)
{
    return FFX_TO_FLOAT16(x * FFX_TO_UINT16(FFX_TO_FLOAT16(1.0)));
}









FfxFloat16x2 ffxZeroOneUint16x2ToFloat16x2(FfxUInt16x2 x)
{
    return FFX_TO_FLOAT16X2(x * FFX_TO_UINT16X2(FfxUInt16x2(FFX_TO_FLOAT16(1.0), FFX_TO_FLOAT16(1.0))));
}









FfxFloat16x3 ffxZeroOneUint16x3ToFloat16x3(FfxUInt16x3 x)
{
    return FFX_TO_FLOAT16X3(x * FFX_TO_UINT16X3(FfxUInt16x3(FFX_TO_FLOAT16(1.0), FFX_TO_FLOAT16(1.0), FFX_TO_FLOAT16(1.0))));
}









FfxFloat16x4 ffxZeroOneUint16x4ToFloat16x4(FfxUInt16x4 x)
{
    return FFX_TO_FLOAT16X4(x * FFX_TO_UINT16X4(FfxUInt16x4(FFX_TO_FLOAT16(1.0), FFX_TO_FLOAT16(1.0), FFX_TO_FLOAT16(1.0), FFX_TO_FLOAT16(1.0))));
}










FfxFloat16 ffxZeroOneAndHalf(FfxFloat16 x, FfxFloat16 y)
{
    return min(x, y);
}










FfxFloat16x2 ffxZeroOneAndHalf(FfxFloat16x2 x, FfxFloat16x2 y)
{
    return min(x, y);
}










FfxFloat16x3 ffxZeroOneAndHalf(FfxFloat16x3 x, FfxFloat16x3 y)
{
    return min(x, y);
}










FfxFloat16x4 ffxZeroOneAndHalf(FfxFloat16x4 x, FfxFloat16x4 y)
{
    return min(x, y);
}










FfxFloat16 ffxSignedZeroOneAndOrHalf(FfxFloat16 x, FfxFloat16 y)
{
    return (-x) * y + FFX_BROADCAST_FLOAT16(1.0);
}










FfxFloat16x2 ffxSignedZeroOneAndOrHalf(FfxFloat16x2 x, FfxFloat16x2 y)
{
    return (-x) * y + FFX_BROADCAST_FLOAT16X2(1.0);
}










FfxFloat16x3 ffxSignedZeroOneAndOrHalf(FfxFloat16x3 x, FfxFloat16x3 y)
{
    return (-x) * y + FFX_BROADCAST_FLOAT16X3(1.0);
}










FfxFloat16x4 ffxSignedZeroOneAndOrHalf(FfxFloat16x4 x, FfxFloat16x4 y)
{
    return (-x) * y + FFX_BROADCAST_FLOAT16X4(1.0);
}












FfxFloat16 ffxZeroOneAndOrHalf(FfxFloat16 x, FfxFloat16 y, FfxFloat16 z)
{
    return ffxSaturate(x * y + z);
}












FfxFloat16x2 ffxZeroOneAndOrHalf(FfxFloat16x2 x, FfxFloat16x2 y, FfxFloat16x2 z)
{
    return ffxSaturate(x * y + z);
}












FfxFloat16x3 ffxZeroOneAndOrHalf(FfxFloat16x3 x, FfxFloat16x3 y, FfxFloat16x3 z)
{
    return ffxSaturate(x * y + z);
}












FfxFloat16x4 ffxZeroOneAndOrHalf(FfxFloat16x4 x, FfxFloat16x4 y, FfxFloat16x4 z)
{
    return ffxSaturate(x * y + z);
}









FfxFloat16 ffxZeroOneIsGreaterThanZeroHalf(FfxFloat16 x)
{
    return ffxSaturate(x * FFX_BROADCAST_FLOAT16(FFX_POSITIVE_INFINITY_HALF));
}









FfxFloat16x2 ffxZeroOneIsGreaterThanZeroHalf(FfxFloat16x2 x)
{
    return ffxSaturate(x * FFX_BROADCAST_FLOAT16X2(FFX_POSITIVE_INFINITY_HALF));
}









FfxFloat16x3 ffxZeroOneIsGreaterThanZeroHalf(FfxFloat16x3 x)
{
    return ffxSaturate(x * FFX_BROADCAST_FLOAT16X3(FFX_POSITIVE_INFINITY_HALF));
}









FfxFloat16x4 ffxZeroOneIsGreaterThanZeroHalf(FfxFloat16x4 x)
{
    return ffxSaturate(x * FFX_BROADCAST_FLOAT16X4(FFX_POSITIVE_INFINITY_HALF));
}









FfxFloat16 ffxZeroOneNotHalf(FfxFloat16 x)
{
    return FFX_BROADCAST_FLOAT16(1.0) - x;
}









FfxFloat16x2 ffxZeroOneNotHalf(FfxFloat16x2 x)
{
    return FFX_BROADCAST_FLOAT16X2(1.0) - x;
}









FfxFloat16x3 ffxZeroOneNotHalf(FfxFloat16x3 x)
{
    return FFX_BROADCAST_FLOAT16X3(1.0) - x;
}









FfxFloat16x4 ffxZeroOneNotHalf(FfxFloat16x4 x)
{
    return FFX_BROADCAST_FLOAT16X4(1.0) - x;
}










FfxFloat16 ffxZeroOneOrHalf(FfxFloat16 x, FfxFloat16 y)
{
    return max(x, y);
}
)<!>" R"<!>(









FfxFloat16x2 ffxZeroOneOrHalf(FfxFloat16x2 x, FfxFloat16x2 y)
{
    return max(x, y);
}










FfxFloat16x3 ffxZeroOneOrHalf(FfxFloat16x3 x, FfxFloat16x3 y)
{
    return max(x, y);
}










FfxFloat16x4 ffxZeroOneOrHalf(FfxFloat16x4 x, FfxFloat16x4 y)
{
    return max(x, y);
}











FfxFloat16 ffxZeroOneSelectHalf(FfxFloat16 x, FfxFloat16 y, FfxFloat16 z)
{
    FfxFloat16 r = (-x) * z + z;
    return x * y + r;
}











FfxFloat16x2 ffxZeroOneSelectHalf(FfxFloat16x2 x, FfxFloat16x2 y, FfxFloat16x2 z)
{
    FfxFloat16x2 r = (-x) * z + z;
    return x * y + r;
}











FfxFloat16x3 ffxZeroOneSelectHalf(FfxFloat16x3 x, FfxFloat16x3 y, FfxFloat16x3 z)
{
    FfxFloat16x3 r = (-x) * z + z;
    return x * y + r;
}











FfxFloat16x4 ffxZeroOneSelectHalf(FfxFloat16x4 x, FfxFloat16x4 y, FfxFloat16x4 z)
{
    FfxFloat16x4 r = (-x) * z + z;
    return x * y + r;
}









FfxFloat16 ffxZeroOneIsSignedHalf(FfxFloat16 x)
{
    return ffxSaturate(x * FFX_BROADCAST_FLOAT16(FFX_NEGATIVE_INFINITY_HALF));
}









FfxFloat16x2 ffxZeroOneIsSignedHalf(FfxFloat16x2 x)
{
    return ffxSaturate(x * FFX_BROADCAST_FLOAT16X2(FFX_NEGATIVE_INFINITY_HALF));
}









FfxFloat16x3 ffxZeroOneIsSignedHalf(FfxFloat16x3 x)
{
    return ffxSaturate(x * FFX_BROADCAST_FLOAT16X3(FFX_NEGATIVE_INFINITY_HALF));
}









FfxFloat16x4 ffxZeroOneIsSignedHalf(FfxFloat16x4 x)
{
    return ffxSaturate(x * FFX_BROADCAST_FLOAT16X4(FFX_NEGATIVE_INFINITY_HALF));
}















FfxFloat16 ffxRec709FromLinearHalf(FfxFloat16 c)
{
    FfxFloat16x3 j = FfxFloat16x3(0.018 * 4.5, 4.5, 0.45);
    FfxFloat16x2 k = FfxFloat16x2(1.099, -0.099);
    return clamp(j.x, c * j.y, pow(c, j.z) * k.x + k.y);
}















FfxFloat16x2 ffxRec709FromLinearHalf(FfxFloat16x2 c)
{
    FfxFloat16x3 j = FfxFloat16x3(0.018 * 4.5, 4.5, 0.45);
    FfxFloat16x2 k = FfxFloat16x2(1.099, -0.099);
    return clamp(j.xx, c * j.yy, pow(c, j.zz) * k.xx + k.yy);
}















FfxFloat16x3 ffxRec709FromLinearHalf(FfxFloat16x3 c)
{
    FfxFloat16x3 j = FfxFloat16x3(0.018 * 4.5, 4.5, 0.45);
    FfxFloat16x2 k = FfxFloat16x2(1.099, -0.099);
    return clamp(j.xxx, c * j.yyy, pow(c, j.zzz) * k.xxx + k.yyy);
}














FfxFloat16 ffxGammaFromLinearHalf(FfxFloat16 c, FfxFloat16 rcpX)
{
    return pow(c, FFX_BROADCAST_FLOAT16(rcpX));
}














FfxFloat16x2 ffxGammaFromLinearHalf(FfxFloat16x2 c, FfxFloat16 rcpX)
{
    return pow(c, FFX_BROADCAST_FLOAT16X2(rcpX));
}














FfxFloat16x3 ffxGammaFromLinearHalf(FfxFloat16x3 c, FfxFloat16 rcpX)
{
    return pow(c, FFX_BROADCAST_FLOAT16X3(rcpX));
}









FfxFloat16 ffxSrgbFromLinearHalf(FfxFloat16 c)
{
    FfxFloat16x3 j = FfxFloat16x3(0.0031308 * 12.92, 12.92, 1.0 / 2.4);
    FfxFloat16x2 k = FfxFloat16x2(1.055, -0.055);
    return clamp(j.x, c * j.y, pow(c, j.z) * k.x + k.y);
}









FfxFloat16x2 ffxSrgbFromLinearHalf(FfxFloat16x2 c)
{
    FfxFloat16x3 j = FfxFloat16x3(0.0031308 * 12.92, 12.92, 1.0 / 2.4);
    FfxFloat16x2 k = FfxFloat16x2(1.055, -0.055);
    return clamp(j.xx, c * j.yy, pow(c, j.zz) * k.xx + k.yy);
}









FfxFloat16x3 ffxSrgbFromLinearHalf(FfxFloat16x3 c)
{
    FfxFloat16x3 j = FfxFloat16x3(0.0031308 * 12.92, 12.92, 1.0 / 2.4);
    FfxFloat16x2 k = FfxFloat16x2(1.055, -0.055);
    return clamp(j.xxx, c * j.yyy, pow(c, j.zzz) * k.xxx + k.yyy);
}









FfxFloat16 ffxSquareRootHalf(FfxFloat16 c)
{
    return sqrt(c);
}









FfxFloat16x2 ffxSquareRootHalf(FfxFloat16x2 c)
{
    return sqrt(c);
}









FfxFloat16x3 ffxSquareRootHalf(FfxFloat16x3 c)
{
    return sqrt(c);
}









FfxFloat16 ffxCubeRootHalf(FfxFloat16 c)
{
    return pow(c, FFX_BROADCAST_FLOAT16(1.0 / 3.0));
}









FfxFloat16x2 ffxCubeRootHalf(FfxFloat16x2 c)
{
    return pow(c, FFX_BROADCAST_FLOAT16X2(1.0 / 3.0));
}









FfxFloat16x3 ffxCubeRootHalf(FfxFloat16x3 c)
{
    return pow(c, FFX_BROADCAST_FLOAT16X3(1.0 / 3.0));
}









FfxFloat16 ffxLinearFromRec709Half(FfxFloat16 c)
{
    FfxFloat16x3 j = FfxFloat16x3(0.081 / 4.5, 1.0 / 4.5, 1.0 / 0.45);
    FfxFloat16x2 k = FfxFloat16x2(1.0 / 1.099, 0.099 / 1.099);
    return ffxZeroOneSelectHalf(ffxZeroOneIsSignedHalf(c - j.x), c * j.y, pow(c * k.x + k.y, j.z));
}









FfxFloat16x2 ffxLinearFromRec709Half(FfxFloat16x2 c)
{
    FfxFloat16x3 j = FfxFloat16x3(0.081 / 4.5, 1.0 / 4.5, 1.0 / 0.45);
    FfxFloat16x2 k = FfxFloat16x2(1.0 / 1.099, 0.099 / 1.099);
    return ffxZeroOneSelectHalf(ffxZeroOneIsSignedHalf(c - j.xx), c * j.yy, pow(c * k.xx + k.yy, j.zz));
}









FfxFloat16x3 ffxLinearFromRec709Half(FfxFloat16x3 c)
{
    FfxFloat16x3 j = FfxFloat16x3(0.081 / 4.5, 1.0 / 4.5, 1.0 / 0.45);
    FfxFloat16x2 k = FfxFloat16x2(1.0 / 1.099, 0.099 / 1.099);
    return ffxZeroOneSelectHalf(ffxZeroOneIsSignedHalf(c - j.xxx), c * j.yyy, pow(c * k.xxx + k.yyy, j.zzz));
}












FfxFloat16 ffxLinearFromGammaHalf(FfxFloat16 c, FfxFloat16 x)
{
    return pow(c, FFX_BROADCAST_FLOAT16(x));
}












FfxFloat16x2 ffxLinearFromGammaHalf(FfxFloat16x2 c, FfxFloat16 x)
{
    return pow(c, FFX_BROADCAST_FLOAT16X2(x));
}












FfxFloat16x3 ffxLinearFromGammaHalf(FfxFloat16x3 c, FfxFloat16 x)
{
    return pow(c, FFX_BROADCAST_FLOAT16X3(x));
}











FfxFloat16 ffxLinearFromSrgbHalf(FfxFloat16 c)
{
    FfxFloat16x3 j = FfxFloat16x3(0.04045 / 12.92, 1.0 / 12.92, 2.4);
    FfxFloat16x2 k = FfxFloat16x2(1.0 / 1.055, 0.055 / 1.055);
    return ffxZeroOneSelectHalf(ffxZeroOneIsSignedHalf(c - j.x), c * j.y, pow(c * k.x + k.y, j.z));
}











FfxFloat16x2 ffxLinearFromSrgbHalf(FfxFloat16x2 c)
{
    FfxFloat16x3 j = FfxFloat16x3(0.04045 / 12.92, 1.0 / 12.92, 2.4);
    FfxFloat16x2 k = FfxFloat16x2(1.0 / 1.055, 0.055 / 1.055);
    return ffxZeroOneSelectHalf(ffxZeroOneIsSignedHalf(c - j.xx), c * j.yy, pow(c * k.xx + k.yy, j.zz));
}











FfxFloat16x3 ffxLinearFromSrgbHalf(FfxFloat16x3 c)
{
    FfxFloat16x3 j = FfxFloat16x3(0.04045 / 12.92, 1.0 / 12.92, 2.4);
    FfxFloat16x2 k = FfxFloat16x2(1.0 / 1.055, 0.055 / 1.055);
    return ffxZeroOneSelectHalf(ffxZeroOneIsSignedHalf(c - j.xxx), c * j.yyy, pow(c * k.xxx + k.yyy, j.zzz));
}














FfxUInt16x2 ffxRemapForQuadHalf(FfxUInt32 a)
{
    return FfxUInt16x2(bitfieldExtract(a, 1u, 3u), bitfieldInsertMask(bitfieldExtract(a, 3u, 3u), a, 1u));
}




















FfxUInt16x2 ffxRemapForWaveReductionHalf(FfxUInt32 a)
{
    return FfxUInt16x2(bitfieldInsertMask(bitfieldExtract(a, 2u, 3u), a, 1u), bitfieldInsertMask(bitfieldExtract(a, 3u, 3u), bitfieldExtract(a, 1u, 2u), 2u));
}

#endif  





















FfxFloat32x3 opAAddOneF3(FfxFloat32x3 d, FfxFloat32x3 a, FfxFloat32 b)
{
    d = a + ffxBroadcast3(b);
    return d;
}

FfxFloat32x3 opACpyF3(FfxFloat32x3 d, FfxFloat32x3 a)
{
    d = a;
    return d;
}

FfxFloat32x3 opAMulF3(FfxFloat32x3 d, FfxFloat32x3 a, FfxFloat32x3 b)
{
    d = a * b;
    return d;
}

FfxFloat32x3 opAMulOneF3(FfxFloat32x3 d, FfxFloat32x3 a, FfxFloat32 b)
{
    d = a * ffxBroadcast3(b);
    return d;
}

FfxFloat32x3 opARcpF3(FfxFloat32x3 d, FfxFloat32x3 a)
{
    d = rcp(a);
    return d;
}
#endif // #if defined(FFX_GPU)
#endif 
#endif // #if defined(FFX_GPU)

#if defined(FFX_GPU)
#ifndef FFX_FSR2_PREFER_WAVE64
#define FFX_FSR2_PREFER_WAVE64
#endif 

#if defined(FSR2_BIND_CB_FSR2)
	layout (set = 1, binding = FSR2_BIND_CB_FSR2, std140) uniform cbFSR2_t
	{
		FfxInt32x2    iRenderSize;
		FfxInt32x2    iMaxRenderSize;
		FfxInt32x2    iDisplaySize;
		FfxInt32x2    iInputColorResourceDimensions;
		FfxInt32x2    iLumaMipDimensions;
		FfxInt32      iLumaMipLevelToUse;
		FfxInt32      iFrameIndex;

		FfxFloat32x4  fDeviceToViewDepth;
		FfxFloat32x2  fJitter;
		FfxFloat32x2  fMotionVectorScale;
		FfxFloat32x2  fDownscaleFactor;
		FfxFloat32x2  fMotionVectorJitterCancellation;
		FfxFloat32    fPreExposure;
		FfxFloat32    fPreviousFramePreExposure;
		FfxFloat32    fTanHalfFOV;
		FfxFloat32    fJitterSequenceLength;
		FfxFloat32    fDeltaTime;
		FfxFloat32    fDynamicResChangeFactor;
		FfxFloat32    fViewSpaceToMetersFactor;
		
		
		FfxFloat32    fPad;
		mat4          mReprojectionMatrix;
		
	} cbFSR2;
#endif

FfxInt32x2 RenderSize()
{
	return cbFSR2.iRenderSize;
}

FfxInt32x2 MaxRenderSize()
{
	return cbFSR2.iMaxRenderSize;
}

FfxInt32x2 DisplaySize()
{
	return cbFSR2.iDisplaySize;
}

FfxInt32x2 InputColorResourceDimensions()
{
	return cbFSR2.iInputColorResourceDimensions;
}

FfxInt32x2 LumaMipDimensions()
{
	return cbFSR2.iLumaMipDimensions;
}

FfxInt32  LumaMipLevelToUse()
{
	return cbFSR2.iLumaMipLevelToUse;
}

FfxInt32 FrameIndex()
{
	return cbFSR2.iFrameIndex;
}

FfxFloat32x4 DeviceToViewSpaceTransformFactors()
{
	return cbFSR2.fDeviceToViewDepth;
}

FfxFloat32x2 Jitter()
{
	return cbFSR2.fJitter;
}

FfxFloat32x2 MotionVectorScale()
{
	return cbFSR2.fMotionVectorScale;
}

FfxFloat32x2 DownscaleFactor()
{
	return cbFSR2.fDownscaleFactor;
}

FfxFloat32x2 MotionVectorJitterCancellation()
{
	return cbFSR2.fMotionVectorJitterCancellation;
}

FfxFloat32 PreExposure()
{
	return cbFSR2.fPreExposure;
}

FfxFloat32 PreviousFramePreExposure()
{
	return cbFSR2.fPreviousFramePreExposure;
}

FfxFloat32 TanHalfFoV()
{
	return cbFSR2.fTanHalfFOV;
}

FfxFloat32 JitterSequenceLength()
{
	return cbFSR2.fJitterSequenceLength;
}

FfxFloat32 DeltaTime()
{
	return cbFSR2.fDeltaTime;
}

FfxFloat32 DynamicResChangeFactor()
{
	return cbFSR2.fDynamicResChangeFactor;
}

FfxFloat32 ViewSpaceToMetersFactor()
{
	return cbFSR2.fViewSpaceToMetersFactor;
}

layout (set = 0, binding = 0) uniform sampler s_PointClamp;
layout (set = 0, binding = 1) uniform sampler s_LinearClamp;


#if defined(FSR2_BIND_SRV_INPUT_OPAQUE_ONLY)
	layout (set = 1, binding = FSR2_BIND_SRV_INPUT_OPAQUE_ONLY)                       uniform texture2D  r_input_opaque_only;
#endif
#if defined(FSR2_BIND_SRV_INPUT_COLOR)
	layout (set = 1, binding = FSR2_BIND_SRV_INPUT_COLOR)                             uniform texture2D  r_input_color_jittered;
#endif
#if defined(FSR2_BIND_SRV_INPUT_MOTION_VECTORS)
	layout (set = 1, binding = FSR2_BIND_SRV_INPUT_MOTION_VECTORS)                    uniform texture2D  r_input_motion_vectors;
#endif
#if defined(FSR2_BIND_SRV_INPUT_DEPTH)
	layout (set = 1, binding = FSR2_BIND_SRV_INPUT_DEPTH)                             uniform texture2D  r_input_depth;
#endif
#if defined(FSR2_BIND_SRV_INPUT_EXPOSURE)
	layout (set = 1, binding = FSR2_BIND_SRV_INPUT_EXPOSURE)                          uniform texture2D  r_input_exposure;
#endif
#if defined(FSR2_BIND_SRV_AUTO_EXPOSURE)
	layout(set = 1, binding = FSR2_BIND_SRV_AUTO_EXPOSURE)                            uniform texture2D  r_auto_exposure;
#endif
#if defined(FSR2_BIND_SRV_REACTIVE_MASK)
	layout (set = 1, binding = FSR2_BIND_SRV_REACTIVE_MASK)                           uniform texture2D  r_reactive_mask;
#endif
#if defined(FSR2_BIND_SRV_TRANSPARENCY_AND_COMPOSITION_MASK)
	layout (set = 1, binding = FSR2_BIND_SRV_TRANSPARENCY_AND_COMPOSITION_MASK)       uniform texture2D  r_transparency_and_composition_mask;
#endif
#if defined(FSR2_BIND_SRV_RECONSTRUCTED_PREV_NEAREST_DEPTH)
	layout (set = 1, binding = FSR2_BIND_SRV_RECONSTRUCTED_PREV_NEAREST_DEPTH)        uniform utexture2D r_reconstructed_previous_nearest_depth;
#endif
#if defined(FSR2_BIND_SRV_DILATED_MOTION_VECTORS)
	layout (set = 1, binding = FSR2_BIND_SRV_DILATED_MOTION_VECTORS)                  uniform texture2D  r_dilated_motion_vectors;
#endif
#if defined (FSR2_BIND_SRV_PREVIOUS_DILATED_MOTION_VECTORS)
	layout(set = 1, binding = FSR2_BIND_SRV_PREVIOUS_DILATED_MOTION_VECTORS)          uniform texture2D  r_previous_dilated_motion_vectors;
#endif
#if defined(FSR2_BIND_SRV_DILATED_DEPTH)
	layout (set = 1, binding = FSR2_BIND_SRV_DILATED_DEPTH)                           uniform texture2D  r_dilatedDepth;
#endif
#if defined(FSR2_BIND_SRV_INTERNAL_UPSCALED)
	layout (set = 1, binding = FSR2_BIND_SRV_INTERNAL_UPSCALED)                       uniform texture2D  r_internal_upscaled_color;
#endif
#if defined(FSR2_BIND_SRV_LOCK_STATUS)
	layout (set = 1, binding = FSR2_BIND_SRV_LOCK_STATUS)                             uniform texture2D  r_lock_status;
#endif
#if defined(FSR2_BIND_SRV_LOCK_INPUT_LUMA)
	layout (set = 1, binding = FSR2_BIND_SRV_LOCK_INPUT_LUMA)                         uniform texture2D  r_lock_input_luma;
#endif
#if defined(FSR2_BIND_SRV_NEW_LOCKS)
	layout(set = 1, binding = FSR2_BIND_SRV_NEW_LOCKS)                                uniform texture2D  r_new_locks;
#endif
#if defined(FSR2_BIND_SRV_PREPARED_INPUT_COLOR)
	layout (set = 1, binding = FSR2_BIND_SRV_PREPARED_INPUT_COLOR)                    uniform texture2D  r_prepared_input_color;
#endif
#if defined(FSR2_BIND_SRV_LUMA_HISTORY)
	layout (set = 1, binding = FSR2_BIND_SRV_LUMA_HISTORY)                            uniform texture2D  r_luma_history;
#endif
#if defined(FSR2_BIND_SRV_RCAS_INPUT)
	layout (set = 1, binding = FSR2_BIND_SRV_RCAS_INPUT)                              uniform texture2D  r_rcas_input;
#endif
#if defined(FSR2_BIND_SRV_LANCZOS_LUT)
	layout (set = 1, binding = FSR2_BIND_SRV_LANCZOS_LUT)                             uniform texture2D  r_lanczos_lut;
#endif
#if defined(FSR2_BIND_SRV_SCENE_LUMINANCE_MIPS)
	layout (set = 1, binding = FSR2_BIND_SRV_SCENE_LUMINANCE_MIPS)                    uniform texture2D  r_imgMips;
#endif
#if defined(FSR2_BIND_SRV_UPSCALE_MAXIMUM_BIAS_LUT)
	layout (set = 1, binding = FSR2_BIND_SRV_UPSCALE_MAXIMUM_BIAS_LUT)                uniform texture2D  r_upsample_maximum_bias_lut;
#endif
#if defined(FSR2_BIND_SRV_DILATED_REACTIVE_MASKS)
	layout (set = 1, binding = FSR2_BIND_SRV_DILATED_REACTIVE_MASKS)                  uniform texture2D  r_dilated_reactive_masks;
#endif			 
#if defined(FSR2_BIND_SRV_PREV_PRE_ALPHA_COLOR)
	layout(set = 1, binding = FSR2_BIND_SRV_PREV_PRE_ALPHA_COLOR) 				      uniform texture2D  r_input_prev_color_pre_alpha;
#endif
#if defined(FSR2_BIND_SRV_PREV_POST_ALPHA_COLOR)
	layout(set = 1, binding = FSR2_BIND_SRV_PREV_POST_ALPHA_COLOR) 				      uniform texture2D  r_input_prev_color_post_alpha;
#endif

)<!>" R"<!>(
#if defined FSR2_BIND_UAV_RECONSTRUCTED_PREV_NEAREST_DEPTH
	layout (set = 1, binding = FSR2_BIND_UAV_RECONSTRUCTED_PREV_NEAREST_DEPTH, r32ui) uniform uimage2D   rw_reconstructed_previous_nearest_depth;
#endif
#if defined FSR2_BIND_UAV_DILATED_MOTION_VECTORS
	layout (set = 1, binding = FSR2_BIND_UAV_DILATED_MOTION_VECTORS, rg16f)           writeonly uniform image2D  rw_dilated_motion_vectors;
#endif
#if defined FSR2_BIND_UAV_DILATED_DEPTH
	layout (set = 1, binding = FSR2_BIND_UAV_DILATED_DEPTH, r16f)                     writeonly uniform image2D  rw_dilatedDepth;
#endif
#if defined FSR2_BIND_UAV_INTERNAL_UPSCALED
	layout (set = 1, binding = FSR2_BIND_UAV_INTERNAL_UPSCALED, rgba16f)              writeonly uniform image2D  rw_internal_upscaled_color;
#endif
#if defined FSR2_BIND_UAV_LOCK_STATUS
	layout (set = 1, binding = FSR2_BIND_UAV_LOCK_STATUS, rg16f)                      uniform image2D    rw_lock_status;
#endif
#if defined(FSR2_BIND_UAV_LOCK_INPUT_LUMA)
	layout(set = 1, binding = FSR2_BIND_UAV_LOCK_INPUT_LUMA, r16f)                    writeonly uniform image2D    rw_lock_input_luma;
#endif
#if defined FSR2_BIND_UAV_NEW_LOCKS
	layout(set = 1, binding = FSR2_BIND_UAV_NEW_LOCKS, r8)				 		      uniform image2D    rw_new_locks;
#endif
#if defined FSR2_BIND_UAV_PREPARED_INPUT_COLOR
	layout (set = 1, binding = FSR2_BIND_UAV_PREPARED_INPUT_COLOR, rgba16)            writeonly uniform image2D  rw_prepared_input_color;
#endif
#if defined FSR2_BIND_UAV_LUMA_HISTORY
	layout (set = 1, binding = FSR2_BIND_UAV_LUMA_HISTORY, rgba8)                     uniform image2D  rw_luma_history;
#endif
#if defined FSR2_BIND_UAV_UPSCALED_OUTPUT
	layout (set = 1, binding = FSR2_BIND_UAV_UPSCALED_OUTPUT /* app controlled format */) writeonly uniform image2D  rw_upscaled_output;
#endif
#if defined FSR2_BIND_UAV_EXPOSURE_MIP_LUMA_CHANGE
	layout (set = 1, binding = FSR2_BIND_UAV_EXPOSURE_MIP_LUMA_CHANGE, r16f)              coherent uniform image2D  rw_img_mip_shading_change;
#endif
#if defined FSR2_BIND_UAV_EXPOSURE_MIP_5
	layout (set = 1, binding = FSR2_BIND_UAV_EXPOSURE_MIP_5, r16f)                        coherent uniform image2D  rw_img_mip_5;
#endif
#if defined FSR2_BIND_UAV_DILATED_REACTIVE_MASKS
	layout (set = 1, binding = FSR2_BIND_UAV_DILATED_REACTIVE_MASKS, rg8)                 writeonly uniform image2D	 rw_dilated_reactive_masks;
#endif 
#if defined FSR2_BIND_UAV_EXPOSURE 
	layout (set = 1, binding = FSR2_BIND_UAV_EXPOSURE, rg32f)                         uniform image2D    rw_exposure;
#endif
#if defined FSR2_BIND_UAV_AUTO_EXPOSURE
	layout(set = 1, binding = FSR2_BIND_UAV_AUTO_EXPOSURE, rg32f)                         uniform image2D    rw_auto_exposure;
#endif
#if defined FSR2_BIND_UAV_SPD_GLOBAL_ATOMIC 
	layout (set = 1, binding = FSR2_BIND_UAV_SPD_GLOBAL_ATOMIC, r32ui)       coherent uniform uimage2D   rw_spd_global_atomic;
#endif

#if defined FSR2_BIND_UAV_AUTOREACTIVE
	layout(set = 1, binding = FSR2_BIND_UAV_AUTOREACTIVE, r32f)                       uniform image2D   	    rw_output_autoreactive;
#endif
#if defined FSR2_BIND_UAV_AUTOCOMPOSITION
	layout(set = 1, binding = FSR2_BIND_UAV_AUTOCOMPOSITION, r32f)                    uniform image2D   	    rw_output_autocomposition;
#endif
#if defined FSR2_BIND_UAV_PREV_PRE_ALPHA_COLOR
	layout(set = 1, binding = FSR2_BIND_UAV_PREV_PRE_ALPHA_COLOR, r11f_g11f_b10f)     uniform image2D   	    rw_output_prev_color_pre_alpha;
#endif
#if defined FSR2_BIND_UAV_PREV_POST_ALPHA_COLOR
	layout(set = 1, binding = FSR2_BIND_UAV_PREV_POST_ALPHA_COLOR, r11f_g11f_b10f)    uniform image2D   	    rw_output_prev_color_post_alpha;
#endif

#if defined(FSR2_BIND_SRV_SCENE_LUMINANCE_MIPS)
FfxFloat32 LoadMipLuma(FfxInt32x2 iPxPos, FfxInt32 mipLevel)
{
	return texelFetch(r_imgMips, iPxPos, FfxInt32(mipLevel)).r;
}
#endif

#if defined(FSR2_BIND_SRV_SCENE_LUMINANCE_MIPS)
FfxFloat32 SampleMipLuma(FfxFloat32x2 fUV, FfxInt32 mipLevel)
{
	return textureLod(sampler2D(r_imgMips, s_LinearClamp), fUV, FfxFloat32(mipLevel)).r;
}
#endif

#if defined(FSR2_BIND_SRV_INPUT_DEPTH)
FfxFloat32 LoadInputDepth(FfxInt32x2 iPxPos)
{
	return texelFetch(r_input_depth, iPxPos, 0).r;
}
#endif

#if defined(FSR2_BIND_SRV_REACTIVE_MASK) 
FfxFloat32 LoadReactiveMask(FfxInt32x2 iPxPos)
{

#if FFX_FSR2_OPTION_GODOT_REACTIVE_MASK_CLAMP
	return min(texelFetch(r_reactive_mask, FfxInt32x2(iPxPos), 0).r, 0.9f);
#else
	return texelFetch(r_reactive_mask, FfxInt32x2(iPxPos), 0).r;
#endif

}
#endif

#if defined(FSR2_BIND_SRV_TRANSPARENCY_AND_COMPOSITION_MASK)
FfxFloat32 LoadTransparencyAndCompositionMask(FfxUInt32x2 iPxPos)
{
	return texelFetch(r_transparency_and_composition_mask, FfxInt32x2(iPxPos), 0).r;
}
#endif

#if defined(FSR2_BIND_SRV_INPUT_COLOR)
FfxFloat32x3 LoadInputColor(FfxInt32x2 iPxPos)
{
	return texelFetch(r_input_color_jittered, iPxPos, 0).rgb;
}
#endif

#if defined(FSR2_BIND_SRV_INPUT_COLOR)
FfxFloat32x3 SampleInputColor(FfxFloat32x2 fUV)
{
	return textureLod(sampler2D(r_input_color_jittered, s_LinearClamp), fUV, 0.0f).rgb;
}
#endif

#if defined(FSR2_BIND_SRV_PREPARED_INPUT_COLOR)
FfxFloat32x3 LoadPreparedInputColor(FfxInt32x2 iPxPos)
{
	return texelFetch(r_prepared_input_color, iPxPos, 0).xyz;
}
#endif

#if defined(FSR2_BIND_SRV_INPUT_MOTION_VECTORS)
FfxFloat32x2 LoadInputMotionVector(FfxInt32x2 iPxDilatedMotionVectorPos)
{
	FfxFloat32x2 fSrcMotionVector = texelFetch(r_input_motion_vectors, iPxDilatedMotionVectorPos, 0).xy;


#if FFX_FSR2_OPTION_GODOT_DERIVE_INVALID_MOTION_VECTORS
	bool bInvalidMotionVector = all(lessThanEqual(fSrcMotionVector, vec2(-1.0f, -1.0f)));
	if (bInvalidMotionVector)
	{
		FfxFloat32 fSrcDepth = LoadInputDepth(iPxDilatedMotionVectorPos);
		FfxFloat32x2 fUv = (iPxDilatedMotionVectorPos + FfxFloat32(0.5)) / RenderSize();
		fSrcMotionVector = FFX_FSR2_OPTION_GODOT_DERIVE_INVALID_MOTION_VECTORS_FUNCTION(fUv, fSrcDepth, cbFSR2.mReprojectionMatrix);
	}
#endif


	FfxFloat32x2 fUvMotionVector = fSrcMotionVector * MotionVectorScale();

#if FFX_FSR2_OPTION_JITTERED_MOTION_VECTORS
	fUvMotionVector -= MotionVectorJitterCancellation();
#endif

	return fUvMotionVector;
}
#endif

#if defined(FSR2_BIND_SRV_INTERNAL_UPSCALED)
FfxFloat32x4 LoadHistory(FfxInt32x2 iPxHistory)
{
	return texelFetch(r_internal_upscaled_color, iPxHistory, 0);
}
#endif

#if defined(FSR2_BIND_UAV_LUMA_HISTORY)
void StoreLumaHistory(FfxInt32x2 iPxPos, FfxFloat32x4 fLumaHistory)
{
	imageStore(rw_luma_history, FfxInt32x2(iPxPos), fLumaHistory);
}
#endif

#if defined(FSR2_BIND_SRV_LUMA_HISTORY)
FfxFloat32x4 SampleLumaHistory(FfxFloat32x2 fUV)
{
	return textureLod(sampler2D(r_luma_history, s_LinearClamp), fUV, 0.0f);
}
#endif

#if defined(FSR2_BIND_UAV_INTERNAL_UPSCALED)
void StoreReprojectedHistory(FfxInt32x2 iPxHistory, FfxFloat32x4 fHistory)
{
	imageStore(rw_internal_upscaled_color, iPxHistory, fHistory);
}
#endif

#if defined(FSR2_BIND_UAV_INTERNAL_UPSCALED)
void StoreInternalColorAndWeight(FfxInt32x2 iPxPos, FfxFloat32x4 fColorAndWeight)
{
	imageStore(rw_internal_upscaled_color, FfxInt32x2(iPxPos), fColorAndWeight);
}
#endif

#if defined(FSR2_BIND_UAV_UPSCALED_OUTPUT)
void StoreUpscaledOutput(FfxInt32x2 iPxPos, FfxFloat32x3 fColor)
{
    imageStore(rw_upscaled_output, FfxInt32x2(iPxPos), FfxFloat32x4(fColor, 1.f));
}
#endif

#if defined(FSR2_BIND_SRV_LOCK_STATUS)
FfxFloat32x2 LoadLockStatus(FfxInt32x2 iPxPos)
{
	FfxFloat32x2 fLockStatus = texelFetch(r_lock_status, iPxPos, 0).rg;

    return fLockStatus;
}
#endif

#if defined(FSR2_BIND_UAV_LOCK_STATUS)
void StoreLockStatus(FfxInt32x2 iPxPos, FfxFloat32x2 fLockstatus)
{
	imageStore(rw_lock_status, iPxPos, vec4(fLockstatus, 0.0f, 0.0f));
}
#endif

#if defined(FSR2_BIND_SRV_LOCK_INPUT_LUMA)
FfxFloat32 LoadLockInputLuma(FfxInt32x2 iPxPos)
{
	return texelFetch(r_lock_input_luma, iPxPos, 0).r;
}
#endif

#if defined(FSR2_BIND_UAV_LOCK_INPUT_LUMA)
void StoreLockInputLuma(FfxInt32x2 iPxPos, FfxFloat32 fLuma)
{
	imageStore(rw_lock_input_luma, iPxPos, vec4(fLuma, 0, 0, 0));
}
#endif

#if defined(FSR2_BIND_SRV_NEW_LOCKS)
FfxFloat32 LoadNewLocks(FfxInt32x2 iPxPos)
{
	return texelFetch(r_new_locks, iPxPos, 0).r;
}
#endif

#if defined(FSR2_BIND_UAV_NEW_LOCKS)
FfxFloat32 LoadRwNewLocks(FfxInt32x2 iPxPos)
{
	return imageLoad(rw_new_locks, iPxPos).r;
}
#endif

#if defined(FSR2_BIND_UAV_NEW_LOCKS)
void StoreNewLocks(FfxInt32x2 iPxPos, FfxFloat32 newLock)
{
	imageStore(rw_new_locks, iPxPos, vec4(newLock, 0, 0, 0));
}
#endif

#if defined(FSR2_BIND_UAV_PREPARED_INPUT_COLOR)
void StorePreparedInputColor(FFX_PARAMETER_IN FfxInt32x2 iPxPos, FFX_PARAMETER_IN FfxFloat32x4 fTonemapped)
{
	imageStore(rw_prepared_input_color, iPxPos, fTonemapped);
}
#endif

#if defined(FSR2_BIND_SRV_PREPARED_INPUT_COLOR)
FfxFloat32 SampleDepthClip(FfxFloat32x2 fUV)
{
	return textureLod(sampler2D(r_prepared_input_color, s_LinearClamp), fUV, 0.0f).w;
}
#endif

#if defined(FSR2_BIND_SRV_LOCK_STATUS)
FfxFloat32x2 SampleLockStatus(FfxFloat32x2 fUV)
{
	FfxFloat32x2 fLockStatus = textureLod(sampler2D(r_lock_status, s_LinearClamp), fUV, 0.0f).rg;
	return fLockStatus;
}
#endif

#if defined(FSR2_BIND_SRV_DEPTH)
FfxFloat32 LoadSceneDepth(FfxInt32x2 iPxInput)
{
	return texelFetch(r_input_depth, iPxInput, 0).r;
}
#endif

#if defined(FSR2_BIND_SRV_RECONSTRUCTED_PREV_NEAREST_DEPTH)
FfxFloat32 LoadReconstructedPrevDepth(FfxInt32x2 iPxPos)
{
	return uintBitsToFloat(texelFetch(r_reconstructed_previous_nearest_depth, iPxPos, 0).r);
}
#endif

#if defined(FSR2_BIND_UAV_RECONSTRUCTED_PREV_NEAREST_DEPTH)
void StoreReconstructedDepth(FfxInt32x2 iPxSample, FfxFloat32 fDepth)
{
	FfxUInt32 uDepth = floatBitsToUint(fDepth);

	#if FFX_FSR2_OPTION_INVERTED_DEPTH
		imageAtomicMax(rw_reconstructed_previous_nearest_depth, iPxSample, uDepth);
	#else
		imageAtomicMin(rw_reconstructed_previous_nearest_depth, iPxSample, uDepth); 
	#endif
}
#endif

#if defined(FSR2_BIND_UAV_RECONSTRUCTED_PREV_NEAREST_DEPTH)
void SetReconstructedDepth(FfxInt32x2 iPxSample, FfxUInt32 uValue)
{
	imageStore(rw_reconstructed_previous_nearest_depth, iPxSample, uvec4(uValue, 0, 0, 0));
}
#endif

#if defined(FSR2_BIND_UAV_DILATED_DEPTH)
void StoreDilatedDepth(FFX_PARAMETER_IN FfxInt32x2 iPxPos, FFX_PARAMETER_IN FfxFloat32 fDepth)
{
	
	imageStore(rw_dilatedDepth, iPxPos, vec4(fDepth, 0.0f, 0.0f, 0.0f));
}
#endif

#if defined(FSR2_BIND_UAV_DILATED_MOTION_VECTORS) 
void StoreDilatedMotionVector(FFX_PARAMETER_IN FfxInt32x2 iPxPos, FFX_PARAMETER_IN FfxFloat32x2 fMotionVector)
{
	imageStore(rw_dilated_motion_vectors, iPxPos, vec4(fMotionVector, 0.0f, 0.0f));
}
#endif

#if defined(FSR2_BIND_SRV_DILATED_MOTION_VECTORS)
FfxFloat32x2 LoadDilatedMotionVector(FfxInt32x2 iPxInput)
{
	return texelFetch(r_dilated_motion_vectors, iPxInput, 0).rg;
}
#endif

#if defined(FSR2_BIND_SRV_DILATED_MOTION_VECTORS)
FfxFloat32x2 SampleDilatedMotionVector(FfxFloat32x2 fUV)
{
	return textureLod(sampler2D(r_dilated_motion_vectors, s_LinearClamp), fUV, 0.0f).rg;
}
#endif

#if defined(FSR2_BIND_SRV_PREVIOUS_DILATED_MOTION_VECTORS)
FfxFloat32x2 LoadPreviousDilatedMotionVector(FfxInt32x2 iPxInput)
{
	return texelFetch(r_previous_dilated_motion_vectors, iPxInput, 0).rg;
}

FfxFloat32x2 SamplePreviousDilatedMotionVector(FfxFloat32x2 fUV)
{
	return textureLod(sampler2D(r_previous_dilated_motion_vectors, s_LinearClamp), fUV, 0.0f).xy;
}
#endif

#if defined(FSR2_BIND_SRV_DILATED_DEPTH)
FfxFloat32 LoadDilatedDepth(FfxInt32x2 iPxInput)
{
	return texelFetch(r_dilatedDepth, iPxInput, 0).r;
}
#endif

#if defined(FSR2_BIND_SRV_INPUT_EXPOSURE)
FfxFloat32 Exposure()
{
	FfxFloat32 exposure = texelFetch(r_input_exposure, FfxInt32x2(0, 0), 0).x;

	if (exposure == 0.0f) {
		exposure = 1.0f;
	}

	return exposure;
}
#endif

#if defined(FSR2_BIND_SRV_AUTO_EXPOSURE)
FfxFloat32 AutoExposure()
{
	FfxFloat32 exposure = texelFetch(r_auto_exposure, FfxInt32x2(0, 0), 0).x;

	if (exposure == 0.0f) {
		exposure = 1.0f;
	}

	return exposure;
}
#endif

FfxFloat32 SampleLanczos2Weight(FfxFloat32 x)
{
#if defined(FSR2_BIND_SRV_LANCZOS_LUT)
	return textureLod(sampler2D(r_lanczos_lut, s_LinearClamp), FfxFloat32x2(x / 2.0f, 0.5f), 0.0f).x; 
#else
    return 0.f;
#endif
}

#if defined(FSR2_BIND_SRV_UPSCALE_MAXIMUM_BIAS_LUT)
FfxFloat32 SampleUpsampleMaximumBias(FfxFloat32x2 uv)
{
    
    return FfxFloat32(2.0f) * FfxFloat32(textureLod(sampler2D(r_upsample_maximum_bias_lut, s_LinearClamp), abs(uv) * 2.0f, 0.0f).r);
}
#endif

#if defined(FSR2_BIND_SRV_DILATED_REACTIVE_MASKS)
FfxFloat32x2 SampleDilatedReactiveMasks(FfxFloat32x2 fUV)
{
	return textureLod(sampler2D(r_dilated_reactive_masks, s_LinearClamp), fUV, 0.0f).rg;
}
#endif

#if defined(FSR2_BIND_SRV_DILATED_REACTIVE_MASKS)
FfxFloat32x2 LoadDilatedReactiveMasks(FFX_PARAMETER_IN FfxInt32x2 iPxPos)
{
    return texelFetch(r_dilated_reactive_masks, iPxPos, 0).rg;
}
#endif

#if defined(FSR2_BIND_UAV_DILATED_REACTIVE_MASKS)
void StoreDilatedReactiveMasks(FFX_PARAMETER_IN FfxInt32x2 iPxPos, FFX_PARAMETER_IN FfxFloat32x2 fDilatedReactiveMasks)
{
    imageStore(rw_dilated_reactive_masks, iPxPos, vec4(fDilatedReactiveMasks, 0.0f, 0.0f));
}
#endif

#if defined(FFX_INTERNAL)
FfxFloat32x4 SampleDebug(FfxFloat32x2 fUV)
{
    return textureLod(sampler2D(r_debug_out, s_LinearClamp), fUV, 0.0f).rgba;
}
#endif

#if defined(FSR2_BIND_SRV_INPUT_OPAQUE_ONLY)
FfxFloat32x3 LoadOpaqueOnly(FFX_PARAMETER_IN FFX_MIN16_I2 iPxPos)
{
	return texelFetch(r_input_opaque_only, iPxPos, 0).xyz;
}
#endif

#if defined(FSR2_BIND_SRV_PREV_PRE_ALPHA_COLOR)
FfxFloat32x3 LoadPrevPreAlpha(FFX_PARAMETER_IN FFX_MIN16_I2 iPxPos)
{
	return texelFetch(r_input_prev_color_pre_alpha, iPxPos, 0).xyz;
}
#endif

#if defined(FSR2_BIND_SRV_PREV_POST_ALPHA_COLOR)
FfxFloat32x3 LoadPrevPostAlpha(FFX_PARAMETER_IN FFX_MIN16_I2 iPxPos)
{
	return texelFetch(r_input_prev_color_post_alpha, iPxPos, 0).xyz;
}
#endif

#if defined(FSR2_BIND_UAV_AUTOREACTIVE)
#if defined(FSR2_BIND_UAV_AUTOCOMPOSITION)
void StoreAutoReactive(FFX_PARAMETER_IN FFX_MIN16_I2 iPxPos, FFX_PARAMETER_IN FFX_MIN16_F2 fReactive)
{
	imageStore(rw_output_autoreactive, iPxPos, vec4(FfxFloat32(fReactive.x), 0.0f, 0.0f, 0.0f));

	imageStore(rw_output_autocomposition, iPxPos, vec4(FfxFloat32(fReactive.y), 0.0f, 0.0f, 0.0f));
}
#endif
#endif

#if defined(FSR2_BIND_UAV_PREV_PRE_ALPHA_COLOR)
void StorePrevPreAlpha(FFX_PARAMETER_IN FFX_MIN16_I2 iPxPos, FFX_PARAMETER_IN FFX_MIN16_F3 color)
{
	imageStore(rw_output_prev_color_pre_alpha, iPxPos, vec4(color, 0.0f));
}
#endif

#if defined(FSR2_BIND_UAV_PREV_POST_ALPHA_COLOR)
void StorePrevPostAlpha(FFX_PARAMETER_IN FFX_MIN16_I2 iPxPos, FFX_PARAMETER_IN FFX_MIN16_F3 color)
{
	imageStore(rw_output_prev_color_post_alpha, iPxPos, vec4(color, 0.0f));
}
#endif

#endif 





















#if !defined(FFX_FSR2_COMMON_H)
#define FFX_FSR2_COMMON_H

#if defined(FFX_CPU) || defined(FFX_GPU)

#define LOCK_LIFETIME_REMAINING 0
#define LOCK_TEMPORAL_LUMA 1
#endif 

#if defined(FFX_GPU)
FFX_STATIC const FfxFloat32 FSR2_FP16_MIN = 6.10e-05f;
FFX_STATIC const FfxFloat32 FSR2_FP16_MAX = 65504.0f;
FFX_STATIC const FfxFloat32 FSR2_EPSILON = 1e-03f;
FFX_STATIC const FfxFloat32 FSR2_TONEMAP_EPSILON = 1.0f / FSR2_FP16_MAX;
FFX_STATIC const FfxFloat32 FSR2_FLT_MAX = 3.402823466e+38f;
FFX_STATIC const FfxFloat32 FSR2_FLT_MIN = 1.175494351e-38f;


#pragma warning(error: 3206)


#pragma warning(disable: 3205)  
#pragma warning(disable: 3571)  


FFX_STATIC const FfxFloat32 fReconstructedDepthBilinearWeightThreshold = 0.01f;


FFX_STATIC const FfxFloat32 fUpsampleLanczosWeightScale = 1.0f / 12.0f;
FFX_STATIC const FfxFloat32 fMaxAccumulationLanczosWeight = 1.0f;
FFX_STATIC const FfxFloat32 fAverageLanczosWeightPerFrame = 0.74f * fUpsampleLanczosWeightScale; 
FFX_STATIC const FfxFloat32 fAccumulationMaxOnMotion = 3.0f * fUpsampleLanczosWeightScale;


FFX_STATIC const FfxFloat32 resetAutoExposureAverageSmoothing = 1e8f;

struct AccumulationPassCommonParams
{
    FfxInt32x2 iPxHrPos;
    FfxFloat32x2 fHrUv;
    FfxFloat32x2 fLrUv_HwSampler;
    FfxFloat32x2 fMotionVector;
    FfxFloat32x2 fReprojectedHrUv;
    FfxFloat32 fHrVelocity;
    FfxFloat32 fDepthClipFactor;
    FfxFloat32 fDilatedReactiveFactor;
    FfxFloat32 fAccumulationMask;

    FfxBoolean bIsResetFrame;
    FfxBoolean bIsExistingSample;
    FfxBoolean bIsNewSample;
};

struct LockState
{
    FfxBoolean NewLock; 
    FfxBoolean WasLockedPrevFrame; 
};

void InitializeNewLockSample(FFX_PARAMETER_OUT FfxFloat32x2 fLockStatus)
{
    fLockStatus = FfxFloat32x2(0, 0);
}
)<!>" R"<!>(
#if FFX_HALF
void InitializeNewLockSample(FFX_PARAMETER_OUT FFX_MIN16_F2 fLockStatus)
{
    fLockStatus = FFX_MIN16_F2(0, 0);
}
#endif


void KillLock(FFX_PARAMETER_INOUT FfxFloat32x2 fLockStatus)
{
    fLockStatus[LOCK_LIFETIME_REMAINING] = 0;
}

#if FFX_HALF
void KillLock(FFX_PARAMETER_INOUT FFX_MIN16_F2 fLockStatus)
{
    fLockStatus[LOCK_LIFETIME_REMAINING] = FFX_MIN16_F(0);
}
#endif

struct RectificationBox
{
    FfxFloat32x3 boxCenter;
    FfxFloat32x3 boxVec;
    FfxFloat32x3 aabbMin;
    FfxFloat32x3 aabbMax;
    FfxFloat32 fBoxCenterWeight;
};
#if FFX_HALF
struct RectificationBoxMin16
{
    FFX_MIN16_F3 boxCenter;
    FFX_MIN16_F3 boxVec;
    FFX_MIN16_F3 aabbMin;
    FFX_MIN16_F3 aabbMax;
    FFX_MIN16_F fBoxCenterWeight;
};
#endif

void RectificationBoxReset(FFX_PARAMETER_INOUT RectificationBox rectificationBox)
{
    rectificationBox.fBoxCenterWeight = FfxFloat32(0);

    rectificationBox.boxCenter = FfxFloat32x3(0, 0, 0);
    rectificationBox.boxVec = FfxFloat32x3(0, 0, 0);
    rectificationBox.aabbMin = FfxFloat32x3(FSR2_FLT_MAX, FSR2_FLT_MAX, FSR2_FLT_MAX);
    rectificationBox.aabbMax = -FfxFloat32x3(FSR2_FLT_MAX, FSR2_FLT_MAX, FSR2_FLT_MAX);
}
#if FFX_HALF
void RectificationBoxReset(FFX_PARAMETER_INOUT RectificationBoxMin16 rectificationBox)
{
    rectificationBox.fBoxCenterWeight = FFX_MIN16_F(0);

    rectificationBox.boxCenter = FFX_MIN16_F3(0, 0, 0);
    rectificationBox.boxVec = FFX_MIN16_F3(0, 0, 0);
    rectificationBox.aabbMin = FFX_MIN16_F3(FSR2_FP16_MAX, FSR2_FP16_MAX, FSR2_FP16_MAX);
    rectificationBox.aabbMax = -FFX_MIN16_F3(FSR2_FP16_MAX, FSR2_FP16_MAX, FSR2_FP16_MAX);
}
#endif

void RectificationBoxAddInitialSample(FFX_PARAMETER_INOUT RectificationBox rectificationBox, const FfxFloat32x3 colorSample, const FfxFloat32 fSampleWeight)
{
    rectificationBox.aabbMin = colorSample;
    rectificationBox.aabbMax = colorSample;

    FfxFloat32x3 weightedSample = colorSample * fSampleWeight;
    rectificationBox.boxCenter = weightedSample;
    rectificationBox.boxVec = colorSample * weightedSample;
    rectificationBox.fBoxCenterWeight = fSampleWeight;
}

void RectificationBoxAddSample(FfxBoolean bInitialSample, FFX_PARAMETER_INOUT RectificationBox rectificationBox, const FfxFloat32x3 colorSample, const FfxFloat32 fSampleWeight)
{
    if (bInitialSample) {
        RectificationBoxAddInitialSample(rectificationBox, colorSample, fSampleWeight);
    } else {
        rectificationBox.aabbMin = ffxMin(rectificationBox.aabbMin, colorSample);
        rectificationBox.aabbMax = ffxMax(rectificationBox.aabbMax, colorSample);

        FfxFloat32x3 weightedSample = colorSample * fSampleWeight;
        rectificationBox.boxCenter += weightedSample;
        rectificationBox.boxVec += colorSample * weightedSample;
        rectificationBox.fBoxCenterWeight += fSampleWeight;
    }
}
#if FFX_HALF
void RectificationBoxAddInitialSample(FFX_PARAMETER_INOUT RectificationBoxMin16 rectificationBox, const FFX_MIN16_F3 colorSample, const FFX_MIN16_F fSampleWeight)
{
    rectificationBox.aabbMin = colorSample;
    rectificationBox.aabbMax = colorSample;

    FFX_MIN16_F3 weightedSample = colorSample * fSampleWeight;
    rectificationBox.boxCenter = weightedSample;
    rectificationBox.boxVec = colorSample * weightedSample;
    rectificationBox.fBoxCenterWeight = fSampleWeight;
}

void RectificationBoxAddSample(FfxBoolean bInitialSample, FFX_PARAMETER_INOUT RectificationBoxMin16 rectificationBox, const FFX_MIN16_F3 colorSample, const FFX_MIN16_F fSampleWeight)
{
    if (bInitialSample) {
        RectificationBoxAddInitialSample(rectificationBox, colorSample, fSampleWeight);
    } else {
        rectificationBox.aabbMin = ffxMin(rectificationBox.aabbMin, colorSample);
        rectificationBox.aabbMax = ffxMax(rectificationBox.aabbMax, colorSample);

        FFX_MIN16_F3 weightedSample = colorSample * fSampleWeight;
        rectificationBox.boxCenter += weightedSample;
        rectificationBox.boxVec += colorSample * weightedSample;
        rectificationBox.fBoxCenterWeight += fSampleWeight;
    }
}
#endif

void RectificationBoxComputeVarianceBoxData(FFX_PARAMETER_INOUT RectificationBox rectificationBox)
{
    rectificationBox.fBoxCenterWeight = (abs(rectificationBox.fBoxCenterWeight) > FfxFloat32(FSR2_EPSILON) ? rectificationBox.fBoxCenterWeight : FfxFloat32(1.f));
    rectificationBox.boxCenter /= rectificationBox.fBoxCenterWeight;
    rectificationBox.boxVec /= rectificationBox.fBoxCenterWeight;
    FfxFloat32x3 stdDev = sqrt(abs(rectificationBox.boxVec - rectificationBox.boxCenter * rectificationBox.boxCenter));
    rectificationBox.boxVec = stdDev;
}
#if FFX_HALF
void RectificationBoxComputeVarianceBoxData(FFX_PARAMETER_INOUT RectificationBoxMin16 rectificationBox)
{
    rectificationBox.fBoxCenterWeight = (abs(rectificationBox.fBoxCenterWeight) > FFX_MIN16_F(FSR2_EPSILON) ? rectificationBox.fBoxCenterWeight : FFX_MIN16_F(1.f));
    rectificationBox.boxCenter /= rectificationBox.fBoxCenterWeight;
    rectificationBox.boxVec /= rectificationBox.fBoxCenterWeight;
    FFX_MIN16_F3 stdDev = sqrt(abs(rectificationBox.boxVec - rectificationBox.boxCenter * rectificationBox.boxCenter));
    rectificationBox.boxVec = stdDev;
}
#endif

FfxFloat32x3 SafeRcp3(FfxFloat32x3 v)
{
    return (all(FFX_NOT_EQUAL(v, FfxFloat32x3(0, 0, 0)))) ? (FfxFloat32x3(1, 1, 1) / v) : FfxFloat32x3(0, 0, 0);
}
#if FFX_HALF
FFX_MIN16_F3 SafeRcp3(FFX_MIN16_F3 v)
{
    return (all(FFX_NOT_EQUAL(v, FFX_MIN16_F3(0, 0, 0)))) ? (FFX_MIN16_F3(1, 1, 1) / v) : FFX_MIN16_F3(0, 0, 0);
}
#endif

FfxFloat32 MinDividedByMax(const FfxFloat32 v0, const FfxFloat32 v1)
{
    const FfxFloat32 m = ffxMax(v0, v1);
    return m != 0 ? ffxMin(v0, v1) / m : 0;
}

#if FFX_HALF
FFX_MIN16_F MinDividedByMax(const FFX_MIN16_F v0, const FFX_MIN16_F v1)
{
    const FFX_MIN16_F m = ffxMax(v0, v1);
    return m != FFX_MIN16_F(0) ? ffxMin(v0, v1) / m : FFX_MIN16_F(0);
}
#endif

FfxFloat32x3 YCoCgToRGB(FfxFloat32x3 fYCoCg)
{
    FfxFloat32x3 fRgb;

    fRgb = FfxFloat32x3(
        fYCoCg.x + fYCoCg.y - fYCoCg.z,
        fYCoCg.x + fYCoCg.z,
        fYCoCg.x - fYCoCg.y - fYCoCg.z);

    return fRgb;
}
#if FFX_HALF
FFX_MIN16_F3 YCoCgToRGB(FFX_MIN16_F3 fYCoCg)
{
    FFX_MIN16_F3 fRgb;

    fRgb = FFX_MIN16_F3(
        fYCoCg.x + fYCoCg.y - fYCoCg.z,
        fYCoCg.x + fYCoCg.z,
        fYCoCg.x - fYCoCg.y - fYCoCg.z);

    return fRgb;
}
#endif

FfxFloat32x3 RGBToYCoCg(FfxFloat32x3 fRgb)
{
    FfxFloat32x3 fYCoCg;

    fYCoCg = FfxFloat32x3(
        0.25f * fRgb.r + 0.5f * fRgb.g + 0.25f * fRgb.b,
        0.5f * fRgb.r - 0.5f * fRgb.b,
        -0.25f * fRgb.r + 0.5f * fRgb.g - 0.25f * fRgb.b);

    return fYCoCg;
}
#if FFX_HALF
FFX_MIN16_F3 RGBToYCoCg(FFX_MIN16_F3 fRgb)
{
    FFX_MIN16_F3 fYCoCg;

    fYCoCg = FFX_MIN16_F3(
        0.25 * fRgb.r + 0.5 * fRgb.g + 0.25 * fRgb.b,
        0.5 * fRgb.r - 0.5 * fRgb.b,
        -0.25 * fRgb.r + 0.5 * fRgb.g - 0.25 * fRgb.b);

    return fYCoCg;
}
#endif

FfxFloat32 RGBToLuma(FfxFloat32x3 fLinearRgb)
{
    return dot(fLinearRgb, FfxFloat32x3(0.2126f, 0.7152f, 0.0722f));
}
#if FFX_HALF
FFX_MIN16_F RGBToLuma(FFX_MIN16_F3 fLinearRgb)
{
    return dot(fLinearRgb, FFX_MIN16_F3(0.2126f, 0.7152f, 0.0722f));
}
#endif

FfxFloat32 RGBToPerceivedLuma(FfxFloat32x3 fLinearRgb)
{
    FfxFloat32 fLuminance = RGBToLuma(fLinearRgb);

    FfxFloat32 fPercievedLuminance = 0;
    if (fLuminance <= 216.0f / 24389.0f) {
        fPercievedLuminance = fLuminance * (24389.0f / 27.0f);
    }
    else {
        fPercievedLuminance = ffxPow(fLuminance, 1.0f / 3.0f) * 116.0f - 16.0f;
    }

    return fPercievedLuminance * 0.01f;
}
#if FFX_HALF
FFX_MIN16_F RGBToPerceivedLuma(FFX_MIN16_F3 fLinearRgb)
{
    FFX_MIN16_F fLuminance = RGBToLuma(fLinearRgb);

    FFX_MIN16_F fPercievedLuminance = FFX_MIN16_F(0);
    if (fLuminance <= FFX_MIN16_F(216.0f / 24389.0f)) {
        fPercievedLuminance = fLuminance * FFX_MIN16_F(24389.0f / 27.0f);
    }
    else {
        fPercievedLuminance = ffxPow(fLuminance, FFX_MIN16_F(1.0f / 3.0f)) * FFX_MIN16_F(116.0f) - FFX_MIN16_F(16.0f);
    }

    return fPercievedLuminance * FFX_MIN16_F(0.01f);
}
#endif

FfxFloat32x3 Tonemap(FfxFloat32x3 fRgb)
{
    return fRgb / (ffxMax(ffxMax(0.f, fRgb.r), ffxMax(fRgb.g, fRgb.b)) + 1.f).xxx;
}

FfxFloat32x3 InverseTonemap(FfxFloat32x3 fRgb)
{
    return fRgb / ffxMax(FSR2_TONEMAP_EPSILON, 1.f - ffxMax(fRgb.r, ffxMax(fRgb.g, fRgb.b))).xxx;
}

#if FFX_HALF
FFX_MIN16_F3 Tonemap(FFX_MIN16_F3 fRgb)
{
    return fRgb / (ffxMax(ffxMax(FFX_MIN16_F(0.f), fRgb.r), ffxMax(fRgb.g, fRgb.b)) + FFX_MIN16_F(1.f)).xxx;
}

FFX_MIN16_F3 InverseTonemap(FFX_MIN16_F3 fRgb)
{
    return fRgb / ffxMax(FFX_MIN16_F(FSR2_TONEMAP_EPSILON), FFX_MIN16_F(1.f) - ffxMax(fRgb.r, ffxMax(fRgb.g, fRgb.b))).xxx;
}
#endif

FfxInt32x2 ClampLoad(FfxInt32x2 iPxSample, FfxInt32x2 iPxOffset, FfxInt32x2 iTextureSize)
{
    FfxInt32x2 result = iPxSample + iPxOffset;
    result.x = (iPxOffset.x < 0) ? ffxMax(result.x, 0) : result.x;
    result.x = (iPxOffset.x > 0) ? ffxMin(result.x, iTextureSize.x - 1) : result.x;
    result.y = (iPxOffset.y < 0) ? ffxMax(result.y, 0) : result.y;
    result.y = (iPxOffset.y > 0) ? ffxMin(result.y, iTextureSize.y - 1) : result.y;
    return result;

    
}
#if FFX_HALF
FFX_MIN16_I2 ClampLoad(FFX_MIN16_I2 iPxSample, FFX_MIN16_I2 iPxOffset, FFX_MIN16_I2 iTextureSize)
{
    FFX_MIN16_I2 result = iPxSample + iPxOffset;
    result.x = (iPxOffset.x < 0) ? ffxMax(result.x, FFX_MIN16_I(0)) : result.x;
    result.x = (iPxOffset.x > 0) ? ffxMin(result.x, iTextureSize.x - FFX_MIN16_I(1)) : result.x;
    result.y = (iPxOffset.y < 0) ? ffxMax(result.y, FFX_MIN16_I(0)) : result.y;
    result.y = (iPxOffset.y > 0) ? ffxMin(result.y, iTextureSize.y - FFX_MIN16_I(1)) : result.y;
    return result;

    
}
#endif

FfxFloat32x2 ClampUv(FfxFloat32x2 fUv, FfxInt32x2 iTextureSize, FfxInt32x2 iResourceSize)
{
    const FfxFloat32x2 fSampleLocation = fUv * iTextureSize;
    const FfxFloat32x2 fClampedLocation = ffxMax(FfxFloat32x2(0.5f, 0.5f), ffxMin(fSampleLocation, FfxFloat32x2(iTextureSize) - FfxFloat32x2(0.5f, 0.5f)));
    const FfxFloat32x2 fClampedUv = fClampedLocation / FfxFloat32x2(iResourceSize);

    return fClampedUv;
}

FfxBoolean IsOnScreen(FfxInt32x2 pos, FfxInt32x2 size)
{
    return all(FFX_LESS_THAN(FfxUInt32x2(pos), FfxUInt32x2(size)));
}
#if FFX_HALF
FfxBoolean IsOnScreen(FFX_MIN16_I2 pos, FFX_MIN16_I2 size)
{
    return all(FFX_LESS_THAN(FFX_MIN16_U2(pos), FFX_MIN16_U2(size)));
}
#endif

FfxFloat32 ComputeAutoExposureFromLavg(FfxFloat32 Lavg)
{
    Lavg = exp(Lavg);

    const FfxFloat32 S = 100.0f; 
    const FfxFloat32 K = 12.5f;
    FfxFloat32 ExposureISO100 = log2((Lavg * S) / K);

    const FfxFloat32 q = 0.65f;
    FfxFloat32 Lmax = (78.0f / (q * S)) * ffxPow(2.0f, ExposureISO100);

    return 1 / Lmax;
}
#if FFX_HALF
FFX_MIN16_F ComputeAutoExposureFromLavg(FFX_MIN16_F Lavg)
{
    Lavg = exp(Lavg);

    const FFX_MIN16_F S = FFX_MIN16_F(100.0f); 
    const FFX_MIN16_F K = FFX_MIN16_F(12.5f);
    const FFX_MIN16_F ExposureISO100 = log2((Lavg * S) / K);

    const FFX_MIN16_F q = FFX_MIN16_F(0.65f);
    const FFX_MIN16_F Lmax = (FFX_MIN16_F(78.0f) / (q * S)) * ffxPow(FFX_MIN16_F(2.0f), ExposureISO100);

    return FFX_MIN16_F(1) / Lmax;
}
#endif

FfxInt32x2 ComputeHrPosFromLrPos(FfxInt32x2 iPxLrPos)
{
    FfxFloat32x2 fSrcJitteredPos = FfxFloat32x2(iPxLrPos) + 0.5f - Jitter();
    FfxFloat32x2 fLrPosInHr = (fSrcJitteredPos / RenderSize()) * DisplaySize();
    FfxInt32x2 iPxHrPos = FfxInt32x2(floor(fLrPosInHr));
    return iPxHrPos;
}
#if FFX_HALF
FFX_MIN16_I2 ComputeHrPosFromLrPos(FFX_MIN16_I2 iPxLrPos)
{
    FFX_MIN16_F2 fSrcJitteredPos = FFX_MIN16_F2(iPxLrPos) + FFX_MIN16_F(0.5f) - FFX_MIN16_F2(Jitter());
    FFX_MIN16_F2 fLrPosInHr = (fSrcJitteredPos / FFX_MIN16_F2(RenderSize())) * FFX_MIN16_F2(DisplaySize());
    FFX_MIN16_I2 iPxHrPos = FFX_MIN16_I2(floor(fLrPosInHr));
    return iPxHrPos;
}
#endif

FfxFloat32x2 ComputeNdc(FfxFloat32x2 fPxPos, FfxInt32x2 iSize)
{
    return fPxPos / FfxFloat32x2(iSize) * FfxFloat32x2(2.0f, -2.0f) + FfxFloat32x2(-1.0f, 1.0f);
}

FfxFloat32 GetViewSpaceDepth(FfxFloat32 fDeviceDepth)
{
    const FfxFloat32x4 fDeviceToViewDepth = DeviceToViewSpaceTransformFactors();

    
    return (fDeviceToViewDepth[1] / (fDeviceDepth - fDeviceToViewDepth[0]));
}

FfxFloat32 GetViewSpaceDepthInMeters(FfxFloat32 fDeviceDepth)
{
    return GetViewSpaceDepth(fDeviceDepth) * ViewSpaceToMetersFactor();
}

FfxFloat32x3 GetViewSpacePosition(FfxInt32x2 iViewportPos, FfxInt32x2 iViewportSize, FfxFloat32 fDeviceDepth)
{
    const FfxFloat32x4 fDeviceToViewDepth = DeviceToViewSpaceTransformFactors();

    const FfxFloat32 Z = GetViewSpaceDepth(fDeviceDepth);

    const FfxFloat32x2 fNdcPos = ComputeNdc(iViewportPos, iViewportSize);
    const FfxFloat32 X = fDeviceToViewDepth[2] * fNdcPos.x * Z;
    const FfxFloat32 Y = fDeviceToViewDepth[3] * fNdcPos.y * Z;

    return FfxFloat32x3(X, Y, Z);
}

FfxFloat32x3 GetViewSpacePositionInMeters(FfxInt32x2 iViewportPos, FfxInt32x2 iViewportSize, FfxFloat32 fDeviceDepth)
{
    return GetViewSpacePosition(iViewportPos, iViewportSize, fDeviceDepth) * ViewSpaceToMetersFactor();
}

FfxFloat32 GetMaxDistanceInMeters()
{
#if FFX_FSR2_OPTION_INVERTED_DEPTH
    return GetViewSpaceDepth(0.0f) * ViewSpaceToMetersFactor();
#else
    return GetViewSpaceDepth(1.0f) * ViewSpaceToMetersFactor();
#endif
}

FfxFloat32x3 PrepareRgb(FfxFloat32x3 fRgb, FfxFloat32 fExposure, FfxFloat32 fPreExposure)
{
    fRgb /= fPreExposure;
    fRgb *= fExposure;

    fRgb = clamp(fRgb, 0.0f, FSR2_FP16_MAX);

    return fRgb;
}

FfxFloat32x3 UnprepareRgb(FfxFloat32x3 fRgb, FfxFloat32 fExposure)
{
    fRgb /= fExposure;
    fRgb *= PreExposure();

    return fRgb;
}


struct BilinearSamplingData
{
    FfxInt32x2 iOffsets[4];
    FfxFloat32 fWeights[4];
    FfxInt32x2 iBasePos;
};

BilinearSamplingData GetBilinearSamplingData(FfxFloat32x2 fUv, FfxInt32x2 iSize)
{
    BilinearSamplingData data;

    FfxFloat32x2 fPxSample = (fUv * iSize) - FfxFloat32x2(0.5f, 0.5f);
    data.iBasePos = FfxInt32x2(floor(fPxSample));
    FfxFloat32x2 fPxFrac = ffxFract(fPxSample);

    data.iOffsets[0] = FfxInt32x2(0, 0);
    data.iOffsets[1] = FfxInt32x2(1, 0);
    data.iOffsets[2] = FfxInt32x2(0, 1);
    data.iOffsets[3] = FfxInt32x2(1, 1);

    data.fWeights[0] = (1 - fPxFrac.x) * (1 - fPxFrac.y);
    data.fWeights[1] = (fPxFrac.x) * (1 - fPxFrac.y);
    data.fWeights[2] = (1 - fPxFrac.x) * (fPxFrac.y);
    data.fWeights[3] = (fPxFrac.x) * (fPxFrac.y);

    return data;
}

struct PlaneData
{
    FfxFloat32x3 fNormal;
    FfxFloat32 fDistanceFromOrigin;
};

PlaneData GetPlaneFromPoints(FfxFloat32x3 fP0, FfxFloat32x3 fP1, FfxFloat32x3 fP2)
{
    PlaneData plane;

    FfxFloat32x3 v0 = fP0 - fP1;
    FfxFloat32x3 v1 = fP0 - fP2;
    plane.fNormal = normalize(cross(v0, v1));
    plane.fDistanceFromOrigin = -dot(fP0, plane.fNormal);

    return plane;
}

FfxFloat32 PointToPlaneDistance(PlaneData plane, FfxFloat32x3 fPoint)
{
    return abs(dot(plane.fNormal, fPoint) + plane.fDistanceFromOrigin);
}

#endif 

#endif 






#ifndef FFX_FSR2_THREAD_GROUP_WIDTH
#define FFX_FSR2_THREAD_GROUP_WIDTH 8
#endif 
#ifndef FFX_FSR2_THREAD_GROUP_HEIGHT
#define FFX_FSR2_THREAD_GROUP_HEIGHT 8
#endif 
#ifndef FFX_FSR2_THREAD_GROUP_DEPTH
#define FFX_FSR2_THREAD_GROUP_DEPTH 1
#endif 
#ifndef FFX_FSR2_NUM_THREADS
#define FFX_FSR2_NUM_THREADS layout (local_size_x = FFX_FSR2_THREAD_GROUP_WIDTH, local_size_y = FFX_FSR2_THREAD_GROUP_HEIGHT, local_size_z = FFX_FSR2_THREAD_GROUP_DEPTH) in;
#endif 

#if defined(FSR2_BIND_CB_REACTIVE)
layout (set = 1, binding = FSR2_BIND_CB_REACTIVE, std140) uniform cbGenerateReactive_t
{
	float   scale;
	float   threshold;
	float   binaryValue;
	uint    flags;
} cbGenerateReactive;
#endif

FFX_FSR2_NUM_THREADS
void main()
{
    FfxUInt32x2 uDispatchThreadId = gl_GlobalInvocationID.xy;

    FfxFloat32x3 ColorPreAlpha  = LoadOpaqueOnly(FFX_MIN16_I2(uDispatchThreadId)).rgb;
    FfxFloat32x3 ColorPostAlpha = LoadInputColor(FFX_MIN16_I2(uDispatchThreadId)).rgb;
    
    if ((cbGenerateReactive.flags & FFX_FSR2_AUTOREACTIVEFLAGS_APPLY_TONEMAP) != 0)
    {
        ColorPreAlpha = Tonemap(ColorPreAlpha);
        ColorPostAlpha = Tonemap(ColorPostAlpha);
    }
)<!>" R"<!>(
    if ((cbGenerateReactive.flags & FFX_FSR2_AUTOREACTIVEFLAGS_APPLY_INVERSETONEMAP) != 0)
    {
        ColorPreAlpha = InverseTonemap(ColorPreAlpha);
        ColorPostAlpha = InverseTonemap(ColorPostAlpha);
    }

    FfxFloat32 out_reactive_value = 0.f;
    FfxFloat32x3 delta = abs(ColorPostAlpha - ColorPreAlpha);
    
    out_reactive_value = ((cbGenerateReactive.flags & FFX_FSR2_AUTOREACTIVEFLAGS_USE_COMPONENTS_MAX)!=0) ? max(delta.x, max(delta.y, delta.z)) : length(delta);
    out_reactive_value *= cbGenerateReactive.scale;

    out_reactive_value = ((cbGenerateReactive.flags & FFX_FSR2_AUTOREACTIVEFLAGS_APPLY_THRESHOLD)!=0) ? ((out_reactive_value < cbGenerateReactive.threshold) ? 0 : cbGenerateReactive.binaryValue) : out_reactive_value;

    imageStore(rw_output_autoreactive, FfxInt32x2(uDispatchThreadId), vec4(out_reactive_value));
}

)<!>"
		};
		setup(nullptr, nullptr, _compute_code, "Fsr2AutogenReactivePassShaderRD");
	}
};

#endif
