//
// Vector2Int.h
//
// Created or modified by Kexuan Zhang on 2023/10/28 15:57.
//

#pragma once

namespace VSoftRenderer
{
    struct Vector2Int
    {
        int X;
        int Y;

        Vector2Int() : X(0), Y(0) {}
        Vector2Int(int x, int y) : X(x), Y(y) {}

        Vector2Int operator + (const Vector2Int& other) const
        {
            return {X + other.X, Y + other.Y};
        }

        Vector2Int operator - (const Vector2Int& other) const
        {
            return {X - other.X, Y - other.Y};
        }

        Vector2Int operator * (float scalar) const
        {
            return {static_cast<int>(X * scalar), static_cast<int>(Y * scalar)};
        }
    };
} // namespace VSoftRenderer