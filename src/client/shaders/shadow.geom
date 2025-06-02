#version 330 core
layout(triangles) in;
layout(triangle_strip, max_vertices = 18) out;

uniform mat4 shadowMatrices[6];
uniform vec3 lightPos;

out vec4 fragPos;

void main() {
    for (int face = 0; face < 6; ++face) {
        for (int vertex = 0; vertex < 3; ++vertex) {
            vec4 worldPos = gl_in[vertex].gl_Position;

            fragPos = worldPos;
            gl_Position = shadowMatrices[face] * worldPos;
            gl_Layer = face;

            EmitVertex();
        }

        EndPrimitive();
    }
}
