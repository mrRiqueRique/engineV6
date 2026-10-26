#pragma once
#include <Core/Object.hpp>
#include <Graphics/Renderer.hpp>

class RendererRasterizer : public Renderer{
    public:
        RendererRasterizer(const Shader* shader, const Shader* zShader, glm::vec2 position, glm::vec2 size);
        ~RendererRasterizer();

        void Draw(const View& view) const  override;
        void ZDraw(const View& view) const override;

        void addObject(Object* object);
        void removeObject(std::string ID);

        void print_toRender();

    private:
        std::map<std::string, Object*> objects;
};