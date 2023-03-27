#pragma once
#include "SoftRender/Math/Math.hpp"
#include "SoftRender/Buffer.hpp"
namespace SoftRender {
class Image {
    Image();
    ~Image();

  private:
    Buffer<Color> buffer;
};

}