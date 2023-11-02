//
// Vector3.h
//
// Created or modified by Kexuan Zhang on 2023/10/28 17:56.
//

#pragma once

#include "VGL/Vector2.h"

#include <iostream>
#include <cmath>
#include <stdexcept>

namespace VGL
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
        Vector3(const Vector3<T>& v) : X(static_cast<T>(v.X)), Y(static_cast<T>(v.Y)), Z(static_cast<T>(v.Z)) {}

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
            if (std::abs(scalar) < 1e-6)
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
            if (length < 1e-6)
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
            if (length < 1e-6)
            {
                return Vector3(X, Y, Z);
            }

            return Vector3(X / length, Y / length, Z / length);
        }

        T& operator[] (size_t index)
        {
            if (index == 0) return X;
            else if (index == 1) return Y;
            else if (index == 2) return Z;
            throw std::out_of_range("Index out of range");
        }

        const T& operator[] (size_t index) const
        {
            if (index == 0) return X;
            else if (index == 1) return Y;
            else if (index == 2) return Z;
            throw std::out_of_range("Index out of range");
        }
    };

    using Vector3Int = Vector3<int>;
    using Vector3Float = Vector3<float>;

    template <typename T>
    std::ostream& operator << (std::ostream& s, Vector3<T>& v)
    {
        s << "(" << v.X << ", " << v.Y << ", " << v.Z << ")" << std::endl;
        return s;
    }
} // namespace VGL