//
// Vector4.h
//
// Created or modified by Kexuan Zhang on 2023/11/1 12:10.
//

#pragma once

#include <stdexcept>
#include <iostream>

namespace VGL
{
    template <typename T>
    struct Vector4
    {
        T X;
        T Y;
        T Z;
        T W;

        Vector4() : X(0), Y(0), Z(0), W(0) {}
        Vector4(T x, T y, T z, T w) : X(x), Y(y), Z(z), W(w) {}
        explicit Vector4(const Vector3<T>& v) : X(v.X), Y(v.Y), Z(v.Z), W(1) {}

        Vector4 operator + (const Vector4& other) const
        {
            return Vector4(X + other.X, Y + other.Y, Z + other.Z, W + other.W);
        }

        Vector4 operator - (const Vector4& other) const
        {
            return Vector4(X - other.X, Y - other.Y, Z - other.Z, W - other.W);
        }

        Vector4 operator * (T scalar) const
        {
            return Vector4(X * scalar, Y * scalar, Z * scalar, W * scalar);
        }

        T& operator[] (size_t index)
        {
            if (index == 0) return X;
            else if (index == 1) return Y;
            else if (index == 2) return Z;
            else if (index == 3) return W;
            throw std::out_of_range("Index out of range");
        }

        const T& operator[] (size_t index) const
        {
            if (index == 0) return X;
            else if (index == 1) return Y;
            else if (index == 2) return Z;
            else if (index == 3) return W;
            throw std::out_of_range("Index out of range");
        }

        inline Vector3<T> ToVector3() const { return Vector3(X, Y, Z);}
        inline Vector3<T> ToPoint3() const { return Vector3(X / W, Y / W, Z / W);}
    };

    using Vector4Int = Vector4<int>;
    using Vector4Float = Vector4<float>;

    template <typename T>
    std::ostream& operator << (std::ostream& s, Vector4<T>& v)
    {
        s << "(" << v.X << ", " << v.Y << ", " << v.Z << ", " << v.W << ")" << std::endl;
        return s;
    }
} // namespace VGL