#include "UIStack.hh"

UIStack::UIStack()
    :   UIControl(vec2(), vec2())
{
    anchor = AnchorMode::All;
    cursor = CursorMode::DontAffect;
    margin = vec2();
}

void UIStack::UpdateLayout()
{
    UIControl::UpdateSelfLayout();

    int i = 0;
    int sum = 0;
    auto posback = position;

    for (auto it = controls.begin(); it != controls.end(); it++, i++)
    {
        auto control = *it;
        position.y += sum;
        control->UpdateLayout();
        sum += control->GetOriginalSize().y + padding.y;
    }

    position = posback;
}

/*
void UIStack::UpdateLayout(vec2 parentPos, vec2 parentSize)
{
    UIControl::UpdateLayout(parentPos, parentSize);
    UIControl::UpdateSelfLayout();

    int i = 0;
    int sum = 0;
    for (auto it = controls.begin(); it != controls.end(); it++, i++)
    {
        auto control = *it;
        control->UpdateLayout(vec2(position.x, position.y + sum), size);
        sum += control->GetOriginalSize().y + padding.y;
    }
}
*/