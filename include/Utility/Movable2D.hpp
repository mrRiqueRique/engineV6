#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtc/constants.hpp>

class Movable2D{
    public:
        Movable2D(glm::vec2 origin, glm::vec2 scale, float rotation);
        Movable2D(glm::mat3 model = glm::mat3(1.0));
        ~Movable2D();

        void goTo(glm::vec2 newPosition);
        void resizeTo(glm::vec2 newSize);
        void rotateTo(float newRotation);

        void translate(glm::vec2 translation);
        void resize(glm::vec2 size, glm::vec2 origin);
        void rotate(float rotation, glm::vec2 origin);
  
        glm::vec2 getPosition() const;
        glm::vec2 getScale() const;
        float getRotation() const;

        glm::mat3 getModel() const { return model; }

    protected:
        glm::mat3 model;
};