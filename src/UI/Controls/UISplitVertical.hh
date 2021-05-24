#pragma once

#include "../UIControl.hh"

enum class VerticalSplitSide
{
    Left,
    Right
};

class UISplitVertical : public UIControl
{
public:

    UISplitVertical();

    void Render(RenderContext& context);

    void UpdateLayout();
    void UpdateLayout(vec2 parentPos, vec2 parentSize);
    void ProcessEvents();

    void SetRoot(UIRoot* root);
    void ClearRoot();
};