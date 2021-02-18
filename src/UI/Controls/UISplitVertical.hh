#pragma once

#include "../UIControl.hh"

enum class VerticalSplitSide
{
    Left,
    Right
};

class UISplitVertical : public UIControl
{
    std::vector<UIControl*> topControls;
    std::vector<UIControl*> bottomControls;
public:

    UISplitVertical();
    ~UISplitVertical();

    void AddControl(UIControl* control, VerticalSplitSide side = VerticalSplitSide::Left);
    void RemoveControl(UIControl* control);

    void Render(RenderContext& context);

    void UpdateLayout();
    void UpdateLayout(vec2 parentPos, vec2 parentSize);
    void ProcessEvents();
};