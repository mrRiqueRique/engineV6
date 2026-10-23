#pragma once
#include <Graphics/Camera/View.hpp>

class Camera {
    public:
        Camera();
        ~Camera();

        void informShader(const Shader& shader) { view->informShader(shader); }

        virtual void update();
        const View* getView() const { return view; }

    protected:
        View* view;
};