#include "Helper/Raster_Manager.hpp"
#include "Image.hpp"
#include "Math/DataStruct.hpp"
#include "Math/Math.hpp"
#include "Texture.hpp"
#include "Window.hpp"

namespace SoftRender {

RasterManager::RasterManager()
{
    m_window.reset(new Window);
}
RasterManager::~RasterManager() { }
bool RasterManager::should_exit() { return m_window->should_exit(); }
void RasterManager::begin_frame() { m_window->begin_frame(); }
void RasterManager::end_frame() { m_window->end_frame(); }
void RasterManager::draw_point(Pixel pos)
{
    // int r = pos.color.r();
    // int g = pos.color.g();
    // int b = pos.color.b();
    m_window->draw_point(pos);
}
void RasterManager::draw_line(Pixel start, Pixel end)
{
    // brensenham
    if (start.pos.x() > end.pos.x()) {
        math::swap(start, end);
    }
    int y_flag = start.pos.y() > end.pos.y() ? -1 : 1;
    int x_flag = 1;
    auto deltaX = end.pos.x() - start.pos.x();
    auto deltaY = (end.pos.y() - start.pos.y()) * y_flag;
    bool swapxy = false;

    if (deltaY > deltaX) {
        math::swap(start.pos.x(), start.pos.y());
        math::swap(end.pos.x(), end.pos.y());
        math::swap(deltaX, deltaY);
        math::swap(x_flag, y_flag);
        swapxy = true;
    }

    std::vector<Position2D> res;
    for (auto x = 0,
              y = 0,
              p = 2 * deltaY - deltaX;
         x < deltaX;
         x++) {

        if (p >= 0) {
            y++;
            p -= 2 * deltaX;
        }
        p += 2 * deltaY;

        auto resx = start.pos.x() + x * x_flag;
        auto resy = start.pos.y() + y * y_flag;
        if (swapxy) {
            math::swap(resx, resy);
        }
        res.emplace_back(resx, resy);
    }
    for (auto& i : res) {
        auto weight = 1.0f;
        if (start.pos.x() == end.pos.x()) {
            weight = float(i.y() - start.pos.y()) / float(deltaY);
        } else {
            weight = float(i.x() - start.pos.x()) / float(deltaX);
        }
        draw_point(Pixel { .pos { i.x(), i.y() }, .color { math::lerp(start.color, end.color, weight) } });
    }
}

std::vector<std::pair<Vertex, float>> RasterManager::raster_triangle(std::pair<Vertex, float> a_and_w, std::pair<Vertex, float> b_and_w, std::pair<Vertex, float> c_and_w)
{
    auto& a = a_and_w.first;
    auto& b = b_and_w.first;
    auto& c = c_and_w.first;
    auto& a_w = a_and_w.second;
    auto& b_w = b_and_w.second;
    auto& c_w = c_and_w.second;
    auto min_x = std::min(std::min(a.pos.x(), b.pos.x()), c.pos.x());
    auto max_x = std::max(std::max(a.pos.x(), b.pos.x()), c.pos.x());
    auto min_y = std::min(std::min(a.pos.y(), b.pos.y()), c.pos.y());

    auto max_y = std::max(std::max(a.pos.y(), b.pos.y()), c.pos.y());
    auto e1 = Vector2 { float(a.pos.x() - b.pos.x()), float(a.pos.y() - b.pos.y()) };
    auto e2 = Vector2 { float(c.pos.x() - b.pos.x()), float(c.pos.y() - b.pos.y()) };
    auto sum_area = std::abs(e1.cross(e2));
    std::vector<Position2D> res;
    std::vector<std::array<float, 3>> weights;

    for (int i = min_x; i <= max_x; i++) {
        for (int j = min_y; j <= max_y; j++) {
            auto _a = Vector2 { float(a.pos.x() - i), float(a.pos.y() - j) };
            auto _b = Vector2 { float(b.pos.x() - i), float(b.pos.y() - j) };
            auto _c = Vector2 { float(c.pos.x() - i), float(c.pos.y() - j) };
            auto cross_1 = _a.cross(_b);
            auto cross_2 = _b.cross(_c);
            auto cross_3 = _c.cross(_a);
            if (cross_1 >= 0 && cross_2 >= 0 && cross_3 >= 0
                || cross_1 <= 0 && cross_2 <= 0 && cross_3 <= 0) {
                auto area_a = std::abs(_b.cross(_c));
                auto area_b = std::abs(_a.cross(_c));
                auto area_c = std::abs(_a.cross(_b));
                auto weight_a = area_a / sum_area;
                auto weight_b = area_b / sum_area;
                auto weight_c = area_c / sum_area;

                res.emplace_back(i, j);
                weights.emplace_back(std::array<float, 3> { weight_a, weight_b, weight_c });
            }
        }
    }
    std::vector<std::pair<Vertex, float>> rester_output;
    for (int i = 0; i < res.size(); i++) {
        // auto pos = res[i];
        auto weight = weights[i];

        auto cur_point = math::lerp(a, b, c, weight);
        cur_point.pos = { (float)res[i].x(), (float)res[i].y(), cur_point.pos.z(), 1 };
        rester_output.emplace_back(cur_point, math::lerp(a_w, b_w, c_w, weight));

        // draw_point(Pixel { { (int)cur_point.pos.x(), (int)cur_point.pos.y() }, { cur_point.color } });
    }
    return rester_output;
}
void RasterManager::draw_image(std::shared_ptr<Texture> texture)
{
    for (int i = 0; i < texture->get_image()->get_width(); i++) {
        for (int j = 0; j < texture->get_image()->get_height(); j++) {
            RGBA rgba = texture->get_image()->get_buffer()->get(
                j * texture->get_image()->get_width() + i);

            draw_point(Pixel { { i, j }, { (float)rgba.mR, (float)rgba.mG, (float)rgba.mB, (float)rgba.mA } });
        }
    }
}
void RasterManager::prepare_pipeline()
{
}

}