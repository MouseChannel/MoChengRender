#pragma once
#include "Helper/Instance.hpp"
#include "Math/DataStruct.hpp"
#include "Math/Matrix.hpp"
#include "VertexObjectArray.hpp"
#include <memory>
#include <vector>
 
namespace SoftRender {
class Shader;
class FrameBuffer;
class Texture;
class Model;
class RenderManager : public Instance<RenderManager> {
public:
    RenderManager();
    ~RenderManager();

    void bind_vertex_buffer(Vertex_Buffer_Type type,
        std::unique_ptr<VertexBuffers> buffers);
    void bind_vertex_buffer(std::unique_ptr<Model> model);
    void bind_shader(std::unique_ptr<Shader> vertex_shader, std::unique_ptr<Shader> fragment_shader);
    void vertex_shader_stage();
    void clip();
    void ndc();
    void screen_map(mat4f screen_matrix);

    void raster();
    bool cull_face(Vertex a, Vertex b, Vertex c);
    void perspective_fix();
    void fragment_shader_stage();
    void draw();

private:
    std::unique_ptr<Shader> vertex_shader_data { nullptr },
        fragment_shader_data { nullptr };
    std::vector<Vertex> points;
    std::vector<float> one_over_w;
    std::vector<std::pair<Vertex, float>> _points;
    std::vector<Vertex> sutherlandHodgman(std::vector<Vertex>);
    std::vector<Fragment> fragments;
    std::unique_ptr<FrameBuffer> framebuffer;
    std::shared_ptr<Texture> texture;
};
}