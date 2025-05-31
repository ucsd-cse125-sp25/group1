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

uniform samplerCube shadowDepthCubemap0;
uniform samplerCube shadowDepthCubemap1;

uniform float shadowFarClip;
uniform vec3 viewPos;

uniform vec3 color;
uniform vec3 specular;
uniform float shininess;
uniform bool hasTexture;
uniform sampler2D modelTexture;

vec3 computeLighting(vec3 lightDir, vec3 lightColor, vec3 normal, vec3 viewDir) {
    vec3 halfwayDir = normalize(lightDir + viewDir);

    float diff = max(dot(normal, lightDir), 0.0);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), shininess);

    vec3 ambient = 0.4 * lightColor;
    vec3 diffuse = 0.5 * diff * lightColor;
    vec3 specularComponent = 0.1 * specular * spec * lightColor;

    return ambient + diffuse + specularComponent;
}

float getShadowFactor(vec3 fragPosWorld, int index) {
    vec3 fragToLight = fragPosWorld - pointLights[index].position;
    float currentDepth = length(fragToLight);

    // PCF parameters
    float shadow = 0.0;
    float samples = 3.0;
    float offset = 0.05 * (1.0 - currentDepth / shadowFarClip);

    vec3 fragDir = normalize(fragToLight);
    vec3 N = normalize(normal);
    float bias = 0.1 + 0.01 * (1.0 - dot(fragDir, N));

    for (float x = -1.0; x <= 1.0; x++) {
        for (float y = -1.0; y <= 1.0; y++) {
            for (float z = -1.0; z <= 1.0; z++) {
                vec3 sampleDir = normalize(fragToLight + vec3(x, y, z) * offset);
                float closestDepth = 0.0;

                if (index == 0) {
                    closestDepth = texture(shadowDepthCubemap0, sampleDir).r * shadowFarClip;
                } else if (index == 1) {
                    closestDepth = texture(shadowDepthCubemap1, sampleDir).r * shadowFarClip;
                }

                if (currentDepth - bias > closestDepth) {
                    shadow += 1.0;
                }
            }
        }
    }

    shadow /= (samples * samples * samples);
    return 1.0 - shadow;
}

void main() {
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 baseColor = hasTexture ? texture(modelTexture, texCoords).rgb : color;

    vec3 result = vec3(0.0);

    // Directional lights
    vec3 dirLightDir1 = normalize(-vec3(0.0, -0.5, -1.0));
    vec3 dirLightDir2 = normalize(-vec3(0.0, -0.5, 1.0));
    vec3 dirLightColor = vec3(1.0) * 0.5;

    result += computeLighting(dirLightDir1, dirLightColor, normal, viewDir) * baseColor;
    result += computeLighting(dirLightDir2, dirLightColor, normal, viewDir) * baseColor;

    // Point lights with shadowing
    for (int i = 0; i < numLights; ++i) {
        vec3 lightDir = normalize(pointLights[i].position - fragPos);
        vec3 lightColor = pointLights[i].color;

        float shadow = getShadowFactor(fragPos, i);
        vec3 lighting = computeLighting(lightDir, lightColor, normal, viewDir);

        // Distance-based fade
        float dist = length(fragPos - pointLights[i].position);
        float fade = clamp(1.0 - dist / shadowFarClip, 0.0, 1.0);
        shadow = mix(0.5, 1.0, shadow * fade);

        result += lighting * baseColor * shadow;
    }

    fragColor = vec4(result, 1.0);
}
