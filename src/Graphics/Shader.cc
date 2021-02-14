#include "Shader.hh"

Shader::Shader(const std::string vstext, const std::string fstext)
    : Shader(vstext.c_str(), fstext.c_str()) { }

Shader::Shader(const char* vstext, const char* fstext) : attribs({})
{
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
}

GLuint Shader::Program()
{
    return program;
}

std::string Shader::GetError()
{
    return std::string(errorString);
}

void Shader::VertexAttribPointer(int location, size_t size, GLenum type, bool normalize, GLsizei stride, void* offset)
{
    glUseProgram(program); // TODO: unsure if this is how this is supposed to work, check later
    glVertexAttribPointer(location, size, type, normalize, stride, offset);
    glEnableVertexAttribArray(location);
    // attribs.push_back(attrib);
}

void Shader::EnableVertexAttribArray(int location)
{
    glUseProgram(program); // TODO: yeah
    glEnableVertexAttribArray(location);
}