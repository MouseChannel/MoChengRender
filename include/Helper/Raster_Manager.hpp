#pragma once
#include "FrameBuffer.hpp"
#include "Helper/Instance.hpp"
#include "Math/DataStruct.hpp"
#include "Math/Math.hpp"
#include "SDL.h"


namespace SoftRender {
class Window;
class Texture;
class RasterManager : public Instance<RasterManager> {

public:
    RasterManager();
    ~RasterManager();
    void draw_point(Pixel point);
    void draw_line(Pixel start, Pixel end);
    std::vector<std::pair<Vertex, float>> raster_triangle(std::pair<Vertex, float> a_and_w, std::pair<Vertex, float> b_and_w, std::pair<Vertex, float> c_and_w);
    void draw_image(std::shared_ptr<Texture> texture);
    void begin_frame();
    void end_frame();
    bool should_exit();
    void prepare_pipeline();

private:
    std::unique_ptr<Window> m_window;
};
}