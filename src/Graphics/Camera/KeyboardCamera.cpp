#include <Graphics/Camera/KeyboardCamera.hpp>

KeyboardCamera::KeyboardCamera(float tVel, float rVel, const Keyboard* keyboard)
    : translationVelocity(tVel), rotationVelocity(rVel), keyboard(keyboard)
{
    view = new View("simple", glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), 45.0f, 16.0f/9.0f, 0.1f, 10000.0f);
}

KeyboardCamera::~KeyboardCamera()
{
    
}

void KeyboardCamera::update()
{
    // TRANSLAÇÃO DA CÂMERA
    if (keyboard->getHold(GLFW_KEY_W)){
        glm::vec3 newPosition = view->getPosition() + view->getForward() * translationVelocity;
        view->goTo(newPosition);
    }

    if (keyboard->getHold(GLFW_KEY_A)){
        glm::vec3 newPosition = view->getPosition() - view->getRight() * translationVelocity;
        view->goTo(newPosition);
    }

    if (keyboard->getHold(GLFW_KEY_S)){
        glm::vec3 newPosition = view->getPosition() - view->getForward() * translationVelocity;
        view->goTo(newPosition);
    }

    if (keyboard->getHold(GLFW_KEY_D)){
        glm::vec3 newPosition = view->getPosition() + view->getRight() * translationVelocity;
        view->goTo(newPosition);
    }

    if (keyboard->getHold(GLFW_KEY_SPACE) && !keyboard->getHold(GLFW_KEY_LEFT_SHIFT)){
        glm::vec3 newPosition = view->getPosition() + view->getUp() * translationVelocity;
        view->goTo(newPosition);
    }

    if (keyboard->getHold(GLFW_KEY_SPACE) && keyboard->getHold(GLFW_KEY_LEFT_SHIFT)){
        glm::vec3 newPosition = view->getPosition() - view->getUp() * translationVelocity;
        view->goTo(newPosition);
    }
    
    if (keyboard->getHold(GLFW_KEY_UP)){
        view->rotateDirection(glm::vec3(rotationVelocity, 0.0f, 0.0f));
    }

    if (keyboard->getHold(GLFW_KEY_DOWN)){
        view->rotateDirection(glm::vec3(-rotationVelocity, 0.0f, 0.0f));
    }

    // YAW CAMERA
    if (keyboard->getHold(GLFW_KEY_LEFT)){
        view->rotateDirection(glm::vec3(0.0f, +rotationVelocity, 0.0f));
    }

    if (keyboard->getHold(GLFW_KEY_RIGHT)){
        view->rotateDirection(glm::vec3(0.0f, -rotationVelocity, 0.0f));
    }
}
