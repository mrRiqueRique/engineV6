#pragma once
#include <Graphics/Mesh.hpp>

class Rectangle : public Mesh {
    public:    
        Rectangle(const std::string& ID, glm::vec2 size);
        ~Rectangle();
        
    private:
        static std::vector<Vertex> createRectangleVertices(glm::vec2 size);
        static std::vector<unsigned int> createRectangleIndices();

};