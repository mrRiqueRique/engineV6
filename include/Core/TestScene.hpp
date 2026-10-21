#pragma once
#include <Core/Scene.hpp>

class TestScene : public Scene{
    public:
        TestScene(const Cursor* cursor, const Keyboard* keyboard, const Window* window);
        ~TestScene();

        void onLoop() override;

    private:        

};