#include <Utility/Movable2D.hpp>

Movable2D::Movable2D(glm::vec2 origin, glm::vec2 scale, float rotation)
    : model(1.0f)
{
    goTo(origin);
    resizeTo(scale);
    rotateTo(rotation);
}

Movable2D::Movable2D(glm::mat3 model)
    : model(model)
{
    
}

Movable2D::~Movable2D()
{
    
}

void Movable2D::goTo(glm::vec2 newPosition)
{
    model[2] = glm::vec3(newPosition, 1.0);
}

void Movable2D::resizeTo(glm::vec2 newSize)
{
    for (int i = 0; i < 2; ++i) {
        glm::vec2 axis = glm::vec2(model[i]);
        float len = glm::length(axis);
        if (len > 0.0f) model[i] = glm::vec3(axis / len * newSize[i], 0.0f);
        else            model[i] = glm::vec3(0.0f);
    }
}

void Movable2D::rotateTo(float newRotation)
{
    glm::vec2 s = getScale();
    glm::mat3 R = glm::rotate(glm::mat3(1.0f), newRotation);
    for (int i = 0; i < 2; ++i) model[i] = glm::vec3(glm::vec2(R[i]) * s[i], 0.0f);
}

void Movable2D::translate(glm::vec2 translation)
{
    model[2] += glm::vec3(translation, 0.0f);
}

void Movable2D::resize(glm::vec2 size, glm::vec2 origin)
{
    glm::vec2 local = glm::vec2(glm::inverse(model) * glm::vec3(origin, 1.0f));

    model = model
    * glm::translate(glm::mat3(1.0f), local)
    * glm::scale(glm::mat3(1.0f), size)
    * glm::translate(glm::mat3(1.0f), -local);
}

void Movable2D::rotate(float rotation, glm::vec2 origin)
{
    glm::mat3 R = glm::translate(glm::mat3(1.0f), origin)
    * glm::rotate(glm::mat3(1.0f), rotation)
    * glm::translate(glm::mat3(1.0f), -origin);
    model = R * model;
}
  
glm::vec2 Movable2D::getPosition() const
{
    return model[2];
}

glm::vec2 Movable2D::getScale() const
{
    glm::vec2 s(
    glm::length(glm::vec2(model[0])),
    glm::length(glm::vec2(model[1])));

    if (glm::determinant(glm::mat2(model)) < 0.0f) s.x = -s.x;
    return s;
}

float Movable2D::getRotation() const
{
    glm::vec2 s = getScale();
    glm::vec2 c = glm::vec2(model[0]) / s.x;

    return glm::atan(c.y, c.x);
}
