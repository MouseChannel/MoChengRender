#pragma once

#include "SDL.h"

#include "SoftRender/Math/Matrix.hpp"
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
    static Mat44<float> translate_matrix(Vector3<float> v)
    {

        Mat44<float> translate_matrix { 1.0f };
        translate_matrix.set_column(3, { v, 1.0f });

        return translate_matrix;
    }
    static Mat44<float> scale_matrix(Vector3<float> v)
    {
        Mat44<float> scale_matrix { 1.0f };
        for (int i = 0; i < 3; i++) {
            scale_matrix.set(i, i, v[i]);
        }
        return scale_matrix;
    }
    static Mat44<float> rotate_matrix(float angle, Vector3<float> dir)
    {
        auto axis = dir.normalize();
        auto x = axis[0], y = axis[1], z = axis[2];
        Mat44<float> res = Mat<float>::Identity(4);
        auto sin = std::sin(angle);
        auto cos = std::cos(angle);
        auto one_minux_cos = 1.0f - cos;
        res.set(0, 0, x * x * one_minux_cos + cos);
        res.set(0, 1, x * y * one_minux_cos - z * sin);
        res.set(0, 2, x * z * one_minux_cos + y * sin);
        res.set(1, 0, x * y * one_minux_cos + z * sin);
        res.set(1, 1, y * y * one_minux_cos + cos);
        res.set(1, 2, y * z * one_minux_cos - x * sin);
        res.set(2, 0, x * z * one_minux_cos - y * sin);
        res.set(2, 1, y * z * one_minux_cos + x * sin);
        res.set(2, 2, z * z * one_minux_cos + cos);
        return res;
    }
    
    /**
     * @brief camera default position at (0,0,0) and look at (0,0,-1)
     *
     * f == -z
     * r == x
     * u == y
     */
    static Mat44<float> view_mat(Vector3<float> position,
        Vector3<float> front)
    {

        Vector3<float> top = { 0, 1, 0 };
        auto t_m = translate_matrix(position * (-1.0f));
        Vector3<float> f = front.normalize();
        Vector3<float> r = front.cross(top).normalize();
        Vector3<float> u = r.cross(f);
        Mat44<float> r_m = Mat<float>::Identity(4);
        r_m.set_row(0, { r, 0 });
        r_m.set_row(1, { u, 0 });
        r_m.set_row(2, { -f, 0 });
        return r_m.mul(t_m);
    }
    static Mat44<float> orthographic(float left, float right, float top,
        float bottom, float near, float far)
    {
        auto t_m = translate_matrix(
            { (left + right) / -2, (top + bottom) / -2, (near + far) / -2 });
        auto s_m = scale_matrix(
            { 2.0f / (right - left), 2.0f / (top - bottom), 2.0f / (near - far) });

        return s_m.mul(t_m);
    }
    static Mat44<float> perspective(float fov, float aspect, float near,
        float far)
    {
        const float wei = 3.14f / 180;

        auto tan_half = std::tan(wei * fov / 2.0f);
        Mat44<float> res { 0 };
        res.set(0, 0, 1.0f / (aspect * tan_half));
        res.set(1, 1, 1.0f / tan_half);
        res.set(2, 2, (-far - near) / (far - near));
        res.set(2, 3, (-2.0f * far * near) / (far - near));
        res.set(3, 2, -1.0f);
        return res;
    }
    static Mat44<float> perspective(float left, float right, float top,
        float bottom, float near, float far)
    {
        Mat44<float> persp_to_ortho = Mat44<float>::Identity(4);
        persp_to_ortho.set(0, 0, near);
        persp_to_ortho.set(1, 1, near);
        persp_to_ortho.set(3, 2, 1);
        persp_to_ortho.set_row(2, { 0, 0, near + far, -near * far });
        persp_to_ortho.set(3, 3, 0);
        auto orr = orthographic(left, right, top, bottom, near, far);
        return orthographic(left, right, top, bottom, near, far).mul(persp_to_ortho);
    }
    static Mat44<float> screen_matrix(const int width, const int height)
    {
        Mat44<float> res { 1 };
        res.set(0, 0, width / 2.0f);
        res.set(1, 1, height / 2.0f);
        res.set(2, 2, 1 / 2.0f);

        res.set_column(3, { width / 2.0f, height / 2.0f, 1 / 2.0f, 1 });

        return res;
    }
};
