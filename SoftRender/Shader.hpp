#include "SoftRender/Math/DataStruct.hpp"
#include "SoftRender/Math/Matrix.hpp"
#include <memory>

namespace SoftRender {
class Texture;
class Shader {
public:
    // Shader() = default;
    Shader(mat4f model_matrix, mat4f view_matrix, mat4f project_matrix, mat4f screen_matrix);
    ~Shader();
    Point3D vertex_shader(int vertex_index);
    Fragment fragment_shader(Point3D point3d, std::shared_ptr<Texture> texture);

private:
    mat4f model_matrix;
    mat4f view_matrix;
    mat4f project_matrix;
    mat4f screen_matrix;
};

}