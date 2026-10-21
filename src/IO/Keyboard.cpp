#include "GLFW/glfw3.h"
#include <IO/Keyboard.hpp>

Keyboard::Keyboard(GLFWwindow* window) : window(window) {
    for(int i = 0; i < 350; i++)
        pressed.push_back(false);
    
    lastPressed = pressed;
}

void Keyboard::update(){
    lastPressed = pressed;

    for(int i = 32; i < 350; i++){
        pressed[i] = glfwGetKey(window, i) == GLFW_PRESS;
    }
}