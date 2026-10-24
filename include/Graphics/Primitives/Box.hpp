#pragma once
#include <Graphics/Mesh.hpp>

class Box : public Mesh {
    public:
        Box(const std::string& ID, glm::vec3 size);
        ~Box();

    private:
        static std::vector<Vertex> createBoxVertices(glm::vec3 size);
        static std::vector<unsigned int> createBoxIndices();
};