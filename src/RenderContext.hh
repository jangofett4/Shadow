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
    GLuint text_vao, text_vbo_position, text_vbo_uv;

    // Generic Quad VAO & VBO, useful for 2D rendering
    GLuint quad_vao, quad_vbo_position;

    // Generic Quad VAO & VBO, useful for textured 2D rendering
    GLuint quad_textured_vao, quad_textured_vbo_position, quad_textured_vbo_uv;

    // Generic Circle VAO & VBO, useful for 2D UI
    GLuint circle_vao, circle_vbo_position;

    // Generic rectangle VAO & VBO, useful for 2D UI
    GLuint rect_vao, rect_vbo_position;

    // Generic text shader & material
    Material* textMaterial; Shader* textShader;

    // Generic UI shader & material
    Material* uiMaterial; Shader* uiShader;

    // GameTime, useful to provide time information to shaders
    GameTime* time;
    
public:
    mat4 view;
    mat4 projection;
    mat4 screen;
    
    //RenderContext(mat4, mat4, mat4);
    RenderContext(GameTime* time);
    ~RenderContext();

    
    void SetupTriple(Material*, GLuint);
    
    void UseProgram(Shader*);
    void UseProgram(Material*);
    void ApplyMaterial(Material*);
    void BindVAO(GLuint);

    mat4 ModelViewProjection3D(Transform*);
    mat4 ModelViewProjection3D(vec3 position, vec3 rotation, vec3 scale);

    mat4 ModelViewProjection2D(Transform*);
    mat4 ModelViewProjection2D(vec2 position, vec2 size, float rotation = 0);

    mat4 ModelScreenProjection(Transform*);
    mat4 ModelScreenProjection(vec2 position, vec2 size, float rotation = 0);

    void Render2D(vec2 position, vec2 size, float rotation, Material* material);
    void Render2DTextured(vec2 position, vec2 size, float rotation, Material* material, Texture* texture);

    void Render2DScreenspace(vec2 position, vec2 size, float rotation, Material* material);
    void Render2DScreenspaceTextured(vec2 position, vec2 size, float rotation, Texture* texture, Material* material);
    
    void RenderUIQuad(vec2 position, vec2 size, float rotation, vec4 color, Material* material);
    void RenderUICircle(vec2 positon, float radius, vec4 color, Material* material);
    void RenderUIRect(vec2 position, vec2 size, float rotation, GLfloat thickness, vec4 color, Material* material);

    void RenderUIText(std::wstring string, vec2 position, float rotation, GlyphSet* font, vec4 color, Material* material);
    void RenderUIText(std::string string, vec2 position, float rotation, GlyphSet* font, vec4 color, Material* material);

    void RenderArrays(size_t count);
    void RenderArrays(size_t count, GLenum mode);
};