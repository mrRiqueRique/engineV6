#pragma once
#include <Graphics/Renderer.hpp>
#include <Graphics/Texture.hpp>
#include <Core/Object.hpp>

class TextureInspector : public Renderer{
    public:
        TextureInspector(const Shader* shader, const Shader* zShader, Mesh* Rectangle, Texture* texture, Object* object, glm::vec2 position, glm::vec2 size);
        ~TextureInspector();

        void Draw(const View& view) const override;
        void ZDraw(const View& view) const override {}

        void setCurrentTexture(Texture* newTexture) { currentTexture = newTexture; }
        void setCurrentObject(Object* newObject) { currentObject = newObject; }

    private:
        Texture* currentTexture;
        Object* currentObject;
        Object* screen;
        glm::mat4 orthoScreen;
        glm::mat4 orthoUV;
};