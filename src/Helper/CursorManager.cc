#include "CursorManager.hh"

#include "../Game.hh"

std::unordered_map<uint32_t, GLFWcursor*> loadedCursors;
GLFWwindow* window;

void CursorManager::Init(Game* game)
{
    loadedCursors = std::unordered_map<uint32_t, GLFWcursor*>();
    window = game->GetWindow();
}

void CursorManager::Cleanup()
{
    for (auto it = loadedCursors.begin(); it != loadedCursors.end(); it++)
        glfwDestroyCursor(it->second);
}

GLFWcursor* CursorManager::GetCursor(uint32_t mode)
{
    auto found = loadedCursors.find(mode);
    if (found == loadedCursors.end())
    {
        auto newcursor = glfwCreateStandardCursor(mode);
        loadedCursors.insert({ mode, newcursor });
        return newcursor;
    }
    return found->second;
}

void CursorManager::SetCursor(uint32_t mode)
{
    // Useful for some cases
    if (mode == CursorMode::DontAffect)
        return;
    auto cursor = GetCursor(mode);
    glfwSetCursor(window, cursor);
}