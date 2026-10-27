#include <Graphics/Mesh.hpp>


Mesh::Mesh(
    const std::string& ID,
    const std::vector<Vertex>& vertices,
    const std::vector<unsigned int>& indices)
    : Movable3D(), ID(ID), count(static_cast<GLsizei>(indices.size())),
      vertices(vertices), indices(indices), isCopy(false)
{
    glm::vec3 center = calculatePoints(vertices);  // fills maxP/minP, returns centroid
    glm::vec3 s = calculateScale();                // now reads valid maxP/minP

    resizeTo(s);
    goTo(-center * s);

    initBuffers(vertices, indices);
}

Mesh::Mesh(const std::string& ID,
            const std::vector<Vertex>& vertices,
            const std::vector<unsigned int>& indices,
            glm::mat4 model)
    : Movable3D(model), ID(ID), count(static_cast<GLsizei>(indices.size())),
      vertices(vertices), indices(indices), isCopy(false)
{
    initBuffers(vertices, indices);
}

Mesh::~Mesh(){
    glDeleteVertexArrays(1, &VAO);

    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Mesh::draw(const Shader& shader, GLenum mode) const{
    glBindVertexArray(VAO);
    glDrawElements(mode, count, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

glm::vec3 Mesh::calculateScale()
{
    glm::vec3 size = maxP - minP;
    float longest = glm::max(size.x, glm::max(size.y, size.z));
    if (longest <= 0.0f) return glm::vec3(1.0f);
    return glm::vec3(1.0f / longest);
}

void Mesh::initBuffers(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
{
    glGenVertexArrays(1, &VAO);
    
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // loc(0): positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    // loc(1): texture coordinates
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(glm::vec3));

    // loc(2): normals
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3) + sizeof(glm::vec2)));

    glBindVertexArray(0);
}

glm::vec3 Mesh::calculatePoints(const std::vector<Vertex>& vertices){
    glm::vec3 soma(0.0f);
    float n = static_cast<float>(vertices.size());
    
    maxP = vertices[0].position;
    minP = vertices[0].position;

    for(auto& v : vertices){
        soma += v.position;

        if(v.position.x > maxP.x)
            maxP.x = v.position.x;

        if(v.position.x < minP.x)
            minP.x = v.position.x;

        if(v.position.y > maxP.y)
            maxP.y = v.position.y;

        if(v.position.y < minP.y)
            minP.y = v.position.y;

        if(v.position.z > maxP.z)
            maxP.z = v.position.z;

        if(v.position.z < minP.z)
            minP.z = v.position.z;
    }
    return soma/n;
}