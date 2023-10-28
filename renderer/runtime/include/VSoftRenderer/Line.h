//
// Line.h
//
// Created or modified by Kexuan Zhang on 2023/10/28 15:50.
//

#pragma once

#include "VSoftRenderer/Color.h"

namespace VSoftRenderer
{
    class Line
    {
    public:
        Line(int x0, int y0, int x1, int y1, const Color& color);
        void Draw();

        static void Draw(int x0, int y0, int x1, int y1, const Color& color);

    private:
        int   m_X0;
        int   m_Y0;
        int   m_X1;
        int   m_Y1;
        Color m_Color;
    };
} // namespace VSoftRenderer