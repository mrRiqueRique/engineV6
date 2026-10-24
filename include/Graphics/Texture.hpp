#pragma once
#include <stb_image.h>
#include <glad/gl.h>
#include <string>
#include <Graphics/Shader.hpp>

class Texture{
    public:
        Texture(const std::string& filePath, const std::string& name);
        Texture(int width, int height, const std::string& name);

        ~Texture() { glDeleteTextures(1, &ID); }
        std::string getName() const { return name; };
        GLuint getID() const { return ID; }

        void bindAt(const Shader& shader, const std::string& loc, unsigned int unit);
        void copyPixelData(const Texture& texture);

        int getWidth() const { return width; }
        int getHeight() const { return height; }

        void clear();

    private:
        GLuint ID;
        int width, height;
        std::string name;
};