#pragma once

#include "../UIControl.hh"
#include "../../Graphics/FontFace.hh"

#include <string>

class UILabel : public UIControl
{
public:
    std::string label;
    GlyphSet* font;

    UILabel(std::string label, vec2 position, GlyphSet* font);

    void Render(RenderContext& context);
};