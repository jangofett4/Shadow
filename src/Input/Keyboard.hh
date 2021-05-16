#pragma once

#include <GL/glew>
#include <GLFW/glfw3.h>
#include <vector>
#include "../CallbackStack.hh"

class InputKeyboard
{
    GLFWwindow* window;

public:
    InputKeyboard();

    bool IsPressed(int);
    bool IsReleased(int);

    void FrameReset();

    void InstallKeyPressTrigger(std::function<void(int32_t*)> trigger);
    void InstallKeyReleaseTrigger(std::function<void(int32_t*)> trigger);

    void InstallTextTrigger(std::function<void(uint32_t*)> trigger);
};