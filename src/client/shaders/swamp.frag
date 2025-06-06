#version 330 core

#define MAX_LIGHTS 2
#define WATER_OPAQUE 0.7

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
uniform bool playerShadowActive[MAX_LIGHTS];

uniform samplerCube shadowDepthCubemap0;
uniform samplerCube shadowDepthCubemap1;
uniform samplerCube shadowDepthCubemap2;
uniform samplerCube shadowDepthCubemap3;
uniform samplerCube shadowDepthCubemap4;
uniform samplerCube shadowDepthCubemap5;

uniform float shadowFarClip;
uniform vec3 viewPos;

uniform vec3 color;
uniform vec3 specular;
uniform float shininess;
uniform bool hasTexture;
uniform sampler2D modelTexture;

uniform bool isWater;

uniform bool useFog;
uniform vec3 fogColor;
uniform float fogStart;
uniform float fogEnd;

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
    float shadowStatic = 0.0;
    float shadowInteractable = 0.0;
    float shadowPlayer = 0.0;
    float samples = 2.0;
    float offset = 0.05 * (1.0 - currentDepth / shadowFarClip);

    vec3 fragDir = normalize(fragToLight);
    vec3 N = normalize(normal);
    float bias = 0.1 + 0.01 * (1.0 - dot(fragDir, N));

    for (float x = -0.5; x <= 0.5; x++) {
        for (float y = -0.5; y <= 0.5; y++) {
            for (float z = -0.5; z <= 0.5; z++) {
                vec3 sampleDir = normalize(fragToLight + vec3(x, y, z) * offset);
                float closestDepthStatic = 0.0;
                float closestDepthInteractable = 0.0;
                float closestDepthPlayer = 0.0;

                if (index == 0) {
                    closestDepthStatic = texture(shadowDepthCubemap0, sampleDir).r * shadowFarClip;
                    closestDepthInteractable =
                        texture(shadowDepthCubemap2, sampleDir).r * shadowFarClip;

                    if (playerShadowActive[0]) {
                        closestDepthPlayer =
                            texture(shadowDepthCubemap4, sampleDir).r * shadowFarClip;
                    }
                } else if (index == 1) {
                    closestDepthStatic = texture(shadowDepthCubemap1, sampleDir).r * shadowFarClip;
                    closestDepthInteractable =
                        texture(shadowDepthCubemap3, sampleDir).r * shadowFarClip;

                    if (playerShadowActive[1]) {
                        closestDepthPlayer =
                            texture(shadowDepthCubemap5, sampleDir).r * shadowFarClip;
                    }
                }

                if (currentDepth - bias > closestDepthStatic) {
                    shadowStatic += 1.0;
                }

                if (currentDepth - bias > closestDepthInteractable) {
                    shadowInteractable += 1.0;
                }

                if (playerShadowActive[index] && currentDepth - bias > closestDepthPlayer) {
                    shadowPlayer += 1.0;
                }
            }
        }
    }

    shadowStatic /= (samples * samples * samples);
    shadowInteractable /= (samples * samples * samples);
    shadowPlayer /= (samples * samples * samples);

    return 1.0 - max(max(shadowStatic, shadowInteractable), shadowPlayer);
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
        float distance = length(fragPos - pointLights[i].position);
        float fade = clamp(1.0 - distance / shadowFarClip, 0.0, 1.0);
        shadow = mix(0.5, 1.0, shadow * fade);

        result += lighting * baseColor * shadow;
    }

    if (isWater) {
        fragColor = vec4(result, WATER_OPAQUE);
    } else {
        fragColor = vec4(result, 1.0);
    }

    if (useFog) {
        float distance = length(viewPos - fragPos);
        float fogFactor = clamp((fogEnd - distance) / (fogEnd - fogStart), 0.0, 1.0);
        fragColor = mix(vec4(fogColor, 1.0), fragColor, fogFactor);
    }
}

// Use this if the current version is lagging a lot
// float getShadowFactor(vec3 fragPosWorld, int index) {
//     vec3 fragToLight = fragPosWorld - pointLights[index].position;
//     float currentDepth = length(fragToLight);

//     float shadowStatic = 0.0;
//     float shadowInteractable = 0.0;

//     float offset = 0.05 * (1.0 - currentDepth / shadowFarClip); // optional soft bias
//     vec3 fragDir = normalize(fragToLight);
//     vec3 N = normalize(normal);
//     float bias = 0.1 + 0.01 * (1.0 - dot(fragDir, N));

//     float closestDepthStatic = 0.0;
//     float closestDepthInteractable = 0.0;

//     if (index == 0) {
//         closestDepthStatic = texture(shadowDepthCubemap0, fragDir).r * shadowFarClip;
//         closestDepthInteractable = texture(shadowDepthCubemap2, fragDir).r * shadowFarClip;
//     } else if (index == 1) {
//         closestDepthStatic = texture(shadowDepthCubemap1, fragDir).r * shadowFarClip;
//         closestDepthInteractable = texture(shadowDepthCubemap3, fragDir).r * shadowFarClip;
//     }

//     if (currentDepth - bias > closestDepthStatic) {
//         shadowStatic = 1.0;
//     }

//     if (currentDepth - bias > closestDepthInteractable) {
//         shadowInteractable = 1.0;
//     }

//     return 1.0 - max(shadowStatic, shadowInteractable);
// }
