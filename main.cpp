

#include "SoftRender/Window.hpp"
// #include "glfw3.h"
#include "SoftRender/Helper/Render_Manager.hpp"
#include "SoftRender/Math/Math.hpp"
#include "SoftRender/Math/Vec.hpp"
#include <iostream>

int main(int, char**)
{

    std::vector<Point> p;
    Point aa;
    aa.pos.x() = 50;
    aa.pos.y() = 50;
    aa.color.r() = 244;

    for (int i = 0; i < 20; i++) {
        aa.pos.x() += 2;

        p.push_back(aa);
    }
    auto& render_manager = SoftRender::RenderManager::Get_Instance();

    while (!render_manager->should_exit()) {
        render_manager->begin_frame();

        render_manager->draw_point(Point { { 30, 30 }, { 255, 255, 255 } });
        render_manager->draw_point(Point { { 100, 200 }, { 255, 255, 255 } });
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
        render_manager->draw_line(Point { { 100, 100 }, { 0, 0, 0 } },
            Point { { 200, 200 }, { 255, 255, 255 } });
        render_manager->draw_triangle(Point { { 0, 0 }, { 0, 0, 255 } }, Point { { 100, 100 }, { 255, 0, 0 } }, Point { { 50, 150 }, { 0, 255, 0 } });
        render_manager->end_frame();
    }

    Position2D aaaa { 1, 2 };
    Position2D bbbb { 2, 2 };
    Position2D ssss;
    Color c1;
    Color c2;
    Vector3<int> v1 { 1, 2, 3 };

    Vector3<int> v2 { 2, 3, 4 };
    aaaa[0] = 2;
    aaaa.y() = 3;
    auto ee = aaaa.dot(ssss);
    auto rr = c2.size;
    // auto eee = c1.cross(c2);
    auto ssw = v1.cross(v2);
    Vector2<int> aasd;
    Vector<float> testt { { 3.0f, 1.0f } };
    auto square = testt.square();
    auto le = testt.length();
    auto ss = testt.normalize();

    int s = 0;

    return 0;
}
