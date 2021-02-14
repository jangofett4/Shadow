#include "RenderContext.hh"

RenderContext::RenderContext(mat4 view, mat4 proj, mat4 screen) : view(view), projection(proj), screen(screen) { }