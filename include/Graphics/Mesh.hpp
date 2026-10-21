#pragma once
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <Graphics/Shader.hpp>

struct Vertex{
    glm::vec3 position;
    glm::vec2 texcoord;
    glm::vec3 normal;
};

class Mesh{
    public:
        Mesh(const std::string& ID, const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

        ~Mesh();

        void draw(const Shader& shader, GLenum mode) const;
        
        std::string getID() const { return ID; }
        glm::vec3 getOrigin() const { return origin; }
        glm::vec3 getMaxP() const { return maxP; }
        glm::vec3 getMinP() const { return minP; }
        glm::mat4 getModel() const { return model; }
        
    private:
        GLuint VAO, VBO, EBO;
        std::string ID;
        
        const std::vector<Vertex> vertices;
        const std::vector<unsigned int> indices;

        glm::vec3 origin;
        glm::vec3 maxP, minP;
        GLsizei count;

        glm::mat4 model;

        void initBuffers(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
        void calculatePoints(const std::vector<Vertex>& vertices);
};