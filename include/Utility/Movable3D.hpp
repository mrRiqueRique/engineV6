#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

class Movable3D{
    public:
        Movable3D(glm::vec3 origin, glm::vec3 scale, glm::vec3 rotation);
        Movable3D(glm::mat4 model = glm::mat4(1.0));
        ~Movable3D();

        void goTo(glm::vec3 newPosition);
        void resizeTo(glm::vec3 newSize);
        void rotateTo(glm::vec3 newRotation);

        void translate(glm::vec3 translation);
        void resize(glm::vec3 size, glm::vec3 origin);
        void rotate(glm::vec3 rotation, glm::vec3 origin);
  
        glm::vec3 getPosition() const;
        glm::vec3 getScale() const;
        glm::vec3 getRotation() const;

        glm::mat4 getModel() const { return model; }

    protected:
        glm::mat4 model;
};