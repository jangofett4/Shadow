SET(PWD ${CMAKE_CURRENT_LIST_DIR})
LIST(APPEND SRC 
    ${PWD}/UITheme.cc
    ${PWD}/UIControl.cc
    ${PWD}/UIRoot.cc
    # ${PWD}/UIEventManager
    # ${PWD}/UILayoutEngine
)

include("${PWD}/Controls/CMakeLists.txt")