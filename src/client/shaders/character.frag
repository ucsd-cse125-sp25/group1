#version 330 core

#define MAX_LIGHTS 2

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

vec3 computeLighting(vec3 lightDir, vec3 lightColor, vec3 normal, vec3 viewDir) {
    vec3 halfwayDir = normalize(lightDir + viewDir);

    float diff = max(dot(normal, lightDir), 0.0);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), max(shininess, 1));

    vec3 ambient = 0.3 * lightColor;
    vec3 diffuse = 0.4 * diff * lightColor;
    vec3 specularComponent = 0.1 * specular * spec * lightColor;

    return ambient + diffuse + specularComponent;
}

void main() {
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 baseColor = hasTexture ? texture(modelTexture, texCoords).rgb : color;
    vec3 N = normalize(normal);

    vec3 result = vec3(0.0);

    vec3 dirLightDir1 = normalize(-vec3(0.0, -0.5, -1.0));
    vec3 dirLightDir2 = normalize(-vec3(0.0, -0.5, 1.0));
    vec3 dirLightColor = vec3(1.0) * 0.3;

    result += computeLighting(dirLightDir1, dirLightColor, N, viewDir) * baseColor;
    result += computeLighting(dirLightDir2, dirLightColor, N, viewDir) * baseColor;

    // Point lights
    for (int i = 0; i < numLights; ++i) {
        vec3 lightDir = normalize(pointLights[i].position - fragPos);
        vec3 lightColor = pointLights[i].color;

        vec3 lighting = computeLighting(lightDir, lightColor, normal, viewDir);
        result += lighting * baseColor;
    }

    fragColor = vec4(result, 1.0);
}
