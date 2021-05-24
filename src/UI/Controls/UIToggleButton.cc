#include "UIToggleButton.hh"

UIToggleButton::UIToggleButton(std::string label, vec2 position, vec2 size, GlyphSet* font)
    :   UIControl(position, size),
        label(label), font(font)
{
    focusable = true;
    state = false;

    events->MouseClickEvent.Subscribe([&](auto){
        state = !state;
        _events.OnStateChange.CallAll(&state);
    });
}

bool UIToggleButton::GetState()
{
    return state;
}

void UIToggleButton::Render(RenderContext& context)
{
    auto color = state ? GetTheme()->SecondaryAlt() : GetTheme()->Secondary();
    context.RenderUIQuad(position, size, 0, color, material);
    context.RenderUIText(label, vec2(position.x + padding.x, position.y + (size.y / 1.5)), font, GetTheme()->OnSecondary(), material);
}