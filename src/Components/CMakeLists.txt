SET(PWD ${CMAKE_CURRENT_LIST_DIR})
LIST(APPEND SRC 
    ${PWD}/Component.cc
    ${PWD}/Transform.cc
    ${PWD}/Camera.cc
    ${PWD}/Script.cc
    # ${PWD}/Renderer.cc
    ${PWD}/Material.cc
    ${PWD}/Renderer.cc
    ${PWD}/Renderer2D.cc
    ${PWD}/Renderer3D.cc
    ${PWD}/UIRenderer.cc
    ${PWD}/UIElement.cc
)

include("${PWD}/UI/CMakeLists.txt")