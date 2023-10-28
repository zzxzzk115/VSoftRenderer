#include "VSoftRenderer/VLine.h"

#include <algorithm>

namespace VSoftRenderer
{
    VLine::VLine(int x0, int y0, int x1, int y1, const Color& color)
        : m_X0(x0), m_Y0(y0), m_X1(x1), m_Y1(y1), m_Color(color) {}

    void VLine::Draw()
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
        float derror = std::abs(dy / static_cast<float>(dx));
        float error = 0;
        int y = m_Y0;

        for (int x = m_X0; x <= m_X1; ++x) 
        {
            if (steep)
            {
                DrawPixel(y, x, m_Color);
            }
            else
            {
                DrawPixel(x, y, m_Color);
            }
            error += derror;
            if (error > 0.5f)
            {
                y += (m_Y1 > m_Y0 ? 1 : -1);
                error -= 1.0f;
            }
        } 
    }

    void VLine::Draw(int x0, int y0, int x1, int y1, const Color& color)
    {
        VLine tempLine(x0, y0, x1, y1, color);
        tempLine.Draw();
    }
} // namespace VSoftRenderer