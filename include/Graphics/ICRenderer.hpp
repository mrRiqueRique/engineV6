#pragma once
#include <Graphics/Renderer.hpp>
#include <Core/Object.hpp>
#include <Graphics/FrameBuffer.hpp>

class ICRenderer : public Renderer {
    public:
        ICRenderer(
            const Shader* simpleShader,
            const Shader* zSimpleShader,
            Mesh* Rectangle,
            glm::vec2 position, 
            glm::vec2 size,
            const Shader* graphicShader
        );

        ~ICRenderer();
        
        void Draw(const View& view) const override;
        void ZDraw(const View& view) const override;

        void updateGraphic();
        float A;
        
    private:
        glm::mat4 ortho;
        Object* screen;
        FrameBuffer* fbo;
        std::vector<Object*> graphics;
        const Shader* graphicShader;
        int steps;
        float dist;
        Mesh* rectangle;
};