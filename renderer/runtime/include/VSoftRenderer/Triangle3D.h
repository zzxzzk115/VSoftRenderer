//
// Triangle3D.h
//
// Created or modified by Kexuan Zhang on 2023/10/30 9:29.
//

#pragma once

#include "VSoftRenderer/AABB.h"
#include "VSoftRenderer/Color.h"
#include "VSoftRenderer/Vector3.h"
#include "VSoftRenderer/Texture2D.h"

#include <memory>

namespace VSoftRenderer
{
    struct VGLShaderBase;

    class Triangle3D
    {
    public:
        Triangle3D() = default;
        Triangle3D(const Vector3Float& v0, const Vector3Float& v1, const Vector3Float& v2);
        Triangle3D(const Vector3Int& v0, const Vector3Int& v1, const Vector3Int& v2);

        void DrawWire(const Color& color);
        void DrawInterpolated(VGLShaderBase* shader);

        AABBFloat GetAABB() const;

        Vector3Float GetBarycentricCoordinates(const Vector3Float& p) const;

        static std::shared_ptr<Triangle3D>& GetInstance();

        static void DrawWire(const Vector3Float& v0, const Vector3Float& v1, const Vector3Float& v2, const Color& color);
        static void DrawInterpolated(const Vector3Float* vertices, VGLShaderBase* shader);

        static void DrawWire(const Vector3Int & v0, const Vector3Int& v1, const Vector3Int& v2, const Color& color);
        static void DrawInterpolated(const Vector3Int& v0, const Vector3Int& v1, const Vector3Int& v2, const Vector2Float* uvCoords, const Texture2D& texture, float intensity);

    private:
        Vector3Float m_Vertices[3];

        static std::shared_ptr<Triangle3D> s_Instance;
    };
} // namespace VSoftRenderer