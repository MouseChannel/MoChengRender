#pragma once
#include <cassert>
#include <memory>

namespace SoftRender {

template <typename T>
class Instance {
public:
    static std::unique_ptr<T> _instance;
    static std::unique_ptr<T>& Get_Instance()
    {
        if (!_instance) {
            _instance.reset(new T);
        }
        assert(_instance);
        return _instance;
    }
};
template <typename T>
std::unique_ptr<T> Instance<T>::_instance = nullptr;
}