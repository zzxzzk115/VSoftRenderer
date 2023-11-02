//
// Color.cpp
//
// Created or modified by Kexuan Zhang on 2023/10/28 15:12.
//

#include "VGL/Color.h"

namespace VGL
{
    const Color Color::COLOR_WHITE = {255, 255, 255, 255};
    const Color Color::COLOR_BLACK = {0, 0, 0, 255};
    const Color Color::COLOR_RED = {255, 0, 0, 255};
    const Color Color::COLOR_GREEN = {0, 255, 0, 255};
    const Color Color::COLOR_BLUE = {0, 0, 255, 255};
    const Color Color::COLOR_YELLOW = {255, 255, 0, 255};
    const Color Color::COLOR_ORANGE = {255, 165, 0, 255};
    const Color Color::COLOR_PURPLE = {128, 0, 128, 255};
    const Color Color::COLOR_PINK = {255, 192, 203, 255};

    Color Color::operator + (const Color& other) const
    {
        return { static_cast<unsigned char>(R + other.R),
                static_cast<unsigned char>(G + other.G),
                static_cast<unsigned char>(B + other.B),
                static_cast<unsigned char>(A + other.A) };
    }

    Color Color::operator - (const Color& other) const
    {
        return { static_cast<unsigned char>(R - other.R),
                static_cast<unsigned char>(G - other.G),
                static_cast<unsigned char>(B - other.B),
                static_cast<unsigned char>(A - other.A) };
    }

    Color Color::operator * (float scalar) const
    {
        return { static_cast<unsigned char>(R * scalar),
                static_cast<unsigned char>(G * scalar),
                static_cast<unsigned char>(B * scalar),
                static_cast<unsigned char>(A * scalar) };
    }

    Color Color::operator / (float scalar) const
    {
        if (std::abs(scalar) < 1e-6)
        {
            throw std::runtime_error("Divided by Zero!!!");
        }
        return { static_cast<unsigned char>(R / scalar),
                static_cast<unsigned char>(G / scalar),
                static_cast<unsigned char>(B / scalar),
                static_cast<unsigned char>(A / scalar) };
    }
} // namespace VGL