#include "common.hlsl"

struct Wave {
  float freq;  // 2*PI / wavelength
  float amp;   // amplitude
  float phase; // speed * 2*PI / wavelength
  float2 dir;
};

struct VertexIn
{
    float4 pos										:POSITION;
	float4 vertexcolor								:COLOR;
	float2 tex										:TEXCOORD;
};

struct VertexOut
{
	float4 oPosition	 : SV_POSITION; 
	float4 oDiffuseColor :COLOR ;
	float2 oBumpCoord1   :TEXCOORD0;
	float2 oBumpCoord2   :TEXCOORD1;
	float2 oBumpCoord3   :TEXCOORD2;
	float4 oEyePosition  :POSITION1;
	float4 rotMatrix1    :POSITION2;
	float4 rotMatrix2    :POSITION3;
	float4 rotMatrix3    :POSITION4;
};

VertexOut vs_main(VertexIn vIn)
{
	#define NWAVES 2
	Wave wave[NWAVES] = {
		{ 0.016, 6.8, 0.4, float2(-1, 0) },
		{ 0.032, 3.244, 1.6, float2(-0.7, 0.7) }
	};
	float textureSpeed = 0.03f;
	float time_0_x = 100.0f;
	time_0_x = time_0_x - gTotalTime;
	VertexOut vOut;
	float Q = 0.01;
	float SigmaQixWAxS = 0.0;
	float SigmaDxxWAxC  = 0.0;
	float SigmaDyxWAxC  = 0.0;
	float SigmaBinX  = 0.0;
	float SigmaBinZ  = 0.0;
	float SigmaTanX  = 0.0;
	float SigmaTanZ  = 0.0;

	//创建Gerstner波形
	//参见 GPU Gems 1 第一章
	//Todo:增加当陡度为0.0时的分支预测，优化性能
	//[25/02/2009 JiangWei]
	
	for(int i = 0; i<NWAVES; ++i)
	{
		float angle = wave[i].freq * dot(wave[i].dir,vIn.pos.xz) + wave[i].phase * time_0_x;
		float WA = wave[i].freq * wave[i].amp;
		
		float S = sin(angle);
		float C = cos(angle);
		
		float WAxS = WA * S;
		float WAxC = WA * C;
		
		float Qi = Q / (WA * NWAVES);
		float QixWAxS = Qi * WAxS;
		float DxxQixWAxS = wave[i].dir.x * QixWAxS;
		float DyxQixWAxS = wave[i].dir.y * QixWAxS;
		
		SigmaQixWAxS += QixWAxS;
		
		SigmaDxxWAxC += wave[i].dir.x * WAxC;
		SigmaDyxWAxC += wave[i].dir.y * WAxC;	
		
		float tmpTerm = wave[i].dir.y * DxxQixWAxS;
		SigmaBinX += wave[i].dir.x * DxxQixWAxS;
		SigmaBinZ += tmpTerm;
		
		SigmaTanX += tmpTerm;
		SigmaTanZ += wave[i].dir.y * DyxQixWAxS;
		
		vIn.pos.y += wave[i].amp * S;
		
		float QixAxC = Qi * wave[i].amp * C;
		vIn.pos.x += QixAxC * wave[i].dir.x;
		vIn.pos.z += QixAxC * wave[i].dir.y;
	}
	
	vOut.rotMatrix1.xyz = 0.2 * normalize(float3(1 - SigmaBinX, SigmaDxxWAxC, -SigmaBinZ)); // Binormal
	vOut.rotMatrix2.xyz = 0.2 * normalize(float3(-SigmaTanX, SigmaDyxWAxC, 1 - SigmaTanZ)); // Tangent
	vOut.rotMatrix3.xyz = normalize(float3(-SigmaDxxWAxC, 1 - SigmaQixWAxS, -SigmaDyxWAxC)); // Normal
	
	// 变换顶点位置
	vOut.oPosition = mul(gWorldViewProj, vIn.pos);
					   				
	vOut.oEyePosition = float4((gEyePosW.xyz - vIn.pos.xyz).xyz,0);
	vOut.oEyePosition = normalize(vOut.oEyePosition);
	
	vOut.oDiffuseColor.xyz = 1.0;
	vOut.oDiffuseColor.w = vIn.vertexcolor.w;
	
	float2 texScale = float2(0.3f,0.3f);
	
	vOut.oBumpCoord1 = vIn.tex.xy * texScale + textureSpeed * time_0_x;
	vOut.oBumpCoord2 = vIn.tex.xy * texScale * 2 + textureSpeed * time_0_x * 4;
	vOut.oBumpCoord3 = vIn.tex.xy * texScale * 4 + textureSpeed * time_0_x * 8;
	
	return vOut;
}


float4 ps_main(VertexOut pIn): SV_Target
{
	float3 normal1 = 2.0 * gTextureArray[0].Sample(gsamLinearWrap, pIn.oBumpCoord1).xyz - 1.0;
	float3 normal2 = 2.0 * gTextureArray[0].Sample(gsamLinearWrap, pIn.oBumpCoord2).xyz - 1.0;
	float3 normal3 = 2.0 * gTextureArray[0].Sample(gsamLinearWrap, pIn.oBumpCoord3).xyz - 1.0;
	float3 adjustNormal = normalize(normal1 + normal1 + normal2);
	
	float3x3 m;
    m[0].xyz = pIn.rotMatrix1.xyz; // Binormal
    m[1].xyz = pIn.rotMatrix2.xyz;
    m[2].xyz = pIn.rotMatrix3.xyz;
  
    adjustNormal = normalize( mul( adjustNormal, m ) );
  
	float3 reflectVec = reflect(-pIn.oEyePosition.xyz,adjustNormal);
	reflectVec.z = - reflectVec.z;
	
	float3 reflectioncolour = gCubeMap[0].Sample(gsamLinearClamp, reflectVec).xyz;
	reflectioncolour *= (reflectioncolour.x + reflectioncolour.y + reflectioncolour.z) * 0.7;
	
	float facing = 1.0 - max(dot(pIn.oEyePosition.xyz,adjustNormal),0.0);
	float fresnelTerm = saturate(0.22037 + pow(facing,5.546));
	
	float4 deepColor = float4(0, 0.3, 0.5, 1.0);
	float4 shallowColor = float4( 0, 1, 1 ,1.0);
	
	// shallowColor = shallowColor + facing * (deepColor - shallowColor);
	// 当前视向量与扰动法线的夹角越小，越趋近于浅表面色,夹角越大，越趋近于深水色[19/2/2009 JiangWei]
	float4 waterColor = lerp(shallowColor,deepColor,facing) * 0.4;
	
	float4 col;
	col.xyz = (1 - fresnelTerm) * waterColor.xyz + reflectioncolour * fresnelTerm;
	col.w = clamp(pIn.oDiffuseColor.a,0.0,0.9);
	return col;
}