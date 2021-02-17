#pragma once

#include "../UIControl.hh"
#include "../../Graphics/FontFace.hh"

#include <string>

class UIButton : public UIControl
{
public:
    vec4 color;
    std::string label;
    GlyphSet* font;

    UIButton(std::string label, vec2 position, vec2 size, Material* material, GlyphSet* font);

    void Render(RenderContext& context);
};