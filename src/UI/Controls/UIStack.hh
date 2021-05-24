#pragma once

#include "../UIControl.hh"

class UIStack : public UIControl
{
public:
    UIStack();

    void UpdateLayout();
    void UpdateLayout(vec2 parentPos, vec2 parentSize);
};