/* WARNING, THIS FILE WAS GENERATED, DO NOT EDIT */
#ifndef SCREEN_SPACE_REFLECTION_GLSL_GEN_H_RD
#define SCREEN_SPACE_REFLECTION_GLSL_GEN_H_RD

#include "servers/rendering/renderer_rd/shader_rd.h"

class ScreenSpaceReflectionShaderRD : public ShaderRD {

public:

	ScreenSpaceReflectionShaderRD() {

		static const char _compute_code[] = {
R"<!>(
#version 450

#VERSION_DEFINES

layout(local_size_x = 8, local_size_y = 8, local_size_z = 1) in;

layout(rgba16f, set = 0, binding = 0) uniform restrict readonly image2D source_diffuse;
layout(r32f, set = 0, binding = 1) uniform restrict readonly image2D source_depth;
layout(rgba16f, set = 1, binding = 0) uniform restrict writeonly image2D ssr_image;
#ifdef MODE_ROUGH
layout(r8, set = 1, binding = 1) uniform restrict writeonly image2D blur_radius_image;
#endif
layout(rgba8, set = 2, binding = 0) uniform restrict readonly image2D source_normal_roughness;
layout(set = 3, binding = 0) uniform sampler2D source_metallic;

layout(push_constant, std430) uniform Params {
	vec4 proj_info;

	ivec2 screen_size;
	float camera_z_near;
	float camera_z_far;

	int num_steps;
	float depth_tolerance;
	float distance_fade;
	float curve_fade_in;

	bool orthogonal;
	float filter_mipmap_levels;
	bool use_half_res;
	uint view_index;
}
params;

layout(constant_id = 0) const bool sc_multiview = false;

layout(set = 4, binding = 0, std140) uniform SceneData {
	mat4x4 projection[2];
	mat4x4 inv_projection[2];
	vec4 eye_offset[2];
}
scene_data;

vec3 reconstructCSPosition(vec2 screen_pos, float z) {
	if (sc_multiview) {
		vec4 pos;
		pos.xy = (2.0 * vec2(screen_pos) / vec2(params.screen_size)) - 1.0;
		pos.z = z * 2.0 - 1.0;
		pos.w = 1.0;

		pos = scene_data.inv_projection[params.view_index] * pos;
		pos.xyz /= pos.w;

		return pos.xyz;
	} else {
		if (params.orthogonal) {
			return vec3(-(screen_pos.xy * params.proj_info.xy + params.proj_info.zw), z);
		} else {
			return vec3((screen_pos.xy * params.proj_info.xy + params.proj_info.zw) * z, z);
		}
	}
}

vec2 view_to_screen(vec3 view_pos, out float w) {
	vec4 projected = scene_data.projection[params.view_index] * vec4(view_pos, 1.0);
	projected.xyz /= projected.w;
	projected.xy = projected.xy * 0.5 + 0.5;
	w = projected.w;
	return projected.xy;
}

#define M_PI 3.14159265359

void main() {
	
	ivec2 ssC = ivec2(gl_GlobalInvocationID.xy);

	if (any(greaterThanEqual(ssC.xy, params.screen_size))) { 
		return;
	}

	vec2 pixel_size = 1.0 / vec2(params.screen_size);
	vec2 uv = vec2(ssC.xy) * pixel_size;

	uv += pixel_size * 0.5;

	float base_depth = imageLoad(source_depth, ssC).r;

	
	vec3 vertex = reconstructCSPosition(uv * vec2(params.screen_size), base_depth);

	vec4 normal_roughness = imageLoad(source_normal_roughness, ssC);
	vec3 normal = normalize(normal_roughness.xyz * 2.0 - 1.0);
	float roughness = normal_roughness.w;
	if (roughness > 0.5) {
		roughness = 1.0 - roughness;
	}
	roughness /= (127.0 / 255.0);

	
	if (roughness > 0.6) {
		
		
#ifdef MODE_ROUGH
		imageStore(blur_radius_image, ssC, vec4(0.0));
#endif
		imageStore(ssr_image, ssC, vec4(0.0));
		return;
	}

	normal = normalize(normal);
	normal.y = -normal.y; 

	vec3 view_dir;
	if (sc_multiview) {
		view_dir = normalize(vertex + scene_data.eye_offset[params.view_index].xyz);
	} else {
		view_dir = params.orthogonal ? vec3(0.0, 0.0, -1.0) : normalize(vertex);
	}
	vec3 ray_dir = normalize(reflect(view_dir, normal));

	if (dot(ray_dir, normal) < 0.001) {
		imageStore(ssr_image, ssC, vec4(0.0));
		return;
	}

	

	
	float ray_len = (vertex.z + ray_dir.z * params.camera_z_far) > -params.camera_z_near ? (-params.camera_z_near - vertex.z) / ray_dir.z : params.camera_z_far;
	vec3 ray_end = vertex + ray_dir * ray_len;

	float w_begin;
	vec2 vp_line_begin = view_to_screen(vertex, w_begin);
	float w_end;
	vec2 vp_line_end = view_to_screen(ray_end, w_end);
	vec2 vp_line_dir = vp_line_end - vp_line_begin;

	
	w_begin = 1.0 / w_begin;
	w_end = 1.0 / w_end;

	float z_begin = vertex.z * w_begin;
	float z_end = ray_end.z * w_end;

	vec2 line_begin = vp_line_begin / pixel_size;
	vec2 line_dir = vp_line_dir / pixel_size;
	float z_dir = z_end - z_begin;
	float w_dir = w_end - w_begin;

	

	float scale_max_x = min(1.0, 0.99 * (1.0 - vp_line_begin.x) / max(1e-5, vp_line_dir.x));
	float scale_max_y = min(1.0, 0.99 * (1.0 - vp_line_begin.y) / max(1e-5, vp_line_dir.y));
	float scale_min_x = min(1.0, 0.99 * vp_line_begin.x / max(1e-5, -vp_line_dir.x));
	float scale_min_y = min(1.0, 0.99 * vp_line_begin.y / max(1e-5, -vp_line_dir.y));
	float line_clip = min(scale_max_x, scale_max_y) * min(scale_min_x, scale_min_y);
	line_dir *= line_clip;
	z_dir *= line_clip;
	w_dir *= line_clip;

	
	vec2 line_advance = normalize(line_dir); 
	float step_size = 1.0 / length(line_dir);
	float z_advance = z_dir * step_size; 
	float w_advance = w_dir * step_size; 

	
	float advance_angle_adj = 1.0 / max(abs(line_advance.x), abs(line_advance.y));
	line_advance *= advance_angle_adj; 
	z_advance *= advance_angle_adj;
	w_advance *= advance_angle_adj;

	vec2 pos = line_begin;
	float z = z_begin;
	float w = w_begin;
	float z_from = z / w;
	float z_to = z_from;
	float depth;
	vec2 prev_pos = pos;

	if (ivec2(pos + line_advance - 0.5) == ssC) {
		
		
		pos += line_advance;
		z += z_advance;
		w += w_advance;
	}

	bool found = false;

	float steps_taken = 0.0;

	for (int i = 0; i < params.num_steps; i++) {
		pos += line_advance;
		z += z_advance;
		w += w_advance;

		
		ivec2 test_pos = ivec2(pos - 0.5);
		depth = imageLoad(source_depth, test_pos).r;
		if (sc_multiview) {
			depth = depth * 2.0 - 1.0;
			depth = 2.0 * params.camera_z_near * params.camera_z_far / (params.camera_z_far + params.camera_z_near - depth * (params.camera_z_far - params.camera_z_near));
			depth = -depth;
		}

		z_from = z_to;
		z_to = z / w;

		if (depth > z_to) {
			
			vec4 test_normal_roughness = imageLoad(source_normal_roughness, test_pos);
			vec3 test_normal = test_normal_roughness.xyz * 2.0 - 1.0;
			test_normal = normalize(test_normal);
			test_normal.y = -test_normal.y; 

			if (dot(ray_dir, test_normal) < 0.001) {
				
				if (depth <= max(z_to, z_from) + params.depth_tolerance && -depth < params.camera_z_far * 0.95) {
					
					
					found = true;
				}
				break;
			}
		}

		steps_taken += 1.0;
		prev_pos = pos;
	}

	if (found) {
		float margin_blend = 1.0;
		vec2 final_pos = pos;

		vec2 margin = vec2((params.screen_size.x + params.screen_size.y) * 0.05); 
		if (any(bvec4(lessThan(pos, vec2(0.0, 0.0)), greaterThan(pos, params.screen_size)))) {
			
			imageStore(ssr_image, ssC, vec4(0.0));
			return;
		}

		{
			
			
			vec2 margin_grad = mix(params.screen_size - pos, pos, lessThan(pos, params.screen_size * 0.5));
			margin_blend = smoothstep(0.0, margin.x * margin.y, margin_grad.x * margin_grad.y);
			
		}

		
		float grad = (steps_taken + 1.0) / float(params.num_steps);
		float initial_fade = params.curve_fade_in == 0.0 ? 1.0 : pow(clamp(grad, 0.0, 1.0), params.curve_fade_in);
		float fade = pow(clamp(1.0 - grad, 0.0, 1.0), params.distance_fade) * initial_fade;

		
		
		if (fade > 0.999) {
			fade = 1.0;
		}

		
		
		float roughness_fade = smoothstep(0.4, 0.7, 1.0 - roughness);

		
		float metallic = texelFetch(source_metallic, ssC << 1, 0).w;

		
		
		float f0 = mix(0.04, 1.0, metallic);
		float m = clamp(1.0 - dot(normal, -view_dir), 0.0, 1.0);
		float m2 = m * m;
		m = m2 * m2 * m; 
		float fresnel_term = f0 + (1.0 - f0) * m; 

		
		
		
		
		
		vec4 final_color = vec4(imageLoad(source_diffuse, ivec2(final_pos - 0.5)).rgb * fresnel_term, fade * margin_blend * roughness_fade);

		imageStore(ssr_image, ssC, final_color);

#ifdef MODE_ROUGH

		
		float blur_radius = 0.0;

		if (roughness > 0.001) {
			float cone_angle = min(roughness, 0.999) * M_PI * 0.5;
			float cone_len = length(final_pos - line_begin);
			float op_len = 2.0 * tan(cone_angle) * cone_len; 
			{
				
				
				
				
				
				
				
				float a = op_len;
				float h = cone_len;
				float a2 = a * a;
				float fh2 = 4.0f * h * h;
				blur_radius = (a * (sqrt(a2 + fh2) - a)) / (4.0f * h);
			}
		}

		imageStore(blur_radius_image, ssC, vec4(blur_radius / 255.0)); 

#endif 

	} else {
#ifdef MODE_ROUGH
		imageStore(blur_radius_image, ssC, vec4(0.0));
#endif
		imageStore(ssr_image, ssC, vec4(0.0));
	}
}
)<!>"
		};
		setup(nullptr, nullptr, _compute_code, "ScreenSpaceReflectionShaderRD");
	}
};

#endif
