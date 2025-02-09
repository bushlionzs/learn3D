/* WARNING, THIS FILE WAS GENERATED, DO NOT EDIT */
#ifndef MOTION_VECTORS_GLSL_GEN_H_RD
#define MOTION_VECTORS_GLSL_GEN_H_RD

#include "servers/rendering/renderer_rd/shader_rd.h"

class MotionVectorsShaderRD : public ShaderRD {

public:

	MotionVectorsShaderRD() {

		static const char _vertex_code[] = {
R"<!>(
#version 450

#VERSION_DEFINES

layout(location = 0) out vec2 uv_interp;

void main() {
	vec2 base_arr[3] = vec2[](vec2(-1.0, -1.0), vec2(-1.0, 3.0), vec2(3.0, -1.0));
	gl_Position = vec4(base_arr[gl_VertexIndex], 0.0, 1.0);
	uv_interp = clamp(gl_Position.xy, vec2(0.0, 0.0), vec2(1.0, 1.0)) * 2.0; 
}

)<!>"
		};
		static const char _fragment_code[] = {
R"<!>(
#version 450

#VERSION_DEFINES

vec2 derive_motion_vector(vec2 uv, float depth, mat4 reprojection_matrix) {
	vec4 previous_pos_ndc = reprojection_matrix * vec4(uv * 2.0f - 1.0f, depth * 2.0f - 1.0f, 1.0f);
	return 0.5f + (previous_pos_ndc.xy / previous_pos_ndc.w) * 0.5f - uv;
}

#define FFX_FSR2_OPTION_GODOT_DERIVE_INVALID_MOTION_VECTORS_FUNCTION(i, j, k) derive_motion_vector(i, j, k)

layout(location = 0) in vec2 uv_interp;

layout(set = 0, binding = 0) uniform sampler2D source_velocity;
layout(set = 0, binding = 1) uniform sampler2D source_depth;

layout(location = 0) out vec4 frag_color;

layout(push_constant, std430) uniform Params {
	highp mat4 reprojection_matrix;
	vec2 resolution;
	bool force_derive_from_depth;
}
params;



float line_segment(in vec2 p, in vec2 a, in vec2 b) {
	vec2 aspect = vec2(params.resolution.x / params.resolution.y, 1.0f);
	vec2 ba = (b - a) * aspect;
	vec2 pa = (p - a) * aspect;
	float h = clamp(dot(pa, ba) / dot(ba, ba), 0.0f, 1.0f);
	return length(pa - h * ba) * (params.resolution.y / 2.0f);
}

void main() {
	
	float cell_size = 32.0f;
	float circle_radius = 2.0f;
	vec3 nan_color = vec3(1.0f, 0.0f, 0.0f);
	vec3 active_color = vec3(1.0f, 0.8f, 0.1f);
	vec3 inactive_color = vec3(0.5f, 0.5f, 0.5f);
	vec2 pos_pixel = uv_interp * params.resolution;
	vec2 cell_pos_pixel = floor(pos_pixel / cell_size) * cell_size + (cell_size * 0.5f);
	vec2 cell_pos_uv = cell_pos_pixel / params.resolution;
	vec2 cell_pos_velocity = textureLod(source_velocity, cell_pos_uv, 0.0f).xy;
	bool derive_velocity = params.force_derive_from_depth || all(lessThanEqual(cell_pos_velocity, vec2(-1.0f, -1.0f)));
	if (derive_velocity) {
		float depth = textureLod(source_depth, cell_pos_uv, 0.0f).x;
		cell_pos_velocity = derive_motion_vector(cell_pos_uv, depth, params.reprojection_matrix);
	}

	vec2 cell_pos_previous_uv = cell_pos_uv + cell_pos_velocity;

	
	float epsilon = 1e-6f;
	vec2 cell_pos_delta_uv = cell_pos_uv - cell_pos_previous_uv;
	bool motion_active = length(cell_pos_delta_uv) > epsilon;
	vec3 color;
	if (any(isnan(cell_pos_delta_uv))) {
		color = nan_color;
	} else if (motion_active) {
		color = active_color;
	} else {
		color = inactive_color;
	}

	float alpha;
	if (length(cell_pos_pixel - pos_pixel) <= circle_radius) {
		
		alpha = 1.0f;
	} else if (motion_active) {
		
		alpha = 1.0f - line_segment(uv_interp, cell_pos_uv, cell_pos_previous_uv);
	} else {
		
		alpha = 0.0f;
	}

	if (derive_velocity) {
		color = vec3(1.0f, 1.0f, 1.0f) - color;
		alpha *= 0.5f;
	}

	frag_color = vec4(color, alpha);
}
)<!>"
		};
		setup(_vertex_code, _fragment_code, nullptr, "MotionVectorsShaderRD");
	}
};

#endif
