#include "UIWindow.hh"

UIWindow::UIWindow(vec2 position, vec2 size)
    :   UIControl(position, size)
{
    cursor = CursorMode::DontAffect;
}

UIWindow::~UIWindow()
{
    for (auto it = controls.begin(); it != controls.end(); it++)
        delete (*it);
}

void UIWindow::Render(RenderContext& context)
{
    context.RenderUIQuad(position, size, 0, GetTheme()->Background(), material);
    UIControl::Render(context);
}