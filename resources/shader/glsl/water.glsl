#version 450
#include "common.glsl"
#ifdef VERTEX_SHADER
struct Wave {
  float freq;  // 2*PI / wavelength
  float amp;   // amplitude
  float phase; // speed * 2*PI / wavelength
  vec2 dir;
};


layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color_diffuse;
layout (location = 3) in vec2 texcoord;

layout (location = 0) out vec4 oDiffuseColor;
layout (location = 1) out vec2 oBumpCoord1;
layout (location = 2) out vec2 oBumpCoord2;
layout (location = 3) out vec2 oBumpCoord3;
layout (location = 4) out vec4 oEyePosition;
layout (location = 5) out vec4 rotMatrix1;
layout (location = 6) out vec4 rotMatrix2;
layout (location = 7) out vec4 rotMatrix3;


void main()
{
	#define NWAVES 2
	Wave wave[NWAVES] = {
		{ 0.016, 6.8, 0.4, vec2(-1, 0) },
		{ 0.032, 3.244, 1.6, vec2(-0.7, 0.7) }
	};
	float textureSpeed = 0.03f;
	float time_0_x = 100.0f;
	time_0_x = time_0_x - cbPass.gTotalTime;
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
	vec3 inpos = position;
	for(int i = 0; i<NWAVES; ++i)
	{
		float angle = wave[i].freq * dot(wave[i].dir, inpos.xz) + wave[i].phase * time_0_x;
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
		
		inpos.y += wave[i].amp * S;
		
		float QixAxC = Qi * wave[i].amp * C;
		inpos.x += QixAxC * wave[i].dir.x;
		inpos.z += QixAxC * wave[i].dir.y;
	}
	
	rotMatrix1.xyz = 0.2 * normalize(vec3(1 - SigmaBinX, SigmaDxxWAxC, -SigmaBinZ)); // Binormal
	rotMatrix2.xyz = 0.2 * normalize(vec3(-SigmaTanX, SigmaDyxWAxC, 1 - SigmaTanZ)); // Tangent
	rotMatrix3.xyz = normalize(vec3(-SigmaDxxWAxC, 1 - SigmaQixWAxS, -SigmaDyxWAxC)); // Normal
	
	// 变换顶点位置
	gl_Position = cbPerObject.gWorldViewProj * vec4(inpos,1.0f);
    gl_Position.y = -gl_Position.y;
	
	oEyePosition = vec4((cbPass.gEyePosW.xyz - inpos.xyz).xyz,0);
	oEyePosition = normalize(oEyePosition);
	
	oDiffuseColor.xyz = vec3(1.0);
	oDiffuseColor.w = color_diffuse.w;
	
	vec2 texScale = vec2(0.3f,0.3f);
	
	oBumpCoord1 = texcoord.xy * texScale + textureSpeed * time_0_x;
	oBumpCoord2 = texcoord.xy * texScale * 2 + textureSpeed * time_0_x * 4;
	oBumpCoord3 = texcoord.xy * texScale * 4 + textureSpeed * time_0_x * 8;
	
}

#endif //VERTEX_SHADER

#ifdef FRAGMENT_SHADER

layout (location = 0) in vec4 oDiffuseColor;
layout (location = 1) in vec2 oBumpCoord1;
layout (location = 2) in vec2 oBumpCoord2;
layout (location = 3) in vec2 oBumpCoord3;
layout (location = 4) in vec4 oEyePosition;
layout (location = 5) in vec4 rotMatrix1;
layout (location = 6) in vec4 rotMatrix2;
layout (location = 7) in vec4 rotMatrix3;

layout(location = 0) out vec4 outColor;
void main()
{
	vec3 normal1 = 2.0 * texture(first, oBumpCoord1).xyz - vec3(1.0);
	vec3 normal2 = 2.0 * texture(first, oBumpCoord2).xyz - vec3(1.0);
	vec3 normal3 = 2.0 * texture(first, oBumpCoord3).xyz - vec3(1.0);
	vec3 adjustNormal = normalize(normal1 + normal1 + normal2);
	
	mat3 m;
    m[0].xyz = rotMatrix1.xyz; // Binormal
    m[1].xyz = rotMatrix2.xyz;
    m[2].xyz = rotMatrix3.xyz;
  
    adjustNormal = normalize( adjustNormal* m );
  
	vec3 reflectVec = reflect(-oEyePosition.xyz,adjustNormal);
	reflectVec.z = - reflectVec.z;
	
	vec3 reflectioncolour = texture(gCubeMap, reflectVec).xyz;
	reflectioncolour *= (reflectioncolour.x + reflectioncolour.y + reflectioncolour.z) * 0.7;
	
	float facing = 1.0 - max(dot(oEyePosition.xyz,adjustNormal),0.0);
	float fresnelTerm = clamp(0.22037 + pow(facing,5.546), 0.0, 1.0);
	
	vec4 deepColor = vec4(0, 0.3, 0.5, 1.0);
	vec4 shallowColor = vec4( 0, 1, 1 ,1.0);
	
	// shallowColor = shallowColor + facing * (deepColor - shallowColor);
	// 当前视向量与扰动法线的夹角越小，越趋近于浅表面色,夹角越大，越趋近于深水色[19/2/2009 JiangWei]
	vec4 waterColor = mix(shallowColor,deepColor,facing) * 0.4;
	
	outColor.xyz = (1 - fresnelTerm) * waterColor.xyz + reflectioncolour * fresnelTerm;
	outColor.w = clamp(oDiffuseColor.a,0.0,0.9);
}
#endif //FRAGMENT_SHADER