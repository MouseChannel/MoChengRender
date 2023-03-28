#pragma once
#include "string_view"
#include <memory>
namespace SoftRender {
class Image;
class Texture {
public:
    Texture(std::string_view path);
    ~Texture();
    [[nodiscard("missing image")]] auto& get_image() { return image; }

private:
    std::unique_ptr<Image> image;
};

}