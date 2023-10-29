//
// Triangle.h
//
// Created or modified by Kexuan Zhang on 2023/10/28 16:03.
//

#pragma once

#include "VSoftRenderer/Color.h"
#include "VSoftRenderer/Vector2Int.h"
#include "VSoftRenderer/Vector3.h"
#include "VSoftRenderer/AABB.h"

#include <memory>

namespace VSoftRenderer
{
    class Triangle
    {
    public:
        Triangle() = default;
        Triangle(Vector2Int v0, Vector2Int v1, Vector2Int v2)
        {
            m_Vertices[0] = v0;
            m_Vertices[1] = v1;
            m_Vertices[2] = v2;
        }

        void DrawWire(const Color& color);
        void DrawFilled(const Color& color) const;
        void DrawFilledSweeping(const Color& color);

        AABB    GetAABB() const;
        Vector3 GetBarycentricCoordinates(Vector2Int p) const;

        static std::shared_ptr<Triangle>& GetInstance();

        static void DrawWire(Vector2Int v0, Vector2Int v1, Vector2Int v2, const Color& color);
        static void DrawFilled(Vector2Int v0, Vector2Int v1, Vector2Int v2, const Color& color);
        static void DrawFilledSweeping(Vector2Int v0, Vector2Int v1, Vector2Int v2, const Color& color);

    private:
        Vector2Int m_Vertices[3];

        static std::shared_ptr<Triangle> s_Instance;
    };
} // namespace VSoftRenderer