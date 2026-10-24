#include <Graphics/Primitives/Box.hpp>

Box::Box(const std::string& ID, glm::vec3 size)
    :   Mesh(
        ID,
        createBoxVertices(size),
        createBoxIndices()
    )
{
    
}

Box::~Box()
{
    
}

std::vector<Vertex> Box::createBoxVertices(glm::vec3 size)
{
    glm::vec3 half = size * 0.5f;

    const std::vector<Vertex> vertices = {
        // Back face (-Z)
        {{-half.x, -half.y, -half.z}, {0.0f, 0.0f}, { 0.0f,  0.0f, -1.0f}},
        {{ half.x, -half.y, -half.z}, {1.0f, 0.0f}, { 0.0f,  0.0f, -1.0f}},
        {{ half.x,  half.y, -half.z}, {1.0f, 1.0f}, { 0.0f,  0.0f, -1.0f}},
        {{-half.x,  half.y, -half.z}, {0.0f, 1.0f}, { 0.0f,  0.0f, -1.0f}},

        // Front face (+Z)
        {{-half.x, -half.y,  half.z}, {0.0f, 0.0f}, { 0.0f,  0.0f,  1.0f}},
        {{ half.x, -half.y,  half.z}, {1.0f, 0.0f}, { 0.0f,  0.0f,  1.0f}},
        {{ half.x,  half.y,  half.z}, {1.0f, 1.0f}, { 0.0f,  0.0f,  1.0f}},
        {{-half.x,  half.y,  half.z}, {0.0f, 1.0f}, { 0.0f,  0.0f,  1.0f}},

        // Left face (-X)
        {{-half.x, -half.y, -half.z}, {0.0f, 0.0f}, {-1.0f,  0.0f,  0.0f}},
        {{-half.x, -half.y,  half.z}, {1.0f, 0.0f}, {-1.0f,  0.0f,  0.0f}},
        {{-half.x,  half.y,  half.z}, {1.0f, 1.0f}, {-1.0f,  0.0f,  0.0f}},
        {{-half.x,  half.y, -half.z}, {0.0f, 1.0f}, {-1.0f,  0.0f,  0.0f}},

        // Right face (+X)
        {{ half.x, -half.y, -half.z}, {0.0f, 0.0f}, { 1.0f,  0.0f,  0.0f}},
        {{ half.x, -half.y,  half.z}, {1.0f, 0.0f}, { 1.0f,  0.0f,  0.0f}},
        {{ half.x,  half.y,  half.z}, {1.0f, 1.0f}, { 1.0f,  0.0f,  0.0f}},
        {{ half.x,  half.y, -half.z}, {0.0f, 1.0f}, { 1.0f,  0.0f,  0.0f}},

        // Bottom face (-Y)
        {{-half.x, -half.y, -half.z}, {0.0f, 0.0f}, { 0.0f, -1.0f,  0.0f}},
        {{ half.x, -half.y, -half.z}, {1.0f, 0.0f}, { 0.0f, -1.0f,  0.0f}},
        {{ half.x, -half.y,  half.z}, {1.0f, 1.0f}, { 0.0f, -1.0f,  0.0f}},
        {{-half.x, -half.y,  half.z}, {0.0f, 1.0f}, { 0.0f, -1.0f,  0.0f}},

        // Top face (+Y)
        {{-half.x,  half.y, -half.z}, {0.0f, 0.0f}, { 0.0f,  1.0f,  0.0f}},
        {{ half.x,  half.y, -half.z}, {1.0f, 0.0f}, { 0.0f,  1.0f,  0.0f}},
        {{ half.x,  half.y,  half.z}, {1.0f, 1.0f}, { 0.0f,  1.0f,  0.0f}},
        {{-half.x,  half.y,  half.z}, {0.0f, 1.0f}, { 0.0f,  1.0f,  0.0f}}
    };

    return vertices;
}

std::vector<unsigned int> Box::createBoxIndices()
{
    const std::vector<unsigned int> indices = {
        // Back face (-Z)
         0,  2,  1,
         0,  3,  2,

        // Front face (+Z)
         4,  5,  6,
         4,  6,  7,

        // Left face (-X)
         8, 10,  9,
         8, 11, 10,

        // Right face (+X)
        12, 13, 14,
        12, 14, 15,

        // Bottom face (-Y)
        16, 18, 17,
        16, 19, 18,

        // Top face (+Y)
        20, 21, 22,
        20, 22, 23
    };

    return indices;
}
