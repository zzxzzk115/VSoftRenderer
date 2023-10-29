//
// Vector3.h
//
// Created or modified by Kexuan Zhang on 2023/10/28 17:56.
//

#pragma once

#include <cmath>
#include <stdexcept>

namespace VSoftRenderer
{
    struct Vector3
    {
        float X;
        float Y;
        float Z;

        Vector3() : X(0.0f), Y(0.0f), Z(0.0f) {}
        Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}

        Vector3 operator + (const Vector3& other) const
        {
            return { X + other.X, Y + other.Y, Z + other.Z};
        }

        Vector3 operator - (const Vector3& other) const
        {
            return { X - other.X, Y - other.Y, Z - other.Z};
        }

        Vector3 operator * (float scalar) const
        {
            return { X * scalar, Y * scalar, Z * scalar};
        }

        float operator * (const Vector3& other) const
        {
            return DotProduct(other);
        }

        Vector3 operator / (float scalar) const
        {
            if (std::abs(scalar) < 1e-6)
            {
                throw std::runtime_error("Divided by Zero!!!");
            }

            return { X / scalar, Y / scalar, Z / scalar};
        }

        float GetLength() const
        {
            return std::sqrt(X * X + Y * Y + Z * Z);
        }

        float DotProduct(const Vector3& other) const
        {
            return X * other.X + Y * other.Y + Z * other.Z;
        }

        Vector3 CrossProduct(const Vector3& other) const
        {
            return {Y * other.Z - Z * other.Y, Z * other.X - X * other.Z, X * other.Y - Y * other.X };
        }

        void Normalize()
        {
            float length = GetLength();
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
            float length = GetLength();
            if (length < 1e-6)
            {
                return {X, Y, Z};
            }

            return { X / length, Y / length, Z / length};
        }
    };
} // namespace VSoftRenderer