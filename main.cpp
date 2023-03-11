

#include "SoftRender/Window.hpp"
// #include "glfw3.h"
#include <iostream>
int main(int, char **) {

  SoftRender::Window q;
  //   SDL_Log("Hello from sdl2");
  //   q.DrawPoint();
  std::vector<Point> p;
  Point aa;
  aa.pos.x = 50;
  aa.pos.y = 50;
  aa.color.r = 244;

  for (int i = 0; i < 20; i++) {
    aa.pos.x += 2;

    p.push_back(aa);
  }

  q.Update(p);
  //   std::cout << "Hello, world!\n";
  return 0;
}
