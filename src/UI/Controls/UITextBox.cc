#include "UITextBox.hh"

#include <iostream>

UITextBox::UITextBox(vec2 position, vec2 size, GlyphSet* font)
    : UIControl(position, size, vec4(0.5, 0.5, 0.5, 0.9)), indexPos(0), index(0), line(0)
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
            if (code == 259 && index > 0)
            {
                value = value.erase(--index, 1);
                UpdateMetrics();
            }
            else if (code == 263 && index > 0)
            {
                index--;
                UpdateMetrics();
            }
            else if (code == 262 && index < value.size())
            {
                index++;
                UpdateMetrics();
            }
            // 265 for up, 264 for down
        }
    });
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
    indexPos = this->font->Length(value, index + 1);
}

void UITextBox::Render(RenderContext& context)
{
    context.RenderUIQuad(position, size, 0, color, material);
    if (IsFocused())
        context.RenderUIQuad(vec2(position.x + indexPos, position.y + 4), vec2(1, size.y - 6), 0, vec4(1), material);
    context.RenderUIText(value, vec2(position.x + padding.x, position.y + (size.y / 1.5)), font, vec4(1), material);
}