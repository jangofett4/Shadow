#include "UITextBox.hh"

#include <iostream>

UITextBox::UITextBox(vec2 position, vec2 size, GlyphSet* font)
    : UIControl(position, size), indexPos(0), index(0), line(0)
{
    this->font = font;
    cursor = CursorMode::IBeam;
    anchor = AnchorMode::Left | AnchorMode::Right | AnchorMode::Top;
    focusable = true;

    value = std::wstring();
    showSlice = std::wstring();

    events->SetupTextEvent([&](uint32_t* unicode){
        const wchar_t ch = (wchar_t)(*unicode);

        if (IsFocused())
        {
            this->value.insert(index++, 1, ch);
            indexPos = this->font->Length(this->value, this->index);
        }
    });

    events->SetupKeyPressEvent([&](int32_t* codeptr){
        auto code = *codeptr;
        std::cout << code << " ";
        if (IsFocused())
        {
            if (code == 259 && index > 0) // Backspace
            {
                value = value.erase(--index, 1);
                UpdateMetrics();
            }
            else if (code == 263 && index > 0) // Left rrow
            {
                index--;
                UpdateMetrics();
            }
            else if (code == 262 && index < value.size()) // Right arrow
            {
                index++;
                UpdateMetrics();
            }
            else if (code == 268) // Home
            {
                index = 0;
                UpdateMetrics();
            }
            else if (code == 269) // End
            {
                index = value.size();
                UpdateMetrics();
            }

            // 265 for up, 264 for down
        }
    });
}

std::wstring UITextBox::GetValue()
{
    return value;
}

void UITextBox::SetValue(std::wstring str)
{
    value = str;
    index = 0;
    line = 0;
}

void UITextBox::Append(std::wstring str)
{
    value += str;
    index += str.size();
}

void UITextBox::Prepend(std::wstring str)
{
    value = str + value;
    index = 0;
}

void UITextBox::Insert(std::wstring str, size_t at)
{
    value = value.insert(index, str);
    index = at;
}

void UITextBox::UpdateMetrics()
{
    indexPos = this->font->Length(value, index);
}

void UITextBox::Render(RenderContext& context)
{
    auto color = IsFocused() ? GetTheme()->SecondaryAlt() : GetTheme()->Secondary();
    context.RenderUIQuad(vec2(position.x, position.y + size.y - 2), vec2(size.x, 2), 0, color, material);
    if (IsFocused())
        context.RenderUIQuad(vec2(position.x + padding.x + indexPos, position.y + 4), vec2(1, size.y - 12), 0, GetTheme()->Secondary(), material);
    context.RenderUIText(value, vec2(position.x + padding.x, position.y + (size.y / 1.5)), font, GetTheme()->OnSurface(), material);
}