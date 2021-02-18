SET(PWD ${CMAKE_CURRENT_LIST_DIR})
LIST(APPEND SRC 
    ${PWD}/UIControl
    ${PWD}/UIRoot
    # ${PWD}/UIEventManager
    # ${PWD}/UILayoutEngine
)

include("${PWD}/Controls/CMakeLists.txt")