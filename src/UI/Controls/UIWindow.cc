#include "UIWindow.hh"

UIWindow::UIWindow(vec2 position, vec2 size)
    :   UIControl(position, size, vec4(1, 1, 1, 0.9)),
        controls()
{
}

UIWindow::~UIWindow()
{
    for (auto it = controls.begin(); it != controls.end(); it++)
        delete (*it);
}

void UIWindow::AddControl(UIControl* control)
{
    // TODO: check, we dont want to assign a new parent to an object that has a parent
    control->parent = this;
    controls.push_back(control);
}

void UIWindow::RemoveControl(UIControl* control)
{
    // TODO: check, we dont want to randomly de-assign parents
    control->parent = nullptr;
    controls.erase(std::find(controls.begin(), controls.end(), control));
}

void UIWindow::Render(RenderContext& context)
{
    context.SetUIColor(color);
    context.Render2DScreenspace(position, size, 0);
    for (auto it = controls.begin(); it != controls.end(); it++)
        (*it)->Render(context);
}

void UIWindow::UpdateLayout()
{
    UIControl::UpdateLayout();
    for (auto it = controls.begin(); it != controls.end(); it++)
        (*it)->UpdateLayout();
}

void UIWindow::ProcessEvents()
{
    UIControl::ProcessEvents();
    for (auto it = controls.begin(); it != controls.end(); it++)
        (*it)->ProcessEvents();
}