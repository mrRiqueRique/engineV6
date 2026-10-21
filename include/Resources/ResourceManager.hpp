#pragma once
#include <Resources/MeshLoader.hpp>
#include <Resources/ShaderLoader.hpp>
// #include <Resources/TextureLoader.hpp>
#include <map>
#include <string>
#include <vector>

class ResourceManager{
    public:
        ResourceManager();
        ~ResourceManager();

        void loadMesh(const std::string& filePath);
        void loadMeshes(const std::string& folderPath);
        std::vector<Mesh*> getMesh(const std::string& ID);
        void removeMesh(const std::string& ID);
        void removeMeshes(const std::vector<std::string>& IDs);

        void loadShader(const std::string& shaderFolderPath);
        void loadShaders(const std::string& folderPath);
        Shader* getShader(const std::string& name);
        void removeShader(const std::string& name);
        void removeShaders(const std::vector<std::string>& names);

        // void loadTexture(const std::string& texturePath);
        // void loadTextures(const std::string& folderPath);
        // Texture* getTexture(const std::string& name);
        // void removeTexture(const std::string& name);
        // void removeTextures(const std::vector<std::string>& names);
    
        void printLoaded();

    private:
        std::map<std::string, std::vector<Mesh*>> meshes;
        std::map<std::string, Shader*> shaders;
        // std::map<std::string, Texture*> textures;
};      