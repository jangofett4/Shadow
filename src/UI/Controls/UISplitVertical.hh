#pragma once

#include "../UIControl.hh"

enum class VerticalSplitSide
{
    Left,
    Right
};

class UISplitVertical : public UIControl
{
    std::vector<VerticalSplitSide> sides;

public:
    UISplitVertical();

    void AddControl(UIControl* control);
    void AddControl(UIControl* control, VerticalSplitSide side);

    void UpdateLayout();
    //void UpdateLayout(vec2 parentPos, vec2 parentSize);
};