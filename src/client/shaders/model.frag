#version 330 core
#define MAX_LIGHTS 8

struct PointLight {
    vec3 position;
    vec3 color;
};

in vec3 fragPos;
in vec3 normal;
in vec2 texCoords;

out vec4 fragColor;

uniform int numLights;
uniform PointLight pointLights[MAX_LIGHTS];

uniform vec3 viewPos;

uniform vec3 color;
uniform vec3 specular;
uniform float shininess;
uniform bool hasTexture;
uniform sampler2D modelTexture;

void main() {
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 baseColor = hasTexture ? texture(modelTexture, texCoords).rgb : color;

    vec3 ambient = vec3(0.0);
    vec3 diffuse = vec3(0.0);
    vec3 specularComponent = vec3(0.0);

    // Process all point lights
    for (int i = 0; i < numLights; ++i) {
        vec3 lightDir = normalize(pointLights[i].position - fragPos);
        vec3 halfwayDir = normalize(lightDir + viewDir);
        vec3 lightColor = pointLights[i].color;

        float diff = max(dot(normal, lightDir), 0.0);
        float spec = pow(max(dot(normal, halfwayDir), 0.0), shininess);

        ambient = 0.4 * lightColor;
        diffuse = 0.5 * diff * lightColor;
        specularComponent = specular * spec * lightColor;
    }

    vec3 result = (ambient + diffuse + specularComponent) * baseColor;

    fragColor = vec4(result, 1.0);
}
