#include "FontFace.hh"

#include <algorithm>
#include <iostream>
#include <iomanip>

#include <glm/glm.hpp>

using namespace glm;

std::wstring loadedChars = LR"chars(
 1234567890abcçdefgğhıijklmnoöpqrsştuüvwxyzABCÇDEFGĞHIİJKLMNOÖPQRSŞTUÜVWXYZ!'^%&()[]{}=?_<>£#$½\|+-*/.,:
)chars";

GlyphSet::GlyphSet(size_t size) : size(size), glyphs() { }

GlyphSet::~GlyphSet()
{
    for (auto it = glyphs.begin(); it != glyphs.end(); it++)
    {
        auto id = it->second.texture->GetTextureID();
        glDeleteTextures(1, &id); // TODO: yeah this is wrong
        delete it->second.texture;
    }
}

std::vector<Glyph> GlyphSet::Text(std::wstring string)
{
    std::vector<Glyph> output;
    for (auto c : string)
    {
        auto found = glyphs.find(c);
        if (found == glyphs.end())
            output.push_back(qmark);
        else
            output.push_back(found->second);
    }

    return output;
}

size_t GlyphSet::Length(std::wstring string)
{
    return Length(string, string.size());
}

size_t GlyphSet::Length(std::wstring string, size_t to)
{
    size_t len = 0;
    for (size_t i = 0; i < to && i < string.size(); i++)
    {
        auto c = string[i];
        auto found = glyphs.find(c);
        len += found->second.size.x;
    }

    return len;
}

FontFace::FontFace(FT_Face face) : face(face)
{ }

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
        switch(c)
        {
            case ' ':
            {
                size_t w, h, t, l;
                w = face->glyph->bitmap.width;
                h = face->glyph->bitmap.rows;
                t = face->glyph->bitmap_top;
                l = face->glyph->bitmap_left;
                
                uint8_t* space_texture = new uint8_t[w * h]();

                auto data = 
                set->glyphs.emplace(c, Glyph {
                    .texture = new Texture(w, h, space_texture, GL_RED, GL_RED),
                    .size = vec2(w, h),
                    .bearing = vec2(l, t),
                    .offset = (size_t)face->glyph
                });
                
                delete[] space_texture;
                break;
            }
            default:
            {
                error = FT_Load_Char(face, c, FT_LOAD_RENDER);
                if (error)
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
                auto tex = new Texture(w, h, face->glyph->bitmap.buffer, GL_RED, GL_RED);
                set->glyphs.emplace(c, Glyph {
                    .texture = tex,
                    .size = vec2(w, h),
                    .bearing = vec2(l, t),
                    .offset = (size_t)face->glyph->advance.x
                });
                break;
            }
        }
    }

    auto qmark = set->glyphs.find('?');
    set->qmark = (*qmark).second;

    return set;
}