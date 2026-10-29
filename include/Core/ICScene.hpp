#pragma once
#include <Resources/ResourceManager.hpp>
#include <Core/Scene.hpp>
#include <Graphics/RendererRM.hpp>
#include <Graphics/Blender.hpp>
#include <Graphics/ICRenderer.hpp>
#include <Graphics/Camera/KeyboardCamera.hpp>
#include <Graphics/CurveRenderer.hpp>

class ICScene : public Scene {
    public:
        ICScene(const Cursor* cursor, const Keyboard* keyboard, const Window* window);
        ~ICScene();

        void onStart() override;
        void onLoop() override;
        void onEnd() override;

    private:
        Blender* blender;
        ResourceManager* manager;
        ICRenderer* graphicsRenderer;
        CurveRenderer* curveRenderer;
        Camera* camera;
        int steps;
        bool toggleRM;
        bool toggleGraphics;
};