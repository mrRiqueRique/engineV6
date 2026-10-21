#include <Core/TestScene.hpp>

TestScene::TestScene(const Cursor* cursor, const Keyboard* keyboard, const Window* window)
: Scene(cursor, keyboard, window)
{
    manager = new ResourceManager();
    manager->loadMeshes("assets/models/");
    manager->loadShaders("assets/shaders/");
    renderer = new Renderer(new KeyboardCamera(0.5f, 2.0f, keyboard), manager->getShader("normalTextured"));

    test = new Object("teste");
    test->addMeshes(manager->getMesh("acklay"));
    renderer->addObject(test);
}

TestScene::~TestScene()
{
    delete test;
    delete manager;
    delete renderer;
}

void TestScene::onStart()
{
    
}

void TestScene::onLoop()
{
    if(keyboard->getPressed(GLFW_KEY_U))
        test->translate(glm::vec3(0.0, 0.5, 0.0));
    if(keyboard->getPressed(GLFW_KEY_J))
        test->translate(glm::vec3(0.0, -0.5, 0.0));
    if(keyboard->getPressed(GLFW_KEY_H))
        test->translate(glm::vec3(-0.5, 0.0, 0.0));
    if(keyboard->getPressed(GLFW_KEY_K))
        test->translate(glm::vec3(0.5, -0.0, 0.0));

    test->printInformation();

    renderer->draw();
}

void TestScene::onEnd()
{
    
}
