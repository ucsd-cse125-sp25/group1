#version 330 core

in vec3 normal;
out vec4 fragColor;

void main() {
    vec3 N = normalize(normal);
    fragColor = vec4(0.5f * N + 0.5f , 1.0f);
}
