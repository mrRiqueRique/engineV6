#pragma once
#include <GLFW/glfw3.h>
#include <vector>

class Keyboard{
    public:
        Keyboard(GLFWwindow* window);

        bool getPressed(unsigned int key) const { return !lastPressed[key] && pressed[key]; }
        bool getHold(unsigned int key) const { return lastPressed[key] && pressed[key]; }
        bool getReleased(unsigned int key) const { return lastPressed[key] && !pressed[key]; }

        void update();

    private:
        GLFWwindow* window;

        std::vector<bool> pressed;
        std::vector<bool> lastPressed;
};
