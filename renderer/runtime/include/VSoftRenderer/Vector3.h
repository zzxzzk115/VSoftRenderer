//
// Vector3.h
//
// Created or modified by Kexuan Zhang on 2023/10/28 17:56.
//

#pragma once

#include "VSoftRenderer/Vector2.h"

#include <cmath>
#include <stdexcept>

namespace VSoftRenderer
{
    template <typename T>
    struct Vector3
    {
        T X;
        T Y;
        T Z;

        Vector3() : X(0), Y(0), Z(0) {}
        Vector3(T x, T y, T z) : X(x), Y(y), Z(z) {}
        explicit Vector3(const Vector2<T>& v) : X(static_cast<T>(v.X)), Y(static_cast<T>(v.Y)), Z(static_cast<T>(0)) {}

        Vector2Int DiscardZInt() const
        {
            return Vector2Int(X, Y);
        }

        Vector2Float DiscardZFloat() const
        {
            return Vector2Float(X, Y);
        }

        Vector3 operator + (const Vector3& other) const
        {
            return Vector3(X + other.X, Y + other.Y, Z + other.Z);
        }

        Vector3 operator - (const Vector3& other) const
        {
            return Vector3(X - other.X, Y - other.Y, Z - other.Z);
        }

        Vector3 operator * (T scalar) const
        {
            return Vector3(X * scalar, Y * scalar, Z * scalar);
        }

        T operator * (const Vector3& other) const
        {
            return DotProduct(other);
        }

        Vector3 operator / (T scalar) const
        {
            if (std::abs(scalar) < static_cast<T>(1e-6))
            {
                throw std::runtime_error("Divided by Zero!!!");
            }

            return Vector3(X / scalar, Y / scalar, Z / scalar);
        }

        T GetLength() const
        {
            return std::sqrt(X * X + Y * Y + Z * Z);
        }

        T DotProduct(const Vector3& other) const
        {
            return X * other.X + Y * other.Y + Z * other.Z;
        }

        Vector3 CrossProduct(const Vector3& other) const
        {
            return Vector3(Y * other.Z - Z * other.Y, Z * other.X - X * other.Z, X * other.Y - Y * other.X);
        }

        void Normalize()
        {
            T length = GetLength();
            if (length < static_cast<T>(1e-6))
            {
                return;
            }

            X /= length;
            Y /= length;
            Z /= length;
        }

        Vector3 Normalized() const
        {
            T length = GetLength();
            if (length < static_cast<T>(1e-6))
            {
                return Vector3(X, Y, Z);
            }

            return Vector3(X / length, Y / length, Z / length);
        }
    };

    using Vector3Int = Vector3<int>;
    using Vector3Float = Vector3<float>;
} // namespace VSoftRenderer