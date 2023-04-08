#pragma once
#include "SDL.h"
#include "SoftRender/FrameBuffer.hpp"
#include "SoftRender/Helper/Instance.hpp"
#include "SoftRender/Math/DataStruct.hpp"
#include "SoftRender/Math/Math.hpp"

namespace SoftRender {
class Window;
class Texture;
class RasterManager : public Instance<RasterManager> {

public:
    RasterManager();
    ~RasterManager();
    void draw_point(Pixel point);
    void draw_line(Pixel start, Pixel end);
    std::vector<std::pair<Point3D, float>> raster_triangle(std::pair<Point3D, float> a_and_w, std::pair<Point3D, float> b_and_w, std::pair<Point3D, float> c_and_w);
    void draw_image(std::shared_ptr<Texture> texture);
    void begin_frame();
    void end_frame();
    bool should_exit();
    void prepare_pipeline();

private:
    std::unique_ptr<Window> m_window;
};
}