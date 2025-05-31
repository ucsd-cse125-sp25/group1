#version 330 core

in vec4 fragPos;

uniform vec3 lightPos;
uniform float farClip;

void main() {
    gl_FragDepth = length(fragPos.xyz - lightPos) / farClip;
}
