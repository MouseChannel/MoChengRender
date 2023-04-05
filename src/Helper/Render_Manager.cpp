#include "SoftRender/Helper/Render_Manager.hpp"
#include "SoftRender/Helper/Raster_Manager.hpp"
#include "SoftRender/Shader.hpp"

namespace SoftRender {
RenderManager::RenderManager() { }
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
void RenderManager::raster(mat4f screen_matrix)
{
    auto temp_a = points[0].pos;
    temp_a = temp_a / points[0].pos.w();
    temp_a = screen_matrix.mul(temp_a);

    auto temp_b = points[1].pos;
    temp_b = screen_matrix.mul(temp_b / temp_b.w());

    auto temp_c = points[2].pos;
    temp_c = screen_matrix.mul(temp_c / temp_c.w());

    Point2D a { .pos { (int)temp_a.x(), (int)temp_a.y() },
        .color { points[0].color } };

    Point2D b { .pos { (int)temp_b.x(), (int)temp_b.y() },
        .color { points[1].color } };

    Point2D
        c { .pos { (int)temp_c.x(), (int)temp_c.y() },
            .color { points[2].color } };
    RasterManager::Get_Instance()->draw_triangle(a, b, c);
}
}