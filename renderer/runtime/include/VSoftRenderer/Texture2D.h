//
// Texture2D.h
//
// Created or modified by Kexuan Zhang on 2023/10/30 18:32.
//

#pragma once

#include "VSoftRenderer/Color.h"

namespace VSoftRenderer
{
    class Texture2D
    {
    public:
        Texture2D(int width, int height, Color* data)
            : m_Width(width), m_Height(height), m_Data(data) {}

        ~Texture2D()
        {
            delete[] m_Data;
            m_Data = nullptr;
        }

        inline int GetWidth() const { return m_Width; }
        inline int GetHeight() const { return m_Height; }

        inline const Color* GetData() { return m_Data; }
        inline Color GetColorAt(float u, float v) const
        {
            int x = static_cast<int>(u * m_Width);
            int y = static_cast<int>((1.0f - v) * m_Height);
            return GetColorAt(x, y);
        }
        inline Color GetColorAt(int x, int y) const
        {
            return m_Data[y * m_Width + x];
        }

    private:
        int    m_Width;
        int    m_Height;
        Color* m_Data;
    };
} // namespace VSoftRenderer