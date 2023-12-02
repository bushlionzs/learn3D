#include "common.hlsl"

struct VertexOnelayerIn
{
    float3 posL : POSITION;
    float3 normalL : NORMAL;
    float2 tex : TEXCOORD0;
};

struct VertexOnelayerLightmapIn
{
    float3 posL : POSITION;
    float3 normalL : NORMAL;
    float2 tex : TEXCOORD0;
	float2 tex2 : TEXCOORD1;
};

struct VertexTwolayerIn
{
    float3 posL : POSITION;
    float3 normalL : NORMAL;
    float2 tex : TEXCOORD0;
	float2 tex2 : TEXCOORD1;
};

struct VertexTwolayerLightmapIn
{
    float3 posL : POSITION;
    float3 normalL : NORMAL;
    float2 tex : TEXCOORD0;
	float2 tex2 : TEXCOORD1;
	float2 tex3 : TEXCOORD2;
};

struct VertexOnelayerOut
{
    float4 posH : SV_POSITION;   
    float3 normalW : NORMAL;    
    float2 tex : TEXCOORD0;
};

struct VertexOnelayerLightmapOut
{
    float4 posH : SV_POSITION;   
    float3 normalW : NORMAL;    
    float2 tex : TEXCOORD0;
	float2 tex2 : TEXCOORD1;
};

struct VertexTwolayerOut
{
    float4 posH : SV_POSITION;   
    float3 normalW : NORMAL;    
    float2 tex : TEXCOORD0;
	float2 tex2 : TEXCOORD1;
};

struct VertexTwolayerLightmapOut
{
    float4 posH : SV_POSITION;   
    float3 normalW : NORMAL;    
    float2 tex : TEXCOORD0;
	float2 tex2 : TEXCOORD1;
	float2 tex3 : TEXCOORD2;
};

VertexOnelayerOut onelayer_vs(VertexOnelayerIn vIn)
{
    VertexOnelayerOut vOut;
    vOut.posH = mul(gWorldViewProj, float4(vIn.posL, 1.0f));
    vOut.normalW = mul((float3x3) gWorld, vIn.normalL);
    vOut.tex = vIn.tex;
    return vOut;
}

float4 onelayer_ps(VertexOnelayerOut pIn) : SV_Target
{
    float4 texColor = gTextureArray[0].Sample(gsamAnisotropicClamp, pIn.tex);
	return texColor;
}

VertexOnelayerLightmapOut onelayer_lightmap_vs(VertexOnelayerLightmapIn vIn)
{
    VertexOnelayerLightmapOut vOut;
    vOut.posH = mul(gWorldViewProj, float4(vIn.posL, 1.0f));
    vOut.normalW = mul((float3x3) gWorld, vIn.normalL);
    vOut.tex = vIn.tex;
	vOut.tex2 = vIn.tex2;
    return vOut;
}

float4 onelayer_lightmap_ps(VertexOnelayerLightmapOut pIn) : SV_Target
{
    float4 BaseTex0 = gTextureArray[0].Sample(gsamAnisotropicClamp, pIn.tex);
	float4 LightMapTex = gTextureArray[1].Sample(gsamAnisotropicClamp, pIn.tex2);
	float3 BlendColor = LightMapTex.rgb * BaseTex0.rgb;
	return float4(BlendColor, 1.0);
}


VertexTwolayerOut twolayer_vs(VertexTwolayerIn vIn)
{
    VertexTwolayerOut vOut;
	vOut.posH = mul(gWorldViewProj, float4(vIn.posL, 1.0f));
    vOut.normalW = mul((float3x3) gWorld, vIn.normalL);
    vOut.tex = vIn.tex;
	vOut.tex2 = vIn.tex2;
    return vOut;
}


float4 twolayer_ps(VertexTwolayerOut pIn) : SV_Target
{
    float4 BaseTex0 = gTextureArray[0].Sample(gsamAnisotropicClamp, pIn.tex);
	float4 BaseTex1 = gTextureArray[1].Sample(gsamAnisotropicClamp, pIn.tex2);
	
	float3 TexColor = lerp(BaseTex0.rgb, BaseTex1.rgb, BaseTex1.a);
    return float4(TexColor, 1.0);
}

VertexTwolayerLightmapOut twolayer_lightmap_vs(VertexTwolayerLightmapIn vIn)
{
    VertexTwolayerLightmapOut vOut;
	vOut.posH = mul(gWorldViewProj, float4(vIn.posL, 1.0f));
    vOut.normalW = mul((float3x3) gWorld, vIn.normalL);
    vOut.tex = vIn.tex;
	vOut.tex2 = vIn.tex2;
	vOut.tex3 = vIn.tex3;
    return vOut;
}


float4 twolayer_lightmap_ps(VertexTwolayerLightmapOut pIn) : SV_Target
{
    float4 BaseTex0 = gTextureArray[0].Sample(gsamAnisotropicClamp, pIn.tex);
	float4 BaseTex1 = gTextureArray[1].Sample(gsamAnisotropicClamp, pIn.tex2);
	float4 LightMapTex = gTextureArray[2].Sample(gsamAnisotropicClamp, pIn.tex3).rrrr;
	
	float3 BlendTexColor = lerp(BaseTex0.rgb, BaseTex1.rgb, BaseTex1.a); 
	
	
	float3 BlendColor = LightMapTex.rgb * BlendTexColor; 
	
	return float4(BlendColor, 1.0);
}