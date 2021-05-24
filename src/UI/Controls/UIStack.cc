#include "UIStack.hh"

UIStack::UIStack()
    :   UIControl(vec2(), vec2())
{
    anchor = AnchorMode::All;
    margin = vec2();
    cursor = CursorMode::DontAffect;
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