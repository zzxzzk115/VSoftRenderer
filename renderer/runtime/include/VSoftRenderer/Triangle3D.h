//
// Triangle3D.h
//
// Created or modified by Kexuan Zhang on 2023/10/30 9:29.
//

#pragma once

#include "VSoftRenderer/AABB.h"
#include "VSoftRenderer/Color.h"
#include "VSoftRenderer/Vector3.h"

#include <memory>

namespace VSoftRenderer
{
    class Triangle3D
    {
    public:
        Triangle3D() = default;
        Triangle3D(Vector3Float v0, Vector3Float v1, Vector3Float v2)
        {
            m_Vertices[0] = v0;
            m_Vertices[1] = v1;
            m_Vertices[2] = v2;
        }

        void DrawWire(const Color& color);
        void DrawFilled(const Color& color) const;
        void DrawFilledSweeping(const Color& color);

        AABBFloat GetAABB() const;
        Vector3Float GetBarycentricCoordinates(const Vector3Float& p) const;

        static std::shared_ptr<Triangle3D>& GetInstance();

        static void DrawWire(const Vector3Float& v0, const Vector3Float& v1, const Vector3Float& v2, const Color& color);
        static void DrawFilled(const Vector3Float& v0, const Vector3Float& v1, const Vector3Float& v2, const Color& color);
        static void DrawFilledSweeping(const Vector3Float& v0, const Vector3Float& v1, const Vector3Float& v2, const Color& color);

        static void DrawWire(const Vector3Int & v0, const Vector3Int& v1, const Vector3Int& v2, const Color& color);
        static void DrawFilled(const Vector3Int& v0, const Vector3Int& v1, const Vector3Int& v2, const Color& color);
        static void DrawFilledSweeping(const Vector3Int& v0, const Vector3Int& v1, const Vector3Int& v2, const Color& color);

    private:
        Vector3Float m_Vertices[3];

        static std::shared_ptr<Triangle3D> s_Instance;
    };
} // namespace VSoftRenderer