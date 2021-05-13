#include "UITextBox.hh"

UITextBox::UITextBox(vec2 position, vec2 size)
    : UIControl(position, size, vec4(0.5, 0.5, 0.5, 0.9))
{

}

void UITextBox::Render(RenderContext& context)
{
    context.RenderUIQuad(position, size, 0, color);
}