#pragma once
#include <Graphics/FrameBuffer.hpp>
#include <Graphics/Renderer.hpp>
#include <Core/Object.hpp>

class Blender : public Renderer{
    public:
        Blender(const Renderer* renderer1, const Renderer* renderer2,
            const Shader* blendingShader,
            glm::vec2 position, glm::vec2 size, Mesh* Rectangle
        );
        ~Blender();

        void Draw(const View& view) const override;
        void ZDraw(const View& view) const override;

    private:
        const Renderer* renderer1;
        const Renderer* renderer2;

        const Shader* blendingShader;

        Object* screen;
        glm::mat4 ortho;

        FrameBuffer* renderer1frameBuffer1;
        FrameBuffer* renderer1frameBuffer2;
        FrameBuffer* renderer2frameBuffer1;
        FrameBuffer* renderer2frameBuffer2;
};