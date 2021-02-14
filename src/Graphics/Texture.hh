#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Texture
{
    GLuint texture;
public:

    GLuint GetTextureID();

    Texture(int, int, uint8_t*);
    ~Texture();
};