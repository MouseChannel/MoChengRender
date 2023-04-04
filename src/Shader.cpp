#include "SoftRender/Shader.hpp"
#include "SoftRender/VertexObjectArray.hpp"

namespace SoftRender {
Shader::Shader(Mat44<float> model_matrix, Mat44<float> view_matrix, Mat44<float> project_matrix, Mat44<float> screen_matrix)
    : model_matrix(model_matrix)
    , view_matrix(view_matrix)
    , project_matrix(project_matrix)
    , screen_matrix(screen_matrix)
{
}
Shader::~Shader() { }

Point3D Shader::vertex_shader(int vertex_index)
{

    auto pos_buffer = VertexObjectArray::Get_Instance()->get_buffer(Vertex_Buffer_Type::position, vertex_index);
    // auto uv_buffer = VertexObjectArray::Get_Instance()->get_buffer(Vertex_Buffer_Type::uv, vertex_index);
    auto color_buffer = VertexObjectArray::Get_Instance()->get_buffer(Vertex_Buffer_Type::color, vertex_index);
    // auto normal_buffer =
    // VertexObjectArray::Get_Instance()->get_buffer(Vertex_Buffer_Type::normal,
    // vertex_index);
    auto mvp = project_matrix.mul(view_matrix).mul(model_matrix);

    Point3D res {
        .pos { mvp.mul({ pos_buffer, 1 }) },
        .color { uint8_t(color_buffer[0]), uint8_t(color_buffer[1]),
            uint8_t(color_buffer[2]), uint8_t(color_buffer[3]) },
        // .uv { uv_buffer },
        // .normal { normal_buffer }
    };

    return res;
}
} // namespace SoftRender