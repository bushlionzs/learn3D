/* Copyright (c) 2018-2023, Sascha Willems
 *
 * SPDX-License-Identifier: MIT
 *
 */

#version 450

layout (location = 0) in vec3 position;

layout(push_constant) uniform PushConsts {
	layout (offset = 0) mat4 mvp;
} pushConsts;

layout (location = 0) out vec3 outUVW;

void main() 
{
	outUVW = position;
	gl_Position = pushConsts.mvp * vec4(position.xyz, 1.0);
	gl_Position.y = -gl_Position.y;
}
