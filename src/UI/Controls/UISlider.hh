#pragma once

#include "../UIControl.hh"

class UISlider : public UIControl
{
    int value;
    vec4 handleColor;

public:
    struct {
        CallbackStack<int> OnChangeEvent {};
    } _events;

    UISlider(vec2 position, float length);

    int GetValue();
    void SetValue(int value);

    void Render(RenderContext& context);
};