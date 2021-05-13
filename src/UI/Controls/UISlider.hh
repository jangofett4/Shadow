#pragma once

#include "../UIControl.hh"

class UISlider : public UIControl
{
    int value;
    vec4 handleColor;

public:
    UISlider(vec2 position, float length);

    int GetValue();
    void SetValue(int value);

    void Render(RenderContext& context);
};