#version 330 core

in vec3 fragPos;
in vec3 normal;
in vec2 texCoords;

out vec4 fragColor;

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

    vec3 ambient = 0.5 * lightColor;
    vec3 diffuse = 0.5 * diff * lightColor;
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
    vec3 dirLightColor = vec3(1.0) * 0.6;

    result += computeLighting(dirLightDir1, dirLightColor, N, viewDir) * baseColor;
    result += computeLighting(dirLightDir2, dirLightColor, N, viewDir) * baseColor;

    fragColor = vec4(result, 1.0);
}
