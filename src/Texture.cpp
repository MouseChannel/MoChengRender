#include "SoftRender/Texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "Tools/stb_image.h"

namespace SoftRender {
Texture::Texture(std::string_view path)
{
    int w, h, channel;
    stbi_uc* pixels = stbi_load(path.data(), &w, &h, &channel, STBI_rgb_alpha);
    size_t size = w * h * 4;
    if (!pixels) {
        throw std::runtime_error("image load failed");
    }
}
Texture::~Texture() { }

}
