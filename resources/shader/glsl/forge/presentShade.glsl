#version 450 core
#extension GL_GOOGLE_include_directive : require
#include "glslBase.glsl"
#ifdef VERTEX_SHADER

layout(location = 0) out(float2) out_texCoord;
void main()
{
    const uint vertexID = uint(gl_VertexIndex);
	
	float4 position;
	position.x = (vertexID == 2) ? 3.0 : -1.0;
	position.y = (vertexID == 0) ? -3.0 : 1.0;
	position.zw = f2(1.0);
	
	gl_Position = position;
    out_texCoord = position.xy * float2(0.5, -0.5) + 0.5;
}
#endif //VERTEX_SHADER

#ifdef FRAGMENT_SHADER
layout(location = 0) in(float2) In_texCoord;
layout(location = 0) out(float4) out_float4;
RES(Tex2D(float4), SourceTexture, UPDATE_FREQ_NONE, t0, binding = 0);
RES(SamplerState, repeatBillinearSampler, UPDATE_FREQ_NONE, s1, binding = 1);
void main()
{
	float4 vertexPosition = float4(float4(gl_FragCoord.xyz, 1.0f / gl_FragCoord.w));
	float4 Out;
	float4 sceneColor = SampleTex2D(Get(SourceTexture), Get(repeatBillinearSampler), In_texCoord);
	out_float4 = float4(sceneColor.rgb, 1.0);
}
#endif //FRAGMENT_SHADER