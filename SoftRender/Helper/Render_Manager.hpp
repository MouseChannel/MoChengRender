#pragma once
#include "SoftRender/Helper/Instance.hpp"
#include "SoftRender/Math/DataStruct.hpp"
#include "SoftRender/Math/Matrix.hpp"
#include "SoftRender/VertexObjectArray.hpp"
#include <memory>
#include <vector>
#define using_perspective_fix
namespace SoftRender {
class Shader;
class FrameBuffer;
class Texture;
class RenderManager : public Instance<RenderManager> {
public:
    RenderManager();
    ~RenderManager();

    void bind_vertex_buffer(Vertex_Buffer_Type type,
        std::unique_ptr<VertexBuffers> buffers);
    void bind_shader(std::unique_ptr<Shader> vertex_shader, std::unique_ptr<Shader> fragment_shader);
    void vertex_shader_stage();
    void clip();
    void ndc();
    void screen_map(mat4f screen_matrix);

    void raster();
    void perspective_fix();
    void fragment_shader_stage();
    void draw();

private:
    std::unique_ptr<Shader> vertex_shader_data { nullptr },
        fragment_shader_data { nullptr };
    std::vector<Point3D> points;
    std::vector<float> one_over_w;
    std::vector<std::pair<Point3D, float>> _points;
    std::vector<Point3D> sutherlandHodgman(std::vector<Point3D>);
    std::vector<Fragment> fragments;
    std::unique_ptr<FrameBuffer> framebuffer;
    std::shared_ptr<Texture> texture;
};
}