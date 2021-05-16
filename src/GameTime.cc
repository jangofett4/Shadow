#include "GameTime.hh"

void GameTime::Reset()
{
    startTime = std::chrono::high_resolution_clock::now();
    timeSinceStart = 0;
}

void GameTime::CalculateElapsed()
{
    timeSinceStart = (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTime)).count() / 1000.0f;
}

float GameTime::GetSecondsSinceStart()
{
    return timeSinceStart;
}