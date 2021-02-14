#include "FontFace.hh"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include <glm/glm.hpp>

std::string loadedChars = "1234567890abcdefghijklmopqrstuxyzABCDEFGHIJKLMNOPQRTSUVWXYZ";

GlyphSet::GlyphSet(size_t size) : size(size), glyphs() { }

GlyphSet::~GlyphSet()
{
    for (auto it = glyphs.begin(); it != glyphs.end(); it++)
        glDeleteTextures(1, &it->second.texture); // TODO: yeah this is wrong
}

FontFace::FontFace(FT_Face face) : face(face)
{
}

FontFace::~FontFace()
{
    for (auto it = loadedSets.begin(); it != loadedSets.end(); it++)
        delete *it;

    FT_Done_Face(face);
}

GlyphSet* FontFace::LoadSize(size_t height)
{
    auto it = std::find_if(loadedSets.begin(), loadedSets.end(), [height](auto x){ return x->size == height; });
    if (it != loadedSets.end())
        return *it;

    auto set = new GlyphSet(height);
    FT_Set_Pixel_Sizes(face, 0, height);
    FT_Error error;
    for (auto c : loadedChars)
    {
        if (!(error = FT_Load_Char(face, c, FT_LOAD_RENDER)))
        {
            std::cout << FT_Error_String(error) << std::endl;
            delete set;
            return nullptr;
        }
        size_t w, h, t, l;
        w = face->glyph->bitmap.width;
        h = face->glyph->bitmap.rows;
        t = face->glyph->bitmap_top;
        l = face->glyph->bitmap_left;

        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            w,
            h,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        set->glyphs.emplace(c, Glyph {
            .texture = texture,
            .size = glm::vec2(w, h),
            .bearing = glm::vec2(l, t),
            .offset = (size_t)face->glyph->advance.x
        });
    }

    return set;
}