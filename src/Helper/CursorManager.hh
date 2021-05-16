#pragma once

#include "../Game.hh"

#include <unordered_map>
#include <stdint.h>

class Game;

struct CursorMode
{
    enum : uint32_t
    {
        Hidden      = 0,
        Default     = GLFW_ARROW_CURSOR,
        IBeam       = GLFW_IBEAM_CURSOR,
        Crosshair   = GLFW_CROSSHAIR_CURSOR,
        Hand        = GLFW_HAND_CURSOR,
        HResize     = GLFW_HRESIZE_CURSOR,
        VResize     = GLFW_VRESIZE_CURSOR,
        DontAffect  = 0x10001000
    };
};

class CursorManager
{    
public:
    static void Init(Game* game);
    static void Cleanup();

    static GLFWcursor* GetCursor(uint32_t mode);
    static void SetCursor(uint32_t mode);
};