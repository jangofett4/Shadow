#pragma once

#include "../UIControl.hh"
#include "../../Graphics/FontFace.hh"

#include <string>

class UIToggleButton : public UIControl
{
    bool state;
public:
    std::string label;
    GlyphSet* font;

    UIToggleButton(std::string label, vec2 position, vec2 size, GlyphSet* font);
    
    bool GetState();

    void Render(RenderContext& context);
};