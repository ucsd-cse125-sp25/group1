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
uniform bool interactableShadowActive[MAX_LIGHTS];
uniform bool playerShadowActive[MAX_LIGHTS];

uniform samplerCube shadowDepthCubemap0;
uniform samplerCube shadowDepthCubemap1;
uniform samplerCube shadowDepthCubemap2;
uniform samplerCube shadowDepthCubemap3;
uniform samplerCube shadowDepthCubemap4;
uniform samplerCube shadowDepthCubemap5;

uniform float shadowFarClip;
uniform bool useFade;
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

    vec3 ambient = 0.3 * lightColor;
    vec3 diffuse = 0.5 * diff * lightColor;
    vec3 specularComponent = specular * spec * lightColor;

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

                    if (interactableShadowActive[0]) {
                        closestDepthInteractable =
                            texture(shadowDepthCubemap2, sampleDir).r * shadowFarClip;
                    }

                    if (playerShadowActive[0]) {
                        closestDepthPlayer =
                            texture(shadowDepthCubemap4, sampleDir).r * shadowFarClip;
                    }
                } else if (index == 1) {
                    closestDepthStatic = texture(shadowDepthCubemap1, sampleDir).r * shadowFarClip;

                    if (interactableShadowActive[1]) {
                        closestDepthInteractable =
                            texture(shadowDepthCubemap3, sampleDir).r * shadowFarClip;
                    }

                    if (playerShadowActive[1]) {
                        closestDepthPlayer =
                            texture(shadowDepthCubemap5, sampleDir).r * shadowFarClip;
                    }
                }

                if (currentDepth - bias > closestDepthStatic) {
                    shadowStatic += 1.0;
                }

                if (interactableShadowActive[index] &&
                    currentDepth - bias > closestDepthInteractable) {
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
    vec4 sampleColor;
    
    if (hasTexture) {
        sampleColor = texture(modelTexture, texCoords);
        // 2 Discard fragments whose alpha is essentially zero
        //if (sampleColor.a < 0.01) {discard;}
    } else {
        sampleColor = vec4(color, 1.0);
    }
    vec3 viewDir = normalize(viewPos - fragPos);
    //vec3 baseColor = hasTexture ? texture(modelTexture, texCoords).rgb : color;
    vec3 baseColor = sampleColor.rgb;
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

        if (useFade) {
            float dist = length(fragPos - pointLights[i].position);
            float fade = clamp(1.0 - dist / shadowFarClip, 0.0, 1.0);
            shadow = mix(0.5, 1.0, shadow * fade);
        } else {
            shadow = mix(0.65, 1.0, shadow);
        }

        result += lighting * baseColor * shadow;
    }
    fragColor = vec4(result, sampleColor.a);
    //fragColor = vec4(result, 1.0);
}
