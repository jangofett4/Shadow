#pragma once

#include <string>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Shader
{
    GLuint vs, fs, gs, program;
    std::vector<GLint> attribs;

    char errorString[512];
public:
    bool DidError;

    Shader(const char* vs, const char* fs);
    Shader(const char* vs, const char* gs, const char* fs);
    Shader(std::string, std::string);
    ~Shader();
    
    GLuint Program();
    std::string GetError();
};