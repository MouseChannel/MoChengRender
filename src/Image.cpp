#include "SoftRender/Image.hpp"

#include "SoftRender/Buffer.hpp"

namespace SoftRender {
Image::Image(RGBA* data, size_t width, size_t height)
    : width(width)
    , height(height)
{

    buffer.reset(new Buffer<RGBA>(width * height, data));
}
Image::~Image() { }

}
