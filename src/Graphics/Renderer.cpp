#include <Graphics/Renderer.hpp>

Renderer::Renderer(Camera* camera, const Shader* shader)
    : camera(camera), shader(shader)
{
    
}

Renderer::~Renderer()
{

}

void Renderer::draw()
{
    camera->update();

    shader->activate();
    camera->informShader(*shader);
    for(const auto& [key, object] : objects)
        object->draw(*shader);
}

void Renderer::addObject(Object* object)
{
    if(!objects.count(object->getID())){
        objects[object->getID()] = object;
        return;
    }
    
    std::cout<<"already in renderer :("<<std::endl;
}

void Renderer::removeObject(std::string ID)
{
    auto it = objects.find(ID);
    if(it == objects.end())
        throw std::runtime_error("Object " + ID + " not found. Unable to remove");
    
    objects.erase(it);
}

void Renderer::print_toRender()
{
    for(auto const& [key, object] : objects){
        glm::vec3 position = object->getPosition();
        std::cout << key << " at " << position.x << " " << position.y << " " << position.z << std::endl;
    }
}
