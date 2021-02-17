#include "RenderContext.hh"
#include "Graphics/Shaders/TextShader.hh"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

static vec2 quad_vbo_texcoords[] = {
    vec2(0.f, 0.f), vec2(0.f, 1.f), vec2(1.f, 0.f),
    vec2(1.f, 0.f), vec2(0.f, 1.f), vec2(1.f, 1.f),
};

static vec2 quad_vbo_verts[] = {
    vec2(0, 0), vec2(0, 1), vec2(1, 0),
    vec2(1, 0), vec2(0, 1), vec2(1, 1),
};

RenderContext::RenderContext()
{
    /* Text VAO & VBOs */
    glGenVertexArrays(1, &text_vao);
    glBindVertexArray(text_vao);

    glGenBuffers(1, &text_vbo_position);
    glGenBuffers(1, &text_vbo_uv);

    glBindBuffer(GL_ARRAY_BUFFER, text_vbo_position);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(vec2), nullptr, GL_DYNAMIC_DRAW); // will be changed a lot
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, text_vbo_uv);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(vec2), &quad_vbo_texcoords[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(1);

    /* Untextured quad VAO & VBO */
    glGenVertexArrays(1, &quad_vao);
    glBindVertexArray(quad_vao);
    
    glGenBuffers(1, &quad_vbo_position);

    glBindBuffer(GL_ARRAY_BUFFER, quad_vbo_position);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(vec2), &quad_vbo_verts[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(0);

    /* Textured quad VAO & VBO */
    glGenVertexArrays(1, &quad_textured_vao);
    glBindVertexArray(quad_textured_vao);
    
    glGenBuffers(1, &quad_textured_vbo_position);
    glGenBuffers(1, &quad_textured_vbo_uv);

    glBindBuffer(GL_ARRAY_BUFFER, quad_textured_vbo_position);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(vec2), &quad_vbo_verts[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, quad_textured_vbo_uv);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(vec2), &quad_vbo_texcoords[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(1);

    textShader = new Shaders::TextShader();
    textMaterial = new Material(textShader);
}

RenderContext::RenderContext(mat4 view, mat4 proj, mat4 screen) : view(view), projection(proj), screen(screen)
{
    RenderContext(); // TODO: I DONT KNOW, CHECK L8R
}

RenderContext::~RenderContext()
{
    glDeleteVertexArrays(1, &text_vao);
    glDeleteBuffers(1, &text_vbo_position);
    glDeleteBuffers(1, &text_vbo_uv);

    delete textMaterial;
    delete textShader;
}

void RenderContext::SetupTriple(Material* mat, GLuint vao)
{
    UseProgram(mat);
    BindVAO(vao);
    ApplyMaterial(mat);
}

void RenderContext::UseProgram(Shader* shader)
{
    glUseProgram(shader->Program());
}

void RenderContext::UseProgram(Material* mat)
{
    glUseProgram(mat->shader->Program());
}

void RenderContext::ApplyMaterial(Material* mat)
{
    mat->Apply();
}

void RenderContext::BindVAO(GLuint vao)
{
    glBindVertexArray(vao);
}

mat4 RenderContext::ModelViewProjection3D(Transform* transform)
{
    mat4 model(1.0f);
    model = glm::translate(model, transform->Position);
    model = glm::rotate(model, glm::radians(transform->Rotation.x), vec3(1.f, 0.f, 0.f));
    model = glm::rotate(model, glm::radians(transform->Rotation.y), vec3(0.f, 1.f, 0.f));
    model = glm::rotate(model, glm::radians(transform->Rotation.z), vec3(0.f, 0.f, 1.f));
    model = glm::scale(model, transform->Scale);

    return projection * view * model;
}

mat4 RenderContext::ModelViewProjection3D(vec3 position, vec3 rotation, vec3 scale)
{
    mat4 model(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(rotation.x), vec3(1.f, 0.f, 0.f));
    model = glm::rotate(model, glm::radians(rotation.y), vec3(0.f, 1.f, 0.f));
    model = glm::rotate(model, glm::radians(rotation.z), vec3(0.f, 0.f, 1.f));
    model = glm::scale(model, scale);

    return projection * view * model;
}

mat4 RenderContext::ModelViewProjection2D(Transform* transform)
{
    mat4 model(1.0f);
    model = glm::translate(model, transform->Position);
    model = glm::rotate(model, glm::radians(transform->Rotation.x), vec3(.0f, .0f, 1.f));
    model = glm::scale(model, transform->Scale);
    return projection * view * model;
}

mat4 RenderContext::ModelViewProjection2D(vec2 position, vec2 size, float rotation)
{
    mat4 model(1.0f);
    model = glm::translate(model, vec3(position.x, position.y, 0));
    model = glm::rotate(model, glm::radians(rotation), vec3(0, 0, 1));
    model = glm::scale(model, vec3(size.x, size.y, 1));
    return projection * view * model;
}

mat4 RenderContext::ModelScreenProjection(Transform* transform)
{
    mat4 model(1.0f);
    model = glm::translate(model, transform->Position);
    model = glm::rotate(model, glm::radians(transform->Rotation.x), vec3(.0f, .0f, 1.f));
    model = glm::scale(model, transform->Scale);
    return screen * model;
}

mat4 RenderContext::ModelScreenProjection(vec2 position, vec2 size, float rotation)
{
    mat4 model(1.0f);
    model = glm::translate(model, vec3(position.x, position.y, 0));
    model = glm::rotate(model, glm::radians(rotation), vec3(0, 0, 1));
    model = glm::scale(model, vec3(size.x, size.y, 1));
    return screen * model;
}

void RenderContext::Render2D(vec2 position, vec2 size, float rotation, Material* material)
{
    material->Value("modelViewProj", ModelViewProjection2D(position, size, rotation));
    SetupTriple(material, quad_vao);
    RenderArrays(6);
}

void RenderContext::Render2DTextured(vec2 position, vec2 size, float rotation, Material* material, Texture* texture)
{
    material->Value("modelViewProj", ModelViewProjection2D(position, size, rotation));
    material->Value("texture2D", texture);
    SetupTriple(material, quad_vao);
    RenderArrays(6);
}

void RenderContext::Render2DScreenspace(vec2 position, vec2 size, float rotation, Material* material)
{
    material->Value("modelViewProj", ModelScreenProjection(position, size, rotation));
    SetupTriple(material, quad_vao);
    RenderArrays(6);
}

void RenderContext::Render2DScreenspaceTextured(vec2 position, vec2 size, float rotation, Material* material, Texture* texture)
{
    material->Value("modelViewProj", ModelScreenProjection(position, size, rotation));
    material->Value("texture2D", texture);
    SetupTriple(material, quad_vao);
    RenderArrays(6);
}

void RenderContext::RenderText(std::string string, vec2 position, vec4 color, GlyphSet* font)
{
    auto gen = font->Text(string);
    
    UseProgram(textMaterial);
    
    textMaterial->Value("modelViewProj", screen);   // No transformation for model itself.
    textMaterial->Value("fsTextColor", color);      // Text color applied only once, all chars use same
    textMaterial->Apply();                          // Apply screen transformation for next draws
    textMaterial->Value("fsCharTexture", (Texture*)nullptr);

    auto samplerUniform = textMaterial->GetUniform("fsCharTexture");

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(text_vao);
    
    for (auto ch : gen)
    {
        vec2 verts[] = {
            vec2(position.x, position.y - ch.bearing.y), vec2(position.x, position.y + ch.size.y - ch.bearing.y), vec2(position.x + ch.size.x, position.y - ch.bearing.y),
            vec2(position.x + ch.size.x, position.y - ch.bearing.y), vec2(position.x, position.y + ch.size.y - ch.bearing.y), vec2(position.x + ch.size.x, position.y + ch.size.y - ch.bearing.y)
        };
        
        textMaterial->Value("fsCharTexture", ch.texture);
        textMaterial->ApplyUniform(samplerUniform);
        
        glBindBuffer(GL_ARRAY_BUFFER, text_vbo_position);
        glBufferSubData(GL_ARRAY_BUFFER, 0, 6 * sizeof(vec2), &verts[0]);
        RenderArrays(6);

        position.x += ch.size.x; // for next character
    }
}

void RenderContext::RenderArrays(size_t count)
{
    glDrawArrays(GL_TRIANGLES, 0, count);
}

void RenderContext::RenderArrays(size_t count, GLenum mode)
{
    glDrawArrays(mode, 0, count);
}