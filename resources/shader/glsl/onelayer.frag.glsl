#version 450

#include "common.glsl"


layout (location = 0) in vec2 outTexC;

layout(location = 0) out vec4 outColor;

void main()
{
    outColor = texture(first, outTexC);
}
