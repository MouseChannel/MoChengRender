#pragma once
#include "SDL.h"
#include "SoftRender/Helper/Instance.hpp"
#include "SoftRender/Math/DataStruct.hpp"
#include "SoftRender/Math/Math.hpp"

namespace SoftRender {
class Window;
class Texture;
class RenderManager : public Instance<RenderManager> {

public:
    RenderManager();
    ~RenderManager();
    void draw_point(Point2D point);
    void draw_line(Point2D start, Point2D end);
    void draw_triangle(Point2D a, Point2D b, Point2D c);
    void draw_image(std::shared_ptr<Texture> texture);
    void begin_frame();
    void end_frame();
    bool should_exit();

private:
    std::unique_ptr<Window> m_window;
};
}