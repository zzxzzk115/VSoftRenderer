//
// Color.h
//
// Created or modified by Kexuan Zhang on 2023/10/28 14:52.
//

#pragma once

#include "Vector3.h"
#include <cmath>
#include <stdexcept>

namespace VGL
{
    struct Color
    {
        unsigned char R;
        unsigned char G;
        unsigned char B;
        unsigned char A;

        Color() : R(0), G(0), B(0), A(0) {}
        Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255)
            : R(r), G(g), B(b), A(a) {}

        Color operator + (const Color& other) const;
        Color operator - (const Color& other) const;
        Color operator * (float scalar) const;
        Color operator / (float scalar) const;

        Vector3Float XYZ() const;

        const static Color COLOR_WHITE;
        const static Color COLOR_BLACK;
        const static Color COLOR_RED;
        const static Color COLOR_GREEN;
        const static Color COLOR_BLUE;
        const static Color COLOR_YELLOW;
        const static Color COLOR_ORANGE;
        const static Color COLOR_PURPLE;
        const static Color COLOR_PINK;
    };
} // namespace VGL