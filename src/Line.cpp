#include "VSoftRenderer/Line.h"

namespace VSoftRenderer
{
    VLine::VLine(int x0, int y0, int x1, int y1, const Color& color)
        : m_X0(x0), m_Y0(y0), m_X1(x1), m_Y1(y1), m_Color(color) {}

    void VLine::Draw() const
    {
        for (int x = m_X0; x <= m_X1; ++x) 
        { 
            float t = (float)(x-m_X0) / (m_X1-m_X0); 
            int y = m_Y0 * (1.0f - t) + m_Y1 * t; 
            DrawPixel(x, y, m_Color); 
        } 
    }
} // namespace VSoftRenderer