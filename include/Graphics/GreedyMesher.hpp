#pragma once
#include <Graphics/Mesh.hpp>
#include <map>

class GreedyMesher{
    protected:
        GreedyMesher(){}
        
        static GreedyMesher* greedyMesher;

    public:
        GreedyMesher(GreedyMesher &other) = delete;
        void operator=(const GreedyMesher &) = delete;

        static GreedyMesher* GetInstance();

        Mesh* joinMeshes(const std::map<std::string, Mesh*> meshes, const std::string& name);

        static void Destroy();
};