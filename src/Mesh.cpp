#include "Mesh.hpp"
#define TINYOBJLOADER_IMPLEMENTATION
#include "Texture.hpp"
#include "Tools/tiny_obj_loader.hpp"

namespace SoftRender {
Mesh::Mesh(std::string_view obj_path)
{
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string err;
    std::string warn;

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, obj_path.data())) {
        throw std::runtime_error("Error: failed to load model");
    }
    // std::vector<float> m_positions;
    // std::vector<float> m_uv;
    // std::vector<uint32_t> m_index;
    std::vector<VertexBuffer> positions;

    std::vector<VertexBuffer> uvs;
    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            vertexs.emplace_back(
                Vertex { .pos { attrib.vertices[3 * index.vertex_index + 0],
                             attrib.vertices[3 * index.vertex_index + 1],
                             attrib.vertices[3 * index.vertex_index + 2], 1 },
                    .color {},
                    .uv { attrib.texcoords[2 * index.texcoord_index + 0],
                        1.0f - attrib.texcoords[2 * index.texcoord_index + 1] },
                    .normal {} });

            // Vector3<float> pos {
            //     attrib.vertices[3 * index.vertex_index + 0],
            //     attrib.vertices[3 * index.vertex_index + 0],
            //     attrib.vertices[3 * index.vertex_index + 0]
            // };

            // Vector2<float> uv {
            //     attrib.texcoords[2 * index.texcoord_index + 0],
            //     1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
            // };
            // position_buf.reset(new VertexBuffers({ { { attrib.vertices[3 * index.vertex_index + 0],
            //     attrib.vertices[3 * index.vertex_index + 0],
            //     attrib.vertices[3 * index.vertex_index + 0] } } }));

            // uv_buf.reset(new VertexBuffers({ { { attrib.texcoords[2 * index.texcoord_index + 0],
            //     1.0f - attrib.texcoords[2 * index.texcoord_index + 1] } } }));

            // m_positions.push_back(attrib.vertices[3 * index.vertex_index + 0]);
            // m_positions.push_back(attrib.vertices[3 * index.vertex_index + 1]);
            // m_positions.push_back(attrib.vertices[3 * index.vertex_index + 2]);

            // m_uv.push_back(attrib.texcoords[2 * index.texcoord_index + 0]);
            // m_uv.push_back(1.0f - attrib.texcoords[2 * index.texcoord_index + 1]);

            m_index.push_back(m_index.size());
            positions.emplace_back(Vector3<float> {
                attrib.vertices[3 * index.vertex_index + 0],
                attrib.vertices[3 * index.vertex_index + 1],
                attrib.vertices[3 * index.vertex_index + 2] });
            uvs.push_back(Vector2<float> {
                attrib.texcoords[2 * index.texcoord_index + 0],
                1.0f - attrib.texcoords[2 * index.texcoord_index + 1] });
        }
    }
    position_buf.reset(new VertexBuffers(std::move(positions)));
    uv_buf.reset(new VertexBuffers(std::move(uvs)));

    // texture.reset(new Texture(texture_path));
}
Mesh::~Mesh() { }
}
