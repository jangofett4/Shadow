SET(PWD ${CMAKE_CURRENT_LIST_DIR})
set(SRC
    GameObject.cc
    AssetManager.cc
    LayerManager.cc
    RenderContext.cc
    Game.cc
    Scene.cc
    TestGame.cc
)

include("Graphics/CMakeLists.txt")
include("Components/CMakeLists.txt")
# include("Math/CMakeLists.txt") # handled by glm
include("Helper/CMakeLists.txt")
include("Input/CMakeLists.txt")
include("UI/CMakeLists.txt")

set(CMAKE_CXX_FLAGS
    # Freetype
    "-I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/harfbuzz -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include"
)

if (WIN32)
# Windows get special treatment, you may want to change these two paths with proper paths in your system
# include path should contain required include files (glfw, glew, freetype and lodepng)
# lib path should contain required lib files (same as above)
# also you will want to copy .dll files into executable folder in order for it to work
include_directories("C:/Library/include")
link_directories("C:/Library/lib")
LIST(APPEND SRC 
    lodepng.cpp
)
endif(WIN32)

add_executable(program ${SRC})

if (WIN32)
target_link_libraries(program opengl32)
target_link_libraries(program glfw3dll.lib)
target_link_libraries(program glew32.lib)
target_link_libraries(program freetype.lib)
elseif (UNIX)
target_link_libraries(program GL)
target_link_libraries(program glfw)
target_link_libraries(program GLEW)
target_link_libraries(program lodepng)
target_link_libraries(program freetype)
endif (WIN32)