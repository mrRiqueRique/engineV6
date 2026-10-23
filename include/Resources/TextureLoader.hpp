#pragma once
#include <Graphics/Texture.hpp>
#include <filesystem>

class TextureLoader{
    public:
        static Texture* loadTexture(const std::string& texturePath){
        
        std::string name = std::filesystem::path(texturePath).stem().string();
        return new Texture(texturePath, name);
    };     
};