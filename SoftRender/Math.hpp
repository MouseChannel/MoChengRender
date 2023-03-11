#pragma once

#include <stdint.h>
#include <variant>
#include "SDL.h"
struct Color {
  uint8_t r, g, b;
};

struct Vec2 {
  int x, y;
};
struct Point {
  Vec2 pos;
  Color color;
};
