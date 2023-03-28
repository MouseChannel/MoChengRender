#include "SoftRender/Texture.hpp"

#include "SoftRender/Image.hpp"
#include "SoftRender/Math/Math.hpp"
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
    image.reset(new Image((RGBA *)pixels, w, h));
    stbi_image_free(pixels);
}
Texture::~Texture() { }

}
