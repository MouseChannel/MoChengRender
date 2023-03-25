#pragma once
#include "SDL.h"
#include "SoftRender/Helper/Instance.hpp"
#include "SoftRender/Math/Math.hpp"

namespace SoftRender {
class Window;
class RenderManager : public Instance<RenderManager> {

public:
    RenderManager();
    ~RenderManager();
    void draw_point(Point point);
    void draw_line(Point start, Point end);
    void draw_triangle(Point a, Point b, Point c);
    void begin_frame();
    void end_frame();
    bool should_exit();

private:
    std::unique_ptr<Window> m_window;
};
}