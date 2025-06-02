#version 330 core

out vec4 fragColor;

void main() {
    vec2 center = gl_PointCoord - vec2(0.5);
    vec3 color = vec3(1.0, 1.0, 0.7);

    float distance = length(center);
    float alpha = smoothstep(0.5, 0.4, distance);

    if (alpha < 0.01) {
        discard;
    }

    fragColor = vec4(color, alpha);
}
