#include <Core/TestScene.hpp>

TestScene::TestScene(const Cursor* cursor, const Keyboard* keyboard, const Window* window)
: Scene(cursor, keyboard, window)
{
    manager = new ResourceManager();
    manager->loadMeshes("assets/models/");
    manager->loadShaders("assets/shaders/");
    manager->loadMesh(new Rectangle("rect", glm::vec2(1.0, 1.0)));
    manager->loadMesh(new Box("box", glm::vec3(1.0, 1.0, 1.0)));

    camera = new KeyboardCamera(0.1f, 2.0f, keyboard);
    renderer = new RendererRasterizer(manager->getShader("normalColored"), manager->getShader("zColored"));
        
    test = new Object("teste", glm::vec3(0.0), glm::mat4(1.0), manager->getMeshes("acklay"));
    
    test->addMesh(manager->getMesh("box"));
    // test->addMesh(manager->getMesh("imerpialcomputerpack1_0"));
    // test->addMesh(manager->getMesh("imerpialcomputerpack1_1"));
    // test->addMesh(manager->getMesh("imerpialcomputerpack1_10"));
    
    renderer->addObject(test);
    
    glm::vec2 resolution = glm::vec2(window->getWidth(), window->getHeight());

    rendererRM = new RendererRM(
        manager->getShader("rmNormalColored"),
        manager->getShader("rmZColored"),
        resolution,
        manager->getMesh("rect_mesh")
    );

    blender = new Blender(rendererRM, renderer, manager->getShader("blender"), resolution, manager->getMesh("rect_mesh"));
}

TestScene::~TestScene()
{
    delete test;
    delete manager;
    delete renderer;
    delete rendererRM;
    delete camera;
    delete blender;
}

void TestScene::onStart()
{
    
}

void TestScene::onLoop()
{
    camera->update();
    if(keyboard->getPressed(GLFW_KEY_U))
        test->translate(glm::vec3(0.0, 0.5, 0.0));
    if(keyboard->getPressed(GLFW_KEY_J))
        test->translate(glm::vec3(0.0, -0.5, 0.0));
    if(keyboard->getPressed(GLFW_KEY_H))
        test->translate(glm::vec3(-0.5, 0.0, 0.0));
    if(keyboard->getPressed(GLFW_KEY_K))
        test->translate(glm::vec3(0.5, -0.0, 0.0));

        
    blender->draw(*camera->getView());
    // rendererRM->draw(*camera->getView());
}

void TestScene::onEnd()
{
    
}
