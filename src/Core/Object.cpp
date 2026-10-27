#include <Core/Object.hpp>

Object::Object(
            const std::string& ID,
            glm::vec3 origin,
            glm::vec3 scale,
            glm::vec3 rotation,
            Movable2D uvModel,
            std::map<std::string, Mesh*> meshes,
            std::map<std::string, Texture*> textures,
            std::map<std::string, Movable3D> meshModels,
            std::map<std::string, Movable2D> uvModels)
    : Movable3D(origin, scale, rotation), ID(ID), uvModel(uvModel),
      meshes(meshes), textures(textures), meshModels(meshModels), uvModels(uvModels)
{
    for(auto const& [key, mesh] : this->meshes){
        if(!this->meshModels.count(key))
            this->meshModels[key] = Movable3D();
    }
    for(auto const& [key, tex] : this->textures){
        if(!this->uvModels.count(key))
            this->uvModels[key] = Movable2D();
    }
}

Object::~Object()
{
    for(const auto& [key, mesh] : meshes)
        if(mesh->isCopy)
            delete mesh;    
}

void Object::draw(const Shader& shader, GLenum mode) const
{
    for(auto const& [key, mesh] : meshes){
        shader.informMat4("model", model * meshModels.at(key).getModel() * mesh->getModel());
        auto it = textures.find(key);
        if(it != textures.end()){
            textures.at(key)->bindAt(shader, "Texture", 0);
            shader.informMat3("uvModel", uvModel.getModel() * uvModels.at(key).getModel());
        }

        mesh->draw(shader, mode);
    }
}

void Object::addMesh(Mesh* newMesh)
{
    if(!meshes.count(newMesh->getID())){
        meshes[newMesh->getID()] = newMesh;
        meshModels[newMesh->getID()] = Movable3D();
        return;
    }
    
    std::cout<<"already in object :("<<std::endl;
}

void Object::addMeshes(const std::vector<Mesh*>& newMeshes)
{
    for(auto const& mesh : newMeshes)
        addMesh(mesh);
}

void Object::addMeshes(const std::map<std::string, Mesh*>& newMeshes)
{
    for(auto const& [key, mesh] : newMeshes)
        addMesh(mesh);
}

void Object::removeMesh(const std::string& meshKey)
{
    auto it = meshes.find(meshKey);
    if(it == meshes.end())
        throw std::runtime_error("Mesh " + meshKey + " not found. Unable to remove");
    
    meshes.erase(it);

    auto ite = meshModels.find(meshKey);
    if(ite != meshModels.end())
        meshModels.erase(ite);

    if(textures.count(meshKey))
        removeTexture(meshKey);
}

void Object::setTexture(Texture* newTexture, const std::string& meshKey)
{
    textures[meshKey] = newTexture;
    if(!uvModels.count(meshKey))
        uvModels[meshKey] = Movable2D();
}

void Object::setAllTextures(Texture* newTexture)
{
    for(auto const& [key, mesh] : meshes)
        setTexture(newTexture, key);
}

void Object::addTextures(const std::map<std::string, Texture*>& newTextures)
{
    for(auto const& [key, texture] : newTextures)
        setTexture(texture, key);
}

void Object::removeTexture(const std::string& textureKey)
{
    auto it = textures.find(textureKey);
    if(it == textures.end())
        throw std::runtime_error("Texture " + textureKey + " not found. Unable to remove");
    
    textures.erase(it);
}

void Object::goMeshTo(glm::vec3 newPosition, std::string meshKey)
{
    auto it = meshes.find(meshKey);
    if(it == meshes.end())
        throw std::runtime_error("Mesh " + meshKey + " not found. Unable to goTo");

    meshModels[meshKey].goTo(newPosition);
}

void Object::resizeMeshTo(glm::vec3 newSize, std::string meshKey)
{
    auto it = meshes.find(meshKey);
    if(it == meshes.end())
        throw std::runtime_error("Mesh " + meshKey + " not found. Unable to resizeTo");

    meshModels[meshKey].resizeTo(newSize);
}

