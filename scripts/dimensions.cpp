#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/glm.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <json.hpp>
#include <cfloat>   // For FLT_MAX

namespace fs = std::filesystem;
using json = nlohmann::json;

int main() {
    json j;
    Assimp::Importer importer;

    // Iterate over the Blender models
    for (const auto& entry : fs::directory_iterator("../src/client/models")) {

        if (entry.path().extension() == ".obj") {

            // EXPLICIT conversion from std::filesystem::path to const char*
            const std::string filepath = entry.path().string();
            const aiScene* scene = importer.ReadFile(
                filepath.c_str(),
                aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace
            );

            if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
                std::cerr << "Error: " << importer.GetErrorString() << "\n";
                return -1;
            }

            // Iterate over the meshes of the Blender file
            for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
                aiMesh* mesh = scene->mMeshes[i];

                // Check if the mesh name starts with "UCX_" (used for collision boxes)
                std::string meshName = mesh->mName.C_Str();
                bool isBoundingBox = meshName.rfind("UCX_", 0) == 0;
                if (!isBoundingBox) continue;

                // Get min and max points
                float minX = FLT_MAX, minY = FLT_MAX, minZ = FLT_MAX;
                float maxX = -FLT_MAX, maxY = -FLT_MAX, maxZ = -FLT_MAX;
                for (unsigned int v = 0; v < mesh->mNumVertices; ++v) {
                    minX = std::min(minX, mesh->mVertices[v].x);
                    minY = std::min(minY, mesh->mVertices[v].y);
                    minZ = std::min(minZ, mesh->mVertices[v].z);

                    maxX = std::max(maxX, mesh->mVertices[v].x);
                    maxY = std::max(maxY, mesh->mVertices[v].y);
                    maxZ = std::max(maxZ, mesh->mVertices[v].z);
                }

                // Store min and max points into JSON format
                j[meshName.substr(4)]["min"] = { minX, minY, minZ };
                j[meshName.substr(4)]["max"] = { maxX, maxY, maxZ };
            }

            // Output to JSON file
            std::ofstream outFile("../src/shared/dimensions.json");
            outFile << j.dump(4);
            outFile.close();
        }
    }

    return 0;
}
