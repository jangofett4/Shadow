#pragma once

#include "../UIControl.hh"

class UIWindow : public UIControl
{
public:
    vec4 color;

    UIWindow(vec2 position, vec2 size, Material* material);
    ~UIWindow();

    void Render(RenderContext& context);
};