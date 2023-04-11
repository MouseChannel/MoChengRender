#pragma once
#include "Math/Vec.hpp"
#include <cassert>
#include <cstdint>
#include <vector>

namespace SoftRender {
template <typename T>
class Buffer {
public:
    Buffer(std::vector<T>&& _data)
        : size(_data.size())
        , mapped(true)
    {
        data = std::move(_data);
    }
    // Buffer(Vector<T> _data) { data = _data.value; }
    Buffer(uint32_t size, T* _data)
        : size(size)
        , mapped(true)
    {
        data.insert(data.end(), _data, _data + size);
    }
    Buffer(Buffer&& other)
        : size { other.get_size() }
    {
        data = std::move(other.get_all_data());
    }
    Buffer(Buffer& other) = delete;
    Buffer() = delete;
    ~Buffer() { }
    T& operator[](int index) { return data[index]; }
    void add(std::vector<T> _data)
    {
        data.push_back(_data);
        size = data.size();
    }
    [[nodiscard]] auto& get(int index) { return data[index]; }
    [[nodiscard]] std::unique_ptr<Buffer> get_slice(int start, int end)
    {
        assert(start >= 0 && end <= get_size() && start <= end);

        std::vector<T> res_data;
        for (int i = start; i < end; i++) {
            res_data.push_back(get(i));
        }
        return res_data;
    }
    [[nodiscard("Missing data")]] auto& get_all_data() { return data; }
    [[nodiscard("missing size")]] auto get_size() { return size; }

private:
    uint32_t size;
    std::vector<T> data;

    bool mapped = false;
};

}