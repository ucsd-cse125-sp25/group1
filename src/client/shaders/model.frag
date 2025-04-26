#version 330 core

in vec3 position;
in vec3 normal;
in vec2 texCoords;

out vec4 fragColor;

uniform vec3 color;
uniform bool hasTexture;
uniform sampler2D modelTexture;

void main() {
    vec3 lightDirection = normalize(vec3(0.0, -0.5, -1.0));
    vec3 lightColor = vec3(1.0);

    float diff = max(dot(normalize(normal), -lightDirection), 0.0);
    vec3 diffuse = 0.5 * diff * lightColor;
    vec3 ambient = 0.5 * lightColor;

    vec3 baseColor = hasTexture ? texture(modelTexture, texCoords).rgb : color;

    vec3 result = (ambient + diffuse) * baseColor;

    fragColor = vec4(result, 1.0f);
}
