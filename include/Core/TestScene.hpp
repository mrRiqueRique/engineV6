#pragma once
#include <Graphics/RendererRasterizer.hpp>
#include <Core/Scene.hpp>
#include <Resources/ResourceManager.hpp>
#include <Graphics/Camera/KeyboardCamera.hpp>
#include <Graphics/RendererRM.hpp>
#include <Graphics/Blender.hpp>
#include <Graphics/Primitives/Box.hpp>

class TestScene : public Scene{
    public:
        TestScene(const Cursor* cursor, const Keyboard* keyboard, const Window* window);
        ~TestScene();

        void onStart() override;
        void onLoop() override;
        void onEnd() override;

    private:
        Object* test;
        RendererRasterizer* renderer;
        RendererRM* rendererRM;
        ResourceManager* manager;
        Camera* camera;
        Blender* blender;
};