#pragma once
#include <glad/gl.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Shader{
    public:
        Shader(const std::string& vertexSrc, const std::string& fragmentSrc, std::string name);
        ~Shader();
        void activate() const;
        void informMat3(const char* loc, glm::mat3 matrix) const;
        void informMat4(const char* loc, glm::mat4 matrix) const;
        void informVec4(const char* loc, glm::vec4 vector) const;
        void informVec3(const char* loc, glm::vec3 vector) const;
        void informVec2(const char* loc, glm::vec2 vector) const;
        void informDVec2(const char* loc, glm::dvec2 vector) const;

        void informBool(const char* loc, bool info) const;
        void informDouble(const char* loc, double value) const;
        void informFloat(const char* loc, float value) const;
        void informInt(const char* loc, int value) const;

        void activateWireframeMode(); 
        void deactivateWireframeMode(); 

        std::string getName() { return name; };

    private:
        GLuint ID;
        std::string name;

        GLuint compileShader(const char* shader, GLenum type, const std::string& ID);
        std::string readShaderFile(const std::string& filePath);
};