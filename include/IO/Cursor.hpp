#pragma once
#include <stb_image.h>
#include "GLFW/glfw3.h"
#include "filesystem"
#include <functional>
#include <glm/gtc/type_ptr.hpp>
#include "vector"
#include <unordered_map>

struct CursorParams{
    GLFWwindow* window;
    std::string imagesPath;
};

class Cursor{
    public:
        Cursor(const CursorParams &params);
        ~Cursor();

        int changeCursor(std::string newCursor);

        float getScroll() const;

        static void DropCallback(GLFWwindow* window, int count, const char** paths);
        void setDroppedPaths(int count, const char** paths);
        std::vector<std::string> getDroppedPaths() const { return droppedPaths; }
        
        static void PosCallback(GLFWwindow* window, double xpos, double ypos);
        void setPos(GLFWwindow* window, double xpos, double ypos);
        glm::vec2 getPos() const { return position; };

        void hide();
        void show();

        bool getPressed(unsigned int button) const;
        bool getHold(unsigned int button) const;
        bool getReleased(unsigned int button) const;

    private:
        GLFWcursor* self;
        GLFWwindow* window;
        std::unordered_map<std::string, GLFWcursor*> cursors;
        glm::vec2 position;

        bool hidden = false;
        bool dropped = false;
        std::vector<bool> pressed;
        std::vector<bool> lastPressed;

        std::vector<std::string> droppedPaths;
};
