#include <Graphics/Camera/View.hpp>

View::View(const std::string& ID, glm::vec3 position, glm::vec3 rotation, float fov, float aspectRatio, float Znear, float Zfar)
    : ID(ID), position(position), rotation(rotation), up(0.0f, 1.0f, 0.0f), fov(fov), aspectRatio(aspectRatio), zNear(Znear), zFar(Zfar)
{
    projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, zNear, zFar);
    target = position + getDirection();
    calculateView(position, target, up);
}

void View::informShader(const Shader& shader) const
{
    shader.informMat4("view", viewMatrix);
    shader.informMat4("projection", projectionMatrix);
}

void View::lookAt(glm::vec3 newTarget)
{
    target = newTarget;
    calculateView(position, newTarget, up);
}

void View::goTo(glm::vec3 newPosition){
    glm::vec3 direction = getDirection();
    position = newPosition;
    target = newPosition + direction;
    calculateView(position, target, up);
}

glm::vec3 View::getDirection(){
    glm::mat4 R = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0,1,0));
    R = glm::rotate(R, glm::radians(rotation.x), glm::vec3(1,0,0));
    R = glm::rotate(R, glm::radians(rotation.z), glm::vec3(0,0,1));
    return glm::normalize(glm::vec3(R * glm::vec4(0, 0, -1, 0)));
}

void View::rotateDirection(glm::vec3 rotationVel){
    rotation += rotationVel;

    glm::vec3 forward = getDirection();
    target = position + forward;

    glm::vec3 worldUp(0.0f, 1.0f, 0.0f);
    glm::vec3 right = glm::normalize(glm::cross(forward, worldUp));
    up = glm::normalize(glm::cross(right, forward));

    calculateView(position, target, up);
}

void View::print_info() const{
    std::cout<<"Info from: "<<ID<<std::endl;
    std::cout<<"Position: "<<" x:"<<position.x<<" y:"<<position.y<<" z:"<<position.z<<std::endl;
    std::cout<<"Rotation: "<<" x:"<<rotation.x<<" y:"<<rotation.y<<" z:"<<rotation.z<<std::endl;
    std::cout<<"Target: "<<" x:"<<target.x<<" y:"<<target.y<<" z:"<<target.z<<std::endl;
    std::cout<<"Up: "<<" x:"<<up.x<<" y:"<<up.y<<" z:"<<up.z<<std::endl;
    std::cout<<"---------------------------------"<<std::endl;
}