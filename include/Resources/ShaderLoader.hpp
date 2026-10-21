#pragma once
#include <Graphics/Shader.hpp>
#include <string>

class ShaderLoader{
    public:
        static Shader* loadShader(const std::string& shaderFolderPath){
            std::string vertexSource = shaderFolderPath + "/shader.vert";
            std::string fragmentSource = shaderFolderPath + "/shader.frag";
            
            std::string name = std::filesystem::path(shaderFolderPath).filename().string();

            return new Shader(vertexSource, fragmentSource, name);
        };
};