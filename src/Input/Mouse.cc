#include "Mouse.hh"
#include "Input.hh"

// Mouse scroll related variables
double scrollX = 0, scrollY = 0;

// Mouse position related variables
double X = 0, Y = 0;
double prevX = 0, prevY = 0;
double motionX = 0, motionY = 0;

// Mouse button related variables
bool leftHold, rightHold, middleHold;
bool leftReleased, rightReleased, middleReleased;
bool leftClicked, rightClicked, middleClicked;

void mousePositionCallback(GLFWwindow*, double x, double y)
{
    prevX = X;
    prevY = Y;

    X = x;
    Y = y;

    motionX = X - prevX;
    motionY = Y - prevY;
}

void mouseButtonCallback(GLFWwindow*, int button, int action, int mods)
{
    // TODO: implement all buttons
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
        {
            leftHold = true;
            leftReleased = false;
        }
        else // release
        {
            if (leftHold)
                leftClicked = true;
            leftHold = false;
            leftReleased = true;
        }
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        if (action == GLFW_PRESS)
        {
            rightHold = true;
            rightReleased = false;
        }
        else // release
        {
            if (rightHold)
                rightClicked = true;
            rightHold = false;
            rightReleased = true;
        }
    }
    else if (button == GLFW_MOUSE_BUTTON_MIDDLE)
    {
        if (action == GLFW_PRESS)
        {
            middleHold = true;
            middleReleased = false;
        }
        else // release
        {
            if (middleHold)
                middleClicked = true;
            middleHold = false;
            middleReleased = true;
        }
    }
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
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
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
    leftHold = leftReleased = leftClicked = false;
    rightHold = rightReleased = rightClicked = false;
    middleHold = middleReleased = middleClicked = false;
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
    return leftHold;
}

bool InputMouse::IsRMBPressed()
{
    return rightHold;
}

bool InputMouse::IsMMBPressed()
{
    return middleHold;
}

bool InputMouse::IsLMBReleased()
{
    return leftReleased;
}

bool InputMouse::IsRMBReleased()
{
    return rightReleased;
}

bool InputMouse::IsMMBReleased()
{
    return middleReleased;
}

bool InputMouse::IsLMBClicked()
{
    return leftClicked;
}

bool InputMouse::IsRMBClicked()
{
    return rightClicked;
}

bool InputMouse::IsMMBClicked()
{
    return middleClicked;
}

double InputMouse::GetMouseScrollX()
{
    return scrollX;
}

double InputMouse::GetMouseScrollY()
{
    return scrollY;
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
    return motionX;
}

double InputMouse::GetMouseMotionY()
{
    return motionY;
}

void InputMouse::FrameReset()
{
    motionX = motionY = 0;
    scrollX = scrollY = 0;
    leftClicked = rightClicked = middleClicked = false;
}