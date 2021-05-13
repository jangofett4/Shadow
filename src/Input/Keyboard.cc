#include "Input.hh"
#include "Keyboard.hh"

#include <GLFW/glfw3.h>

InputKeyboard::InputKeyboard() { }

bool InputKeyboard::IsPressed(int key)
{
    return glfwGetKey(Input::game->GetWindow(), key) == GLFW_PRESS;
}

bool InputKeyboard::IsReleased(int key)
{
    return glfwGetKey(Input::game->GetWindow(), key) == GLFW_RELEASE;
}