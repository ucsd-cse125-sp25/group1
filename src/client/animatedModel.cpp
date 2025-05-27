#include "animatedModel.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <assimp/postprocess.h>
#include <iostream>

AnimatedModel::AnimatedModel(const std::string& path) {
    loadModel(path);
}

void AnimatedModel::draw() {
    for (const auto& mesh : subMeshes) {
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

    return subMesh;
}
