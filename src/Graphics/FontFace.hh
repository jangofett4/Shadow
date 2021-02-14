#pragma once

#include <vector>
#include <map>

#include <freetype2/ft2build.h>
#include FT_FREETYPE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

struct Glyph
{
    GLuint      texture;
    glm::vec2   size;
    glm::vec2   bearing;
    size_t      offset;
};

class GlyphSet
{
    friend class FontFace;

    std::map<wchar_t, Glyph> glyphs;
public:
    const size_t size;

    GlyphSet(size_t);
    ~GlyphSet();
};

class FontFace
{
    FT_Face face;

    std::vector<GlyphSet*> loadedSets;
public:

    FontFace(FT_Face);
    ~FontFace();

    GlyphSet* LoadSize(size_t);
};