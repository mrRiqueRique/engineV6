#pragma once
#include <Graphics/Renderer.hpp>
#include <Graphics/Primitives/Rectangle.hpp>
#include <Core/Object.hpp>
#include <Graphics/Renderer.hpp>

class CurveRenderer : public Renderer {
    public:
        CurveRenderer(const Shader* shader, const Shader* zShader, Mesh* Rectangle, glm::vec2 position, glm::vec2 size);
        ~CurveRenderer();
        
        void Draw(const View& view) const override;
        void ZDraw(const View& view) const override;

        void updateCurve() { steps += 1; }
        float A;

    private:
        glm::mat4 ortho;
        Object* screen;

        int steps;
        float dist;
};