#include "UISplitVertical.hh"

UISplitVertical::UISplitVertical()
    :   UIControl(vec2(), vec2(), vec4()),
        topControls(), bottomControls()
{
    anchor = AnchorMode::All;
    margin = vec2();
    padding = vec2();
}

UISplitVertical::~UISplitVertical()
{
    for (auto it = topControls.begin(); it != topControls.end(); it++)
        delete (*it);
    for (auto it = bottomControls.begin(); it != bottomControls.end(); it++)
        delete (*it);
}

void UISplitVertical::AddControl(UIControl* control, VerticalSplitSide side)
{
    control->parent = this;
    if (side == VerticalSplitSide::Left)
        topControls.push_back(control);
    else
        bottomControls.push_back(control);
}

void UISplitVertical::RemoveControl(UIControl* control)
{
    auto it = std::find(topControls.begin(), topControls.end(), control);
    if (it == topControls.end())
    {
        it = std::find(bottomControls.begin(), bottomControls.end(), control);
        bottomControls.erase(it);
    }
    else
        topControls.erase(it);
}

void UISplitVertical::Render(RenderContext& context)
{
    for (auto it = topControls.begin(); it != topControls.end(); it++)
        (*it)->Render(context);
    for (auto it = bottomControls.begin(); it != bottomControls.end(); it++)
        (*it)->Render(context);
}

void UISplitVertical::UpdateLayout()
{
    UIControl::UpdateLayout();
    for (auto it = topControls.begin(); it != topControls.end(); it++)
    {
        auto control = *it;
        control->UpdateLayout(position, vec2(size.x / 2 - padding.x, size.y));
    }
    for (auto it = bottomControls.begin(); it != bottomControls.end(); it++)
    {
        auto control = *it;
        control->UpdateLayout(vec2(position.x + (size.x / 2) + padding.x, position.y), vec2(size.x / 2, size.y));
    }
}

void UISplitVertical::UpdateLayout(vec2 parentPos, vec2 parentSize)
{
    UIControl::UpdateLayout(parentPos, parentSize);
    for (auto it = topControls.begin(); it != topControls.end(); it++)
    {
        auto control = *it;
        control->UpdateLayout(position, vec2(size.x / 2 - padding.x, size.y));
    }
    for (auto it = bottomControls.begin(); it != bottomControls.end(); it++)
    {
        auto control = *it;
        control->UpdateLayout(vec2(position.x + (size.x / 2) + padding.x, position.y), vec2(size.x / 2, size.y));
    }
}

void UISplitVertical::ProcessEvents()
{
    UIControl::ProcessEvents();
    for (auto it = topControls.begin(); it != topControls.end(); it++)
        (*it)->ProcessEvents();
    for (auto it = bottomControls.begin(); it != bottomControls.end(); it++)
        (*it)->ProcessEvents();
}