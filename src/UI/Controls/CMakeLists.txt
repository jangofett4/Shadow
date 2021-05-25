SET(PWD ${CMAKE_CURRENT_LIST_DIR})
LIST(APPEND SRC 
    ${PWD}/UIWindow.cc
    ${PWD}/UIButton.cc
    ${PWD}/UILabel.cc
    ${PWD}/UIToggleButton.cc
    ${PWD}/UISlider.cc
    ${PWD}/UITextBox.cc
    ${PWD}/UIStack.cc
    ${PWD}/UIProgressBar.cc
    # Made listbox into a template class, this is not needed
    # ${PWD}/UIListBox.cc
    # TODO: these two need special attention, fix them
    # ${PWD}/UISplitHorizontal.cc
    # ${PWD}/UISplitVertical.cc
)