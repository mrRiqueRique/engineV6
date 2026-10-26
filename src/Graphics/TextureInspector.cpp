#include <Graphics/TextureInspector.hpp>

TextureInspector::TextureInspector(const Shader* shader, const Shader* zShader, Mesh* Rectangle, Texture* texture, Mesh* mesh, glm::vec2 position, glm::vec2 size)
    : Renderer(shader, zShader, position, size), screen(new Object("screen")), currentTexture(texture), currentMesh(mesh)
{
    screen->addMesh(Rectangle);
    screen->translate(glm::vec3(-0.5, -0.5, 0.0));
    screen->resize(glm::vec3(size.x, size.y, 1.0f));
    orthoScreen = glm::ortho(0.0f, size.x, size.y, 0.0f);
    orthoUV = glm::ortho(0.0f, 1.0f, 1.0f, 0.0f);
}

TextureInspector::~TextureInspector()
{
    delete screen;
}

void TextureInspector::Draw(const View& view) const 
{
    zShader->activate();
    currentTexture->bindAt(*zShader, "Texture", 0);
    zShader->informMat4("ortho", orthoScreen);
    screen->draw(*zShader);

    glLineWidth(2.0);
    glPointSize(2.0);
    shader->activate();
    shader->informMat4("ortho", orthoUV);
    currentMesh->draw(*shader, GL_LINES);
    currentMesh->draw(*shader, GL_POINT);
    glLineWidth(1.0);
    glPointSize(1.0);
}
