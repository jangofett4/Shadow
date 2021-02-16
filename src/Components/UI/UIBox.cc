#include "UIBox.hh"
#include "../../GameObject.hh"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const std::string UIBox::Name() { return "UI Box"; }

UIBox::UIBox(Material* mat, GlyphSet* font) : UIElement(mat), font(font)
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
    /* Position */ glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, 0); glEnableVertexAttribArray(0);
}

void UIBox::Render(RenderContext& context)
{
    auto mat = GetMaterial();
    if (!mat)
        return;

    mat->Value("modelViewProj",
        context.ModelScreenProjection(Parent->transform)
    );
    context.SetupTriple(mat, vao);
    mat->Apply();
    context.RenderArrays(6);
}