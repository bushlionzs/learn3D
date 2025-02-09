/* WARNING, THIS FILE WAS GENERATED, DO NOT EDIT */
#ifndef BLUR_RASTER_GLSL_GEN_H_RD
#define BLUR_RASTER_GLSL_GEN_H_RD

#include "servers/rendering/renderer_rd/shader_rd.h"

class BlurRasterShaderRD : public ShaderRD {

public:

	BlurRasterShaderRD() {

		static const char _vertex_code[] = {
R"<!>(
#version 450

#VERSION_DEFINES

#define FLAG_HORIZONTAL (1 << 0)
#define FLAG_USE_ORTHOGONAL_PROJECTION (1 << 1)
#define FLAG_GLOW_FIRST_PASS (1 << 2)

layout(push_constant, std430) uniform Blur {
	vec2 pixel_size; 
	uint flags; 
	uint pad; 

	
	float glow_strength; 
	float glow_bloom; 
	float glow_hdr_threshold; 
	float glow_hdr_scale; 

	float glow_exposure; 
	float glow_white; 
	float glow_luminance_cap; 
	float glow_auto_exposure_scale; 

	float luminance_multiplier; 
	float res1; 
	float res2; 
	float res3; 
}
blur;

layout(location = 0) out vec2 uv_interp;
/* clang-format on */

void main() {
	vec2 base_arr[3] = vec2[](vec2(-1.0, -1.0), vec2(-1.0, 3.0), vec2(3.0, -1.0));
	gl_Position = vec4(base_arr[gl_VertexIndex], 0.0, 1.0);
	uv_interp = clamp(gl_Position.xy, vec2(0.0, 0.0), vec2(1.0, 1.0)) * 2.0; 
}

/* clang-format off */
)<!>"
		};
		static const char _fragment_code[] = {
R"<!>(
#version 450

#VERSION_DEFINES

#define FLAG_HORIZONTAL (1 << 0)
#define FLAG_USE_ORTHOGONAL_PROJECTION (1 << 1)
#define FLAG_GLOW_FIRST_PASS (1 << 2)

layout(push_constant, std430) uniform Blur {
	vec2 pixel_size; 
	uint flags; 
	uint pad; 

	
	float glow_strength; 
	float glow_bloom; 
	float glow_hdr_threshold; 
	float glow_hdr_scale; 

	float glow_exposure; 
	float glow_white; 
	float glow_luminance_cap; 
	float glow_auto_exposure_scale; 

	float luminance_multiplier; 
	float res1; 
	float res2; 
	float res3; 
}
blur;

layout(location = 0) in vec2 uv_interp;
/* clang-format on */

layout(set = 0, binding = 0) uniform sampler2D source_color;

#ifdef GLOW_USE_AUTO_EXPOSURE
layout(set = 1, binding = 0) uniform sampler2D source_auto_exposure;
#endif

layout(location = 0) out vec4 frag_color;

void main() {
	

#ifdef MODE_MIPMAP

	vec2 pix_size = blur.pixel_size;
	vec4 color = texture(source_color, uv_interp + vec2(-0.5, -0.5) * pix_size);
	color += texture(source_color, uv_interp + vec2(0.5, -0.5) * pix_size);
	color += texture(source_color, uv_interp + vec2(0.5, 0.5) * pix_size);
	color += texture(source_color, uv_interp + vec2(-0.5, 0.5) * pix_size);
	frag_color = color / 4.0;

#endif

#ifdef MODE_GAUSSIAN_BLUR

	
	
	
	vec4 A = texture(source_color, uv_interp + blur.pixel_size * vec2(-1.0, -1.0));
	vec4 B = texture(source_color, uv_interp + blur.pixel_size * vec2(0.0, -1.0));
	vec4 C = texture(source_color, uv_interp + blur.pixel_size * vec2(1.0, -1.0));
	vec4 D = texture(source_color, uv_interp + blur.pixel_size * vec2(-0.5, -0.5));
	vec4 E = texture(source_color, uv_interp + blur.pixel_size * vec2(0.5, -0.5));
	vec4 F = texture(source_color, uv_interp + blur.pixel_size * vec2(-1.0, 0.0));
	vec4 G = texture(source_color, uv_interp);
	vec4 H = texture(source_color, uv_interp + blur.pixel_size * vec2(1.0, 0.0));
	vec4 I = texture(source_color, uv_interp + blur.pixel_size * vec2(-0.5, 0.5));
	vec4 J = texture(source_color, uv_interp + blur.pixel_size * vec2(0.5, 0.5));
	vec4 K = texture(source_color, uv_interp + blur.pixel_size * vec2(-1.0, 1.0));
	vec4 L = texture(source_color, uv_interp + blur.pixel_size * vec2(0.0, 1.0));
	vec4 M = texture(source_color, uv_interp + blur.pixel_size * vec2(1.0, 1.0));

	float base_weight = 0.5 / 4.0;
	float lesser_weight = 0.125 / 4.0;

	frag_color = (D + E + I + J) * base_weight;
	frag_color += (A + B + G + F) * lesser_weight;
	frag_color += (B + C + H + G) * lesser_weight;
	frag_color += (F + G + L + K) * lesser_weight;
	frag_color += (G + H + M + L) * lesser_weight;
#endif

#ifdef MODE_GAUSSIAN_GLOW

	

#define GLOW_ADD(m_ofs, m_mult)                                                  \
	{                                                                            \
		vec2 ofs = uv_interp + m_ofs * pix_size;                                 \
		vec4 c = texture(source_color, ofs) * m_mult;                            \
		if (any(lessThan(ofs, vec2(0.0))) || any(greaterThan(ofs, vec2(1.0)))) { \
			c *= 0.0;                                                            \
		}                                                                        \
		color += c;                                                              \
	}

	if (bool(blur.flags & FLAG_HORIZONTAL)) {
		vec2 pix_size = blur.pixel_size;
		pix_size *= 0.5; 

		vec4 color = texture(source_color, uv_interp + vec2(0.0, 0.0) * pix_size) * 0.174938;
		GLOW_ADD(vec2(1.0, 0.0), 0.165569);
		GLOW_ADD(vec2(2.0, 0.0), 0.140367);
		GLOW_ADD(vec2(3.0, 0.0), 0.106595);
		GLOW_ADD(vec2(-1.0, 0.0), 0.165569);
		GLOW_ADD(vec2(-2.0, 0.0), 0.140367);
		GLOW_ADD(vec2(-3.0, 0.0), 0.106595);

		
		color *= blur.glow_strength;

		frag_color = color;
	} else {
		vec2 pix_size = blur.pixel_size;
		vec4 color = texture(source_color, uv_interp + vec2(0.0, 0.0) * pix_size) * 0.288713;
		GLOW_ADD(vec2(0.0, 1.0), 0.233062);
		GLOW_ADD(vec2(0.0, 2.0), 0.122581);
		GLOW_ADD(vec2(0.0, -1.0), 0.233062);
		GLOW_ADD(vec2(0.0, -2.0), 0.122581);

		frag_color = color;
	}

#undef GLOW_ADD

	if (bool(blur.flags & FLAG_GLOW_FIRST_PASS)) {
		
		
		frag_color *= blur.luminance_multiplier;

#ifdef GLOW_USE_AUTO_EXPOSURE

		frag_color /= texelFetch(source_auto_exposure, ivec2(0, 0), 0).r / blur.glow_auto_exposure_scale;
#endif
		frag_color *= blur.glow_exposure;

		float luminance = max(frag_color.r, max(frag_color.g, frag_color.b));
		float feedback = max(smoothstep(blur.glow_hdr_threshold, blur.glow_hdr_threshold + blur.glow_hdr_scale, luminance), blur.glow_bloom);

		frag_color = min(frag_color * feedback, vec4(blur.glow_luminance_cap)) / blur.luminance_multiplier;
	}

#endif 

#ifdef MODE_COPY
	vec4 color = textureLod(source_color, uv_interp, 0.0);
	frag_color = color;
#endif
}
)<!>"
		};
		setup(_vertex_code, _fragment_code, nullptr, "BlurRasterShaderRD");
	}
};

#endif
