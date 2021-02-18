#pragma once

#include "../UIControl.hh"

class UIStack : public UIControl
{
    std::vector<UIControl*> controls;
public:
    UIStack();
    ~UIStack();

    void AddControl(UIControl* control);
    void RemoveControl(UIControl* control);

    void Render(RenderContext& context);

    void UpdateLayout();
    void UpdateLayout(vec2 parentPos, vec2 parentSize);
    
    void ProcessEvents();
};