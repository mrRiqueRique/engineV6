#include <Core/TestScene.hpp>

TestScene::TestScene(const Cursor* cursor, const Keyboard* keyboard, const Window* window)
: Scene(cursor, keyboard, window)
{
    manager = new ResourceManager();
    manager->loadMeshes("assets/models/");
    manager->loadShaders("assets/shaders/");
    manager->loadMesh(new Rectangle("rect", glm::vec2(1.0, 1080.0/1920.0)));
    renderer = new Renderer(new KeyboardCamera(0.5f, 2.0f, keyboard), manager->getShader("normalTextured"));
    manager->printLoaded();
    test = new Object("teste", glm::vec3(0.0), glm::mat4(1.0), manager->getMeshes("imerpialcomputerpack1"));
    test->addMesh(manager->getMesh("rect_mesh"));
    // test->addMesh(manager->getMesh("hangar_0"));
    // test->addMesh(manager->getMesh("imerpialcomputerpack1_0"));
    // test->addMesh(manager->getMesh("imerpialcomputerpack1_1"));
    // test->addMesh(manager->getMesh("imerpialcomputerpack1_10"));
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

    renderer->draw();
}

void TestScene::onEnd()
{
    
}
