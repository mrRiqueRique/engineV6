#pragma once
#include <Graphics/Primitives/Rectangle.hpp>
#include <Core/Object.hpp>
#include <Graphics/Renderer.hpp>

class RendererRM : public Renderer{
    public:
        RendererRM(const Shader* shader, const Shader* zShader, glm::vec2 resolution, Mesh* Rectangle);
        ~RendererRM();

        void draw(const View& view) const override;
        void zDraw(const View& view) const override;

    private:
        glm::mat4 ortho;
        Object* screen;
        glm::vec2 resolution;
};