#pragma once
#include <glad/gl.h>
#include <Utility/Movable3D.hpp>
#include <string>
#include <vector>
#include <Graphics/Shader.hpp>

struct Vertex{
    glm::vec3 position;
    glm::vec2 texcoord;
    glm::vec3 normal;
};

class Mesh : public Movable3D {
    public:
        Mesh(
            const std::string& ID,
            const std::vector<Vertex>& vertices,
            const std::vector<unsigned int>& indices
        );

        Mesh(
            const std::string& ID,
            const std::vector<Vertex>& vertices,
            const std::vector<unsigned int>& indices,
            glm::mat4 model
        );


        ~Mesh();

        void draw(const Shader& shader, GLenum mode) const;
        
        std::string getID() const { return ID; }
        glm::vec3 getMaxP() const { return maxP; }
        glm::vec3 getMinP() const { return minP; }
        const std::vector<Vertex> getVertices() const { return vertices; }
        const std::vector<unsigned int> getIndices() const { return indices; }

        bool isCopy;
        void setIsCopy() { isCopy = !isCopy; }

    private:
        GLuint VAO, VBO, EBO;
        std::string ID;
        
        const std::vector<Vertex> vertices;
        const std::vector<unsigned int> indices;

        glm::vec3 maxP, minP;
        GLsizei count;

        glm::vec3 calculateScale();
        glm::vec3 calculatePoints(const std::vector<Vertex>& vertices);

        void initBuffers(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
};