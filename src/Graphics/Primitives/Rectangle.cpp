#include <Graphics/Primitives/Rectangle.hpp>

Rectangle::Rectangle(const std::string& ID, glm::vec2 size)
    : Mesh(
        ID + "_mesh",
        createRectangleVertices(size),
        createRectangleIndices()
        )
{

}

Rectangle::~Rectangle()
{

}


std::vector<Vertex> Rectangle::createRectangleVertices(glm::vec2 size){
    glm::vec2 half = size * 0.5f;
    
    const std::vector<Vertex> vertices = {
        {{-half.x, -half.y, 0.0f}, {0.0f, 0.0f}},
        {{ half.x, -half.y, 0.0f}, {1.0f, 0.0f}},
        {{ half.x,  half.y, 0.0f}, {1.0f, 1.0f}},
        {{-half.x,  half.y, 0.0f}, {0.0f, 1.0f}}
    };
    
    return vertices;
}

std::vector<unsigned int> Rectangle::createRectangleIndices()
{
     const std::vector<unsigned int> indices = {
        0, 1, 2,
        0, 2, 3
    };

    return indices;
}