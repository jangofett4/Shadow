#pragma once

#include <string>
#include <mutex>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
// #include <glm/glm.hpp>

#include "Scene.hh"
#include "AssetManager.hh"
#include "Input.hh"

class Game
{
    const int width;
    const int height;
    GLFWwindow* Window;
    const GLFWvidmode* videoMode;
    Scene* CurrentScene;
    
    std::mutex* GameMutex;
    
    std::string ErrorString;
    volatile bool Exit;
public:
    bool DidError;

    AssetManager* Assets;
    
    Game(const char*, int, int);
    ~Game();

    GLFWwindow* GetWindow() const;

    std::string GetError();
    void LoadScene(Scene*);
    void Start();

    void LockCursor();
    void ReleaseCursor();
};