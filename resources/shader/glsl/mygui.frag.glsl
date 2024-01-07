#version 450

#include "common.glsl"

layout (location = 0) in vec4 inColor;
layout (location = 1) in vec2 inTexC;

layout(location = 0) out vec4 outColor;

void main() {
    outColor = texture(gTextureArray[0], inTexC)* inColor;
}