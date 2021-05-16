#include "UIButton.hh"

UIButton::UIButton(std::string label, vec2 position, vec2 size, GlyphSet* font)
    :   UIControl(position, size, vec4(0.5, 0.5, 0.5, 0.9)),
        label(label), font(font)
{
    hoverColor = vec4(0.6, 0.6, 0.6, 0.9);
    clickColor =vec4(0.7, 0.7, 0.7, 0.9);
    focusable = true;
    
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
    context.RenderUIQuad(position, size, 0, color, material);
    context.RenderUIText(label, vec2(position.x + padding.x, position.y + (size.y / 1.5)), font, vec4(1), material);
}