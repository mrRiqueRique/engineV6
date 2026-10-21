#include <IO/Window.hpp>

Window::Window(const windowParams &params)
{
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    
    if(params.fullscreen){
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        width = mode->width;
        height = mode->height;
        handle = glfwCreateWindow(width, height, params.windowName, monitor, NULL);

    } else{
        width = params.width;
        height = params.height;
        handle = glfwCreateWindow(width, height, params.windowName, NULL, NULL);
    }

    if(!handle){
        throw std::runtime_error("Falha ao inicializar janela");
    }
}

Window::~Window()
{
    glfwDestroyWindow(handle);
}
