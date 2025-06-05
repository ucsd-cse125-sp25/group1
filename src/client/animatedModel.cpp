#include "animatedModel.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <assimp/postprocess.h>
#include <filesystem>
#include <iostream>
#include <stb_image.h>

AnimatedModel::AnimatedModel(const std::string& path) {
    directory = path.substr(0, path.find_last_of('/'));
    loadModel(path);
}

void AnimatedModel::draw(Shader& shader) {
    for (const auto& mesh : subMeshes) {
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

        mesh.draw();
    }
}

int AnimatedModel::getBoneID(const std::string& name) const {
    return bones.contains(name) ? bones.at(name) : -1;
}

void AnimatedModel::loadModel(const std::string& path) {
    scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices |
                                        aiProcess_LimitBoneWeights | aiProcess_GenSmoothNormals |
                                        aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "Error: " << importer.GetErrorString() << "\n";
        return;
    }

    processNode(scene->mRootNode);
}

void AnimatedModel::processNode(aiNode* node) {
    for (unsigned int m = 0; m < node->mNumMeshes; ++m) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[m]];

        AnimatedSubMesh subMesh = processMesh(mesh);
        subMesh.setup();
        subMeshes.push_back(subMesh);
    }

    for (unsigned int c = 0; c < node->mNumChildren; ++c) {
        processNode(node->mChildren[c]);
    }
}

AnimatedSubMesh AnimatedModel::processMesh(aiMesh* mesh) {
    AnimatedSubMesh subMesh;

    std::vector<SkinnedVertexCPU> tempVertices;
    tempVertices.reserve(mesh->mNumVertices);

    for (unsigned int v = 0; v < mesh->mNumVertices; ++v) {
        SkinnedVertexCPU vertex;

        vertex.position =
            glm::vec3(mesh->mVertices[v].x, mesh->mVertices[v].y, mesh->mVertices[v].z);

        vertex.normal = glm::vec3(mesh->mNormals[v].x, mesh->mNormals[v].y, mesh->mNormals[v].z);

        if (mesh->HasTextureCoords(0)) {
            vertex.texCoords =
                glm::vec2(mesh->mTextureCoords[0][v].x, mesh->mTextureCoords[0][v].y);
        } else {
            vertex.texCoords = glm::vec2(0.0f);
        }

        tempVertices.push_back(vertex);
    }

    for (unsigned int b = 0; b < mesh->mNumBones; ++b) {
        aiBone* bone = mesh->mBones[b];
        std::string boneName = bone->mName.C_Str();
        int boneID;

        if (!bones.contains(boneName)) {
            boneID = boneCount++;
            bones[boneName] = boneID;

            glm::mat4 offsetMatrix = glm::transpose(glm::make_mat4(&bone->mOffsetMatrix.a1));
            boneOffsets.push_back(offsetMatrix);
        } else {
            boneID = bones[boneName];
        }

        for (unsigned int w = 0; w < bone->mNumWeights; ++w) {
            unsigned int vertexID = bone->mWeights[w].mVertexId;
            float weight = bone->mWeights[w].mWeight;

            tempVertices[vertexID].addBoneData(boneID, weight);
        }
    }

    subMesh.vertices.reserve(tempVertices.size());

    for (const auto& vertex : tempVertices) {
        subMesh.vertices.push_back(static_cast<SkinnedVertex>(vertex));
    }

    for (unsigned int f = 0; f < mesh->mNumFaces; ++f) {
        const aiFace& face = mesh->mFaces[f];

        for (unsigned int i = 0; i < face.mNumIndices; ++i) {
            subMesh.indices.push_back(face.mIndices[i]);
        }
    }

    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    glm::vec3 color = glm::vec3(0.0f);
    glm::vec3 specular = glm::vec3(0.0f);
    float shininess = 16.0f;

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

    aiString textureImage;

    // Load texture if available
    if (material->GetTexture(aiTextureType_DIFFUSE, 0, &textureImage) == AI_SUCCESS) {
        std::string fileName = std::filesystem::path(textureImage.C_Str()).filename().string();
        std::string texturePath = directory + "/" + fileName;

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
            std::cerr << "Error: Failed to load texture: " << textureImage.C_Str() << "\n";
        }

        stbi_image_free(data);

        subMesh.textureId = textureId;
        subMesh.hasTexture = true;
    } else {
        subMesh.hasTexture = false;
    }

    return subMesh;
}
