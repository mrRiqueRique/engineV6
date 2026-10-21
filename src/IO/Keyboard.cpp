#include <IO/Keyboard.hpp>
#include <iostream>

Keyboard::Keyboard(GLFWwindow* window) : window(window) {
    for(int i = 0; i < 350; i++){
        pressed[i] = false;
        held[i] = false;
        released[i] = true;
    }
    
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, KeyCallback);
}

void Keyboard::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Keyboard* keyboard = static_cast<Keyboard*>(glfwGetWindowUserPointer(window));

    if (keyboard)
        keyboard->setKey(key, action);
}

void Keyboard::setKey(int key, int action)
{   
    if(action == GLFW_RELEASE){
        released[key] = true;
        pressed[key] = false;
        held[key] = false;
    }
    else if(action == GLFW_PRESS){
        released[key] = false;
        pressed[key] = true;
        held[key] = true;
    }
    else if(action == GLFW_REPEAT){
        released[key] = false;
        pressed[key] = false;
        held[key] = true;
    }   
}

