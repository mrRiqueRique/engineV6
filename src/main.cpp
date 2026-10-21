#include <iostream>
#include <Core/Core.hpp>

int main(){
    Core* core = new Core();
    if(!core->onStart())
        std::cout<<"Failed to initialize"<<std::endl;
    
    while(!core->shouldEnd){
        if(!core->onLoop())
            std::cout<<"Something went wrong on the loop"<<std::endl;
    }

    delete core;
    return 0;
}