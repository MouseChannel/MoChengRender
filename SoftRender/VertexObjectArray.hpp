#pragma once
#include "SoftRender/BindingAttribute.hpp"
#include "SoftRender/Buffer.hpp"
#include "SoftRender/Helper/Instance.hpp"
#include "SoftRender/Math/Vec.hpp"
#include <map>

namespace SoftRender {
using VertexBuffers = Buffer<Vector<float>>;
using VertexBuffer = Vector<float>;
// class Buffer;
class VertexObjectArray : public Instance<VertexObjectArray> {

public:
    VertexObjectArray();
    ~VertexObjectArray();
    VertexBuffer get_buffer(Vertex_Buffer_Type type, int index)
    {
        return vertex_buffers[type]->get(index);
    }
    void set_buffers(Vertex_Buffer_Type type,
        std::unique_ptr<VertexBuffers> buffer)
    {
        vertex_buffers[type] = std::move(buffer);
    }

    std::map<Vertex_Buffer_Type, std::unique_ptr<VertexBuffers>> vertex_buffers;
    int indices_count = 3;

private:
};

}