//
// Line.h
//
// Created or modified by Kexuan Zhang on 2023/10/28 15:50.
//

#pragma once

#include "VSoftRenderer/Color.h"
#include "VSoftRenderer/Vector2.h"

#include <memory>

namespace VSoftRenderer
{
    class Line
    {
    public:
        Line() : m_P0(0, 0), m_P1(0, 0) {}
        Line(int x0, int y0, int x1, int y1) : m_P0(x0, y0), m_P1(x1, y1) {}
        Line(Vector2Int p0, Vector2Int p1) : m_P0(p0), m_P1(p1) {}

        void Draw(const Color& color) const;

        static std::shared_ptr<Line>& GetInstance();
        static void Draw(int x0, int y0, int x1, int y1, const Color& color);
        static void Draw(const Vector2Int& p0, const Vector2Int& p1, const Color& color);

    private:
        Vector2Int m_P0;
        Vector2Int m_P1;

        static std::shared_ptr<Line> s_Instance;
    };
} // namespace VSoftRenderer