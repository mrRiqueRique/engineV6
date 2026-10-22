#include <Graphics/FrameBuffer.hpp>


FrameBuffer::FrameBuffer(int width, int height)
{
    glGenFramebuffers(1, &ID);
    bind();

    shaderOutput = new Texture(width, height, "frameBuffer");

    glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_COLOR_ATTACHMENT0,
        GL_TEXTURE_2D,
        shaderOutput->getID(),
        0
    );
    
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        throw std::runtime_error("Framebuffer is not complete");

    unbind();
}

FrameBuffer::~FrameBuffer()
{
    delete shaderOutput;
    glDeleteFramebuffers(1, &ID);
}
