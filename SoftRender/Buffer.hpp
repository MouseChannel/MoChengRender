#pragma once
#include <cstdint>
#include <vector>

namespace SoftRender {
template <typename T>
class Buffer {
public:
    Buffer(std::vector<T>&& _data)
        : size(data.size())
        , mapped(true)
    {

        data = std::move(_data);
    }
    Buffer(uint32_t size, T* _data)
        : size(size)
        , mapped(true)
    {
        data.insert(data.end(), _data, _data + size);
    }
    Buffer() = delete;
    ~Buffer() { }
    T& operator[](int index) { return data[index]; }
    [[nodiscard]] auto& get(int index) { return data[index]; }

private:
    uint32_t size;
    std::vector<T> data;

    bool mapped = false;
};

}