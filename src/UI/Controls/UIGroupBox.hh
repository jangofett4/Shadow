#pragma once

#include "../UIControl.hh"

class UIGroupBox : public UIControl
{
public:
    GlyphSet* font;
    std::wstring title;

    UIGroupBox(std::wstring title, GlyphSet* font);

    void Render(RenderContext& context);
};