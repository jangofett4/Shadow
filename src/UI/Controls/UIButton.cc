#include "UIButton.hh"

UIButton::UIButton(std::string label, vec2 position, vec2 size, Material* material, GlyphSet* font)
    :   UIControl(position, size, material,
            vec4(0.5, 0.5, 0.5, 0.9),
            vec4(0.6, 0.6, 0.6, 0.9),
            vec4(0.7, 0.7, 0.7, 0.9)
        ),
        label(label), font(font)
{
    anchor = AnchorMode::Left | AnchorMode::Right;

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
    material->Value("color", color);
    context.Render2DScreenspace(position, size, 0, material);
    context.RenderText(label, vec2(position.x + margin.x, position.y + (size.y / 1.5)), vec4(1), font);
}