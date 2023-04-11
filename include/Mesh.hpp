#pragma once
#include "Math/DataStruct.hpp"
#include "VertexObjectArray.hpp"
#include <memory>
#include <string_view>
#include <vector>

namespace SoftRender {
class Texture;
class Mesh {

public:
    Mesh(std::string_view obj_path);
    ~Mesh();
    [[nodiscard("missing position_buf")]] auto& get_position_buf() { return position_buf; }
    [[nodiscard("missing uv_buf")]] auto& get_uv_buf() { return uv_buf; }
    [[nodiscard]] auto get_indices() { return m_index.size(); }

private:
    std::vector<Vertex> vertexs;
    std::unique_ptr<VertexBuffers> position_buf;

    std::unique_ptr<VertexBuffers> uv_buf;

    std::vector<uint32_t> m_index;
};

}