#include "UIWindow.hh"

UIWindow::UIWindow(vec2 position, vec2 size)
    :   UIControl(position, size, vec4(1, 1, 1, 0.9)),
        controls()
{
    cursor = CursorMode::DontAffect;
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
    context.RenderUIQuad(position, size, 0, color, material);
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

void UIWindow::SetRoot(UIRoot* root)
{
    UIControl::SetRoot(root);
    this->root = root;
    for (auto it = controls.begin(); it != controls.end(); it++)
        (*it)->SetRoot(root);
}

void UIWindow::ClearRoot()
{
    UIControl::ClearRoot();
    for (auto it = controls.begin(); it != controls.end(); it++)
        (*it)->ClearRoot();
}