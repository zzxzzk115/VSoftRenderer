//
// Vector3.h
//
// Created or modified by Kexuan Zhang on 2023/10/28 17:56.
//

#pragma once

namespace VSoftRenderer
{
    struct Vector3
    {
        float X;
        float Y;
        float Z;

        Vector3() : X(0.0f), Y(0.0f), Z(0.0f) {}
        Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}

        Vector3 CrossProduct(const Vector3& other) const
        {
            return {Y * other.Z - Z * other.Y, Z * other.X - X * other.Z, X * other.Y - Y * other.X };
        }
    };
} // namespace VSoftRenderer