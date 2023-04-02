#pragma once
#include "SoftRender/Math/Vec.hpp"
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
struct Position3D : public Vector3<float> {

    Position3D()
        : Vector3<float> { 0, 0, 0 }

    {
    }
    Position3D(float _x, float _y, float _z)
        : Vector3<float> { _x, _y, _z }

    {
    }
    Position3D(Vector3<float> value)
        : Vector3<float> {
            value[0], value[1], value[2]
        }
    {
    }
};
struct Color : Vector4<uint8_t> {

    Color()
        : Vector4<uint8_t>()
    {
    }
    Color(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a)
        : Vector4<uint8_t> { _r, _g, _b, _a }

    {
    }
    Color(Vector<uint8_t>&& value)
        : Vector4<uint8_t> { value[0], value[1], value[2], value[3] }
    {
    }
    uint8_t& r() { return x(); }
    uint8_t& g() { return y(); }
    uint8_t& b() { return z(); }
    uint8_t& a() { return w(); }
};
struct Point2D {
    Position2D pos;
    Color color;
};
struct Point3D {
    Position3D pos;
    Color color;
};