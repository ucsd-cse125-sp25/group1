#include "shadowMap.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <array>
#include "config.hpp"
#include "scene.hpp"

ShadowMap::ShadowMap(glm::vec3 lightPos, int resolution)
    : lightPos(lightPos), depthCubemap(0), fbo(0), resolution(resolution),
      shader("../src/client/shaders/shadow.vert", "../src/client/shaders/shadow.frag",
             "../src/client/shaders/shadow.geom") {
    init();
}

ShadowMap::~ShadowMap() {
    glDeleteTextures(1, &depthCubemap);
    glDeleteFramebuffers(1, &fbo);
}

void ShadowMap::init() {
    glGenTextures(1, &depthCubemap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);

    // Set up the 6 faces
    for (unsigned int i = 0; i < 6; ++i) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, // face
                     0,                                  // mipmap level
                     GL_DEPTH_COMPONENT,                 // internal format
                     resolution,                         // width
                     resolution,                         // height
                     0,                                  // border
                     GL_DEPTH_COMPONENT,                 // input data format
                     GL_FLOAT,                           // data type
                     nullptr                             // data
        );
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubemap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ShadowMap::begin() {
    glm::mat4 projection = glm::perspective(glm::radians(90.0f), 1.0f, config::SHADOW_NEAR_CLIP,
                                            config::SHADOW_FAR_CLIP);

    std::array<glm::mat4, 6> transforms = {
        projection * glm::lookAt(lightPos, lightPos + glm::vec3(1, 0, 0), glm::vec3(0, -1, 0)),
        projection * glm::lookAt(lightPos, lightPos + glm::vec3(-1, 0, 0), glm::vec3(0, -1, 0)),
        projection * glm::lookAt(lightPos, lightPos + glm::vec3(0, 1, 0), glm::vec3(0, 0, 1)),
        projection * glm::lookAt(lightPos, lightPos + glm::vec3(0, -1, 0), glm::vec3(0, 0, -1)),
        projection * glm::lookAt(lightPos, lightPos + glm::vec3(0, 0, 1), glm::vec3(0, -1, 0)),
        projection * glm::lookAt(lightPos, lightPos + glm::vec3(0, 0, -1), glm::vec3(0, -1, 0))};

    glGetIntegerv(GL_VIEWPORT, prevViewport);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glViewport(0, 0, resolution, resolution);
    glClear(GL_DEPTH_BUFFER_BIT);

    shader.use();

    for (unsigned int i = 0; i < 6; ++i) {
        shader.setMat4("shadowMatrices[" + std::to_string(i) + "]", transforms[i]);
    }

    shader.setVec3("lightPos", lightPos);
    shader.setFloat("nearClip", config::SHADOW_NEAR_CLIP);
    shader.setFloat("farClip", config::SHADOW_FAR_CLIP);
}

void ShadowMap::end() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(prevViewport[0], prevViewport[1], prevViewport[2], prevViewport[3]);
}

GLuint getDummyCubemap() {
    static GLuint dummy = []() {
        GLuint tex;
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_CUBE_MAP, tex);

        for (GLuint i = 0; i < 6; ++i) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, 1, 1, 0,
                         GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        return tex;
    }();

    return dummy;
}
