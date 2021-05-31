#include "UIGroupBox.hh"

UIGroupBox::UIGroupBox(std::wstring title, GlyphSet* font)
    : UIControl(vec2(), vec2()), title(title), font(font)
{
    anchor = AnchorMode::All;
    margin = vec2();
}

void UIGroupBox::Render(RenderContext& context)
{
    context.RenderUIQuad(position, size, 0, GetTheme()->Surface(), material);
    context.RenderUIRect(position, size, 0, 1, GetTheme()->SecondaryAlt(), material);
    context.RenderUIQuad(vec2(position.x + 20, position.y - 8), vec2(7 * title.length() + 8, 16), 0, GetTheme()->Surface(), material);
    context.RenderUIText(title, vec2(position.x + 24, position.y + 4), 0, font, GetTheme()->OnSurface(), material);
    
    //UIControl::Render(context);
}