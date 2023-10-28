//
// Triangle.h
//
// Created or modified by Kexuan Zhang on 2023/10/28 16:03.
//

#pragma once

#include "VSoftRenderer/Color.h"
#include "VSoftRenderer/Vector2Int.h"

namespace VSoftRenderer
{
    class Triangle
    {
    public:
        Triangle(Vector2Int v0, Vector2Int v1, Vector2Int v2)
            : m_V0(v0), m_V1(v1), m_V2(v2) {}

        void DrawWire(const Color& color);

        static void DrawWire(Vector2Int v0, Vector2Int v1, Vector2Int v2, const Color& color);

    private:
        Vector2Int m_V0;
        Vector2Int m_V1;
        Vector2Int m_V2;
    };
} // namespace VSoftRenderer