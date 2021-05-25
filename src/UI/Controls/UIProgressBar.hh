#pragma once

#include "../UIControl.hh"

class UIProgressBar : public UIControl
{
    int progress;
    float progressWidth;
    
public:
    UIProgressBar(vec2 position, float length);

    int GetProgress();
    void SetProgress(int progress);

    // Adds a value to progress, returns true if progress value hits 100 or 0
    // Both positive and negative values can be added to progress and they are bound checked
    bool AddProgress(int value);

    void Render(RenderContext& context);
};