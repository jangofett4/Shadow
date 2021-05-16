#include "UIButton.hh"

#include "UILabel.hh"

UILabel::UILabel(std::string label, vec2 position, GlyphSet* font)
    :   UIControl(position, vec2(font->size), vec4(0)),
        label(label), font(font)
{
    anchor = AnchorMode::Left | AnchorMode::Right | AnchorMode::Top;
}

void UILabel::Render(RenderContext& context)
{
    context.RenderUIText(label, vec2(position.x, position.y + (size.y / 2)), font, vec4(0, 0, 0, 1), material);
}