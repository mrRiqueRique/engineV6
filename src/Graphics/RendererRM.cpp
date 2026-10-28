#include <Graphics/RendererRM.hpp>

RendererRM::RendererRM(const Shader* shader, const Shader* zShader, Mesh* Rectangle, glm::vec2 position, glm::vec2 size)
    : Renderer(shader, zShader, position, size), screen(new Object("screen", glm::vec3(size.x * 0.5f, size.y * 0.5f, 0.0f), glm::vec3(size.x, size.y, 1.0f), glm::vec3(0.0f)))
{
    screen->addMesh(Rectangle);
    ortho = ortho = glm::ortho(0.0f, size.x, 0.0f, size.y);
}

RendererRM::~RendererRM()
{
    delete screen;
}

void RendererRM::Draw(const View& view) const
{
    shader->activate();
    shader->informMat4("ortho", ortho);
    shader->informMat4("inverseView", glm::inverse(view.getView()));
    shader->informMat4("inverseProjection", glm::inverse(view.getProjection()));
    shader->informVec3("cameraPosition", view.getPosition());
    shader->informVec2("resolution", size);
    shader->informFloat("maxDistance", view.getZFar());
    screen->draw(*shader, GL_TRIANGLES);
}

void RendererRM::ZDraw(const View& view) const
{
    zShader->activate();
    zShader->informMat4("ortho", ortho);
    zShader->informMat4("inverseView", glm::inverse(view.getView()));
    zShader->informMat4("inverseProjection", glm::inverse(view.getProjection()));
    zShader->informVec3("cameraPosition", view.getPosition());
    zShader->informVec2("resolution", size);
    zShader->informFloat("maxDistance", view.getZFar());
    screen->draw(*zShader, GL_TRIANGLES);
}