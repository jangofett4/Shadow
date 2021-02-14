#include "UIBox.hh"
#include "../../GameObject.hh"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// const std::string Renderer3D::Name() { return "3D Renderer"; }
const std::string UIBox::Name() { return "UI Box"; }

UIBox::UIBox(Material* mat) : UIElement(mat)
{
    vec2 vertices[] = {
        vec2(0, 0), vec2(0, 1), vec2(1, 0),
        vec2(1, 0), vec2(0, 1), vec2(1, 1),
    };

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
    /* Position */ mat->shader->VertexAttribPointer(0, 2, GL_FLOAT, false, 0, 0);
}

void UIBox::Render(const RenderContext& context)
{
    auto mat = GetMaterial();
    if (!mat)
        return;

    glUseProgram(mat->GetProgram());
    
    mat4 matModel(1.0f);
    matModel = glm::translate(matModel, Parent->transform->Position);
    matModel = glm::rotate(matModel, glm::radians(Parent->transform->Rotation.x), vec3(0.f, 0.f, 1.f));
    matModel = glm::scale(matModel, Parent->transform->Scale);

    mat->Value("modelViewProj", context.screen * matModel);
    mat->Apply();
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}