#include "Texture.hpp"

#include "Image.hpp"
#include "Math/Math.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "Tools/stb_image.h"

namespace SoftRender {
Texture::Texture(std::string_view path)
{
    int w, h, channel;
    auto pixels = stbi_load(path.data(), &w, &h, &channel, STBI_rgb_alpha);

    if (!pixels) {
        throw std::runtime_error("image load failed");
    }
    image.reset(new Image((RGBA*)pixels, w, h));
    stbi_image_free(pixels);
}
Texture::~Texture() { }

RGBA Texture::sampleNearest(float _x, float _y)
{
    int x = std::round(std::min(_x, 1.0f) * (image->get_width() - 1));
    int y = std::round(std::min(_y, 1.0f) * (image->get_height() - 1));
    return image->get_buffer()->get(y * image->get_width() + x);
}
}
