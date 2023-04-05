#include "SoftRender/Math/DataStruct.hpp"
#include "SoftRender/Math/Matrix.hpp"
#include <memory>

namespace SoftRender {
class Shader {
public:
    Shader(mat4f model_matrix, mat4f view_matrix, mat4f project_matrix, mat4f screen_matrix);
    ~Shader();
    Point3D vertex_shader(int vertex_index);
    void fragment_shader();

private:
    mat4f model_matrix;
    mat4f view_matrix;
    mat4f project_matrix;
    mat4f screen_matrix;
};

}