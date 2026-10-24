#include <Graphics/RendererRasterizer.hpp>

RendererRasterizer::RendererRasterizer(const Shader* shader, const Shader* zShader)
    : Renderer(shader, zShader)
{
    
}

RendererRasterizer::~RendererRasterizer()
{

}

void RendererRasterizer::draw(const View& view) const
{
    shader->activate();
    view.informShader(*shader);
    shader->informVec3("cameraPosition", view.getPosition());
    for(const auto& [key, object] : objects)
        object->draw(*shader);
}

void RendererRasterizer::zDraw(const View& view) const
{
    zShader->activate();
    view.informShader(*zShader);
    zShader->informVec3("cameraPosition", view.getPosition());
    zShader->informFloat("zFar", view.getZFar());
    for(const auto& [key, object] : objects)
        object->draw(*zShader);
}

void RendererRasterizer::addObject(Object* object)
{
    if(!objects.count(object->getID())){
        objects[object->getID()] = object;
        return;
    }
    
    std::cout<<"already in rendererRasterizer :("<<std::endl;
}

void RendererRasterizer::removeObject(std::string ID)
{
    auto it = objects.find(ID);
    if(it == objects.end())
        throw std::runtime_error("Object " + ID + " not found. Unable to remove");
    
    objects.erase(it);
}

void RendererRasterizer::print_toRender()
{
    for(auto const& [key, object] : objects){
        glm::vec3 position = object->getPosition();
        std::cout << key << " at " << position.x << " " << position.y << " " << position.z << std::endl;
    }
}
