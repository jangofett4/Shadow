#pragma once

#include <chrono>

#define CLOCKS_PER_MILLISEC (CLOCKS_PER_SEC / 1000)

class GameTime
{
    std::chrono::high_resolution_clock::time_point startTime;
    float timeSinceStart;
public:
    std::chrono::duration<float> FrameTime;
    float Delta;

    void Reset();
    void CalculateElapsed();

    float GetSecondsSinceStart();
};