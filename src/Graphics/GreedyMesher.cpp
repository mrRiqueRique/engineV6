#include <Graphics/GreedyMesher.hpp>

GreedyMesher* GreedyMesher::greedyMesher = nullptr;


GreedyMesher* GreedyMesher::GetInstance()
{
    if(greedyMesher==nullptr){
        greedyMesher = new GreedyMesher();
    }
    return greedyMesher;
}

Mesh* GreedyMesher::joinMeshes(const std::map<std::string, Mesh*> meshes, const std::string& name)
{
    std::vector<Vertex> allVertices;
    std::vector<unsigned int> allIndices;
    for(const auto& [key, mesh] : meshes){
        const std::vector<Vertex> vertices = mesh->getVertices();
        const std::vector<unsigned int> indices = mesh->getIndices();
        for(int i = 0; i < vertices.size(); i++)
            allVertices.push_back(vertices[i]);
        for(int i = 0; i < indices.size(); i++){
            unsigned int index = indices[i];
            index += allVertices.size();
            allIndices.push_back(index);
        }
    }

    return new Mesh(name, allVertices, allIndices);
}

void GreedyMesher::Destroy()
{
    delete greedyMesher;
}
