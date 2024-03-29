#include "Shader.hh"

Shader::Shader(const std::string vstext, const std::string fstext)
    : Shader(vstext.c_str(), fstext.c_str()) { }

Shader::Shader(const char* vstext, const char* gstext, const char* fstext) : attribs(), DidError(false)
{
    vs = glCreateShader(GL_VERTEX_SHADER);
    gs = glCreateShader(GL_GEOMETRY_SHADER);
    fs = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vs, 1, &vstext, nullptr);
    glShaderSource(gs, 1, &gstext, nullptr);
    glShaderSource(fs, 1, &fstext, nullptr);

    glCompileShader(vs);
    glCompileShader(gs);
    glCompileShader(fs);

    GLint status;
    glGetShaderiv(vs, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        glGetShaderInfoLog(vs, 512, nullptr, errorString);
        DidError = true;
    }

    glGetShaderiv(gs, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        glGetShaderInfoLog(gs, 512, nullptr, errorString);
        DidError = true;
    }

    glGetShaderiv(fs, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        glGetShaderInfoLog(fs, 512, nullptr, errorString);
        DidError = true;
    }

    if (DidError)
        return;

    program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, gs);
    glAttachShader(program, fs);
    glBindFragDataLocation(program, 0, "outColor");
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (!status)
    {
        glGetProgramInfoLog(program, 512, nullptr, errorString);
        DidError = true;
        return;
    }

    DidError = false;
}

Shader::Shader(const char* vstext, const char* fstext) : attribs(), DidError(false)
{
    gs = -1;
    vs = glCreateShader(GL_VERTEX_SHADER);
    fs = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vs, 1, &vstext, nullptr);
    glShaderSource(fs, 1, &fstext, nullptr);

    glCompileShader(vs);
    glCompileShader(fs);

    GLint status;
    glGetShaderiv(vs, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        glGetShaderInfoLog(vs, 512, nullptr, errorString);
        DidError = true;
    }

    glGetShaderiv(fs, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        glGetShaderInfoLog(fs, 512, nullptr, errorString);
        DidError = true;
    }

    if (DidError)
        return;

    program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glBindFragDataLocation(program, 0, "outColor");
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (!status)
    {
        glGetProgramInfoLog(program, 512, nullptr, errorString);
        DidError = true;
        return;
    }

    DidError = false;
}

Shader::~Shader()
{
    // glDeleteShader(program);
    glDeleteShader(fs);
    glDeleteShader(vs);
    // Not all programs use geometry shader
    // if it's used, delete it
    if (gs != -1)
        glDeleteShader(gs);
}

GLuint Shader::Program()
{
    return program;
}

std::string Shader::GetError()
{
    return std::string(errorString);
}