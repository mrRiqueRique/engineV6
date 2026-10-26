#pragma once
#include <Graphics/Renderer.hpp>
#include <Graphics/Texture.hpp>
#include <Core/Object.hpp>

class TextureInspector : public Renderer{
    public:
        TextureInspector(const Shader* shader, const Shader* zShader, Mesh* Rectangle, Texture* texture, Mesh* mesh, glm::vec2 position, glm::vec2 size);
        ~TextureInspector();

        void Draw(const View& view) const override;
        void ZDraw(const View& view) const override {}

        void setCurrentTexture(Texture* newTexture) { currentTexture = newTexture; }
        void setCurrentMesh(Mesh* newMesh) { currentMesh = newMesh; }

    private:
        Texture* currentTexture;
        Mesh* currentMesh;
        Object* screen;
        glm::mat4 orthoScreen;
        glm::mat4 orthoUV;
};