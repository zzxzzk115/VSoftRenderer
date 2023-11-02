//
// Texture2D.cpp
//
// Created or modified by Kexuan Zhang on 2023/11/1 11:24.
//

#include "VGL/Texture2D.h"

namespace VGL
{
    Texture2D::~Texture2D()
    {
        delete[] m_Data;
        m_Data = nullptr;
    }

    Color Texture2D::GetColorAt(float u, float v) const
    {
        int x = static_cast<int>(u * m_Width);
        int y = static_cast<int>((1.0f - v) * m_Height);
        return GetColorAt(x, y);
    }

    Color Texture2D::GetColorAt(int x, int y) const
    {
        if (x < 0 || x > m_Width || y < 0 || y > m_Height)
        {
            throw std::out_of_range("x or y out of range");
        }
        return m_Data[y * m_Width + x];
    }
} //