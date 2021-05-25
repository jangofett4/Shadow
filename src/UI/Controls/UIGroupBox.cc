#include "UIGroupBox.hh"

UIGroupBox::UIGroupBox(vec2 position, vec2 size, std::wstring title, GlyphSet* font)
    : UIControl(position, size), title(title), font(font)
{
    anchor = AnchorMode::All;
}

void UIGroupBox::Render(RenderContext& context)
{
    context.RenderUIQuad(position, size, 0, GetTheme()->Surface(), material);
    context.RenderUIRect(position, size, 0, 1, GetTheme()->Primary(), material);
    context.RenderUIText(title, vec2(position.x + 24), 0, font, GetTheme()->OnSurface(), material);
    UIControl::Render(context);
}