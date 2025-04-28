#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;

out vec3 position;
out vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    position = vec3(model * vec4(aPosition, 1.0));
    normal = mat3(transpose(inverse(model))) * aNormal;
    gl_Position = projection * view * vec4(position, 1.0);
}
