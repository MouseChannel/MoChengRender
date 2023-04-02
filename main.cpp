

#include "SoftRender/Window.hpp"

#include "SoftRender/Helper/Render_Manager.hpp"
#include "SoftRender/Math/Math.hpp"
#include "SoftRender/Math/Matrix.hpp"
#include "SoftRender/Math/Vec.hpp"
#include "SoftRender/Texture.hpp"
#include <iostream>
Point3D a { { 0, 100, 0 }, { 255, 0, 0, 255 } };
Point3D b { { -50, 50, 0 }, { 0, 255, 0, 255 } };
Point3D c { { 50, 50, 0 }, { 0, 0, 255, 255 } };
Point3D mid { { (a.pos.x() + b.pos.x() + c.pos.x()) / 3, (a.pos.y() + b.pos.y() + c.pos.y()) / 3, 0 } };

int main(int, char**)
{

    std::shared_ptr<SoftRender::Texture> imag { new SoftRender::Texture("D:/MoChengRender/Asset/goku.jpg") };
    auto& render_manager = SoftRender::RenderManager::Get_Instance();
    float angle = 0.00f;

    while (!render_manager->should_exit()) {
        render_manager->begin_frame();

        angle += 0.1f;
        render_manager->draw_point(Point2D { { (int)mid.pos.x(), (int)mid.pos.y() }, { 255, 255, 255, 255 } });

        auto translate_matrix = math::translate_matrix({ mid.pos.x()+ 100, mid.pos.y(), mid.pos.z() });
        auto model_matrix = translate_matrix.mul(math::rotate_matrix(angle, { mid.pos.x(), 1, 0 }));
        // auto model_matrix = Mat44<float>(1);
        Vector3<float> camera_pos { 0, 0, 2 };
        Vector3<float> front { 0, 0, 1 };
        auto view_matrix = math::view_mat(camera_pos, front);
        auto project_matrix = math::orthographic(0, SoftRender::WEIGHT,
            SoftRender::HEIGHT, 0, -1, 1);
        auto screen_matrix = math::screen_matrix(SoftRender::WEIGHT, SoftRender::HEIGHT);

        auto mvp = model_matrix.mul(view_matrix).mul(project_matrix);
        auto mvpp = screen_matrix.mul(project_matrix.mul(view_matrix).mul(model_matrix));
        Vector3<float>
            temp_a { a.pos.x(), a.pos.y(), a.pos.z() };
        auto triangle_a = mvpp
                              .mul({ temp_a, 1 });
        auto triangle_b = mvpp
                              .mul({ b.pos.x(), b.pos.y(), b.pos.z(), 1 });
        auto triangle_c = mvpp.mul({ c.pos.x(), c.pos.y(), c.pos.z(), 1 });
        Point2D aa { { (int)triangle_a.x(), (int)triangle_a.y() },
            { 255, 0, 0, 255 } };
        Point2D bb { { (int)triangle_b.x(), (int)triangle_b.y() },
            { 0, 255, 0, 255 } };
        Point2D cc { { (int)triangle_c.x(), (int)triangle_c.y() },
            { 0, 0, 255, 255 } };

        render_manager->draw_triangle(aa, bb, cc);
        // render_manager->draw_image(imag);
        render_manager->end_frame();
    }

    Mat33<Color> moiche(Color);

    int s = 0;

    return 0;
}
