#include "RenderContext.hh"

#include "Graphics/Shaders/TextShader.hh"
#include "Graphics/Shaders/UIShader.hh"

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

static vec2 quad_vbo_texcoords[] = {
    vec2(0.f, 0.f), vec2(0.f, 1.f), vec2(1.f, 0.f),
    vec2(1.f, 0.f), vec2(0.f, 1.f), vec2(1.f, 1.f),
};

static vec2 quad_vbo_verts[] = {
    vec2(0, 0), vec2(0, 1), vec2(1, 0),
    vec2(1, 0), vec2(0, 1), vec2(1, 1),
};

static vec2 circle_vbo_verts[] = {
    #include "Circle360.inc"
};

static vec2 rect_vbo_verts[] = {
    vec2(0, 0), vec2(0, 1),
    vec2(0, 1), vec2(1, 1),
    vec2(1, 1), vec2(1, 0),
    vec2(1, 0), vec2(0, 0)
};

RenderContext::RenderContext(GameTime* time) : time(time)
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

    /* Untextured circle VAO & VBO */
    glGenVertexArrays(1, &circle_vao);
    glBindVertexArray(circle_vao);

    glGenBuffers(1, &circle_vbo_position);

    glBindBuffer(GL_ARRAY_BUFFER, circle_vbo_position);
    glBufferData(GL_ARRAY_BUFFER, 361 * sizeof(vec2), &circle_vbo_verts[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(0);

    /* Rectangle VAO & VBO */
    glGenVertexArrays(1, &rect_vao);
    glBindVertexArray(rect_vao);

    glGenBuffers(1, &rect_vbo_position);

    glBindBuffer(GL_ARRAY_BUFFER, rect_vbo_position);
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(vec2), &rect_vbo_verts[0], GL_STATIC_DRAW);
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

    uiShader = new Shaders::UIShader();
    uiMaterial = new Material(uiShader);
}

/*
RenderContext::RenderContext(mat4 view, mat4 proj, mat4 screen) : view(view), projection(proj), screen(screen)
{
    RenderContext(); // TODO: I DONT KNOW, CHECK L8R
}
*/

RenderContext::~RenderContext()
{
    glDeleteVertexArrays(1, &text_vao);
    glDeleteBuffers(1, &text_vbo_position);
    glDeleteBuffers(1, &text_vbo_uv);

    delete textMaterial;
    delete textShader;

    delete uiMaterial;
    delete uiShader;
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
    auto halfsize = transform->Scale / 2.0f;
    mat4 model(1.0f);
    model = glm::translate(model, transform->Position);
    model = glm::translate(model, vec3(halfsize.x, halfsize.y, 0));
    model = glm::rotate(model, glm::radians(transform->Rotation.x), vec3(.0f, .0f, 1.f));
    model = glm::translate(model, vec3(-halfsize.x, -halfsize.y, 0));
    model = glm::scale(model, transform->Scale);
    return screen * model;
}

mat4 RenderContext::ModelScreenProjection(vec2 position, vec2 size, float rotation)
{
    auto halfsize = size / 2.0f;
    mat4 model(1.0f);
    model = glm::translate(model, vec3(position.x, position.y, 0));
    model = glm::translate(model, vec3(halfsize.x, halfsize.y, 0));
    model = glm::rotate(model, glm::radians(rotation), vec3(0, 0, 1));
    model = glm::translate(model, vec3(-halfsize.x, -halfsize.y, 0));
    model = glm::scale(model, vec3(size.x, size.y, 1));
    return screen * model;
}

void RenderContext::Render2D(vec2 position, vec2 size, float rotation, Material* material)
{
    material->Value("modelViewProj", ModelViewProjection2D(position, size, rotation));
    material->Value("deltaTime", time->Delta);
    material->Value("time", time->GetSecondsSinceStart());
    SetupTriple(material, quad_vao);
    RenderArrays(6);
}

