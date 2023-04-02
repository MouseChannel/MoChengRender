#include "SoftRender/Helper/Render_Manager.hpp"
#include "SoftRender/Image.hpp"
#include "SoftRender/Math/DataStruct.hpp"
#include "SoftRender/Math/Math.hpp"
#include "SoftRender/Texture.hpp"
#include "SoftRender/Window.hpp"

namespace SoftRender {

RenderManager::RenderManager()
{
    m_window.reset(new Window);
}
RenderManager::~RenderManager() { }
bool RenderManager::should_exit() { return m_window->should_exit(); }
void RenderManager::begin_frame() { m_window->begin_frame(); }
void RenderManager::end_frame() { m_window->end_frame(); }
void RenderManager::draw_point(Point2D pos)
{
    int r = pos.color.r();
    int g = pos.color.g();
    int b = pos.color.b();
    m_window->draw_point(pos);
}
void RenderManager::draw_line(Point2D start, Point2D end)
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
        draw_point(Point2D { .pos { i.x(), i.y() }, .color { math::lerp(start.color, end.color, weight) } });
    }
}

void RenderManager::draw_triangle(Point2D a, Point2D b, Point2D c)
{

    auto min_x = std::min(std::min(a.pos.x(), b.pos.x()), c.pos.x());
    auto max_x = std::max(std::max(a.pos.x(), b.pos.x()), c.pos.x());
    auto min_y = std::min(std::min(a.pos.y(), b.pos.y()), c.pos.y());

    auto max_y = std::max(std::max(a.pos.y(), b.pos.y()), c.pos.y());
    auto e1 = Vector2 { float(a.pos.x() - b.pos.x()), float(a.pos.y() - b.pos.y()) };
    auto e2 = Vector2 { float(c.pos.x() - b.pos.x()), float(c.pos.y() - b.pos.y()) };
    auto sum_area = std::abs(e1.cross(e2));
    std::vector<Position2D> res;
    std::vector<std::tuple<float, float, float>> weights;
    for (int i = min_x; i <= max_x; i++) {
        for (int j = min_y; j <= max_y; j++) {
            auto _a = Vector2 { float(a.pos.x() - i), float(a.pos.y() - j) };
            auto _b = Vector2 { float(b.pos.x() - i), float(b.pos.y() - j) };
            auto _c = Vector2 { float(c.pos.x() - i), float(c.pos.y() - j) };
            auto cross_1 = _a.cross(_b);
            auto cross_2 = _b.cross(_c);
            auto cross_3 = _c.cross(_a);
            if (cross_1 >= 0 && cross_2 >= 0 && cross_3 >= 0 || cross_1 <= 0 && cross_2 <= 0 && cross_3 <= 0) {
                auto area_a = std::abs(_b.cross(_c));
                auto area_b = std::abs(_a.cross(_c));
                auto area_c = std::abs(_a.cross(_b));
                auto weight_a = area_a / sum_area;
                auto weight_b = area_b / sum_area;
                auto weight_c = area_c / sum_area;

                res.emplace_back(i, j);
                weights.emplace_back(std::make_tuple(weight_a, weight_b, weight_c));
            }
        }
    }
    for (int i = 0; i < res.size(); i++) {
        auto pos = res[i];
        auto weight = weights[i];
        auto color = math::lerp(a.color, b.color, c.color, std::get<0>(weight),
            std::get<1>(weight), std::get<2>(weight));
        draw_point(Point2D { { pos.x(), pos.y() }, { color } });
    }
    // for (auto& i : res) {
    //     draw_point(Point { { i.x(), i.y() }, { math::lerp(a.color, b.color, c.color, float weight_a, float weight_b, float weight_c) } });
    // }
}
void RenderManager::draw_image(std::shared_ptr<Texture> texture)
{
    for (int i = 0; i < texture->get_image()->get_width(); i++) {
        for (int j = 0; j < texture->get_image()->get_height(); j++) {
            RGBA rgba = texture->get_image()->get_buffer()->get(
                j * texture->get_image()->get_width() + i);

            draw_point(Point2D { { i, j }, { rgba.mR, rgba.mG, rgba.mB, rgba.mA } });
        }
    }
}

}