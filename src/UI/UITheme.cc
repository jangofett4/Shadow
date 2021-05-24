#include "UITheme.hh"

// This looks ugly, I dont even know anymore
// Won't affect the performace one bit, its all compiled
// And even probably staticcally linked

UITheme::UITheme(
    vec4 primary, vec4 secondary, vec4 primary_alt, vec4 secondary_alt,
    vec4 background, vec4 surface,
    vec4 onprimary, vec4 onsecondary,
    vec4 onbackground, vec4 onsurface
) : color_primary(primary), color_secondary(secondary), color_primary_alt(primary_alt), color_secondary_alt(secondary_alt),
    color_on_primary(onprimary), color_on_secondary(onsecondary),
    color_background(background), color_surface(surface), color_on_background(onbackground), color_on_surface(onsurface)
{}

vec4 UITheme::Primary() { return color_primary; }
vec4 UITheme::PrimaryAlt() { return color_primary_alt; }

vec4 UITheme::Secondary() { return color_secondary; }
vec4 UITheme::SecondaryAlt() { return color_secondary_alt; }

vec4 UITheme::Background() { return color_background; }
vec4 UITheme::Surface() { return color_surface; }
vec4 UITheme::OnPrimary() { return color_on_primary; }
vec4 UITheme::OnSecondary() { return color_on_secondary; }
vec4 UITheme::OnBackground() { return color_on_background; }
vec4 UITheme::OnSurface() { return color_on_surface; }

// Colors & Theme idea taken from https://material.io/design/color/the-color-system.html
UITheme* MaterialDefaultTheme()
{
    // Use some alpha for text, otherwise text becomes super aliased
    return new UITheme(
        // Primary, Secondary, PrimaryAlt, SecondaryAlt
        vec4(Hex2Rgb4(6200EEFF)), vec4(Hex2Rgb4(03DAC6FF)), vec4(Hex2Rgb4(9A66f4FF)), vec4(Hex2Rgb4(92E9DCFF)),
        // Background, Surface
        vec4(Hex2Rgb4(FFFFFFFF)), vec4(Hex2Rgb4(FFFFFFFF)),
        // OnPrimary, OnSecondary
        vec4(Hex2Rgb4(FFFFFFDD)), vec4(Hex2Rgb4(000000DD)),
        // OnBackground, OnSurface
        vec4(Hex2Rgb4(000000DD)), vec4(Hex2Rgb4(000000DD))
    );
}