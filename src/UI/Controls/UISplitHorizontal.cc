#include "UISplitHorizontal.hh"

UISplitHorizontal::UISplitHorizontal()
    :   UIControl(vec2(), vec2(), vec4()),
        topControls(), bottomControls()
{
    anchor = AnchorMode::All;
    margin = vec2();
    padding = vec2();
    cursor = CursorMode::DontAffect;
}

UISplitHorizontal::~UISplitHorizontal()
{
    for (auto it = topControls.begin(); it != topControls.end(); it++)
        delete (*it);
    for (auto it = bottomControls.begin(); it != bottomControls.end(); it++)
        delete (*it);
}

void UISplitHorizontal::AddControl(UIControl* control, HorizontalSplitSide side)
{
    control->parent = this;
    if (side == HorizontalSplitSide::Top)
        topControls.push_back(control);
    else
        bottomControls.push_back(control);
}

void UISplitHorizontal::RemoveControl(UIControl* control)
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

void UISplitHorizontal::Render(RenderContext& context)
{
    for (auto it = topControls.begin(); it != topControls.end(); it++)
        (*it)->Render(context);
    for (auto it = bottomControls.begin(); it != bottomControls.end(); it++)
        (*it)->Render(context);
}

void UISplitHorizontal::UpdateLayout()
{
    UIControl::UpdateLayout();
    for (auto it = topControls.begin(); it != topControls.end(); it++)
    {
        auto control = *it;
        control->UpdateLayout(position, vec2(size.x, size.y / 2 - padding.y));
    }
    for (auto it = bottomControls.begin(); it != bottomControls.end(); it++)
    {
        auto control = *it;
        control->UpdateLayout(vec2(position.x, position.y + (size.y / 2) + padding.y), vec2(size.x, size.y / 2));
    }
}

void UISplitHorizontal::UpdateLayout(vec2 parentPos, vec2 parentSize)
{
    UIControl::UpdateLayout(parentPos, parentSize);
    for (auto it = topControls.begin(); it != topControls.end(); it++)
    {
        auto control = *it;
        control->UpdateLayout(position, vec2(size.x, size.y / 2 - padding.y));
    }
    for (auto it = bottomControls.begin(); it != bottomControls.end(); it++)
    {
        auto control = *it;
        control->UpdateLayout(vec2(position.x, position.y + (size.y / 2) + padding.y), vec2(size.x, size.y / 2));
    }
}

void UISplitHorizontal::ProcessEvents()
{
    UIControl::ProcessEvents();
    for (auto it = topControls.begin(); it != topControls.end(); it++)
        (*it)->ProcessEvents();
    for (auto it = bottomControls.begin(); it != bottomControls.end(); it++)
        (*it)->ProcessEvents();
}
void UISplitHorizontal::SetRoot(UIRoot* root)
{
    UIControl::SetRoot(root);
    this->root = root;
    for (auto it = topControls.begin(); it != topControls.end(); it++)
        (*it)->SetRoot(root);
    for (auto it = bottomControls.begin(); it != bottomControls.end(); it++)
        (*it)->SetRoot(root);
}

void UISplitHorizontal::ClearRoot()
{
    UIControl::ClearRoot();
    for (auto it = topControls.begin(); it != topControls.end(); it++)
        (*it)->ClearRoot();
    for (auto it = bottomControls.begin(); it != bottomControls.end(); it++)
        (*it)->ClearRoot();
}