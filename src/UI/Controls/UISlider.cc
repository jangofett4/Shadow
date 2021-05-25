#include "UISlider.hh"

UISlider::UISlider(vec2 position, float length)
    : UIControl(position, vec2(length, 16)), value(0)
{
    focusable = true;
    cursor = CursorMode::Hand;

    events->MouseLeftHoldEvent.Subscribe([&](vec2* pos){
        value = (GetRelativePosition(*pos).x / size.x) * 100;
        _events.OnChangeEvent.CallAll(&value);
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
    context.RenderUIQuad(position, vec2(size.x, 6), 0, GetTheme()->Secondary(), material);
    context.RenderUICircle(position + vec2((value / 100.0f) * size.x, 0), 8, GetTheme()->SecondaryAlt(), material);
}