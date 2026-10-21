#pragma once
#include <GLFW/glfw3.h>

class Keyboard{
    public:
        Keyboard(GLFWwindow* window);

        bool getPressed(unsigned int key) const { return pressed[key] == 1; }
        bool getHold(unsigned int key) const { return held[key] == 1; }
        bool getReleased(unsigned int key) const { return released[key] == 1; }

        static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        void setKey(int key, int action);

    private:
        GLFWwindow* window;

        bool pressed[350];
        bool held[350];
        bool released[350];
};

