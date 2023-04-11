#include "Model.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"
namespace SoftRender {
Model::Model(std::string_view obj_path, std::string_view texture_path)
{
    mesh.reset(new Mesh(obj_path));
    texture.reset(new Texture(texture_path));
}
Model::~Model() { }
}