#pragma once
#include "Buffer.hpp"
#include "Math/Math.hpp"

namespace SoftRender {
struct RGBA {
    // using uint8_t = uint8_t;

    uint8_t mR;
    uint8_t mG;
    uint8_t mB;
    uint8_t mA;

    RGBA(
        uint8_t r = 255,
        uint8_t g = 255,
        uint8_t b = 255,
        uint8_t a = 255)
    {
        mR = r;
        mG = g;
        mB = b;
        mA = a;
    }
};
class Image {
public:
    Image(RGBA* data, size_t width, size_t height);
    ~Image();
    [[nodiscard]] auto get_width() { return width; }
    [[nodiscard]] auto get_height() { return height; }
    [[nodiscard]] auto& get_buffer() { return buffer; }

private:
    std::unique_ptr<Buffer<RGBA>> buffer;
    size_t width;
    size_t height;
};

}