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
    for (int i = 0; i < VertexObjectArray::Get_Instance()->indices_count; i++) {
        points.emplace_back(
            vertex_shader_data->vertex_shader(i));
    }
}
void RenderManager::raster(Mat44<float> screen_matrix)
{
    auto temp_a = points[0].pos;
    temp_a = screen_matrix.mul(temp_a / temp_a.w());

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