#include "UITextBox.hh"

#include <iostream>

std::string blink_vs = R"glsl(
    #version 330 core
    layout(location = 0) in vec2 vsPosition;

    uniform mat4 modelViewProj;
    uniform float time;

    void main()
    {
        gl_Position = modelViewProj * vec4(vsPosition.xy, 1.0, 1.0);
    }
)glsl";

std::string blink_fs = R"glsl(
    #version 330 core
    
    out vec4 outColor;
    uniform vec4 color;

    uniform float time;

    void main()
    {
        outColor = vec4(color.xyz, abs(cos(time * 2)));
    }
)glsl";

UITextBox::UITextBox(vec2 position, vec2 size, GlyphSet* font)
    : UIControl(position, size), font(font), indexPos(0), index(0), line(0)
{
    if (!UITextBox::blink_material)
        UITextBox::blink_material = Material::QuickMaterial(blink_vs, blink_fs);
    cursor = CursorMode::IBeam;
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
        context.RenderUIQuad(vec2(position.x + padding.x + indexPos, position.y + 4), vec2(1, size.y - 12), 0, GetTheme()->Secondary(), blink_material);
    context.RenderUIText(value, vec2(position.x + padding.x, position.y + (size.y / 1.5)), 0, font, GetTheme()->OnSurface(), material);
}

Material* UITextBox::blink_material = nullptr;