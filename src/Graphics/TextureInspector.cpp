#include <Graphics/TextureInspector.hpp>

TextureInspector::TextureInspector(const Shader* shader, const Shader* zShader, Mesh* Rectangle, Texture* texture, Object* object, glm::vec2 position, glm::vec2 size)
    : Renderer(shader, zShader, position, size),
      screen(new Object("screen", glm::vec3(size.x * 0.5f, size.y * 0.5f, 0.0f), glm::vec3(size.x, size.y, 1.0f), glm::vec3(0.0f))),
      currentTexture(texture), currentObject(object)
{
    screen->addMesh(Rectangle);
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
    screen->draw(*zShader, GL_TRIANGLES);

    glLineWidth(2.0);
    glPointSize(2.0);
    shader->activate();
    shader->informMat4("ortho", orthoUV);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    currentObject->draw(*shader, GL_TRIANGLES);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glLineWidth(1.0);
    glPointSize(1.0);
}
