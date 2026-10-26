#include <Core/Object.hpp>


Object::Object(const std::string& ID, glm::vec3 origin, glm::mat4 model, std::map<std::string, Mesh*> meshes)
    : ID(ID), origin(origin), model(model), meshes(meshes)
{
    texture = nullptr;
}

Object::~Object()
{
    
}

void Object::draw(const Shader& shader) const
{
    for(auto const& [key, mesh] : meshes){
        shader.informMat4("model", mesh->getModel() * model);
        if(texture)
            texture->bindAt(shader, "Texture", 0);
        mesh->draw(shader, GL_TRIANGLES);
    }
}

void Object::addMesh(Mesh* newMesh)
{
    if(!meshes.count(newMesh->getID())){
        meshes[newMesh->getID()] = newMesh;
        return;
    }
    
    std::cout<<"already in object :("<<std::endl;
}

void Object::addMeshes(const std::vector<Mesh*>& newMeshes)
{
    for(auto const& mesh : newMeshes)
        addMesh(mesh);
}

void Object::removeMesh(const std::string& meshKey)
{
    auto it = meshes.find(meshKey);
    if(it == meshes.end())
        throw std::runtime_error("Mesh " + meshKey + " not found. Unable to remove");
    
    meshes.erase(it);
}

void Object::goTo(glm::vec3 newPosition)
{
    origin = newPosition;
    
}

void Object::resizeTo(glm::vec3 newSize)
{
    
}

void Object::rotateTo(glm::vec3 newRotation)
{
    
}

void Object::translate(glm::vec3 translation)
{
    origin += translation;
    model *= glm::translate(glm::mat4(1.0), translation);
}

void Object::resize(glm::vec3 size)
{
    model *= glm::translate(glm::mat4(1.0f), origin) * glm::scale(glm::mat4(1.0f), size) * glm::translate(glm::mat4(1.0f), -origin);

}

void Object::rotate(glm::vec3 rotation)
{
    model *= glm::translate(glm::mat4(1.0f), origin) * glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1.0, 0.0, 0.0)) * glm::translate(glm::mat4(1.0f), -origin);
    model *= glm::translate(glm::mat4(1.0f), origin) * glm::rotate(glm::mat4(1.0f), rotation.y, glm::vec3(0.0, 1.0, 0.0)) * glm::translate(glm::mat4(1.0f), -origin);
    model *= glm::translate(glm::mat4(1.0f), origin) * glm::rotate(glm::mat4(1.0f), rotation.z, glm::vec3(0.0, 0.0, 1.0)) * glm::translate(glm::mat4(1.0f), -origin);
}

void Object::printInformation()
{
    std::cout<<ID<<" with origin: "<<origin.x<<" "<<origin.y<<" "<<origin.z<<std::endl;
    std::cout<<"Meshes are:"<<std::endl;
    for(auto const& [key, mesh] : meshes){
        std::cout<<key<<" with origin: "<<mesh->getOrigin().x<<" "<<mesh->getOrigin().y<<" "<<mesh->getOrigin().z<<std::endl;
    }
    std::cout<<"model matrix is:"<<std::endl;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            std::cout<<i<<j<<" = "<<model[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}
