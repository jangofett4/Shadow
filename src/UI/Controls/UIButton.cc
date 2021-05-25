#include "UIButton.hh"

UIButton::UIButton(std::string label, vec2 position, vec2 size, GlyphSet* font)
    :   UIControl(position, size),
        label(label), font(font)
{
    focusable = true;
}

void UIButton::Render(RenderContext& context)
{
    context.RenderUIQuad(position, size, 0, GetTheme()->Secondary(), material);
    context.RenderUIText(label, vec2(position.x + padding.x, position.y + (size.y / 1.5)), 0, font, GetTheme()->OnSecondary(), material);
}