#version 330 core

in vec3 position;
in vec3 normal;

out vec4 fragColor;

uniform vec3 color;

void main() {
    vec3 lightDirection = normalize(vec3(0.0, -0.5, -1.0));
    vec3 lightColor = vec3(1.0);

    float diff = max(dot(normalize(normal), -lightDirection), 0.0);
    vec3 diffuse = 0.5 * diff * lightColor;
    vec3 ambient = 0.5 * lightColor;
    
    vec3 result = (ambient + diffuse) * color;

    fragColor = vec4(result, 1.0f);
}
