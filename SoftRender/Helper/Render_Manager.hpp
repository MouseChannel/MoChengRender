#pragma once
#include "SoftRender/Helper/Instance.hpp"
#include "SoftRender/Math/DataStruct.hpp"
#include "SoftRender/Math/Matrix.hpp"
#include "SoftRender/VertexObjectArray.hpp"
#include <memory>
#include <vector>

namespace SoftRender {
class Shader;
class RenderManager : public Instance<RenderManager> {
public:
    RenderManager();
    ~RenderManager();

    void bind_vertex_buffer(Vertex_Buffer_Type type,
        std::unique_ptr<VertexBuffers> buffers);
    void bind_shader(std::unique_ptr<Shader> vertex_shader, std::unique_ptr<Shader> fragment_shader);
    void vertex_shader_stage();
    void clip();
    void raster(mat4f screen_matrix);

private:
    std::unique_ptr<Shader> vertex_shader_data { nullptr },
        fragment_shader_data { nullptr };
    std::vector<Point3D> points;
    std::vector<Point3D> sutherlandHodgman(std::vector<Point3D>);
};
}