#pragma once
#include <Graphics/Mesh.hpp>
#include <Graphics/Texture.hpp>
#include <Utility/Movable2D.hpp>
#include <map>

class Object : public Movable3D {
    public:
        Object(
            const std::string& ID,
            glm::vec3 origin = glm::vec3(0.0),
            glm::vec3 scale = glm::vec3(1.0),
            glm::vec3 rotation = glm::vec3(0.0),
            glm::mat3 uvModel = glm::mat3(1.0),
            std::map<std::string, Mesh*> meshes = {},
            std::map<std::string, Texture*> textures = {},
            std::map<std::string, Movable3D> meshModels = {},
            std::map<std::string, Movable2D> uvModels = {}
        );

        ~Object();

        void draw(const Shader& shader, GLenum mode) const;

        void addMesh(Mesh* newMesh);
        void addMeshes(const std::vector<Mesh*>& newMeshes);
        void addMeshes(const std::map<std::string, Mesh*>& newMeshes);
        void removeMesh(const std::string& meshKey);

        void setTexture(Texture* newTexture, const std::string& meshKey);
        void setAllTextures(Texture* newTexture);
        void addTextures(const std::map<std::string, Texture*>& newTextures);
        void removeTexture(const std::string& textureKey);

        void goMeshTo(glm::vec3 newPosition, std::string meshKey);
        void resizeMeshTo(glm::vec3 newSize, std::string meshKey);
        void rotateMeshTo(glm::vec3 newRotation, std::string meshKey);

        void translateMesh(glm::vec3 translation, std::string meshKey);
        void resizeMesh(glm::vec3 size, glm::vec3 origin, std::string meshKey);
        void rotateMesh(glm::vec3 rotation, glm::vec3 origin, std::string meshKey);

        void goUVTo(glm::vec2 newPosition, std::string uvKey);
        void resizeUVTo(glm::vec2 newSize, std::string uvKey);
        void rotateUVTo(float newRotation, std::string uvKey);

        void translateUV(glm::vec2 translation, std::string uvKey);
        void resizeUV(glm::vec2 size, glm::vec2 origin, std::string uvKey);
        void rotateUV(float rotation, glm::vec2 origin, std::string uvKey);

        void printInformation();
        std::string getID() const { return ID; }

    private:
        std::string ID;

        glm::mat3 uvModel;

        std::map<std::string, Movable3D> meshModels;
        std::map<std::string, Movable2D> uvModels;
        
        std::map<std::string, Mesh*> meshes;
        std::map<std::string, Texture*> textures;
};