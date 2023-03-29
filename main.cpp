

#include "SoftRender/Window.hpp"

#include "SoftRender/Helper/Render_Manager.hpp"
#include "SoftRender/Math/Math.hpp"
#include "SoftRender/Math/Matrix.hpp"
#include "SoftRender/Math/Vec.hpp"
#include "SoftRender/Texture.hpp"
#include <iostream>

int main(int, char**)
{

    std::unique_ptr<Mat33<int>> a(new Mat33<int>(2));
    std::unique_ptr<Mat33<int>> b(new Mat33<int>(3));
    a->set_column(0, { 1, 2, 3 });

    auto res = a->mul(b->get_column(1));

    std::shared_ptr<SoftRender::Texture> imag { new SoftRender::Texture("D:/MoChengRender/Asset/goku.jpg") };
    auto& render_manager = SoftRender::RenderManager::Get_Instance();

    while (!render_manager->should_exit()) {
        render_manager->begin_frame();

        // render_manager->draw_point(Point { { 30, 30 }, { 255, 255, 255, 255 } });
        // render_manager->draw_point(Point { { 100, 200 }, { 255, 255, 255, 255 } });
        // render_manager->draw_line(Point  {  {{300, 100}} }, Point { 200, 400 });
        // render_manager->draw_line(Point  {  {{300, 100}} }, Point { 200, 150 });
        // render_manager->draw_line(Point { { 300, 100 } }, Point { { 200, 0 } });
        // render_manager->draw_line(Point { { 300, 100 } }, Point { { 200, 50 } });
        // render_manager->draw_line(Point { { 300, 100 } }, Point { { 200, 100 } });
        // render_manager->draw_line(Point { { 300, 100 } }, Point { { 100, 100 } });
        // render_manager->draw_line(Point { { 300, 100 } }, Point { { 250, 0 } });

        // render_manager->draw_line(Point { { 300, 100 } }, Point { { 200, 400 } });
        // render_manager->draw_line(Point { { 300, 100 } }, Point { { 200, 300 } });
        // render_manager->draw_line(Point { { 300, 100 } }, Point { { 200, 150 } });
        // render_manager->draw_line(Point { { 300, 100 } }, Point { { 200, 200 } });
        // render_manager->draw_line(Point { { 100, 100 } }, Point { { 200, 0 } });
        // render_manager->draw_line(Point { { 100, 100 } }, Point { { 200, 50 } });

        // render_manager->draw_line(Point { { 100, 100 } }, Point { { 150, 0 } });
        // render_manager->draw_line(Point { { 100, 100 } }, Point { { 200, 100 } });

        // render_manager->draw_line(Point { { 100, 100 } }, Point { { 200, 400
        // } }); render_manager->draw_line(Point { { 100, 100 } }, Point { {
        // 200, 300 } }); render_manager->draw_line(Point { { 100, 100 } },
        // Point { { 200, 150 } }); render_manager->draw_line(Point { { 100, 100
        // } }, Point { { 200, 200 } });
        // render_manager->draw_line(Point { { 100, 100 }, { 0, 0, 0,255 } },
        //     Point { { 200, 200 }, { 255, 255, 255, 255 } });
        // render_manager->draw_triangle(Point { { 0, 0 }, { 0, 0, 255, 255 } }, Point { { 100, 100 }, { 255, 0, 0,255 } }, Point { { 50, 150 }, { 0, 255, 0 ,255} });
        render_manager->draw_image(imag);
        render_manager->end_frame();
    }

    Mat33<Color> moiche(Color);

    int s = 0;

    return 0;
}
