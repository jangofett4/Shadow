#include "UIProgressBar.hh"

UIProgressBar::UIProgressBar(vec2 position, float length)
    : UIControl(position, vec2(length, 16), vec4(0.5, 0.5, 0.5, 0.9)), value(0)
{
    hoverColor = vec4(0.6, 0.6, 0.6, 0.9);
    clickColor = vec4(0.7, 0.7, 0.7, 0.9);
    focusable = true;
    cursor = CursorMode::Hand;

    anchor = AnchorMode::Left | AnchorMode::Right | AnchorMode::Top;

    events->MouseHoverEvent.Subscribe([&](auto){
        handleColor = hoverColor;
    });

    events->MouseLeftHoldEvent.Subscribe([&](vec2* pos){
        handleColor = clickColor;
        value = (GetRelativePosition(*pos).x / size.x) * 100;
        _events.OnChangeEvent.CallAll(&value);
    });
    
    events->MouseExitEvent.Subscribe([&](auto){
        handleColor = GetOriginalColor();
    });
}

int UISlider::GetValue()
{
    return value;
}

void UISlider::SetValue(int newval)
{
    if (newval > 100)
        value = 100;
    else if (newval < 0)
        value = 0;
    else
        value = newval;
}

void UISlider::Render(RenderContext& context)
{
    context.RenderUIQuad(position, vec2(size.x, 6), 0, color, material);
    context.RenderUICircle(position + vec2((value / 100.0f) * size.x, 0), 8, handleColor, material);
}