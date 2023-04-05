

#include "SoftRender/Buffer.hpp"
#include "SoftRender/Description.hpp"
#include "SoftRender/FrameBuffer.hpp"
#include "SoftRender/Helper/Raster_Manager.hpp"
#include "SoftRender/Helper/Render_Manager.hpp"
#include "SoftRender/Math/Math.hpp"
#include "SoftRender/Math/Matrix.hpp"
#include "SoftRender/Math/Vec.hpp"
#include "SoftRender/Shader.hpp"
#include "SoftRender/Texture.hpp"
#include "SoftRender/Window.hpp"
#include <iostream>
// #define npipeline
using namespace SoftRender;
Point3D a { { -2.0f, 0, 0, 1 }, { 255, 0, 0, 255 } };
Point3D b { { 2.0f, 0, 0, 1 }, { 0, 255, 0, 255 } };
Point3D c { { 0, 2, 0, 1 }, { 0, 0, 255, 255 } };
Point3D mid { { (a.pos.x() + b.pos.x() + c.pos.x()) / 3, (a.pos.y() + b.pos.y() + c.pos.y()) / 3, 0, 1 } };

void normalized(auto& x)
{
    x = x / x[3];
}
int main(int, char**)
{

    std::shared_ptr<SoftRender::Texture> imag { new SoftRender::Texture("D:/MoChengRender/Asset/goku.jpg") };
    auto& raster_manager = SoftRender::RasterManager::Get_Instance();
    float angle = 0.00f;
    float car_pos = 5.0f;

    while (!raster_manager->should_exit()) {
        raster_manager->begin_frame();

        //---
        // angle += 0.1f;
        // car_pos -= 0.02f;
        mat4f translate_matrix = mat4f::Identity(4);
        auto model_matrix = translate_matrix.mul(math::rotate_matrix(angle, { 0, 1, 0 }));
        Vector3<float> camera_pos { 0, 0, car_pos };

        Vector3<float> front { 0, 0, -1.0f };
        auto view_matrix = math::view_mat(camera_pos, front);
        auto project_matrix = math::perspective(-3, 3, 3, -3, -1.0f, -10.0f);
        // auto project_matrix = math::perspective(60.0f, (float)4 / (float)3, 0.1f, 10.0f);
        // auto project_matrix = math::orthographic(-3, 3, 3, -3, 1.0f, -2.0f);

        auto screen_matrix
            = math::screen_matrix(SoftRender::WEIGHT, SoftRender::HEIGHT);

        // pipeline
        auto& render_manager = RenderManager::Get_Instance();
        std::unique_ptr<VertexBuffers> position_buf {
            new VertexBuffers({ { { -20, 0, 0 } },
                { { 2, 0, 0 } },
                { { 0, 1, 0 } } })
        };

        render_manager->bind_vertex_buffer(Vertex_Buffer_Type::position, std::move(position_buf));
        std::unique_ptr<VertexBuffers> color_buf { new VertexBuffers(
            { { { 255, 0, 0, 255 } }, { { 0, 255, 0, 255 } }, { { 0, 0, 255, 255 } } }) };
        render_manager->bind_vertex_buffer(Vertex_Buffer_Type ::color,
            std::move(color_buf));
        std::unique_ptr<Shader> vertex_shader { new Shader(model_matrix, view_matrix, project_matrix, screen_matrix) };
        render_manager->bind_shader(std::move(vertex_shader), nullptr);
        render_manager->vertex_shader_stage();
        render_manager->clip();
        render_manager->raster(screen_matrix);

        raster_manager->end_frame();
    }

    return 0;
}
