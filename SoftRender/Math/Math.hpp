#pragma once

#include "SDL.h"

#include "SoftRender/Math/Vec.hpp"

#include <stdint.h>
#include <variant>

class math {
public:
    template <typename T>
    static void swap(T& a, T& b)
    {
        T c;
        c = b;
        b = a;
        a = c;
    }

    template <Check T>
    static T lerp(T x1, T x2, float weight)
    {
        return x1 + (x2 - x1) * weight;
    }

    template <Check T>
    static T lerp(T a, T b, T c, float weight_a, float weight_b,
        float weight_c)
    {
        return a * weight_a + b * weight_b + c * weight_c;
    }
};

struct Position2D : public Vector2<int> {

    Position2D()
        : Vector2<int> { 0, 0 }

    {
    }
    Position2D(int _x, int _y)
        : Vector2<int> { _x, _y }

    {
    }
    Position2D(Vector2<int> value)
        : Vector2<int> {
            value[0], value[1]
        }
    {
    }
};
struct Color : Vector3<uint8_t> {

    Color()
        : Vector3<uint8_t> { 0, 0, 0 }
    {
    }
    Color(uint8_t _r, uint8_t _g, uint8_t _b)
        : Vector3<uint8_t> { _r, _g, _b }

    {
    }
    Color(Vector<uint8_t>&& value)
        : Vector3<uint8_t> { value[0], value[1], value[2] }
    {
    }
    uint8_t& r() { return value[0]; }
    uint8_t& g() { return value[1]; }
    uint8_t& b() { return value[2]; }
};
struct Point {
    Position2D pos;
    Color color;
};
