#include "fireflyRenderer.hpp"

FireflyRenderer::FireflyRenderer()
    : shader("../src/client/shaders/firefly.vert", "../src/client/shaders/firefly.frag") {
    setup();
}

FireflyRenderer::~FireflyRenderer() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

void FireflyRenderer::setup() {
    GLfloat fireflyPoint[3] = {0.0f, 0.0f, 0.0f};

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(fireflyPoint), fireflyPoint, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void FireflyRenderer::draw(const std::vector<Firefly>& fireflies, const glm::mat4& view,
                           const glm::mat4& projection) {
    shader.use();
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);

    glBindVertexArray(vao);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    for (const auto& firefly : fireflies) {
        shader.setVec3("offset", firefly.position);
        shader.setFloat("size", firefly.size);

        glDrawArrays(GL_POINTS, 0, 1);
    }

    glDisable(GL_BLEND);
    glBindVertexArray(0);
}
