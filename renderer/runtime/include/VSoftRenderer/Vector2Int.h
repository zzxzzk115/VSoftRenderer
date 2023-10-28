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

        Vector2Int(int x, int y) : X(x), Y(y) {}
    };
} // namespace VSoftRenderer