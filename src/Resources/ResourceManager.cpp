#include <Resources/ResourceManager.hpp>
#include <ostream>

ResourceManager::ResourceManager(){
    meshes.clear();
    shaders.clear();
    // textures.clear();
}

ResourceManager::~ResourceManager(){
    for(auto vecmesh : meshes)
        for(auto mesh : vecmesh.second)
            delete mesh;

    for(auto shader : shaders)
        delete shader.second;
    
    // for(auto texture : textures)
    //     delete texture.second;
}

void ResourceManager::loadMesh(const std::string& filePath){
    std::filesystem::path path = filePath;
    std::vector<Mesh*> newMeshes = MeshLoader::loadMesh(filePath);
    meshes[path.stem().string()] = newMeshes;

}

void ResourceManager::loadMeshes(const std::string& folderPath){
    std::vector<Mesh*> newMeshes;
    for(auto const& file : std::filesystem::directory_iterator(folderPath))
        loadMesh(file.path().string());
    
}

std::vector<Mesh*> ResourceManager::getMesh(const std::string& ID){
    auto it = meshes.find(ID);

    if(it == meshes.end())
        throw std::runtime_error("Mesh " + ID + " not found. Unable to get");

    return it->second;
}

void ResourceManager::removeMesh(const std::string& ID){
    auto it = meshes.find(ID);

    if(it == meshes.end())
        throw std::runtime_error("Mesh " + ID + " not found. Unable to remove");

    for(auto mesh : it->second)
        delete mesh;

    meshes.erase(it);
}

void ResourceManager::removeMeshes(const std::vector<std::string>& IDs){
    for(auto ID : IDs)
        removeMesh(ID);
}

void ResourceManager::loadShader(const std::string& shaderFolderPath){
    Shader* newShader = ShaderLoader::loadShader(shaderFolderPath);
    shaders[newShader->getName()] = newShader;
}

void ResourceManager::loadShaders(const std::string& folderPath){
    Shader* newShader;
    for (auto const& folder : std::filesystem::directory_iterator(folderPath)) {
        std::string folderName = folder.path().filename().string();

        newShader = ShaderLoader::loadShader(folderPath + folderName);
        shaders[newShader->getName()] = newShader;
    }
}

Shader* ResourceManager::getShader(const std::string& name){
    auto it = shaders.find(name);

    if(it == shaders.end())
        throw std::runtime_error("Shader " + name + " not found. Unable to get");

    return it->second;
}

void ResourceManager::removeShader(const std::string& name){
    auto it = shaders.find(name);

    if(it == shaders.end())
        throw std::runtime_error("Shader " + name + " not found. Unable to remove");

    delete it->second;
    shaders.erase(it);
}

void ResourceManager::removeShaders(const std::vector<std::string>& names){
    for(auto name : names)
        removeShader(name);
}


// void ResourceManager::loadTexture(const std::string& texturePath){
//     Texture* newTexture = TextureLoader::loadTexture(texturePath);
//     textures[newTexture->getName()] = newTexture;
// }

// void ResourceManager::loadTextures(const std::string& folderPath){
//     Texture* newTexture;
//     for (auto const& file : std::filesystem::directory_iterator(folderPath)) {
//         std::string fileName = file.path().string();
//         newTexture = TextureLoader::loadTexture(fileName);
//         textures[newTexture->getName()] = newTexture;
//     }
// }

// Texture* ResourceManager::getTexture(const std::string& name){
//     auto it = textures.find(name);

//     if(it == textures.end())
//         throw std::runtime_error("Texture " + name + " not found. Unable to get");

//     return it->second;
// }

// void ResourceManager::removeTexture(const std::string& name){
//     auto it = textures.find(name);

//     if(it == textures.end())
//         throw std::runtime_error("Texture " + name + " not found. Unable to remove");

//     delete it->second;
//     textures.erase(it);
// }

// void ResourceManager::removeTextures(const std::vector<std::string>& names){
//     for(auto name : names)
//         removeTexture(name);
// }

void ResourceManager::printLoaded()
{
    std::cout << "MESHES:" << std::endl;
    for(auto vecmesh : meshes){
        std::cout << "FULL_MESH: " << vecmesh.first << std::endl;
        for(auto mesh : vecmesh.second){
            std::cout << mesh->getID() << std::endl;
        }
        std::cout << "=======================" << std::endl;
    }
    std::cout << "=======================" << std::endl;
    std::cout << "TEXTURES" << std::endl;
    // for(auto texture : textures){
    //     std::cout << texture.first << std::endl;
    // }
    std::cout << "=======================" << std::endl;
    std::cout << "SHADERS" << std::endl;
    for(auto shader : shaders){
        std::cout << shader.first << std::endl;
    }
}