void RenderContext::Render2DTextured(vec2 position, vec2 size, float rotation, Material* material, Texture* texture)
{
    material->Value("modelViewProj", ModelViewProjection2D(position, size, rotation));
    material->Value("texture2D", texture);
    material->Value("deltaTime", time->Delta);
    material->Value("time", time->GetSecondsSinceStart());
    SetupTriple(material, quad_vao);
    RenderArrays(6);
}

void RenderContext::Render2DScreenspace(vec2 position, vec2 size, float rotation, Material* material)
{
    material->Value("modelViewProj", ModelScreenProjection(position, size, rotation));
    material->Value("deltaTime", time->Delta);
    material->Value("time", time->GetSecondsSinceStart());
    SetupTriple(material, quad_vao);
    RenderArrays(6);
}

void RenderContext::Render2DScreenspaceTextured(vec2 position, vec2 size, float rotation, Texture* texture, Material* material)
{
    if (!material)
        material = uiMaterial;
    material->Value("modelViewProj", ModelScreenProjection(position, size, rotation));
    material->Value("deltaTime", time->Delta);
    material->Value("time", time->GetSecondsSinceStart());
    material->Value("texture2D", texture);
    SetupTriple(material, quad_vao);
    RenderArrays(6);
}

void RenderContext::RenderUIQuad(vec2 position, vec2 size, float rotation, vec4 color, Material* material)
{
    if (!material)
        material = uiMaterial;
    material->Value("color", color);
    material->Value("modelViewProj", ModelScreenProjection(position, size, rotation));
    material->Value("deltaTime", time->Delta);
    material->Value("time", time->GetSecondsSinceStart());
    SetupTriple(material, quad_vao);
    RenderArrays(6);
}

void RenderContext::RenderUICircle(vec2 position, float radius, vec4 color, Material* material)
{
    if (!material)
        material = uiMaterial;
    auto r2 = radius / 2;
    material->Value("color", color);
    material->Value("modelViewProj", ModelScreenProjection(position + vec2(r2, r2), vec2(radius, radius)));
    material->Value("deltaTime", time->Delta);
    material->Value("time", time->GetSecondsSinceStart());
    SetupTriple(material, circle_vao);
    RenderArrays(361, GL_TRIANGLE_FAN);
}

void RenderContext::RenderUIRect(vec2 position, vec2 size, float rotation, GLfloat thickness, vec4 color, Material* material)
{
    if (!material)
        material = uiMaterial;
    material->Value("color", color);
    material->Value("modelViewProj", ModelScreenProjection(position, size, rotation));
    material->Value("deltaTime", time->Delta);
    material->Value("time", time->GetSecondsSinceStart());
    SetupTriple(material, rect_vao);
    glLineWidth(thickness);
    RenderArrays(8, GL_LINES);
}

// FIXME: This is stupidly un-optimized, reducing fps by 100+ in some cases
void RenderContext::RenderUIText(std::wstring string, vec2 position, float rotation, GlyphSet* font, vec4 color, Material* material)
{
    // TODO: use custom material if passed
    if (string.empty())
        return;
    auto gen = font->Text(string);
    
    UseProgram(textMaterial);
    
    textMaterial->Value("modelViewProj", ModelScreenProjection(vec2(0), vec2(1), rotation));   // No transformation for model itself.
    // textMaterial->Value("fsCharTexture", (Texture*)nullptr);
    textMaterial->Value("fsTextColor", color);
    auto samplerUniform = textMaterial->GetUniform("fsCharTexture");
    
    textMaterial->Value("deltaTime", time->Delta);
    textMaterial->Value("time", time->GetSecondsSinceStart());
    textMaterial->Apply();                          // Apply screen transformation for next draws


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

void RenderContext::RenderUIText(std::string string, vec2 position, float rotation, GlyphSet* font, vec4 color, Material* material)
{
    RenderUIText(std::wstring(string.begin(), string.end()), position, rotation, font, color, material);
}

void RenderContext::RenderArrays(size_t count)
{
    glDrawArrays(GL_TRIANGLES, 0, count);
}

void RenderContext::RenderArrays(size_t count, GLenum mode)
{
    glDrawArrays(mode, 0, count);
}