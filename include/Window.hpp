#pragma once
#include "Math/DataStruct.hpp"
#include "Math/Math.hpp"
#include "SDL.h"
#include <vector>


namespace SoftRender {
const int WEIGHT = 800;
const int HEIGHT = 600;
class Window {
public:
    Window();
    ~Window();
    void Init();

    void draw_point(Pixel point);
    void begin_frame();
    void end_frame();
    bool should_exit();

private:
    SDL_Window* m_window;
    SDL_Surface* m_surface;
    SDL_Renderer* m_renderer;
};

} // namespace SoftRender