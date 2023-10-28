#pragma once

#include <raylib-cpp.hpp>

namespace VSoftRenderer
{
    class VLine
    {
    public:
        VLine(int x0, int y0, int x1, int y1, const Color& color);
        void Draw() const;

    private:
        int   m_X0;
        int   m_Y0;
        int   m_X1;
        int   m_Y1;
        Color m_Color;
    };
} // namespace VSoftRenderer