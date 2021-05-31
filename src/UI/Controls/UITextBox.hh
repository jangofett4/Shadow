#pragma once

#include "../UIControl.hh"

class UITextBox : public UIControl
{
    static Material* blink_material;
    
    std::wstring value;
    std::wstring showSlice;

    size_t indexPos;
    size_t index;
    size_t line;

public:
    GlyphSet* font;

    UITextBox(vec2 position, vec2 size, GlyphSet* font);

    std::wstring GetValue();
    void SetValue(std::wstring str);
    void Append(std::wstring str);
    void Prepend(std::wstring str);
    void Insert(std::wstring str, size_t at);

    void UpdateMetrics();

    void Render(RenderContext& context);

private:
    void HandleKeyPress();
};