#include <Core/Router.hpp>

Router* Router::router= nullptr;;

Router* Router::GetInstance(std::unordered_map<std::string, Scene*> scenes)
{
    if(router==nullptr){
        router = new Router(scenes);
    }
    return router;
}

void Router::Destroy(){
    for (const auto& [name, scene] : router->scenes)
        delete scene;

    router->currentScene = nullptr;

    delete router;
    router = nullptr;
}