#pragma once
#include <Core/Scene.hpp>

class Router{
    protected:
        Router(std::unordered_map<std::string, Scene*> scenes): scenes(scenes)
        {
        }

        static Router* router;

        std::unordered_map<std::string, Scene*> scenes;
        Scene* currentScene = nullptr;

        
    public:
        Router(Router &other) = delete;
        void operator=(const Router &) = delete;
        
        static Router* GetInstance(std::unordered_map<std::string, Scene*> scenes = {});
        
        void setCurrentScene(std::string newScene) { currentScene = scenes[newScene]; }
        
        Scene* getCurrentScene() const { return currentScene; } 
        
        static void Destroy();
};
