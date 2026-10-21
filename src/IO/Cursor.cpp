#include "GLFW/glfw3.h"
#include <IO/Cursor.hpp>

Cursor::Cursor(const CursorParams &params) : window(params.window){
    int width, height, channels;

    for (const auto& entry : std::filesystem::directory_iterator(params.imagesPath)) {
        unsigned char* pixels = stbi_load(
            entry.path().string().c_str(),
            &width,
            &height,
            &channels,
            4
        );
        
        if(!pixels)
            throw std::runtime_error("Falha ao abrir imagem");
    
        GLFWimage image;
        image.width = width;
        image.height = height;
        image.pixels = pixels;
        GLFWcursor* cursor = glfwCreateCursor(&image, 0, 0);
        
        cursors[entry.path().stem()] = cursor;
        stbi_image_free(pixels);
    }

    self = cursors["arrow"];
    glfwSetCursor(window, self);

    for(int i = 0; i < 8; i++)
        pressed.push_back(false);
    
    lastPressed = pressed;

    glfwSetWindowUserPointer(params.window, this);
    
    glfwSetDropCallback(params.window, DropCallback);
    glfwSetCursorPosCallback(params.window, PosCallback);
}

Cursor::~Cursor(){
    for (const auto& [name, cursor] : cursors)
        glfwDestroyCursor(cursor);
    
    cursors.clear();
    self = NULL;
}

int Cursor::changeCursor(std::string newCursor){    
    self = cursors[newCursor];
    if(self == NULL)
        return 0;
    
    glfwSetCursor(window, self);
    return 1;
}

void Cursor::hide(){
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Cursor::show(){
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); 
}

bool Cursor::getPressed(unsigned int button) const {
    return !lastPressed[button] && pressed[button];
}

bool Cursor::getHold(unsigned int button) const {
    return lastPressed[button] && pressed[button];
}

bool Cursor::getReleased(unsigned int button) const {
    return lastPressed[button] && !pressed[button];
}

void Cursor::DropCallback(GLFWwindow* window, int count, const char **paths){
    Cursor* cursor = static_cast<Cursor*>(glfwGetWindowUserPointer(window));

    if (cursor)
        cursor->setDroppedPaths(count, paths);
}

void Cursor::setDroppedPaths(int count, const char** paths){
    droppedPaths.clear();
    for(int i = 0; i < count; i++)
        droppedPaths.push_back(std::string(paths[i]));
}

void Cursor::PosCallback(GLFWwindow* window, double xpos, double ypos)
{
    Cursor* cursor = static_cast<Cursor*>(glfwGetWindowUserPointer(window));

    if(cursor)
        cursor->setPos(window, xpos, ypos);
}

void Cursor::setPos(GLFWwindow* window, double xpos, double ypos)
{
    position = glm::vec2(xpos, ypos);
}

