#include "FrameBuffer.hpp"

namespace SoftRender {
FrameBuffer::FrameBuffer(int weight, int height)
    : weight(weight)
    , height(height)

{
    reset();
}
FrameBuffer::~FrameBuffer() { }
void FrameBuffer::reset()
{
    // datas.resize(weight * height, { Color { 0, 0, 0, 255 }, 1.0f });
    m_data.clear();
}
void FrameBuffer::add_fragments(std::vector<Fragment> fragments)
{

    for (auto& i : fragments) {
        Position2D pos { i.pos.x(), i.pos.y() };

        if (auto v = m_data.find(pos); v != m_data.end()) {
            if (i.depth < v->second.depth) {
                continue;
                // m_data[pos] = i;
            }
        }
        RR temp { .r = i.color.x(), .g = i.color.y(), .b = i.color.z(), .a = i.color.w() };
        m_data[pos] = i;
    }
}
}