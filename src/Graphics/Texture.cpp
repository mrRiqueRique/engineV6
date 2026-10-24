#include <Graphics/Texture.hpp>

Texture::Texture(const std::string& filePath, const std::string& name) : name(name){
    int width, height, nrChannels;
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char *data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);

    this->width = width;
    this->height = height;

    if(!data)
        throw std::runtime_error("Failed to load texture");
    
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        width,
        height,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        data
    );
    
    glGenerateMipmap(GL_TEXTURE_2D);
    
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(int width, int height, const std::string& name) 
    : width(width), height(height), name(name)
{
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA32F,
        width,
        height,
        0,
        GL_RGBA,
        GL_FLOAT,
        nullptr
    );

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bindAt(const Shader& shader, const std::string& loc, unsigned int unit)
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, ID);
    shader.informInt(loc.c_str(), unit);
}

void Texture::copyPixelData(const Texture& texture)
{
    std::vector<float> pixels(static_cast<std::size_t>(texture.getWidth()) * texture.getHeight() * 4);

    glBindTexture(GL_TEXTURE_2D, texture.getID());

    glGetTexImage(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        GL_FLOAT,
        pixels.data()
    );

    glBindTexture(GL_TEXTURE_2D, ID);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA32F,
        width,
        height,
        0,
        GL_RGBA,
        GL_FLOAT,
        pixels.data()
    ); 
    glGenerateMipmap(GL_TEXTURE_2D);

    GLenum error = glGetError();

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::clear()
{
    const float zero[4] = {0.f, 0.f, 0.f, 0.f};
    glClearTexImage(ID, 0, GL_RGBA, GL_FLOAT, zero);   
}