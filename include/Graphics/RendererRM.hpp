#pragma once
#include <Graphics/Primitives/Rectangle.hpp>
#include <Core/Object.hpp>
#include <Graphics/Renderer.hpp>

class RendererRM : public Renderer{
    public:
        RendererRM(const Shader* shader, const Shader* zShader, Mesh* Rectangle, glm::vec2 position, glm::vec2 size);
        ~RendererRM();

        void Draw(const View& view) const override;
        void ZDraw(const View& view) const override;

    private:
        glm::mat4 ortho;
        Object* screen;
};