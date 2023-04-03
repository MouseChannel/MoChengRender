#include "SoftRender/Window.hpp"
#include "SoftRender/Helper/Render_Manager.hpp"
namespace SoftRender {

Window::Window()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_Log("init fail");
    }
    m_window = SDL_CreateWindow("MO", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WEIGHT, HEIGHT, SDL_WINDOW_SHOWN);
    m_renderer = SDL_CreateRenderer(m_window, -1, 0);
}
Window::~Window()
{
    SDL_DestroyRenderer(m_renderer);

    SDL_DestroyWindow(m_window);
    SDL_Quit();
}
bool Window::should_exit()
{
    SDL_Event evt;
    if (SDL_PollEvent(&evt) != 0) {
        if (evt.type == SDL_QUIT) {
            return true;
        }
    }
    return false;
}
void Window::draw_point(Point2D point)
{
    SDL_SetRenderDrawColor(m_renderer, point.color.r(), point.color.g(), point.color.b(), 255);
    SDL_RenderDrawPoint(m_renderer, point.pos.x(), HEIGHT - point.pos.y());
}
void Window::begin_frame()
{

    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);
}
void Window::end_frame() { SDL_RenderPresent(m_renderer); }

} // namespace SoftRender