void Object::rotateMeshTo(glm::vec3 newRotation, std::string meshKey)
{
    auto it = meshes.find(meshKey);
    if(it == meshes.end())
        throw std::runtime_error("Mesh " + meshKey + " not found. Unable to scaleTo");

    meshModels[meshKey].rotateTo(newRotation);
}

void Object::translateMesh(glm::vec3 translation, std::string meshKey)
{
    auto it = meshes.find(meshKey);
    if(it == meshes.end())
        throw std::runtime_error("Mesh " + meshKey + " not found. Unable to translate");

    meshModels[meshKey].translate(translation);
}

void Object::resizeMesh(glm::vec3 size, glm::vec3 origin, std::string meshKey)
{
    auto it = meshes.find(meshKey);
    if(it == meshes.end())
        throw std::runtime_error("Mesh " + meshKey + " not found. Unable to resize");

    meshModels[meshKey].resize(size, origin);
}

void Object::rotateMesh(glm::vec3 rotation, glm::vec3 origin, std::string meshKey)
{
    auto it = meshes.find(meshKey);
    if(it == meshes.end())
        throw std::runtime_error("Mesh " + meshKey + " not found. Unable to rotate");

    meshModels[meshKey].rotate(rotation, origin);
}

void Object::goUVTo(glm::vec2 newPosition, std::string uvKey)
{
    auto it = uvModels.find(uvKey);
    if(it == uvModels.end())
        throw std::runtime_error("UV " + uvKey + " not found. Unable to goTo");

    uvModels[uvKey].goTo(newPosition);
}

void Object::resizeUVTo(glm::vec2 newSize, std::string uvKey)
{
    auto it = uvModels.find(uvKey);
    if(it == uvModels.end())
        throw std::runtime_error("UV " + uvKey + " not found. Unable to resizeTo");

    uvModels[uvKey].resizeTo(newSize);
}

void Object::rotateUVTo(float newRotation, std::string uvKey)
{
    auto it = uvModels.find(uvKey);
    if(it == uvModels.end())
        throw std::runtime_error("UV " + uvKey + " not found. Unable to rotateTo");

    uvModels[uvKey].rotateTo(newRotation);
}

void Object::translateUV(glm::vec2 translation, std::string uvKey)
{
    auto it = uvModels.find(uvKey);
    if(it == uvModels.end())
        throw std::runtime_error("UV " + uvKey + " not found. Unable to translate");

    uvModels[uvKey].translate(translation);
}

void Object::resizeUV(glm::vec2 size, glm::vec2 origin, std::string uvKey)
{
    auto it = uvModels.find(uvKey);
    if(it == uvModels.end())
        throw std::runtime_error("UV " + uvKey + " not found. Unable to resize");

    uvModels[uvKey].resize(size, origin);
}

void Object::rotateUV(float rotation, glm::vec2 origin, std::string uvKey)
{
    auto it = uvModels.find(uvKey);
    if(it == uvModels.end())
        throw std::runtime_error("UV " + uvKey + " not found. Unable to rotate");

    uvModels[uvKey].rotate(rotation, origin);
}

void Object::printInformation()
{
    glm::vec3 origin = getPosition();
    glm::vec3 scale = getScale();
    glm::vec3 rotation = getRotation();
    std::cout<<ID<<" with origin: "<<origin.x<<" "<<origin.y<<" "<<origin.z<<std::endl;
    std::cout<<"Meshes are:"<<std::endl;
    for(auto const& [key, mesh] : meshes){
        std::cout<<key<<" with origin: "<<mesh->getPosition().x<<" "<<mesh->getPosition().y<<" "<<mesh->getPosition().z<<std::endl;
        std::cout<<"with texture: "<<textures[key]->getID()<<std::endl;
    }

    std::cout<<"model matrix is:"<<std::endl;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            std::cout<<i<<j<<" = "<<model[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}
