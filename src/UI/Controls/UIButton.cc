#include "UIButton.hh"

UIButton::UIButton(std::string label, vec2 position, vec2 size, GlyphSet* font)
    :   UIControl(position, size, vec4(0.5, 0.5, 0.5, 0.9)),
        label(label), font(font)
{
    hoverColor = vec4(0.6, 0.6, 0.6, 0.9);
    clickColor =vec4(0.7, 0.7, 0.7, 0.9);
    
    anchor = AnchorMode::Left | AnchorMode::Right | AnchorMode::Top;

    events->MouseHoverEvent.Subscribe([&](auto){
        color = hoverColor;
    });

    events->MouseLeftHoldEvent.Subscribe([&](auto){
        color = clickColor;
    });
    
    events->MouseExitEvent.Subscribe([&](auto){
        color = GetOriginalColor();
    });
}

void UIButton::Render(RenderContext& context)
{
    context.SetUIColor(color);
    context.SetTextColor(vec4(1));
    context.Render2DScreenspace(position, size, 0);
    context.RenderText(label, vec2(position.x + padding.x, position.y + (size.y / 1.5)), font);
}