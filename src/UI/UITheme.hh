#pragma once

#include <glm/glm.hpp>

// Statically compiled HTML color code to rgb4 converter
#define Hex2Rgb4(hex) ((0x ## hex >> 24) & 0xff) / 255.0f, ((0x ## hex >> 16) & 0xff) / 255.0f, ((0x ## hex >> 8) & 0xff) / 255.0f, ((0x ## hex) & 0xff) / 255.0f

// Statically compiled HTML color code to rgb3 converter, no alpha
#define Hex2Rgb3(hex) ((0x ## hex >> 16) & 0xff) / 255.0f, ((0x ## hex >> 8) & 0xff) / 255.0f, ((0x ## hex) & 0xff) / 255.0f

using namespace glm;

class UITheme
{
    const vec4 color_primary, color_secondary, color_on_primary, color_on_secondary;
    const vec4 color_primary_alt, color_secondary_alt;

    const vec4 color_background, color_surface, color_on_background, color_on_surface;

public:
    UITheme(
        vec4 primary, vec4 secondary, vec4 primary_alt, vec4 secondary_alt,
        vec4 background, vec4 surface,
        vec4 onprimary, vec4 onsecondary,
        vec4 onbackground, vec4 onsurface
    );

    // Original material theme is much more complicated than this colors
    // I've stripped down some stuff to make it more usable in this context
    // Dynamic accent colors are simply discarded, instead a static variant is used

    vec4 Primary();
    vec4 PrimaryAlt();
    
    vec4 Secondary();
    vec4 SecondaryAlt();

    vec4 Background();
    vec4 Surface();
    vec4 OnPrimary();
    vec4 OnSecondary();
    vec4 OnBackground();
    vec4 OnSurface();
};

UITheme* MaterialDefaultTheme();