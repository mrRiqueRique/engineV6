#pragma once
#include <Graphics/Shader.hpp>
#include <Graphics/Camera/Camera.hpp>

class Renderer{
    public:
        Renderer(const Shader* shader, const Shader* zShader);
        virtual ~Renderer() = 0;

        virtual void draw(const View& view) const = 0;
        virtual void zDraw(const View& view) const = 0;

    protected:
        const Shader* shader;
        const Shader* zShader;
};