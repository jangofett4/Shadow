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

set(CMAKE_CXX_FLAGS
    # Freetype
    "-I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/harfbuzz -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include"
)

add_executable(program ${SRC})
target_link_libraries(program GL)
target_link_libraries(program glfw)
target_link_libraries(program GLEW)
target_link_libraries(program lodepng)
target_link_libraries(program freetype)