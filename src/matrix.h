#ifndef _MATRIX_H
#define _MATRIX_H

// A relatively simple implementation of 3D matrix math.
// Matrix is implemented as column major.

#include "vector.h"
#include <cassert>
#include <cmath>

template<typename T>
struct Matrix4 {
    using dataType = T;
    Vector4<T> col[4];

    Matrix4() = default;
    Matrix4(
        T m00, T m01, T m02, T m03, 
        T m10, T m11, T m12, T m13, 
        T m20, T m21, T m22, T m23, 
        T m30, T m31, T m32, T m33 )
        : col{{m00, m10, m20, m30},
              {m01, m11, m21, m31},
              {m02, m12, m22, m32},
              {m03, m13, m23, m33}} {}

    Matrix4(Matrix4 const& other)
        : col{ other.col[0], other.col[1], other.col[2], other.col[3] } {}

    Matrix4& operator=(Matrix4 const& other) {
        col[0] = other.col[0];
        col[1] = other.col[1];
        col[2] = other.col[2];
        col[3] = other.col[3];
        return (*this);
    }

    Vector4<T>& operator[] (size_t c) {
        return col[c];
    }

    Vector4<T> const operator[] (size_t c) const {
        return col[c];
    }
    
    Vector4<T> row(size_t r) const {
        assert(r < 4);
        return Vector4<T>{
            col[0][r],
            col[1][r],
            col[2][r],
            col[3][r],
        };
    }

    static Matrix4 identity() {
        return Matrix4{
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f,
        };
    }
};

template<typename T>
Matrix4<T> operator*(Matrix4<T> const& first, Matrix4<T> const& second) {
    Matrix4<T> m;
    m.col[0] = first * second.col[0];
    m.col[1] = first * second.col[1];
    m.col[2] = first * second.col[2];
    m.col[3] = first * second.col[3];
    return m;
}

template<typename T>
Vector4<T> operator*(Matrix4<T> const& first, Vector4<T> const& second) {
    return Vector4<T>{
        first.row(0).dot(second),
        first.row(1).dot(second),
        first.row(2).dot(second),
        first.row(3).dot(second),
    };
}

using float4x4 = Matrix4<float>;
using int4x4 = Matrix4<int>;

#endif
