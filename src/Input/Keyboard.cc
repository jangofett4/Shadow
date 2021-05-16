#include "Input.hh"
#include "Keyboard.hh"

#include <GLFW/glfw3.h>

std::vector<std::function<void(int32_t*)>> keyPressTriggers;
std::vector<std::function<void(int32_t*)>> keyReleaseTriggers;
std::vector<std::function<void(uint32_t*)>> textTriggers;

void keyPressCallback(GLFWwindow*, int key, int, int action, int)
{
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
        for (auto it = keyPressTriggers.begin(); it != keyPressTriggers.end(); it++)
            (*it)(&key);
    else if (action == GLFW_RELEASE)
        for (auto it = keyReleaseTriggers.begin(); it != keyReleaseTriggers.end(); it++)
            (*it)(&key);
}

void textCallback(GLFWwindow*, uint32_t unicode)
{
    for (auto it = textTriggers.begin(); it != textTriggers.end(); it++)
        (*it)(&unicode);
}

InputKeyboard::InputKeyboard() : window(Input::game->GetWindow())
{
    keyPressTriggers = std::vector<std::function<void(int32_t*)>>();
    keyReleaseTriggers = std::vector<std::function<void(int32_t*)>>();
    textTriggers = std::vector<std::function<void(uint32_t*)>>();
    
    glfwSetKeyCallback(window, keyPressCallback);
    glfwSetCharCallback(window, textCallback);
}

bool InputKeyboard::IsPressed(int key)
{
    return glfwGetKey(Input::game->GetWindow(), key) == GLFW_PRESS;
}

bool InputKeyboard::IsReleased(int key)
{
    return glfwGetKey(Input::game->GetWindow(), key) == GLFW_RELEASE;
}

void InputKeyboard::InstallKeyPressTrigger(std::function<void(int32_t*)> trigger) 
{
    keyPressTriggers.push_back(trigger);
}

void InputKeyboard::InstallKeyReleaseTrigger(std::function<void(int32_t*)> trigger)
{
    keyReleaseTriggers.push_back(trigger);
}

void InputKeyboard::InstallTextTrigger(std::function<void(uint32_t*)> trigger)
{
    textTriggers.push_back(trigger);
}