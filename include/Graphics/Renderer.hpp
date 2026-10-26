#pragma once
#include <Graphics/Shader.hpp>
#include <Graphics/Camera/Camera.hpp>

class Renderer{
    public:
        Renderer(const Shader* shader, const Shader* zShader, glm::vec2 position, glm::vec2 size);
        virtual ~Renderer() = 0;

        virtual void Draw(const View& view) const = 0;
        virtual void ZDraw(const View& view) const = 0;

        void draw(const View& view) const {
            glViewport(position.x, position.y, size.x, size.y);
            Draw(view);
        }

        void zDraw(const View& view) const {
            glViewport(position.x, position.y, size.x, size.y);
            ZDraw(view);
        }

    protected:
        const Shader* shader;
        const Shader* zShader;

        glm::vec2 position;
        glm::vec2 size;
};