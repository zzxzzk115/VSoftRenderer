//
// Triangle.cpp
//
// Created or modified by Kexuan Zhang on 2023/10/28 16:07.
//

#include "VSoftRenderer/Triangle.h"
#include "VSoftRenderer/Line.h"

namespace VSoftRenderer
{
    void Triangle::DrawWire(const Color& color)
    {
        Line::Draw(m_V0, m_V1, color);
        Line::Draw(m_V1, m_V2, color);
        Line::Draw(m_V2, m_V0, color);
    }

    void Triangle::DrawWire(Vector2Int v0, Vector2Int v1, Vector2Int v2, const Color& color)
    {
        Triangle tempTriangle(v0, v1, v2);
        tempTriangle.DrawWire(color);
    }
} // namespace VSoftRenderer