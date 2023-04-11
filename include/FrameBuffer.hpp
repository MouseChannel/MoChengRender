// #include "Description.hpp"
#pragma once
#include "Math/DataStruct.hpp"
#include <map>
#include <memory>
#include <vector>

namespace SoftRender {

class FrameBuffer {
public:
    FrameBuffer(int weight, int height);
    ~FrameBuffer();
    void add_fragments(std::vector<Fragment> fragments);
    [[nodiscard]] auto get(int x, int y) { return datas[x * weight + y]; }
    void set_data(int x, int y, std::pair<Color, float> data)
    {
        datas[x * weight + y] = data;
    }
    void reset();
    [[nodiscard]] auto& get_data() { return m_data; }

private:
    int weight, height;
    std::vector<std::pair<Color, float>> datas;
    std::map<Position2D, Fragment> m_data;
};
}