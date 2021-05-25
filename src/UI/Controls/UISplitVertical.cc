#include "UISplitVertical.hh"

UISplitVertical::UISplitVertical()
    :   UIControl(vec2(), vec2())
{
    anchor = AnchorMode::All;
}

void UISplitVertical::AddControl(UIControl* control)
{
    UIControl::AddControl(control);
    sides.push_back(VerticalSplitSide::Left);
}

void UISplitVertical::AddControl(UIControl* control, VerticalSplitSide side)
{
    UIControl::AddControl(control);
    sides.push_back(side);
}

void UISplitVertical::UpdateLayout()
{
    UIControl::UpdateSelfLayout();
    auto leftpos = position, leftsize = vec2(size.x / 2 - padding.x, size.y);
    auto rightpos = vec2(position.x + (size.x / 2) + padding.x, position.y), rightsize = vec2(size.x / 2, size.y);
    
    auto posback = position;
    auto sizeback = size;
    
    size_t i = 0;
    for (auto it = controls.begin(); it != controls.end(); it++)
    {
        auto control = *it;
        auto side = sides[i];
        if (side == VerticalSplitSide::Left)
        {
            position = leftpos;
            size = leftsize;
            control->UpdateLayout();
        }
        else
        {
            position = rightpos;
            size = rightsize;
            control->UpdateLayout();
        }
        i++;
    }

    position = posback;
    size = sizeback;
}