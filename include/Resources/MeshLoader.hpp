#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <Graphics/Mesh.hpp>
#include <filesystem>

class MeshLoader{
    public:
        static std::vector<Mesh*> loadMesh(std::string filePath);
    private:
        static void processNode(aiNode *node, const aiScene *scene, std::vector<Mesh*> &meshes, unsigned int nodeIndex, std::string filePath);
        static Mesh* processMesh(aiMesh *mesh, const aiScene *scene, unsigned int meshIndex, std::string filePath);
};