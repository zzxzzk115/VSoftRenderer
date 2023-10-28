//
// Triangle.cpp
//
// Created or modified by Kexuan Zhang on 2023/10/28 16:07.
//

#include "VSoftRenderer/Triangle.h"
#include "VSoftRenderer/Extern.h"
#include "VSoftRenderer/Line.h"
#include <algorithm>
#include <stdexcept>

namespace VSoftRenderer
{
    void Triangle::DrawWire(const Color& color)
    {
        Line::Draw(m_V0, m_V1, color);
        Line::Draw(m_V1, m_V2, color);
        Line::Draw(m_V2, m_V0, color);
    }

    void Triangle::DrawFilled(const Color& color)
    {
        // old-school line sweeping
        // first sort the vertices by using bubble sort.
        if (m_V0.Y > m_V1.Y) std::swap(m_V0, m_V1);
        if (m_V0.Y > m_V2.Y) std::swap(m_V0, m_V2);
        if (m_V1.Y > m_V2.Y) std::swap(m_V1, m_V2);

        // get total height
        int totalHeight = m_V2.Y - m_V0.Y;

        // draw from bottom to mid
        for (int y = m_V0.Y; y < m_V1.Y; ++y)
        {
            int segmentHeight = m_V1.Y - m_V0.Y + 1;

            float alpha = static_cast<float>(y - m_V0.Y) / totalHeight;
            float beta = static_cast<float>(y - m_V0.Y) / segmentHeight;
            Vector2Int a = m_V0 + (m_V2 - m_V0) * alpha;
            Vector2Int b = m_V0 + (m_V1 - m_V0) * beta;
            if (a.X > b.X) std::swap(a, b);
            for (int j = a.X; j <= b.X; ++j)
            {
                VDrawPixel(j, y, color);
            }
        }

        // draw from mid to top
        for (int y = m_V1.Y; y <= m_V2.Y; ++y)
        {
            int segmentHeight = m_V2.Y - m_V1.Y + 1;
            float alpha = static_cast<float>(y - m_V0.Y) / totalHeight;
            float beta = static_cast<float>(y - m_V1.Y) / segmentHeight;
            Vector2Int a = m_V0 + (m_V2 - m_V0) * alpha;
            Vector2Int b = m_V1 + (m_V2 - m_V1) * beta;
            if (a.X > b.X) std::swap(a, b);
            for (int j = a.X; j <= b.X; ++j)
            {
                VDrawPixel(j, y, color);
            }
        }
    }

    void Triangle::DrawWire(Vector2Int v0, Vector2Int v1, Vector2Int v2, const Color& color)
    {
        Triangle tempTriangle(v0, v1, v2);
        tempTriangle.DrawWire(color);
    }

    void Triangle::DrawFilled(Vector2Int v0, Vector2Int v1, Vector2Int v2, const Color& color)
    {
        Triangle tempTriangle(v0, v1, v2);
        tempTriangle.DrawFilled(color);
    }
} // namespace VSoftRenderer