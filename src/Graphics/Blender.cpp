#include <Graphics/Blender.hpp>


Blender::Blender(const Renderer* renderer1, const Renderer* renderer2,
    const Shader* blendingShader,
    glm::vec2 resolution, Mesh* Rectangle
)
    : renderer1(renderer1), renderer2(renderer2), blendingShader(blendingShader), resolution(resolution)
{
    screen = new Object("screen");

    renderer1frameBuffer1 = new FrameBuffer(resolution.x, resolution.y);
    renderer1frameBuffer2 = new FrameBuffer(resolution.x, resolution.y);
    renderer2frameBuffer1 = new FrameBuffer(resolution.x, resolution.y);
    renderer2frameBuffer2 = new FrameBuffer(resolution.x, resolution.y);

    screen->addMesh(Rectangle);
    screen->translate(glm::vec3(-0.5, 0.5, 1.0));
    screen->resize(glm::vec3(resolution.x, resolution.y, 1.0f));
    ortho = glm::ortho(0.0f, resolution.x, -resolution.y, 0.0f);
}

Blender::~Blender()
{
    delete renderer1frameBuffer1;
    delete renderer1frameBuffer2;
    delete renderer2frameBuffer1;
    delete renderer2frameBuffer2;
}

void Blender::draw(const View& view)
{
    glClearColor(0, 0, 0, 1);

    renderer1frameBuffer1->bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderer1->draw(view);

    renderer1frameBuffer2->bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderer1->zDraw(view);

    glViewport(0, 0, resolution.x, resolution.y);

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
    screen->draw(*blendingShader);
}
