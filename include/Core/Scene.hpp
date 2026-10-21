#pragma once
#include <IO/Cursor.hpp>
#include <IO/Keyboard.hpp>
#include <IO/Window.hpp>

class Scene{
    public:
        Scene(const Cursor* cursor, const Keyboard* keyboard, const Window* window);
        virtual ~Scene() = 0;

        virtual void onStart() = 0;
        virtual void onLoop() = 0;
        virtual void onEnd() = 0;

    protected:
        const Window* window;
        const Cursor* cursor;
        const Keyboard* keyboard;
};