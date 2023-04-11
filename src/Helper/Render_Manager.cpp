#include "Helper/Render_Manager.hpp"
#include "Helper/Raster_Manager.hpp"
#include "Mesh.hpp"
#include "Model.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

namespace SoftRender {
RenderManager::RenderManager()
{
    framebuffer.reset(new FrameBuffer(800, 600));
    // texture.reset(new Texture("D:/MoChengRender/Asset/goku.jpg"));
}
RenderManager::~RenderManager() { }

void RenderManager::bind_vertex_buffer(std::unique_ptr<Model> model)
{
    auto& mesh = model->get_mesh();
    auto& position_buf = mesh->get_position_buf();
    auto& uv_buf = mesh->get_uv_buf();
    bind_vertex_buffer(Vertex_Buffer_Type::position, std::move(position_buf));
    bind_vertex_buffer(Vertex_Buffer_Type ::uv, std::move(uv_buf));
    VertexObjectArray::Get_Instance()->indices_count = mesh->get_indices();
    texture = std::move(model->get_texture());
}
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
    std::vector<Vertex> res;
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
std::vector<Vertex> RenderManager::sutherlandHodgman(std::vector<Vertex> source)
{
    assert(source.size() == 3);
    const static auto inside = [](Vector4<float> a, Vector4<float> b) {
        return a.dot(b) >= 0.0f;
    };
    static const auto intersect = [](Vertex last, Vertex current,
                                      Vector4<float> plane) {
        auto distance_last = last.pos.dot(plane);
        auto distance_current = current.pos.dot(plane);
        auto weight = distance_last / (distance_last - distance_current);
        return Vertex {
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

    std::vector<Vertex> cur = source;
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

        // float low = -1.0f;
        // float high = 1.0f;
        _points.emplace_back(std::pair {
            Vertex { .pos { std::clamp((point.pos / w)[0], -1.0f, 1.0f),
                         std::clamp((point.pos / w)[1], -1.0f, 1.0f),
                         std::clamp((point.pos / w)[2], -1.0f, 1.0f),
                         std::clamp((point.pos / w)[3], -1.0f, 1.0f) },
                .color = point.color / w,
                .uv = point.uv / w },
            w });
    }
}
void RenderManager::screen_map(mat4f screen_matrix)
{
    for (auto& _point : _points) {
        auto& point = _point.first;
        point.pos = screen_matrix.mul(point.pos);
    }
}
bool RenderManager::cull_face(Vertex a, Vertex b, Vertex c)
{
    auto aa = a.pos - b.pos;
    auto bb = b.pos - c.pos;
    Vector3<float> aaa { aa[0], aa[1], aa[2] };

    Vector3<float> bbb { bb[0], bb[1], bb[2] };
    // return false;
    return aaa.cross(bbb)[2] < 0.0f;
}
void RenderManager::raster()
{

    std::vector<std::pair<Vertex, float>> _res;
    for (auto i = 0; i < _points.size(); i += 3) {
        auto a = _points[i];
        auto b = _points[i + 1];
        auto c = _points[i + 2];
        if (cull_face(a.first, b.first, c.first)) {
            continue;
        }
        auto temp = RasterManager::Get_Instance()->raster_triangle(
            a, b, c);
        _res.insert(_res.end(), temp.begin(), temp.end());
    }
    _points = std::move(_res);
}
void RenderManager::perspective_fix()
{

    for (auto& _point : _points) {
        auto& point = _point.first;
        auto _w = _point.second;

        point.color
            = point.color * _w;
        point.uv = point.uv * _w;
    }
}
void RenderManager::fragment_shader_stage()
{
    fragments.clear();
    for (auto& _point : _points) {

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