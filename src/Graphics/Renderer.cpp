#include <Graphics/Renderer.hpp>

Renderer::Renderer(const Shader* shader, const Shader* zShader, glm::vec2 position, glm::vec2 size)
    : shader(shader), zShader(zShader), position(position), size(size)
{
    
}

Renderer::~Renderer()
{
    
}
