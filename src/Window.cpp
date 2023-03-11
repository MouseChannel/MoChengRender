#include "SoftRender/Window.hpp"
namespace SoftRender {
Window::Window() {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    SDL_Log("init fail");
  }
  m_window =
      SDL_CreateWindow("MO", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       800, 800, SDL_WINDOW_SHOWN);
  m_renderer = SDL_CreateRenderer(m_window, -1, 0);
}
Window::~Window() {
  SDL_DestroyRenderer(m_renderer);

  SDL_DestroyWindow(m_window);
  SDL_Quit();
}

void Window::Update(std::vector<Point> points) {

  bool quit = false;
  SDL_Event evt;
  while (!quit) {
    while (SDL_PollEvent(&evt) != 0) {
      if (evt.type == SDL_QUIT) {
        quit = true;
      }
    }
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);
    for (auto &point : points) {
      auto color = point.color;
      auto pos = point.pos;
      SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, 255);
      SDL_RenderDrawPoint(m_renderer, pos.x, pos.y);
    }
    SDL_RenderPresent(m_renderer);
  }
}
} // namespace SoftRender