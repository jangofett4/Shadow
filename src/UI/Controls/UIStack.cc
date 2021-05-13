#include "UIStack.hh"

UIStack::UIStack()
    :   UIControl(vec2(), vec2(), vec4(0.5, 0.5, 0.5, 0.9)),
        controls()
{
    anchor = AnchorMode::All;
    margin = vec2();
}

UIStack::~UIStack()
{
    for (auto it = controls.begin(); it != controls.end(); it++)
        delete (*it);
}

void UIStack::AddControl(UIControl* control)
{
    // TODO: check, we dont want to assign a new parent to an object that has a parent
    control->parent = this;
    controls.push_back(control);
}

void UIStack::RemoveControl(UIControl* control)
{
    // TODO: check, we dont want to randomly de-assign parents
    control->parent = nullptr;
    controls.erase(std::find(controls.begin(), controls.end(), control));
}

void UIStack::Render(RenderContext& context)
{
    for (auto it = controls.begin(); it != controls.end(); it++)
        (*it)->Render(context);
}

void UIStack::UpdateLayout()
{
    UIControl::UpdateLayout();
    int i = 0;
    int sum = 0;
    for (auto it = controls.begin(); it != controls.end(); it++, i++)
    {
        auto control = *it;
        control->UpdateLayout(vec2(position.x, position.y + sum), size);
        sum += control->GetOriginalSize().y + padding.y;
    }
}

void UIStack::UpdateLayout(vec2 parentPos, vec2 parentSize)
{
    UIControl::UpdateLayout(parentPos, parentSize);
    int i = 0;
    int sum = 0;
    for (auto it = controls.begin(); it != controls.end(); it++, i++)
    {
        auto control = *it;
        control->UpdateLayout(vec2(position.x, position.y + sum), size);
        sum += control->GetOriginalSize().y + padding.y;
    }
}

void UIStack::ProcessEvents()
{
    UIControl::ProcessEvents();
    for (auto it = controls.begin(); it != controls.end(); it++)
        (*it)->ProcessEvents();
}