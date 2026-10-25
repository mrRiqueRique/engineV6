#include <Resources/MeshLoader.hpp>

std::vector<Mesh*> MeshLoader::loadMesh(std::string filePath){
        Assimp::Importer importer;
        const aiScene *scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals); 
        std::vector<Mesh*> meshes;
        
        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
            throw std::runtime_error("erro carregando modelo: " + filePath);
        
        aiMatrix4x4 identity;
        MeshLoader::processNode(scene->mRootNode, scene, meshes, identity, 0, filePath);

        return meshes;
}

void MeshLoader::processNode(aiNode *node, const aiScene *scene, std::vector<Mesh*> &meshes, const aiMatrix4x4& parentTransform, unsigned int nodeIndex, std::string filePath){
    aiMatrix4x4 globalTransform = parentTransform * node->mTransformation;

    for(unsigned int i = 0; i < node->mNumMeshes; i++){
        unsigned int sceneMeshIndex = node->mMeshes[i];
        aiMesh *mesh = scene->mMeshes[sceneMeshIndex];
        meshes.push_back(processMesh(mesh, scene, sceneMeshIndex, globalTransform, filePath));
    }

    for(unsigned int i = 0; i < node->mNumChildren; i++)
        processNode(node->mChildren[i], scene, meshes, globalTransform, i, filePath);            
}

static glm::mat4 toGlm(const aiMatrix4x4& m)
{
    glm::mat4 result(1.0f);

    result[0][0] = m.a1;
    result[1][0] = m.a2;
    result[2][0] = m.a3;
    result[3][0] = m.a4;

    result[0][1] = m.b1;
    result[1][1] = m.b2;
    result[2][1] = m.b3;
    result[3][1] = m.b4;

    result[0][2] = m.c1;
    result[1][2] = m.c2;
    result[2][2] = m.c3;
    result[3][2] = m.c4;

    result[0][3] = m.d1;
    result[1][3] = m.d2;
    result[2][3] = m.d3;
    result[3][3] = m.d4;

    return result;
}

Mesh* MeshLoader::processMesh(aiMesh *mesh, const aiScene *scene, unsigned int meshIndex, const aiMatrix4x4& transform, std::string filePath){
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

    return new Mesh(name, vertices, indices, toGlm(transform));

}