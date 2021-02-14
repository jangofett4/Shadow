#pragma once

class InputKeyboard
{
public:
    InputKeyboard();

    bool IsPressed(int);
    bool IsReleased(int);
};