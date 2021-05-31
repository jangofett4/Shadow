#include "UISplitHorizontal.hh"

UISplitHorizontal::UISplitHorizontal()
    :   UIControl(vec2(), vec2()), sides()
{
    anchor = AnchorMode::All;
    margin = vec2();
}

void UISplitHorizontal::AddControl(UIControl* control)
{
    UIControl::AddControl(control);
    sides.push_back(HorizontalSplitSide::Top);
}

void UISplitHorizontal::AddControl(UIControl* control, HorizontalSplitSide side)
{
    UIControl::AddControl(control);
    sides.push_back(side);
}

void UISplitHorizontal::UpdateLayout()
{
    UIControl::UpdateSelfLayout();
    auto toppos = position - vec2(0, padding.y), topsize = vec2(size.x, size.y / 2);
    auto bottompos = vec2(position.x, position.y + size.y / 2 + padding.y), bottomsize = vec2(size.x, size.y / 2);

    auto posback = position;
    auto sizeback = size;
    
    size_t i = 0;
    for (auto it = controls.begin(); it != controls.end(); it++)
    {
        auto control = *it;
        auto side = sides[i];
        if (side == HorizontalSplitSide::Top)
        {
            position = toppos;
            size = topsize;
            control->UpdateLayout();
        }
        else
        {
            position = bottompos;
            size = bottomsize;
            control->UpdateLayout();
        }
        i++;
    }

    position = posback;
    size = sizeback;
}