#pragma once
#include <Graphics/FrameBuffer.hpp>
#include <Graphics/Renderer.hpp>
#include <Core/Object.hpp>

class Blender{
    public:
        Blender(const Renderer* renderer1, const Renderer* renderer2,
            const Shader* blendingShader,
            glm::vec2 resolution, Mesh* Rectangle
        );
        ~Blender();

        void draw(const View& view);

    private:
        const Renderer* renderer1;
        const Renderer* renderer2;

        const Shader* blendingShader;

        Object* screen;
        glm::mat4 ortho;

        glm::vec2 resolution;

        FrameBuffer* renderer1frameBuffer1;
        FrameBuffer* renderer1frameBuffer2;
        FrameBuffer* renderer2frameBuffer1;
        FrameBuffer* renderer2frameBuffer2;
};