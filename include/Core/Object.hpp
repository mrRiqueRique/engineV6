#pragma once
#include <Graphics/Mesh.hpp>
#include <map>

class Object{
    public:
        Object(const std::string& ID, glm::vec3 origin = glm::vec3(0.0), glm::mat4 model = glm::mat4(1.0), std::map<std::string, Mesh*> meshes = {});
        ~Object();

        void draw(const Shader& shader) const;

        void addMesh(Mesh* newMesh);
        void addMeshes(const std::vector<Mesh*>& newMeshes);
        void removeMesh(const std::string& meshKey);

        void goTo(glm::vec3 newPosition);
        void resizeTo(glm::vec3 newSize);
        void rotateTo(glm::vec3 newRotation);

        void translate(glm::vec3 translation);
        void resize(glm::vec3 size);
        void rotate(glm::vec3 rotation);

        void printInformation();
        std::string getID() const { return ID; }
        glm::vec3 getPosition() const { return origin; };

    private:
        std::string ID;

        glm::vec3 origin;
        glm::mat4 model;
        
        std::map<std::string, Mesh*> meshes;
};