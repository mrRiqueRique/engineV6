#include <Core/ICScene.hpp>

ICScene::ICScene(const Cursor* cursor, const Keyboard* keyboard, const Window* window)
    : Scene(cursor, keyboard, window)
{
    manager = new ResourceManager();
    manager->loadShaders("assets/shaders/");
    manager->loadMesh(new Rectangle("rect", glm::vec2(1.0, 1.0)));
    
    graphicsRenderer = new ICRenderer(
        manager->getShader("textured"),
        manager->getShader("zColored"),
        manager->getMesh("rect_mesh"),
        glm::vec2(0.0f, 0.0f),
        glm::vec2(window->getWidth(), window->getHeight()),
        manager->getShader("graphic")
    );

    curveRenderer = new CurveRenderer(
        manager->getShader("curve"),
        manager->getShader("zCurve"),
        manager->getMesh("rect_mesh"),
        glm::vec2(0.0f, 0.0f),
        glm::vec2(window->getWidth(), window->getHeight())
    );

    camera = new KeyboardCamera(1.0f, 2.0f, keyboard);
    
    blender = new Blender(
        graphicsRenderer,
        curveRenderer,
        manager->getShader("blender"),
        glm::vec2(0.0),
        glm::vec2(window->getWidth(), window->getHeight()),
        manager->getMesh("rect_mesh")
    );

    toggleRM = false;
    toggleGraphics = false;
}

ICScene::~ICScene()
{
    
}

void ICScene::onStart()
{
    
}

void ICScene::onLoop()
{
    camera->update();

    if(keyboard->getPressed(GLFW_KEY_I)){
        graphicsRenderer->updateGraphic();
        curveRenderer->updateCurve();
    }
    if(keyboard->getPressed(GLFW_KEY_G)){
        toggleGraphics = !toggleGraphics;
    }
    if(keyboard->getPressed(GLFW_KEY_H)){
        toggleRM = !toggleRM;
    }
    if(toggleGraphics && toggleRM)
        blender->draw(*camera->getView());
    else if(toggleGraphics)
        graphicsRenderer->draw(*camera->getView());
    else if(toggleRM)
        curveRenderer->draw(*camera->getView());

    if(keyboard->getHold(GLFW_KEY_T) && !keyboard->getHold(GLFW_KEY_LEFT_SHIFT)){
        graphicsRenderer->A *= 1.1;
        curveRenderer->A *= 1.1;
    }

    if(keyboard->getHold(GLFW_KEY_T) && keyboard->getHold(GLFW_KEY_LEFT_SHIFT)){
        graphicsRenderer->A /= 1.1;
        curveRenderer->A /= 1.1;
    }

    // curveRenderer->zDraw(*camera->getView());
}

void ICScene::onEnd()
{
    
}
