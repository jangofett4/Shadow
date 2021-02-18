#include "UIWindow.hh"

UIWindow::UIWindow(vec2 position, vec2 size, Material* material)
    :   UIControl(position, size, material,
            vec4(1, 1, 1, 0.9),
            vec4(), vec4()
        )
{
    anchor = AnchorMode::Left | AnchorMode::Right | AnchorMode::Top | AnchorMode::Bottom;
}

UIWindow::~UIWindow() { }

void UIWindow::Render(RenderContext& context)
{
    material->Value("color", color);
    context.Render2DScreenspace(position, size, 0, material);
    for (auto it = controls.begin(); it != controls.end(); it++)
        (*it)->Render(context);
}