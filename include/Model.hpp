#pragma once
#include <memory>
#include <string_view>

namespace SoftRender {
class Mesh;
class Texture;
class Model {

public:
    Model(std::string_view obj_path, std::string_view texture_path);
    ~Model();
    [[nodiscard("missing mesh")]] auto& get_mesh() { return mesh; }
    [[nodiscard("missing texture")]] auto& get_texture() { return texture; }

private:
    std::unique_ptr<Mesh> mesh;
    std::unique_ptr<Texture> texture;
};

}