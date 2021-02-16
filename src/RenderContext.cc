#include "RenderContext.hh"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

static vec2 text_vbo_texcoord_verts[] = {
    vec2(0.f, 0.f), vec2(0.f, 1.f), vec2(1.f, 0.f),
    vec2(1.f, 0.f), vec2(0.f, 1.f), vec2(1.f, 1.f),
};

RenderContext::RenderContext()
{
    glGenVertexArrays(1, &text_vao);
    glBindVertexArray(text_vao);

    glGenBuffers(1, &text_vbo_position);
    glGenBuffers(1, &text_vbo_texcoord);

    glBindBuffer(GL_ARRAY_BUFFER, text_vbo_position);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(vec2), nullptr, GL_DYNAMIC_DRAW); // will be changed a lot
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, text_vbo_texcoord);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(vec2), &text_vbo_texcoord_verts[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(1);
}

RenderContext::RenderContext(mat4 view, mat4 proj, mat4 screen) : view(view), projection(proj), screen(screen)
{
    RenderContext(); // TODO: I DONT KNOW, CHECK L8R
}

RenderContext::~RenderContext()
{
    glDeleteVertexArrays(1, &text_vao);
    glDeleteBuffers(1, &text_vbo_position);
    glDeleteBuffers(1, &text_vbo_texcoord);
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

mat4 RenderContext::ModelViewProjection2D(Transform* transform)
{
    mat4 model(1.0f);
    model = glm::translate(model, transform->Position);
    model = glm::rotate(model, glm::radians(transform->Rotation.x), vec3(.0f, .0f, 1.f));
    model = glm::scale(model, transform->Scale);
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

void RenderContext::RenderText(std::string string, vec2 position, GlyphSet* font, Material* material)
{
    auto gen = font->Text(string);
    
    UseProgram(material);
    
    material->Value("modelViewProj", screen); // No transformation for model itself.
    material->Apply();                        // Apply screen transformation for next draws
    material->Value("charTexture", (Texture*)nullptr);

    auto samplerUniform = material->GetUniform("charTexture");

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(text_vao);
    
    for (auto ch : gen)
    {
        vec2 verts[] = {
            vec2(position.x, position.y - ch.bearing.y), vec2(position.x, position.y + ch.size.y - ch.bearing.y), vec2(position.x + ch.size.x, position.y - ch.bearing.y),
            vec2(position.x + ch.size.x, position.y - ch.bearing.y), vec2(position.x, position.y + ch.size.y - ch.bearing.y), vec2(position.x + ch.size.x, position.y + ch.size.y - ch.bearing.y)
        };
        
        material->Value("charTexture", ch.texture);
        material->ApplyUniform(samplerUniform);
        
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