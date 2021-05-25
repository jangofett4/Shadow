#pragma once

#include "../UIControl.hh"

class UIGroupBox : public UIControl
{
public:
    GlyphSet* font;
    std::wstring title;

    UIGroupBox(vec2 position, vec2 size, std::wstring title, GlyphSet* font);

    void Render(RenderContext& context);
};