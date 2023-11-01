//
// Vector2.h
//
// Created or modified by Kexuan Zhang on 2023/10/28 15:57.
//

#pragma once

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
    };

    using Vector2Int = Vector2<int>;
    using Vector2Float = Vector2<float>;
} // namespace VSoftRenderer