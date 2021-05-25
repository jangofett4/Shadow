#include "UIProgressBar.hh"

UIProgressBar::UIProgressBar(vec2 position, float length)
    : UIControl(position, vec2(length, 16)), progress(0), progressWidth(0)
{
}

int UIProgressBar::GetProgress()
{
    return progress;
}

void UIProgressBar::SetProgress(int newprogress)
{
    if (newprogress > 100)
        progress = 100;
    else if (newprogress < 0)
        progress = 0;
    else
        progress = newprogress;
    progressWidth = (progress / 100.0) * size.x;
}

bool UIProgressBar::AddProgress(int value)
{
    auto newprogress = progress + value;
    auto result = true;
    if (newprogress > 100)
        progress = 100;
    else if (newprogress < 0)
        progress = 0;
    else
    {
        progress = newprogress;
        result = false;
    }
    progressWidth = (progress / 100) * size.x;
    return false;
}

void UIProgressBar::Render(RenderContext& context)
{
    context.RenderUIQuad(position, size, 0, GetTheme()->SecondaryAlt(), material);
    context.RenderUIQuad(position, vec2(progressWidth, size.y), 0, GetTheme()->Secondary(), material);
}