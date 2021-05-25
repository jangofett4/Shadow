#pragma once

#include "../UIControl.hh"

class UIWindow : public UIControl
{
public:
    UIWindow(vec2 position, vec2 size);

    void Render(RenderContext& context);
};