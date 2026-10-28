#include <Graphics/Blender.hpp>


Blender::Blender(const Renderer* renderer1, const Renderer* renderer2,
    const Shader* blendingShader,
    glm::vec2 position, glm::vec2 size, Mesh* Rectangle
)
    : Renderer(blendingShader, blendingShader, position, size),
      renderer1(renderer1), renderer2(renderer2), blendingShader(blendingShader),
      screen(new Object("screen", glm::vec3(size.x * 0.5f, size.y * 0.5f, 0.0f), glm::vec3(size.x, size.y, 1.0f), glm::vec3(0.0f)))
{
    renderer1frameBuffer1 = new FrameBuffer(size.x, size.y);
    renderer1frameBuffer2 = new FrameBuffer(size.x, size.y);
    renderer2frameBuffer1 = new FrameBuffer(size.x, size.y);
    renderer2frameBuffer2 = new FrameBuffer(size.x, size.y);

    screen->addMesh(Rectangle);
    ortho = ortho = glm::ortho(0.0f, size.x, 0.0f, size.y);
}

Blender::~Blender()
{
    delete renderer1frameBuffer1;
    delete renderer1frameBuffer2;
    delete renderer2frameBuffer1;
    delete renderer2frameBuffer2;
}

void Blender::Draw(const View& view) const
{
    glClearColor(0, 0, 0, 1);

    renderer1frameBuffer1->bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderer1->draw(view);

    renderer1frameBuffer2->bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderer1->zDraw(view);

    renderer2frameBuffer1->bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderer2->draw(view);

    renderer2frameBuffer2->bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderer2->zDraw(view);

    renderer2frameBuffer2->unbind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    blendingShader->activate();
    renderer1frameBuffer1->getFrame()->bindAt(*blendingShader, "texture1", 0);
    renderer1frameBuffer2->getFrame()->bindAt(*blendingShader, "texture2", 1);
    renderer2frameBuffer1->getFrame()->bindAt(*blendingShader, "texture3", 2);
    renderer2frameBuffer2->getFrame()->bindAt(*blendingShader, "texture4", 3);

    blendingShader->informMat4("ortho", ortho);
    screen->draw(*blendingShader, GL_TRIANGLES);
}

void Blender::ZDraw(const View& view) const
{
    glClearColor(0, 0, 0, 1);

    renderer1frameBuffer1->bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderer1->zDraw(view);

    renderer1frameBuffer2->bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderer1->zDraw(view);

    renderer2frameBuffer1->bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderer2->zDraw(view);

    renderer2frameBuffer2->bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderer2->zDraw(view);

    renderer2frameBuffer2->unbind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    blendingShader->activate();
    renderer1frameBuffer1->getFrame()->bindAt(*blendingShader, "texture1", 0);
    renderer1frameBuffer2->getFrame()->bindAt(*blendingShader, "texture2", 1);
    renderer2frameBuffer1->getFrame()->bindAt(*blendingShader, "texture3", 2);
    renderer2frameBuffer2->getFrame()->bindAt(*blendingShader, "texture4", 3);

    blendingShader->informMat4("ortho", ortho);
    screen->draw(*blendingShader, GL_TRIANGLES);
}
