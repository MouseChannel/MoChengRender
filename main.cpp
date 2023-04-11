

#include "Buffer.hpp"
#include "Description.hpp"
#include "FrameBuffer.hpp"
#include "Helper/Raster_Manager.hpp"
#include "Helper/Render_Manager.hpp"
#include "Math/Math.hpp"
#include "Math/Matrix.hpp"
#include "Math/Vec.hpp"
#include "Mesh.hpp"
#include "Model.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Window.hpp"
#include <iostream>

 
using namespace SoftRender;

int main(int, char**)
{

    auto& raster_manager = SoftRender::RasterManager::Get_Instance();
    float angle = 0.00f;
    float car_pos = 2.0f;
    std::unique_ptr<Model> model {
        new SoftRender::Model { "../Asset/model.obj",
            "../Asset/model.png" }
    };
    auto& render_manager = RenderManager::Get_Instance();
    render_manager->bind_vertex_buffer(std::move(model));
    while (!raster_manager->should_exit()) {
        raster_manager->begin_frame();

        angle += 0.2f;
        // car_pos -= 0.02f;
        mat4f translate_matrix = mat4f::Identity(4);
        auto model_matrix = translate_matrix.mul(math::rotate_matrix(angle, { 0, 1, 0 }));
        Vector3<float> camera_pos { 0, 0, car_pos };

        Vector3<float> front { 0, 0, -1.0f };
        auto view_matrix = math::view_mat(camera_pos, front);
        auto project_matrix = math::perspective(-3, 3, 3, -3, -1.0f, -10.0f);

        auto screen_matrix
            = math::screen_matrix(SoftRender::WEIGHT, SoftRender::HEIGHT);

        std::unique_ptr<Shader> vertex_shader { new Shader(
            model_matrix, view_matrix, project_matrix, screen_matrix) };

        std::unique_ptr<Shader> fragment_shader { new Shader(
            model_matrix, view_matrix, project_matrix, screen_matrix) };

        render_manager->bind_shader(std::move(vertex_shader), std::move(fragment_shader));
        render_manager->vertex_shader_stage();
        render_manager->clip();
        render_manager->ndc();
        render_manager->screen_map(screen_matrix);
        render_manager->raster();
        render_manager->perspective_fix();
        render_manager->fragment_shader_stage();
        render_manager->draw();
        raster_manager->end_frame();
    }

    return 0;
}
