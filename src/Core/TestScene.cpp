#include <Core/TestScene.hpp>

TestScene::TestScene(const Cursor* cursor, const Keyboard* keyboard, const Window* window)
: Scene(cursor, keyboard, window)
{
    manager = new ResourceManager();
    manager->loadMeshes("assets/models/");
    manager->loadShaders("assets/shaders/");
    manager->loadMesh(new Rectangle("rect", glm::vec2(1.0, 1.0)));
    manager->loadMesh(new Box("box", glm::vec3(1.0, 1.0, 1.0)));
    manager->loadTextures("assets/images/");

    camera = new KeyboardCamera(0.1f, 2.0f, keyboard);
    glm::vec2 resolution = glm::vec2(window->getWidth(), window->getHeight());
    renderer = new RendererRasterizer(manager->getShader("blinnphongTextured"), manager->getShader("zColored"), glm::vec2(0, 0), resolution);
        
    test = new Object(
        "teste",
        glm::vec3(0.0), glm::vec3(1.0), glm::vec3(0.0),
        glm::mat3(1.0),
        manager->getMeshes("acklay"));
    test->setAllTextures(manager->getTexture("image"));
    // test->setTexture(manager->getTexture("image"));
    // test->addMesh(manager->getMesh("imerpialcomputerpack1_0"));
    // test->addMesh(manager->getMesh("imerpialcomputerpack1_1"));
    // test->addMesh(manager->getMesh("imerpialcomputerpack1_10"));
    
    renderer->addObject(test);

    rendererRM = new RendererRM(
        manager->getShader("rmNormalColored"),
        manager->getShader("rmZColored"),
        manager->getMesh("rect_mesh"),
        glm::vec2(0, 0), resolution
    );

    blender = new Blender(rendererRM, renderer, manager->getShader("blender"), glm::vec2(0.0f), resolution, manager->getMesh("rect_mesh"));

    inspector = new TextureInspector(
        manager->getShader("uv"),
        manager->getShader("orthoTextured"),
        manager->getMesh("rect_mesh"),
        manager->getTexture("image"),
        test,
        glm::vec2(0.0, 0.0), glm::vec2(800.0, 800.0) 
    );
}

TestScene::~TestScene()
{
    delete test;
    delete manager;
    delete renderer;
    delete rendererRM;
    delete camera;
    delete blender;
    delete inspector;
}

void TestScene::onStart()
{
    
}

void TestScene::onLoop()
{
    camera->update();
    
    if(keyboard->getPressed(GLFW_KEY_R)){
        manager->printLoaded();
    }

    const float T_VEL = 0.01;
    const float R_VEL = 0.01;

    if(keyboard->getHold(GLFW_KEY_U))
        test->translateAllUVs(glm::vec3(0.0, -T_VEL, 0.0));
    if(keyboard->getHold(GLFW_KEY_J))
        test->translateAllUVs(glm::vec3(0.0, T_VEL, 0.0));
    if(keyboard->getHold(GLFW_KEY_H))
        test->translateAllUVs(glm::vec3(-T_VEL, 0.0, 0.0));
    if(keyboard->getHold(GLFW_KEY_K))
        test->translateAllUVs(glm::vec3(T_VEL, -0.0, 0.0));

    if(keyboard->getHold(GLFW_KEY_Y))
        test->rotateAllUVs(R_VEL, glm::vec3(0.0));
    if(keyboard->getHold(GLFW_KEY_I))
        test->rotateAllUVs(-R_VEL, glm::vec3(0.0));

    blender->draw(*camera->getView());
    // renderer->draw(*camera->getView());
    inspector->draw(*camera->getView());
    // rendererRM->draw(*camera->getView());
}

void TestScene::onEnd()
{
    
}
