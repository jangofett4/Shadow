#include "Mouse.hh"
#include "Input.hh"

// Mouse scroll related variables
double scrollX = 0, scrollY = 0;

// Mouse position related variables
double X = 0, Y = 0;
double prevX = 0, prevY = 0;
double motionX = 0, motionY = 0;

void mousePositionCallback(GLFWwindow*, double x, double y)
{
    prevX = X;
    prevY = Y;

    X = x;
    Y = y;

    motionX = X - prevX;
    motionY = Y - prevY;
}

void mouseScrollCallback(GLFWwindow*, double x, double y)
{
    scrollX = x;
    scrollY = y;
}

InputMouse::InputMouse() : window(Input::game->GetWindow())
{
    glfwSetScrollCallback(window, mouseScrollCallback);
    glfwSetCursorPosCallback(window, mousePositionCallback);
}

void InputMouse::ResetMotion()
{
    motionX = 0;
    motionY = 0;
}

void InputMouse::ResetTo(double x, double y)
{
    ResetMotion();
    X = x;
    Y = y;
    prevX = x;
    prevY = y;
}

bool InputMouse::IsPressed(int button)
{
    return glfwGetMouseButton(window, button) == GLFW_PRESS;
}

bool InputMouse::IsReleased(int button)
{
    return glfwGetMouseButton(window, button) == GLFW_RELEASE;
}

bool InputMouse::IsLMBPressed()
{
    return glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
}

bool InputMouse::IsRMBPressed()
{
    return glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
}

bool InputMouse::IsMMBPressed()
{
    return glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS;
}

bool InputMouse::IsLMBReleased()
{
    return glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE;
}

bool InputMouse::IsRMBReleased()
{
    return glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE;
}

bool InputMouse::IsMMBReleased()
{
    return glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_RELEASE;
}

double InputMouse::GetMouseScrollX()
{
    double result = scrollX;
    scrollX = 0;
    return result;
}

double InputMouse::GetMouseScrollY()
{
    double result = scrollY;
    scrollY = 0;
    return result;
}

double InputMouse::GetMouseX()
{
    return X;
}

double InputMouse::GetMouseY()
{
    return Y;
}

double InputMouse::GetMouseMotionX()
{
    double result = motionX;
    motionX = 0;
    return result;
}

double InputMouse::GetMouseMotionY()
{
    double result = motionY;
    motionY = 0;
    return result;
}