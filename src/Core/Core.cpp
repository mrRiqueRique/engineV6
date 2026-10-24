#include <Core/Core.hpp>

Core::Core(){
    if(!glfwInit()){
        throw std::runtime_error("Failed to initialize glfw");
    }


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    windowParams wParams = {
        .fullscreen = GLFW_TRUE,
        .width = 1400,
        .height = 788,
        .windowName = "Test"
    };

    
    window = new Window(wParams);

    window->makeCurrent();

    if (!gladLoadGL(glfwGetProcAddress))
        throw std::runtime_error("Failed to initialize GLAD");

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glViewport(0, 0, window->getWidth(), window->getHeight());

    CursorParams cParams = {
        .window = window->getHandle(),
        .imagesPath = "assets/cursors/"
    };

    cursor = new Cursor(cParams);
    keyboard = new Keyboard(window->getHandle());
}

Core::~Core(){
    delete window;
    delete cursor;
    delete keyboard;
    
    Router::Destroy();

    glfwTerminate();
}

int Core::onStart(){
    glfwSetTime(0.0);

    std::unordered_map<std::string, Scene*> scenes;

    int x = window->getWidth();
    int y = window->getHeight();

    scenes["test"] = new TestScene(cursor, keyboard, window);
    Router::GetInstance(scenes);
    Router::GetInstance()->setCurrentScene("test");

    return 1;
}

int Core::onLoop(){
    window->poll();
    window->clear();

    keyboard->update();

    Router::GetInstance()->getCurrentScene()->onLoop();

    if(keyboard->getPressed(GLFW_KEY_ESCAPE)){
        window->close();
        shouldEnd = true;
    }
    
    window->update();
    return 1;
}