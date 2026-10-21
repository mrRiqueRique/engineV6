#pragma once
#include <Graphics/Renderer.hpp>
#include <Core/Scene.hpp>
#include <Resources/ResourceManager.hpp>
#include <Graphics/Camera/KeyboardCamera.hpp>

class TestScene : public Scene{
    public:
        TestScene(const Cursor* cursor, const Keyboard* keyboard, const Window* window);
        ~TestScene();

        void onStart() override;
        void onLoop() override;
        void onEnd() override;

    private:        
        Object* test;
        Renderer* renderer;
        ResourceManager* manager;
        
};