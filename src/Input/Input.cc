#include "Input.hh"
#include "Keyboard.hh"
#include "Mouse.hh"

#include "../Game.hh"

Game* Input::game = nullptr;
InputKeyboard* Input::Keyboard = nullptr;
InputMouse* Input::Mouse = nullptr;

void Input::Init(Game* game)
{
    Input::game = game;
    glfwSetInputMode(game->GetWindow(), GLFW_STICKY_KEYS, true); // I have no clue
    
    // Initialize modules
    Input::Keyboard = new InputKeyboard();
    Input::Mouse = new InputMouse();
}

void Input::Cleanup()
{
    delete Input::Keyboard;
    delete Input::Mouse;

    // Its safe to assign them to nullptr
    // Later deleting nullptr's prevent segfault
    Input::Keyboard = nullptr;
    Input::Mouse = nullptr;
}