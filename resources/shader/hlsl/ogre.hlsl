#include "common.hlsl"
struct VertexIn
{
	float3 PosL    : POSITION;
#ifdef USENORMAL
    float3 NormalL : NORMAL;
#endif
	float2 iTexcoord_0 : TEXCOORD0;
	float2 iTexcoord_1 : TEXCOORD1;
};

struct VertexOut
{
	float4 PosH    : SV_POSITION;
	
#ifdef USENORMAL
	float3	oTexcoord_0 : TEXCOORD0;
	float3	oTexcoord_1 : TEXCOORD1;
	float2	oTexcoord_2 : TEXCOORD2;
	float2	oTexcoord_3 : TEXCOORD3;
#else
    float2	oTexcoord_0 : TEXCOORD0;
	float2	oTexcoord_1 : TEXCOORD1;
#endif
};

#ifdef USENORMAL
VertexOut VS(VertexIn vIn)
{
	VertexOut vOut;
	//float4 posW = mul(float4(vIn.PosL, 1.0f), gWorld);
	//vOut.PosH = mul(posW, gViewProj);
	vOut.PosH = mul(gWorldViewProj, float4(vIn.PosL, 1.0f));
	vOut.oTexcoord_0 = mul(vIn.NormalL, (float3x3) gWorldInvTranspose);
	matrix worldview = gView * gWorld;
	vOut.oTexcoord_1 = mul(float4(vIn.PosL, 1.0f), worldview).xyz;
	vOut.oTexcoord_2	=	vIn.iTexcoord_0;
	vOut.oTexcoord_3	=	vIn.iTexcoord_1;
	return vOut;
}

void SGX_Light_Point_DiffuseSpecular(
				    in float3 vNormal,
				    in float3 vViewPos,
				    in float3 vLightPos,
				    in float4 vAttParams,
				    in float3 vDiffuseColour, 
				    in float3 vSpecularColour, 
					in float fSpecularPower,
					inout float3 vOutDiffuse,
					inout float3 vOutSpecular)
{
	float3 vLightView    = vLightPos - vViewPos;
	float fLightD      = length(vLightView);
	vLightView		   = normalize(vLightView);	
	float3 vNormalView = normalize(vNormal);
	float nDotL        = dot(vNormalView, vLightView);	
		
	if (nDotL > 0.0 && fLightD <= vAttParams.x)
	{					
		float3 vView       = -normalize(vViewPos);
		float3 vHalfWay    = normalize(vView + vLightView);		
		float nDotH        = dot(vNormalView, vHalfWay);
		float fAtten	   = 1.0 / (vAttParams.y + vAttParams.z*fLightD + vAttParams.w*fLightD*fLightD);					
		
		vOutDiffuse  += vDiffuseColour * nDotL * fAtten;
#ifdef NORMALISED
		vSpecularColour *= (fSpecularPower + 8.0)/(8.0 * M_PI);
#endif
		vOutSpecular += vSpecularColour * pow(clamp(nDotH, 0.0, 1.0), fSpecularPower) * fAtten;

        vOutDiffuse = clamp(vOutDiffuse, 0.0, 1.0);
        vOutSpecular = clamp(vOutSpecular, 0.0, 1.0);
	}
}

float4 PS(VertexOut pin) : SV_Target
{
    float4	lColor_0;
	float4	lColor_1;
	float4	texel_0;
	float4	texel_1;

	lColor_0	=	float4(1.00000,1.00000,1.00000,1.00000);

	lColor_1	=	float4(0.00000,0.00000,0.00000,0.00000);


	float4 oColor_0	=	float4(0.7, 0.7, 0.7, 1.0);
	
	float4 light_attenuation = float4(10000.0f, 1.0f, 1.0f, 1.0f);
	float4 derived_light_diffuse_colour = float4(0.7, 0.7, 0.7, 1.0);
	float4 derived_light_specular_colour = float4(0.9, 0.9, 0.9, 1.0);
	float surface_shininess = 20.0f;
	float4 light_position_view_space = mul(float4(20, 80, 50, 1.0f), gView);
	SGX_Light_Point_DiffuseSpecular(pin.oTexcoord_0, pin.oTexcoord_1, light_position_view_space.xyz, 
	light_attenuation, derived_light_diffuse_colour.xyz, 
	derived_light_specular_colour.xyz, surface_shininess, oColor_0.xyz, lColor_1.xyz);

	texel_0 = gTextureArray[0].Sample(gsamAnisotropicWrap, pin.oTexcoord_2) * float4(1.0f, 1.0f, 1.0f, 1.0f);
	
	texel_1 = gTextureArray[1].Sample(gsamAnisotropicWrap, pin.oTexcoord_3) * float4(1.0f, 1.0f, 1.0f, 1.0f);

	oColor_0	=	texel_0*oColor_0;

	oColor_0	=	texel_1*oColor_0;

	oColor_0.xyz	=	oColor_0.xyz+lColor_1.xyz;
	return float4(oColor_0.xyz, 1.0f);
}
#else
VertexOut VS(VertexIn vIn)
{
	VertexOut vOut;
	
	vOut.PosH = mul(gWorldViewProj, float4(vIn.PosL, 1.0f));
	vOut.oTexcoord_0 = vIn.iTexcoord_0;
    vOut.oTexcoord_1 = vIn.iTexcoord_1;
	return vOut;
}

float4 PS(VertexOut pin) : SV_Target
{
    float4	lColor_0;
	float4	lColor_1;
	float4	texel_0;
	float4	texel_1;

	lColor_0	=	float4(1.00000,1.00000,1.00000,1.00000);

	lColor_1	=	float4(0.00000,0.00000,0.00000,0.00000);

	float4 oColor_0	=	lColor_0;
	
	texel_0 = gTextureArray[0].Sample(gsamAnisotropicWrap, pin.oTexcoord_0);
	
	texel_1 = gTextureArray[1].Sample(gsamAnisotropicWrap, pin.oTexcoord_1);

	oColor_0	=	texel_0*oColor_0;

	oColor_0	=	texel_1*oColor_0;

	oColor_0.xyz	=	oColor_0.xyz+lColor_1.xyz;
	
	return float4(oColor_0.xyz, 1.0f);
}
#endif
