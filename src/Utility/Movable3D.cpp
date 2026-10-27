#include <Utility/Movable3D.hpp>

Movable3D::Movable3D(glm::vec3 origin, glm::vec3 scale, glm::vec3 rotation)
    : model(1.0f)
{
    goTo(origin);
    resizeTo(scale);
    rotateTo(rotation);
}

Movable3D::Movable3D(glm::mat4 model)
    : model(model)
{

}

Movable3D::~Movable3D()
{
    
}

void Movable3D::goTo(glm::vec3 newPosition)
{
    model[3] = glm::vec4(newPosition, 1.0);
}

void Movable3D::resizeTo(glm::vec3 newSize)
{
    for (int i = 0; i < 3; ++i) {
        glm::vec3 axis = glm::vec3(model[i]);
        float len = glm::length(axis);
        if (len > 0.0f) model[i] = glm::vec4(axis / len * newSize[i], 0.0f);
        else            model[i] = glm::vec4(0.0f);
    }
}

static glm::mat3 eulerToMat3(glm::vec3 r)
{
    return glm::mat3(glm::rotate(glm::mat4(1.0f), r.x, glm::vec3(1, 0, 0)))
         * glm::mat3(glm::rotate(glm::mat4(1.0f), r.y, glm::vec3(0, 1, 0)))
         * glm::mat3(glm::rotate(glm::mat4(1.0f), r.z, glm::vec3(0, 0, 1)));
}


void Movable3D::rotateTo(glm::vec3 newRotation)
{
    glm::vec3 s = getScale();
    glm::mat3 R = eulerToMat3(newRotation);
    for (int i = 0; i < 3; ++i) model[i] = glm::vec4(R[i] * s[i], 0.0f);
}

void Movable3D::translate(glm::vec3 translation)
{
    model[3] += glm::vec4(translation, 0.0f);
}

void Movable3D::resize(glm::vec3 size, glm::vec3 origin)
{
    glm::vec3 local = glm::vec3(glm::inverse(model) * glm::vec4(origin, 1.0f));

    model = model
          * glm::translate(glm::mat4(1.0f), local)
          * glm::scale(glm::mat4(1.0f), size)
          * glm::translate(glm::mat4(1.0f), -local);
}

void Movable3D::rotate(glm::vec3 rotation, glm::vec3 origin)
{
    glm::mat4 R = glm::translate(glm::mat4(1.0f), origin)
                * glm::mat4(eulerToMat3(rotation))
                * glm::translate(glm::mat4(1.0f), -origin);
    model = R * model;
}
  
glm::vec3 Movable3D::getPosition() const
{
    return model[3];
}

glm::vec3 Movable3D::getScale() const
{
    glm::vec3 s(
        glm::length(glm::vec3(model[0])),
        glm::length(glm::vec3(model[1])),
        glm::length(glm::vec3(model[2]))
    );

    if (glm::determinant(glm::mat3(model)) < 0.0f) s.x = -s.x;
    return s;
}

glm::vec3 Movable3D::getRotation() const
{
    glm::vec3 s = getScale();

    glm::mat3 R(
        glm::vec3(model[0])/s.x,
        glm::vec3(model[1])/s.y,
        glm::vec3(model[2])/s.z
    );

    float x, y, z;
    if(glm::abs(R[0][2]) < 0.99999f){
        y = glm::asin(-R[0][2]);
        x = glm::atan(R[1][2], R[2][2]);
        z = glm::atan(R[0][1], R[0][0]);
    }else{
        y = (R[0][2] < 0.0f) ? glm::half_pi<float>() : -glm::half_pi<float>();
        z = 0.0f;
        x = glm::atan(-R[2][1], R[1][1]);
    }

    return glm::vec3(x, y, z);
}

