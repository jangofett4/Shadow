#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Texture
{
    GLuint texture;
public:

    GLuint GetTextureID();

    Texture(int width, int height, uint8_t* data, GLenum internalFormat = GL_RGBA, GLenum format = GL_RGBA);
    ~Texture();
};