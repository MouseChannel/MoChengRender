#pragma once
#include "string_view"
namespace SoftRender {
class Texture {
    Texture(std::string_view path);
    ~Texture();
};

}