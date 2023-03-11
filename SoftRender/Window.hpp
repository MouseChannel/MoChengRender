#pragma once
#include "SDL.h"
#include "SoftRender/Math.hpp"
#include <vector>
namespace SoftRender {
class Window {
public:
  Window();
  ~Window();
  void Update(std::vector<Point> points);
  

private:
  SDL_Window *m_window;
  SDL_Surface *m_surface;
  SDL_Renderer *m_renderer;
};

} // namespace SoftRender