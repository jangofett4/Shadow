#pragma once

#include "../UIControl.hh"

enum class HorizontalSplitSide
{
    Top,
    Bottom
};

class UISplitHorizontal : public UIControl
{
    std::vector<int> sides;
public:

    UISplitHorizontal();
    ~UISplitHorizontal();

    void AddControl(UIControl* control, HorizontalSplitSide side = HorizontalSplitSide::Top);
    void RemoveControl(UIControl* control);

    void Render(RenderContext& context);

    void UpdateLayout();
    void UpdateLayout(vec2 parentPos, vec2 parentSize);
    void ProcessEvents();

    void SetRoot(UIRoot* root);
    void ClearRoot();
};