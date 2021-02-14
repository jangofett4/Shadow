#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class InputMouse
{
    GLFWwindow* window;
public:
    InputMouse();

    void ResetMotion();
    void ResetTo(double, double);

    bool IsPressed(int);
    bool IsReleased(int);

    bool IsLMBPressed();
    bool IsRMBPressed();
    bool IsMMBPressed();

    bool IsLMBReleased();
    bool IsRMBReleased();
    bool IsMMBReleased();

    double GetMouseScrollX();
    double GetMouseScrollY();

    double GetMouseX();
    double GetMouseY();
    double GetMouseMotionX();
    double GetMouseMotionY();
};