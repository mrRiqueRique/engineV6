#pragma once
#include <Graphics/Camera/Camera.hpp>
#include <IO/Keyboard.hpp>

class KeyboardCamera : public Camera {
    public:
        KeyboardCamera(float tVel, float rVel, const Keyboard* keyboard);
        ~KeyboardCamera();

        void update() override;

    private:
        float translationVelocity, rotationVelocity;
        const Keyboard* keyboard;
};