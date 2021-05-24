# Shadow Game Engine
This is a personal project of mine to try and implement a game engine in C++.
This game engine currently uses OpenGL for rendering, but Vulkan support might be added later.
As of right now project is mostly cross platform. Required tools:
 - C++ Compiler (clang is recommended)
 - CMake
 - Ninja
 - (possibly) GNU Make
 
Required libraries:
 - GLFW 3
 - GLEW
 - GLM
 - lodepng
 - freetype2

## Compiling
Use VSCode CMake tools:
1. `Command Palette > CMake: Configure`
2. `Command Palette > CMake: Build` **OR** `F7` to build
3. `Command Palette > CMake: Debug` **OR** `Ctrl + F5` to debug

## Features
 - Shaders & Materials
 - 3D and (partial) UI rendering
 - Truetype loading & (partial) rendering
 - Textures
 - Layers
 - Asset manager
 - Component support
 - Scripts (in C++, later maybe Lua)
Most stuff that makes game engine a game engine is not implemented yet. Also an editor is in plans.

## Goals
To implement a basic game engine. Not to make a competitive game engine, this is mostly done to learn 3D & game programming.

## License
GNU GPL v3

## Support
Send me a quintillion dogecoins.
