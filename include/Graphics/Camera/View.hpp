#pragma once
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Graphics/Shader.hpp>
#include <string>

class View{
    public:
        View(const std::string& ID, glm::vec3 position, glm::vec3 rotation, float fov, float aspectRation, float Znear, float Zfar);
        ~View(){};

        glm::vec3 getPosition() const { return position; }
        glm::vec3 getTarget() const { return target; }
        glm::vec3 getUp() const { return up; }
        
        glm::vec3 getForward() const { return glm::normalize(this->target - this->position); }
        glm::vec3 getRight() const { return glm::normalize(glm::cross(this->getForward(), this->up)); }

        glm::mat4 getView() const { return viewMatrix; }
        glm::mat4 getProjection() const { return projectionMatrix; }

        void informShader(const Shader& shader) const;

        void setFov(float newFov) { projectionMatrix = glm::perspective(glm::radians(newFov), aspectRatio, zNear, zFar); }

        void lookAt(glm::vec3 newTarget);
        void goTo(glm::vec3 newPosition);

        glm::vec3 getDirection();
        void rotateDirection(glm::vec3 rotationVel);

        std::string getID() { return ID; };

    private:
        std::string ID;

        glm::vec3 position;
        glm::vec3 target;
        glm::vec3 up;

        glm::vec3 rotation;

        float fov;
        float aspectRatio;
        float zNear;
        float zFar;

        glm::mat4 projectionMatrix;
        glm::mat4 viewMatrix;

        void calculateView(glm::vec3 p, glm::vec3 t, glm::vec3 u) { viewMatrix = glm::lookAt(p, t, u); }
};


