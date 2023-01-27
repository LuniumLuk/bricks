#ifndef _VECTOR_H
#define _VECTOR_H

// A relatively simple implementation of 3D vector math.
// Vectors are column vectors.

#include <cmath>
#include <cassert>
#include <algorithm>

template<typename T>
struct Vector2;
template<typename T>
struct Vector3;
template<typename T>
struct Vector4;

template<typename T>
struct Vector2 {
    using dataType = T;
    dataType x, y;

    Vector2()
        : x(static_cast<T>(0))
        , y(static_cast<T>(0)) {}
    Vector2(T s)
        : x(s)
        , y(s) {}
    Vector2(T _x, T _y)
        : x(_x)
        , y(_y) {}
    Vector2(Vector3<T> const& v)
        : x(v.x)
        , y(v.y) {}

    T& operator[] (size_t i) {
        assert(i < 2);
        return (&x)[i];
    }

    T operator[] (size_t i) const {
        assert(i < 2);
        return (&x)[i];
    }

    Vector2 operator- (Vector2 const& other) const {
        return Vector2{
            x - other.x,
            y - other.y,
        };
    }
    Vector2 operator+ (Vector2 const& other) const {
        return Vector2{
            x + other.x,
            y + other.y,
        };
    }
    Vector2 operator* (T scaler) const {
        return Vector2{
            x * scaler,
            y * scaler,
        };
    }
    Vector2 operator/ (T scaler) const {
        return Vector2{
            x / scaler,
            y / scaler,
        };
    }

    static Vector2<T> min(Vector2<T> const& first, Vector2<T> const& second) {
        return Vector2<T>{
            std::min(first.x, second.x),
            std::min(first.y, second.y),
        };
    }

    static Vector2<T> max(Vector2<T> const& first, Vector2<T> const& second) {
        return Vector2<T>{
            std::max(first.x, second.x),
            std::max(first.y, second.y),
        };
    }

    T dot(Vector2 const& other) {
        return x * other.x + y * other.y;
    }

    T cross(Vector2 const& other) {
        return x * other.y - y * other.x;
    }
};

template<typename T>
struct Vector3 {
    using dataType = T;
    union { dataType x, r; };
    union { dataType y, g; };
    union { dataType z, b; };

    Vector3()
        : x(static_cast<T>(0))
        , y(static_cast<T>(0))
        , z(static_cast<T>(0)) {}
    Vector3(T s)
        : x(s)
        , y(s)
        , z(s) {}
    Vector3(T _x, T _y, T _z)
        : x(_x)
        , y(_y)
        , z(_z) {}
    Vector3(Vector4<T> const& v)
        : x(v.x)
        , y(v.y)
        , z(v.z) {}

    T& operator[] (size_t i) {
        assert(i < 3);
        return (&x)[i];
    }

    T operator[] (size_t i) const {
        assert(i < 3);
        return (&x)[i];
    }

    Vector3 operator- (Vector3 const& other) const {
        return Vector3{
            x - other.x,
            y - other.y,
            z - other.z,
        };
    }
    Vector3 operator+ (Vector3 const& other) const {
        return Vector3{
            x + other.x,
            y + other.y,
            z + other.z,
        };
    }
    Vector3 operator* (T scaler) const {
        return Vector3{
            x * scaler,
            y * scaler,
            z * scaler,
        };
    }
    Vector3 operator/ (T scaler) const {
        return Vector3{
            x / scaler,
            y / scaler,
            z / scaler,
        };
    }

    static Vector3<T> min(Vector3<T> const& first, Vector3<T> const& second) {
        return Vector3<T>{
            std::min(first.x, second.x),
            std::min(first.y, second.y),
            std::min(first.z, second.z),
        };
    }

    static Vector3<T> max(Vector3<T> const& first, Vector3<T> const& second) {
        return Vector3<T>{
            std::max(first.x, second.x),
            std::max(first.y, second.y),
            std::max(first.z, second.z),
        };
    }

    T dot(Vector3 const& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3 cross(Vector3 const& other) const {
        return Vector3{
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x,
        };
    }

    Vector3 normalized() const {
        T magnitude = (*this).dot(*this);
        if (magnitude == 0) return (*this);
        T f = 1.0f / sqrtf(magnitude);
        return Vector3{
            x * f,
            y * f,
            z * f,
        };
    }
};

template<typename T>
struct Vector4 {
    using dataType = T;
    union { dataType x, r; };
    union { dataType y, g; };
    union { dataType z, b; };
    union { dataType w, a; };

    Vector4()
        : x(static_cast<T>(0))
        , y(static_cast<T>(0))
        , z(static_cast<T>(0))
        , w(static_cast<T>(0)) {}
    Vector4(T s)
        : x(s)
        , y(s)
        , z(s)
        , w(s) {}
    Vector4(T _x, T _y, T _z, T _w)
        : x(_x)
        , y(_y)
        , z(_z)
        , w(_w) {}
    Vector4(Vector3<T> const& v, T _w)
        : x(v.x)
        , y(v.y)
        , z(v.z)
        , w(_w) {}

    Vector4(Vector4 const& other)
        : x(other.x)
        , y(other.y)
        , z(other.z)
        , w(other.w) {}

    Vector4& operator=(Vector4 const& other) {
        x = other.x;
        y = other.y;
        z = other.z;
        w = other.w;
        return (*this);
    }

    T& operator[] (size_t i) {
        assert(i < 4);
        return (&x)[i];
    }

    T operator[] (size_t i) const {
        assert(i < 4);
        return (&x)[i];
    }

    Vector4 operator- (Vector4 const& other) const {
        return Vector4{
            x - other.x,
            y - other.y,
            z - other.z,
            w - other.w,
        };
    }
    Vector4 operator+ (Vector4 const& other) const {
        return Vector4{
            x + other.x,
            y + other.y,
            z + other.z,
            w + other.w,
        };
    }
    Vector4 operator* (T scaler) const {
        return Vector4{
            x * scaler,
            y * scaler,
            z * scaler,
            w * scaler,
        };
    }
    Vector4 operator/ (T scaler) const {
        return Vector4{
            x / scaler,
            y / scaler,
            z / scaler,
            w / scaler,
        };
    }

    static Vector4<T> min(Vector4<T> const& first, Vector4<T> const& second) {
        return Vector4<T>{
            std::min(first.x, second.x),
            std::min(first.y, second.y),
            std::min(first.z, second.z),
            std::min(first.w, second.w),
        };
    }

    static Vector4<T> max(Vector4<T> const& first, Vector4<T> const& second) {
        return Vector4<T>{
            std::max(first.x, second.x),
            std::max(first.y, second.y),
            std::max(first.z, second.z),
            std::max(first.w, second.w),
        };
    }

    T dot(Vector4 const& other) {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }
};

using float2 = Vector2<float>;
using int2 = Vector2<int>;
using float3 = Vector3<float>;
using int3 = Vector3<int>;
using float4 = Vector4<float>;
using int4 = Vector4<int>;
using colorf = Vector3<float>;

#endif
