//
// Vector2.h
//
// Created or modified by Kexuan Zhang on 2023/10/28 15:57.
//

#pragma once

#include <iostream>
#include <stdexcept>

namespace VSoftRenderer
{
    template <typename T>
    struct Vector2
    {
        T X;
        T Y;

        Vector2() : X(0), Y(0) {}
        Vector2(T x, T y) : X(x), Y(y) {}

        Vector2 operator + (const Vector2& other) const
        {
            return Vector2(X + other.X, Y + other.Y);
        }

        Vector2 operator - (const Vector2& other) const
        {
            return Vector2(X - other.X, Y - other.Y);
        }

        Vector2 operator * (T scalar) const
        {
            return Vector2(X * scalar, Y * scalar);
        }

        T& operator[] (size_t index)
        {
            if (index == 0) return X;
            else if (index == 1) return Y;
            throw std::out_of_range("Index out of range");
        }

        const T& operator[] (size_t index) const
        {
            if (index == 0) return X;
            else if (index == 1) return Y;
            throw std::out_of_range("Index out of range");
        }
    };

    using Vector2Int = Vector2<int>;
    using Vector2Float = Vector2<float>;

    template <typename T>
    std::ostream& operator << (std::ostream& s, Vector2<T>& v)
    {
        s << "(" << v.X << ", " << v.Y << ")" << std::endl;
        return s;
    }
} // namespace VSoftRenderer