#pragma once
#include <Graphics/Texture.hpp>

class FrameBuffer{
    public:
        FrameBuffer(int width, int height);
        ~FrameBuffer();

        GLuint getID(){ return ID; }
        Texture* getFrame() { return shaderOutput; }

        void bind(){ glBindFramebuffer(GL_FRAMEBUFFER, ID); }
        void unbind(){ glBindFramebuffer(GL_FRAMEBUFFER, 0); }
        void clear();

    private:
        GLuint ID;
        GLuint depthRBO;
        Texture* shaderOutput;
};