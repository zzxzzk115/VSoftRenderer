//
// Line.cpp
//
// Created or modified by Kexuan Zhang on 2023/10/28 15:50.
//

#include "VSoftRenderer/Line.h"
#include "VSoftRenderer/FrameBuffer.h"

#include <algorithm>

namespace VSoftRenderer
{
    std::shared_ptr<Line> Line::s_Instance = nullptr;

    void Line::Draw(const Color& color) const
    {
        bool steep = false;
        int x0 = m_P0.X;
        int y0 = m_P0.Y;
        int x1 = m_P1.X;
        int y1 = m_P1.Y;
        if (std::abs(x0 - x1) < std::abs(y0 - y1))
        {
            // steep, then transpose
            std::swap(x0, y0);
            std::swap(x1, y1);
            steep = true;
        }

        // left to right order
        if (x0 > x1)
        {
            std::swap(x0, x1);
            std::swap(y0, y1);
        }

        int dx = x1 - x0;
        int dy = y1 - y0;
        float derror2 = std::abs(dy) * 2;
        float error2 = 0;
        int y = y0;

        for (int x = x0; x <= x1; ++x) 
        {
            if (steep)
            {
                FrameBuffer::GetInstance()->SetPixel(y, x, color);
            }
            else
            {
                FrameBuffer::GetInstance()->SetPixel(x, y, color);
            }
            error2 += derror2;
            if (error2 > dx)
            {
                y += (y1 > y0 ? 1 : -1);
                error2 -= dx * 2;
            }
        } 
    }

    std::shared_ptr<Line>& Line::GetInstance()
    {
        if (s_Instance == nullptr)
        {
            s_Instance = std::make_shared<Line>();
        }

        return s_Instance;
    }

    void Line::Draw(int x0, int y0, int x1, int y1, const Color& color)
    {
        auto& instance = GetInstance();
        instance->m_P0 = {x0, y0};
        instance->m_P1 = {x1, y1};
        instance->Draw(color);
    }

    void Line::Draw(const Vector2Int& p0, const Vector2Int& p1, const Color& color)
    {
        auto& instance = GetInstance();
        instance->m_P0 = p0;
        instance->m_P1 = p1;
        instance->Draw(color);
    }
} // namespace VSoftRenderer