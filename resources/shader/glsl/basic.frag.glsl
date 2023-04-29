#version 450
#extension GL_ARB_separate_shader_objects : enable

#include "common.glsl"

layout (location = 0) in vec4 outPosH;
layout (location = 1) in vec4 outShadowPosH;
layout (location = 2) in vec3 outPosW;
layout (location = 3) in vec3 outNormalW;
layout (location = 4) in vec2 outTexC;

layout(location = 0) out vec4 outColor;

void main() {
    outColor = texture(gTextureArray[0], outTexC);
}