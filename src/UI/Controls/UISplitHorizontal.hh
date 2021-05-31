#pragma once

#include "../UIControl.hh"

enum class HorizontalSplitSide
{
    Top,
    Bottom
};

class UISplitHorizontal : public UIControl
{
    std::vector<HorizontalSplitSide> sides;

public:
    UISplitHorizontal();

    void AddControl(UIControl* control);
    void AddControl(UIControl* control, HorizontalSplitSide side);
    
    void UpdateLayout();
};