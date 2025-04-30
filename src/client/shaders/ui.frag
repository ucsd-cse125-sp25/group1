#version 410 core

layout(location=0) in vec3 inColor;
layout(location=0) out vec4 outColor;

void main()
{
    outColor = vec4(1.0, 0.85, 0.94, 1.0);  // Green
    outColor.rgb = inColor;
}