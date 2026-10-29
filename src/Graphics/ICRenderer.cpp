#include <Graphics/ICRenderer.hpp>

ICRenderer::ICRenderer(const Shader* simpleShader,
            const Shader* zSimpleShader,
            Mesh* Rectangle,
            glm::vec2 position, 
            glm::vec2 size,
            const Shader* graphicShader)
    : Renderer(simpleShader, zSimpleShader, position, size),
      steps(0), screen(new Object("screen", glm::vec3(size.x * 0.5f, size.y * 0.5f, 0.0f), glm::vec3(size.x, size.y, 1.0f), glm::vec3(0.0f))),
      graphicShader(graphicShader), rectangle(Rectangle), dist(5.0)
{
    screen->addMesh(Rectangle);
    fbo = new FrameBuffer(size.x, size.y);
    ortho = ortho = glm::ortho(0.0f, size.x, 0.0f, size.y);
    A = 1.0;
}

ICRenderer::~ICRenderer()
{
    delete fbo;
    for(auto const& graphic : graphics)
        delete graphic;
    
    delete screen;
}

void ICRenderer::Draw(const View& view) const 
{
    shader->activate();
    view.informShader(*shader);
    shader->informFloat("A", A);
    shader->informVec3("cameraPosition", view.getPosition());
    for(auto const& graphic : graphics)
        graphic->draw(*shader, GL_TRIANGLES);
}

void ICRenderer::ZDraw(const View& view) const 
{
    zShader->activate();
    view.informShader(*zShader);
    zShader->informVec3("cameraPosition", view.getPosition());
    zShader->informFloat("A", A);
    zShader->informFloat("zFar", view.getZFar());
    for(auto const& graphic : graphics)
        graphic->draw(*zShader, GL_TRIANGLES);
}

void ICRenderer::updateGraphic()
{
    steps += 1;
    fbo->bind();
    graphicShader->activate();
    graphicShader->informMat4("ortho", ortho);
    graphicShader->informInt("steps", steps);
    screen->draw(*graphicShader, GL_TRIANGLES);
    graphics.push_back(new Object(
        "rect" + std::to_string(steps),
        glm::vec3(0.0, 0.0, steps*dist),
        glm::vec3(size.x/100.0, size.y/100.0, 1.0)    
    ));
    graphics[steps - 1]->addMesh(rectangle);
    Texture* texture = new Texture(size.x, size.y, "rect" + std::to_string(steps));
    texture->copyPixelData(*fbo->getFrame());
    graphics[steps - 1]->setAllTextures(texture);
    fbo->clear();
    fbo->unbind();
}
