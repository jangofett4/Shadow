#include "UIWindow.hh"
#include "../../GameObject.hh"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// const std::string Renderer3D::Name() { return "3D Renderer"; }
const std::string UIWindow::Name() { return "UI Box"; }

UIWindow::UIWindow(Material* mat) : UIElement(mat)
{
    vec2 vertices[] = {
        vec2(0, 0), vec2(0, 1), vec2(1, 0),
        vec2(1, 0), vec2(0, 1), vec2(1, 1),
    };

    glGenVertexArrays(1, &vao_win);
    glBindVertexArray(vao_win);

    glGenBuffers(1, &vbo_win);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_win);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
    /* Position */ mat->shader->VertexAttribPointer(0, 2, GL_FLOAT, false, 0, 0);

    glGenVertexArrays(1, &vao_handle);
    glBindVertexArray(vao_handle);

    glGenBuffers(1, &vao_handle);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_win);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
    /* Position */ mat->shader->VertexAttribPointer(0, 2, GL_FLOAT, false, 0, 0);
}

void UIWindow::Render(RenderContext& context)
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
    glBindVertexArray(vao_win);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}