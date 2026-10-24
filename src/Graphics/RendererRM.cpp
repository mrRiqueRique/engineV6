#include <Graphics/RendererRM.hpp>

RendererRM::RendererRM(const Shader* shader, const Shader* zShader, glm::vec2 resolution, Mesh* Rectangle)
    : Renderer(shader, zShader), resolution(resolution), screen(new Object("screen"))
{
    screen->addMesh(Rectangle);
    screen->translate(glm::vec3(-0.5, -0.5, 0.0));
    screen->resize(glm::vec3(resolution, 1.0f));
    ortho = glm::ortho(0.0f, resolution.x, resolution.y, 0.0f);
}

RendererRM::~RendererRM()
{
    delete screen;
}

void RendererRM::draw(const View& view) const
{
    shader->activate();
    shader->informMat4("ortho", ortho);
    shader->informMat4("inverseView", glm::inverse(view.getView()));
    shader->informMat4("inverseProjection", glm::inverse(view.getProjection()));
    shader->informVec3("cameraPosition", view.getPosition());
    shader->informVec2("resolution", resolution);
    shader->informFloat("maxDistance", view.getZFar());
    screen->draw(*shader);
}

void RendererRM::zDraw(const View& view) const
{
    zShader->activate();
    zShader->informMat4("ortho", ortho);
    zShader->informMat4("inverseView", glm::inverse(view.getView()));
    zShader->informMat4("inverseProjection", glm::inverse(view.getProjection()));
    zShader->informVec3("cameraPosition", view.getPosition());
    zShader->informVec2("resolution", resolution);
    zShader->informFloat("maxDistance", view.getZFar());
    screen->draw(*zShader);
}