#pragma once

#include "Keyboard.hh"
#include "Mouse.hh"
#include "../Game.hh"

class Game;

class Input
{
    friend class InputKeyboard;
    friend class InputMouse;

    static Game* game;
public:
    static InputKeyboard* Keyboard;
    static InputMouse* Mouse;

    static void Init(Game*);
    static void Cleanup();
};