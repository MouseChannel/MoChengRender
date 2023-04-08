#pragma once
#include "SoftRender/Image.hpp"
#include "string_view"
#include <memory>

namespace SoftRender {
class Image;

class Texture {
public:
    Texture(std::string_view path);
    ~Texture();
    [[nodiscard("missing image")]] auto& get_image() { return image; }
    RGBA sampleNearest(float x, float y);

private:
    std::unique_ptr<Image>
        image;
};

}