#include <Resources/MeshLoader.hpp>

std::vector<Mesh*> MeshLoader::loadMesh(std::string filePath){
        Assimp::Importer importer;
        const aiScene *scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals); 
        std::vector<Mesh*> meshes;
        
        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
            throw std::runtime_error("erro carregando modelo: " + filePath);
        
        MeshLoader::processNode(scene->mRootNode, scene, meshes, 0, filePath);

        return meshes;
}

void MeshLoader::processNode(aiNode *node, const aiScene *scene, std::vector<Mesh*> &meshes, unsigned int nodeIndex, std::string filePath){
    for(unsigned int i = 0; i < node->mNumMeshes; i++){
        unsigned int sceneMeshIndex = node->mMeshes[i];
        aiMesh *mesh = scene->mMeshes[sceneMeshIndex];
        meshes.push_back(processMesh(mesh, scene, sceneMeshIndex, filePath));
        
    }

    for(unsigned int i = 0; i < node->mNumChildren; i++)
        processNode(node->mChildren[i], scene, meshes, i, filePath);            
}

Mesh* MeshLoader::processMesh(aiMesh *mesh, const aiScene *scene, unsigned int meshIndex, std::string filePath){
    std::string name = std::filesystem::path(filePath).stem().string() + "_" + std::to_string(meshIndex);
    
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    
    for(unsigned int i = 0; i < mesh->mNumVertices; i++){
        glm::vec3 vertexPosition;
        vertexPosition.x = mesh->mVertices[i].x;
        vertexPosition.y = mesh->mVertices[i].y;
        vertexPosition.z = mesh->mVertices[i].z;

        glm::vec2 textureCoords;
        if(mesh->mTextureCoords[0]){
            textureCoords.x = mesh->mTextureCoords[0][i].x; 
            textureCoords.y = mesh->mTextureCoords[0][i].y;
        }
        else
            textureCoords = glm::vec2(0.0f, 0.0f); 

        glm::vec3 vertexNormal;
        vertexNormal.x = mesh->mNormals[i].x;
        vertexNormal.y = mesh->mNormals[i].y;
        vertexNormal.z = mesh->mNormals[i].z;
        
        vertices.push_back(Vertex{vertexPosition, textureCoords, vertexNormal});
    }
    
    for(unsigned int i = 0; i < mesh->mNumFaces; i++){
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    return new Mesh(name, vertices, indices);

}