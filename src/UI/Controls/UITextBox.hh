#pragma once

#include "../UIControl.hh"

class UITextBox : public UIControl
{
    std::string value;

public:
    UITextBox(vec2 position, vec2 size);

    std::string GetValue();
    void SetValue(std::string value);
    void Append(std::string value);
    void Prepend(std::string value);
    void Insert(std::string value, size_t index);

    void Render(RenderContext& context);

private:
    void HandleKeyPress();
};