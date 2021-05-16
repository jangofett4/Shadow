#pragma once

#include "../UIControl.hh"

class UIWindow : public UIControl
{
    std::vector<UIControl*> controls;

public:
    UIWindow(vec2 position, vec2 size);
    ~UIWindow();

    void AddControl(UIControl* control);
    void RemoveControl(UIControl* control);

    void Render(RenderContext& context);

    void UpdateLayout();
    void ProcessEvents();

    void SetRoot(UIRoot* root);
    void ClearRoot();
};