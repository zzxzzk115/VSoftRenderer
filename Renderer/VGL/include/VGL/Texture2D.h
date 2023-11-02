//
// Texture2D.h
//
// Created or modified by Kexuan Zhang on 2023/10/30 18:32.
//

#pragma once

#include "VGL/Color.h"

namespace VGL
{
    class Texture2D
    {
    public:
        Texture2D(int width, int height, Color* data)
            : m_Width(width), m_Height(height), m_Data(data) {}

        ~Texture2D();

        inline int GetWidth() const { return m_Width; }
        inline int GetHeight() const { return m_Height; }

        inline const Color* GetData() { return m_Data; }

        Color GetColorAt(float u, float v) const;
        Color GetColorAt(int x, int y) const;

    private:
        int    m_Width;
        int    m_Height;
        Color* m_Data;
    };
} // namespace VGL