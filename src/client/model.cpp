#include "model.hpp"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <iostream>
#include <stb_image.h>

Model::Model(const std::string& path) {
    loadModel(path);
}

Model::~Model() {
    for (auto& mesh : subMeshes) {
        glDeleteVertexArrays(1, &mesh.vao);
        glDeleteBuffers(1, &mesh.vbo);
        glDeleteBuffers(1, &mesh.ebo);
    }
}

void Model::draw(Shader& shader, bool boundingBoxMode) {
    for (const auto& mesh : subMeshes) {
        if (mesh.isBoundingBox && !boundingBoxMode)
            continue;
        if (!mesh.isBoundingBox && boundingBoxMode)
            continue;

        if (mesh.hasTexture) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, mesh.textureId);

            shader.setBool("hasTexture", true);
            shader.setInt("modelTexture", 0);
        } else {
            shader.setBool("hasTexture", false);
            shader.setVec3("color", mesh.color);
        }

        shader.setVec3("specular", mesh.specular);
        shader.setFloat("shininess", mesh.shininess);

        shader.setBool("isWater", mesh.isWater);

        if (mesh.isWater) {
            glDepthMask(GL_FALSE);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }

        mesh.draw();

        if (mesh.isWater) {
            glDepthMask(GL_TRUE);
            glDisable(GL_BLEND);
        }
    }
}

void Model::loadModel(const std::string& path) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs |
                                                       aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "Error: " << importer.GetErrorString() << "\n";
        return;
    }

    for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
        aiMesh* mesh = scene->mMeshes[i];

        std::vector<GLfloat> vertices;
        std::vector<GLuint> indices;

        for (unsigned int v = 0; v < mesh->mNumVertices; ++v) {
            vertices.push_back(mesh->mVertices[v].x);
            vertices.push_back(mesh->mVertices[v].y);
            vertices.push_back(mesh->mVertices[v].z);

            vertices.push_back(mesh->mNormals[v].x);
            vertices.push_back(mesh->mNormals[v].y);
            vertices.push_back(mesh->mNormals[v].z);

            if (mesh->HasTextureCoords(0)) {
                vertices.push_back(mesh->mTextureCoords[0][v].x);
                vertices.push_back(mesh->mTextureCoords[0][v].y);
            } else {
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
            }
        }

        for (unsigned int f = 0; f < mesh->mNumFaces; ++f) {
            aiFace face = mesh->mFaces[f];

            for (unsigned int j = 0; j < face.mNumIndices; ++j) {
                indices.push_back(face.mIndices[j]);
            }
        }

        SubMesh subMesh;

        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        glm::vec3 color = glm::vec3(0.0f);
        glm::vec3 specular = glm::vec3(0.0f);
        float shininess = 32.0f;

        aiColor3D kd(0.0f);
        aiColor3D ks(0.0f);

        // Get diffuse color if available
        if (material->Get(AI_MATKEY_COLOR_DIFFUSE, kd) == AI_SUCCESS) {
            color = glm::vec3(kd.r, kd.g, kd.b);
        }

        // Get specular reflectivy if available
        if (material->Get(AI_MATKEY_COLOR_SPECULAR, ks) == AI_SUCCESS) {
            specular = glm::vec3(ks.r, ks.g, ks.b);
        }

        // Get shininess if available
        material->Get(AI_MATKEY_SHININESS, shininess);

        subMesh.color = color;
        subMesh.specular = specular;
        subMesh.shininess = shininess;

        std::string directory = path.substr(0, path.find_last_of('/'));
        aiString textureImage;

        // Load texture if available
        if (material->GetTexture(aiTextureType_DIFFUSE, 0, &textureImage) == AI_SUCCESS) {
            std::string texturePath = directory + "/" + std::string(textureImage.C_Str());

            GLuint textureId;
            glGenTextures(1, &textureId);
            glBindTexture(GL_TEXTURE_2D, textureId);

            int width, height, channels;
            unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &channels, 0);

            if (data) {
                GLenum format = (channels == 3) ? GL_RGB : GL_RGBA;
                glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE,
                             data);
                glGenerateMipmap(GL_TEXTURE_2D);
            } else {
                std::cerr << "Error: Failed to load texture: " << texturePath << "\n";
            }

            stbi_image_free(data);

            subMesh.textureId = textureId;
            subMesh.hasTexture = true;
        } else {
            subMesh.hasTexture = false;
        }

        aiString name;
        material->Get(AI_MATKEY_NAME, name);

        // Check if the mesh is water
        if (std::string(name.C_Str()) == "MAT_swamp_water") {
            subMesh.isWater = true;
        }

        // Check if the mesh name starts with "UCX_" (used for collision boxes)
        std::string meshName = mesh->mName.C_Str();
        bool isBoundingBox = meshName.rfind("UCX_", 0) == 0;
        subMesh.isBoundingBox = isBoundingBox;

        setupSubMesh(subMesh, vertices, indices);
        subMeshes.push_back(subMesh);
    }
}

void Model::setupSubMesh(SubMesh& mesh, const std::vector<GLfloat>& vertices,
                         const std::vector<GLuint>& indices) {
    mesh.indexCount = indices.size();

    glGenVertexArrays(1, &mesh.vao);
    glGenBuffers(1, &mesh.vbo);
    glGenBuffers(1, &mesh.ebo);

    glBindVertexArray(mesh.vao);

    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(),
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(),
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
                          (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
                          (void*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}
