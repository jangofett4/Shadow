#pragma once

#include <chrono>

#define CLOCKS_PER_MILLISEC (CLOCKS_PER_SEC / 1000)

struct GameTime
{
    std::chrono::duration<float> FrameTime;
    float Delta;
};