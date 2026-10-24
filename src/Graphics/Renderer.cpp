#include <Graphics/Renderer.hpp>

Renderer::Renderer(const Shader* shader, const Shader* zShader)
    : shader(shader), zShader(zShader)
{
    
}

Renderer::~Renderer()
{
    
}
