//
// Line.h
//
// Created or modified by Kexuan Zhang on 2023/10/28 15:50.
//

#pragma once

#include "VSoftRenderer/Color.h"
#include "VSoftRenderer/Vector2Int.h"

namespace VSoftRenderer
{
    class Line
    {
    public:
        Line(int x0, int y0, int x1, int y1)
            : m_X0(x0), m_Y0(y0), m_X1(x1), m_Y1(y1) {}

        Line(Vector2Int v0, Vector2Int v1)
            : m_X0(v0.X), m_Y0(v0.Y), m_X1(v1.X), m_Y1(v1.Y) {}

        void Draw(const Color& color);

        static void Draw(int x0, int y0, int x1, int y1, const Color& color);
        static void Draw(Vector2Int v0, Vector2Int v1, const Color& color);

    private:
        int   m_X0;
        int   m_Y0;
        int   m_X1;
        int   m_Y1;
    };
} // namespace VSoftRenderer