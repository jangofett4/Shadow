SET(PWD ${CMAKE_CURRENT_LIST_DIR})
LIST(APPEND SRC 
    ${PWD}/UIControl
    ${PWD}/UIContainer
    ${PWD}/UILayoutEngine
)

include("${PWD}/Controls/CMakeLists.txt")