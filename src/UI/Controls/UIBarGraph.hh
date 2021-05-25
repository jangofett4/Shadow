#pragma once

#include "../UIControl.hh"

class UIBarGraph : public UIControl
{
public:
    std::vector<double> data;
    GlyphSet* font;

    UIBarGraph(vec2 position, vec2 size, GlyphSet* font);

    void Render(RenderContext& context);
};