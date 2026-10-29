#include <glad/gl.h>
#include <IO/Window.hpp>
#include <IO/Cursor.hpp>
#include <IO/Keyboard.hpp>
#include <Core/Router.hpp>
#include <Core/TestScene.hpp>
#include <Core/ICScene.hpp>

class Core{
    public:
        Core();
        ~Core();
        int onStart();
        int onLoop();
        bool shouldEnd = false;

    private:
        Window* window;
        Cursor* cursor;
        Keyboard* keyboard;
};