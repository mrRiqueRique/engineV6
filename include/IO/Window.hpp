#pragma once
#include <GLFW/glfw3.h>
#include <iostream>

struct windowParams{
    bool fullscreen = true;
    int width;
    int height;
    const char *windowName = "Window";
};

class Window{
    public:
        Window(const windowParams &params);
        ~Window();

        void close() { glfwSetWindowShouldClose(handle, GLFW_TRUE); }
        void update() { glfwSwapBuffers(handle); }
        void poll() { glfwPollEvents(); }
        void clear() const { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }
        bool shouldClose() { return glfwWindowShouldClose(handle); }
        void makeCurrent() { glfwMakeContextCurrent(handle); }

        double getWidth() const { return width; }
        double getHeight() const { return height; }

        GLFWwindow* getHandle(){ return handle; }
    private:
        GLFWwindow* handle = nullptr;
        int width, height;
};