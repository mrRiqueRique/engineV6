#pragma once
#include <Core/Object.hpp>
#include <Graphics/Camera/Camera.hpp>
#include <map>

class Renderer{
    public:
        Renderer(Camera* camera, const Shader* shader);
        ~Renderer();

        void draw();
        
        void addObject(Object* object);
        void removeObject(std::string ID);

        void print_toRender();

    private:
        std::map<std::string, Object*> objects;
        Camera* camera;
        const Shader* shader;
};