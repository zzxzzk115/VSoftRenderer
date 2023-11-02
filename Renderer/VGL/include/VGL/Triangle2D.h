//
// Triangle2D.h
//
// Created or modified by Kexuan Zhang on 2023/10/28 16:03.
//

#pragma once

#include "VGL/AABB.h"
#include "VGL/Color.h"
#include "VGL/Vector2.h"
#include "VGL/Vector3.h"

#include <memory>

namespace VGL
{
    class Triangle2D
    {
    public:
        Triangle2D() = default;
        Triangle2D(Vector2Int v0, Vector2Int v1, Vector2Int v2)
        {
            m_Vertices[0] = v0;
            m_Vertices[1] = v1;
            m_Vertices[2] = v2;
        }

        void DrawWire(const Color& color);
        void DrawFilled(const Color& color) const;
        void DrawFilledSweeping(const Color& color);

        AABBInt GetAABB() const;
        Vector3Float GetBarycentricCoordinates(const Vector2Int& p) const;

        static std::shared_ptr<Triangle2D>& GetInstance();

        static void DrawWire(const Vector2Int& v0, const Vector2Int& v1, const Vector2Int& v2, const Color& color);
        static void DrawFilled(const Vector2Int& v0, const Vector2Int& v1, const Vector2Int& v2, const Color& color);
        static void DrawFilledSweeping(const Vector2Int& v0, const Vector2Int& v1, const Vector2Int& v2, const Color& color);

    private:
        Vector2Int m_Vertices[3];

        static std::shared_ptr<Triangle2D> s_Instance;
    };
} // namespace VGL