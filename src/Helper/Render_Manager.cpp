#include "SoftRender/Helper/Render_Manager.hpp"
#include "SoftRender/Helper/Raster_Manager.hpp"
#include "SoftRender/Shader.hpp"
#include "SoftRender/Texture.hpp"

namespace SoftRender {
RenderManager::RenderManager()
{
    framebuffer.reset(new FrameBuffer(800, 600));
    texture.reset(new Texture("D:/MoChengRender/Asset/goku.jpg"));
}
RenderManager::~RenderManager() { }
void RenderManager::bind_vertex_buffer(Vertex_Buffer_Type type,
    std::unique_ptr<VertexBuffers> buffers)
{
    VertexObjectArray::Get_Instance()->set_buffers(type, std::move(buffers));
}
void RenderManager::bind_shader(std::unique_ptr<Shader> vertex_shader,
    std::unique_ptr<Shader> fragment_shader)
{
    vertex_shader_data = std::move(vertex_shader);
    fragment_shader_data = std::move(fragment_shader);
}
void RenderManager::vertex_shader_stage()
{
    assert(vertex_shader_data);
    points.clear();
    for (int i = 0; i < VertexObjectArray::Get_Instance()->indices_count; i++) {
        points.emplace_back(
            vertex_shader_data->vertex_shader(i));
    }
}

void RenderManager::clip()
{
    std::vector<Point3D> res;
    for (int i = 0; i < points.size(); i += 3) {
        auto clip_res = sutherlandHodgman({ points[i], points[i + 1], points[i + 2] });
        if (clip_res.empty())
            continue;
        for (int j = 0; j < clip_res.size() - 2; j++) {

            res.push_back(clip_res[0]);
            res.push_back(clip_res[j + 1]);
            res.push_back(clip_res[j + 2]);
        }
    }
    points = res;
}
std::vector<Point3D> RenderManager::sutherlandHodgman(std::vector<Point3D> source)
{
    assert(source.size() == 3);
    const static auto inside = [](Vector4<float> a, Vector4<float> b) {
        return a.dot(b) >= 0.0f;
    };
    static const auto intersect = [](Point3D last, Point3D current,
                                      Vector4<float> plane) {
        auto distance_last = last.pos.dot(plane);
        auto distance_current = current.pos.dot(plane);
        auto weight = distance_last / (distance_last - distance_current);
        return Point3D {
            .pos = math::lerp(last.pos, current.pos, weight),
            .color = math::lerp(last.color, current.color, weight),
            .uv = math::lerp(last.uv, current.uv, weight),
            .normal = math::lerp(last.normal, current.normal, weight)
        };
    };
    static std::vector<Vector4<float>> planes {
        { 0, 0, 0, -1 }, { 0, 0, 1, -1 }, { 0, 0, -1, -1 }, { 1, 0, 0, -1 },
        { -1, 0, 0, -1 }, { 0, 1, 0, -1 }, { 0, -1, 0, -1 }
    };

    std::vector<Point3D> cur = source;
    for (auto& plane : planes) {

        cur.clear();
        for (int i = 0; i < source.size(); i++) {
            auto current = source[i];
            auto last = source[(i + source.size() - 1) % source.size()];
            auto current_inside = inside(current.pos, plane);
            auto last_inside = inside(last.pos, plane);

            if (current_inside && last_inside) {
                cur.push_back(current);
            }
            if (current_inside && !last_inside) {
                cur.push_back(intersect(last, current, plane));
                cur.push_back(current);
            }
            if (!current_inside && last_inside) {
                cur.push_back(intersect(last, current, plane));
            }
        }
        source = cur;
    }
    return source;
}

void RenderManager::ndc()
{
    _points.clear();
    for (auto& point : points) {
        auto w = point.pos.w();

#ifdef nusing_perspective_fix
        _points.emplace_back(std::pair {
            Point3D { .pos = point.pos / w,
                .color = point.color,
                .uv = point.uv },
            w });
#else
        _points.emplace_back(std::pair {
            Point3D { .pos = point.pos / w,
                .color = point.color / w,
                .uv = point.uv / w },
            w });
#endif
    }
}
void RenderManager::screen_map(mat4f screen_matrix)
{
    for (auto& _point : _points) {
        auto& point = _point.first;
        point.pos = screen_matrix.mul(point.pos);
    }
}
void RenderManager::raster()
{
    auto temp_a = points[0].pos;

    auto temp_b = points[1].pos;

    auto temp_c = points[2].pos;

    Pixel a { .pos { (int)temp_a.x(), (int)temp_a.y() },
        .color { points[0].color } };

    Pixel b { .pos { (int)temp_b.x(), (int)temp_b.y() },
        .color { points[1].color } };

    Pixel c { .pos { (int)temp_c.x(), (int)temp_c.y() }, .color { points[2].color } };

    _points = RasterManager::Get_Instance()->raster_triangle(_points[0], _points[1], _points[2]);
}
void RenderManager::perspective_fix()
{
#ifdef nusing_perspective_fix
    return;
#endif // !using_perspective_fix

    for (auto& _point : _points) {
        auto& point = _point.first;
        auto _w = _point.second;
        RR temp { point.color.x(), point.color.y(), point.color.z(), point.color.w() };
        point.color
            = point.color * _w;
        point.uv = point.uv * _w;
    }
}
void RenderManager::fragment_shader_stage()
{
    fragments.clear();
    for (auto& _point : _points) {
        // RR temp { _point.first.color.r(), _point.first.color.g(), _point.first.color.b(), _point.first.color.a() };
        fragments.emplace_back(fragment_shader_data->fragment_shader(_point.first, texture));
    }
    framebuffer->reset();
    framebuffer->add_fragments(fragments);
}
void RenderManager::draw()
{
    auto& data = framebuffer->get_data();
    for (auto& i : data) {
        RasterManager::Get_Instance()->draw_point(Pixel { i.first, i.second.color });
    }
}
}