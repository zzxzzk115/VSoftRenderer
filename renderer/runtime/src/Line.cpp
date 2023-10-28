//
// Line.cpp
//
// Created or modified by Kexuan Zhang on 2023/10/28 15:50.
//

#include "VSoftRenderer/Line.h"
#include "VSoftRenderer/Extern.h"

#include <algorithm>

namespace VSoftRenderer
{
    Line::Line(int x0, int y0, int x1, int y1, const Color& color)
        : m_X0(x0), m_Y0(y0), m_X1(x1), m_Y1(y1), m_Color(color) {}

    void Line::Draw()
    {
        bool steep = false;
        if (std::abs(m_X0 - m_X1) < std::abs(m_Y0 - m_Y1))
        {
            // steep, then transpose
            std::swap(m_X0, m_Y0);
            std::swap(m_X1, m_Y1);
            steep = true;
        }

        // left to right order
        if (m_X0 > m_X1)
        {
            std::swap(m_X0, m_X1);
            std::swap(m_Y0, m_Y1);
        }

        int dx = m_X1 - m_X0;
        int dy = m_Y1 - m_Y0;
        float derror2 = std::abs(dy) * 2;
        float error2 = 0;
        int y = m_Y0;

        for (int x = m_X0; x <= m_X1; ++x) 
        {
            if (steep)
            {
                VDrawPixel(y, x, m_Color);
            }
            else
            {
                VDrawPixel(x, y, m_Color);
            }
            error2 += derror2;
            if (error2 > dx)
            {
                y += (m_Y1 > m_Y0 ? 1 : -1);
                error2 -= dx * 2;
            }
        } 
    }

    void Line::Draw(int x0, int y0, int x1, int y1, const Color& color)
    {
        Line tempLine(x0, y0, x1, y1, color);
        tempLine.Draw();
    }
} // namespace VSoftRenderer