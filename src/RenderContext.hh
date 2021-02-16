#pragma once

#include "Components/Material.hh"
#include "Components/Transform.hh"
#include "Graphics/FontFace.hh"

#include <glm/glm.hpp>
#include <GL/glew.h>

using namespace glm;

class RenderContext
{
    // Renderer is single threaded, this is a safe & effective way of storing these variables
    // However render context should be created only once to avoid a lot of OpenGL buffer overhead
    GLuint text_vao, text_vbo_position, text_vbo_texcoord;

public:
    mat4 view;
    mat4 projection;
    mat4 screen;
    
    RenderContext(mat4, mat4, mat4);
    RenderContext();
    ~RenderContext();

    void SetupTriple(Material*, GLuint);
    
    void UseProgram(Shader*);
    void UseProgram(Material*);
    void ApplyMaterial(Material*);
    void BindVAO(GLuint);

    mat4 ModelViewProjection3D(Transform*);
    mat4 ModelViewProjection2D(Transform*);
    mat4 ModelScreenProjection(Transform*);

    void RenderText(std::string string, vec2 position, GlyphSet* font, Material* material);
    void RenderArrays(size_t count);
    void RenderArrays(size_t count, GLenum mode);
};