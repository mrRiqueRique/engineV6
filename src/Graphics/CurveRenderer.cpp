#include <Graphics/CurveRenderer.hpp>


CurveRenderer::CurveRenderer(const Shader* shader, const Shader* zShader, Mesh* Rectangle, glm::vec2 position, glm::vec2 size)
    : Renderer(shader, zShader, position, size),
    steps(0), dist(5.0),
    screen(new Object("screen", glm::vec3(size.x * 0.5f, size.y * 0.5f, 0.0f), glm::vec3(size.x, size.y, 1.0f), glm::vec3(0.0f)))
{
   screen->addMesh(Rectangle);
    ortho = ortho = glm::ortho(0.0f, size.x, 0.0f, size.y);
    A = 1.0;
}

CurveRenderer::~CurveRenderer()
{
    delete screen;
}

void CurveRenderer::Draw(const View& view) const 
{
    shader->activate();
    shader->informMat4("ortho", ortho);
    shader->informMat4("inverseView", glm::inverse(view.getView()));
    shader->informMat4("inverseProjection", glm::inverse(view.getProjection()));
    shader->informVec3("cameraPosition", view.getPosition());
    shader->informVec2("resolution", size);
    shader->informFloat("maxDistance", view.getZFar());
    shader->informInt("steps", steps);
    shader->informFloat("dist", dist);
    shader->informFloat("A", A);

    screen->draw(*shader, GL_TRIANGLES);
}

void CurveRenderer::ZDraw(const View& view) const 
{
    zShader->activate();
    zShader->informMat4("ortho", ortho);
    zShader->informMat4("inverseView", glm::inverse(view.getView()));
    zShader->informMat4("inverseProjection", glm::inverse(view.getProjection()));
    zShader->informVec3("cameraPosition", view.getPosition());
    zShader->informVec2("resolution", size);
    zShader->informFloat("maxDistance", view.getZFar());
    zShader->informInt("steps", steps);
    zShader->informFloat("dist", dist);
    zShader->informFloat("A", A);

    screen->draw(*zShader, GL_TRIANGLES);
}

