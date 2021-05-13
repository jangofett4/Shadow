#pragma once

#include <GL/glew>
#include <GLFW/glfw3.h>
#include <vector>

class InputKeyboard
{
    GLFWwindow* window;
public:
    InputKeyboard();

    bool IsPressed(int);
    bool IsReleased(int);

    void FrameReset();
};