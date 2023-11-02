//
// Triangle3D.cpp
//
// Created or modified by Kexuan Zhang on 2023/10/30 9:32.
//

#include "VSoftRenderer/Triangle3D.h"
#include "VSoftRenderer/FrameBuffer.h"
#include "VSoftRenderer/Line.h"
#include "VSoftRenderer/Utils.h"
#include "VSoftRenderer/VGL.h"

#include <algorithm>

namespace VSoftRenderer
{
    std::shared_ptr<Triangle3D> Triangle3D::s_Instance = nullptr;

    Triangle3D::Triangle3D(const Vector3Float& v0,
                           const Vector3Float& v1,
                           const Vector3Float& v2)
    {
        m_Vertices[0] = v0;
        m_Vertices[1] = v1;
        m_Vertices[2] = v2;
    }

    Triangle3D::Triangle3D(const Vector3Int& v0,
                           const Vector3Int& v1,
                           const Vector3Int& v2)
    {
        m_Vertices[0] = Utils::Vector3Int2Float(v0);
        m_Vertices[1] = Utils::Vector3Int2Float(v1);
        m_Vertices[2] = Utils::Vector3Int2Float(v2);
    }

    void Triangle3D::DrawWire(const Color& color)
    {
        Line::Draw(m_Vertices[0].DiscardZInt(), m_Vertices[1].DiscardZInt(), color);
        Line::Draw(m_Vertices[1].DiscardZInt(), m_Vertices[2].DiscardZInt(), color);
        Line::Draw(m_Vertices[2].DiscardZInt(), m_Vertices[0].DiscardZInt(), color);
    }

    void Triangle3D::DrawInterpolated(VGLShaderBase* shader)
    {
        Vector3Int p;
        auto aabb = GetAABB();
        for (p.X = aabb.GetMin().X; p.X <= aabb.GetMax().X; ++p.X)
        {
            for (p.Y = aabb.GetMin().Y; p.Y <= aabb.GetMax().Y; ++p.Y)
            {
                Vector3Float bcScreen  = GetBarycentricCoordinates(Utils::Vector3Int2Float(p));
                if (bcScreen.X < 0 || bcScreen.Y < 0 || bcScreen.Z < 0) continue;
                // Interpolate Z value by barycentric coordinates
                p.Z = static_cast<int>(m_Vertices[0].Z * bcScreen.X +
                                       m_Vertices[1].Z * bcScreen.Y +
                                       m_Vertices[2].Z * bcScreen.Z);
                float zBufferValue =
                    FrameBuffer::GetInstance()->GetZBufferValue(static_cast<int>(p.X), static_cast<int>(p.Y));
                if (zBufferValue < p.Z)
                {
                    Color color;
                    bool discard = shader->frag(bcScreen, color);
                    if (!discard)
                    {
                        FrameBuffer::GetInstance()->SetZBufferValue(p.X, p.Y, p.Z);
                        FrameBuffer::GetInstance()->SetPixel(p.X, p.Y, color);
                    }
                }
            }
        }
    }

    AABBFloat Triangle3D::GetAABB() const
    {
        const auto& frameBufferSize = FrameBuffer::GetInstance()->GetSize();
        AABBFloat     aabb;
        Vector2Float  clamp = {static_cast<float>(frameBufferSize.X - 1), static_cast<float>(frameBufferSize.Y - 1)};
        aabb.SetMin(clamp);
        aabb.SetMax({0, 0});

        for (int i = 0; i < 3; ++i)
        {
            auto minX = std::max(0.0f, std::min(aabb.GetMin().X, m_Vertices[i].X));
            auto minY = std::max(0.0f, std::min(aabb.GetMin().Y, m_Vertices[i].Y));
            aabb.SetMin({minX, minY});

            auto maxX = std::min(clamp.X, std::max(aabb.GetMax().X, m_Vertices[i].X));
            auto maxY = std::min(clamp.Y, std::max(aabb.GetMax().Y, m_Vertices[i].Y));
            aabb.SetMax({maxX, maxY});
        }

        return aabb;
    }

    Vector3Float Triangle3D::GetBarycentricCoordinates(const Vector3Float& p) const
    {
        auto PA = m_Vertices[0] - p;
        auto AB = m_Vertices[1] - m_Vertices[0];
        auto AC = m_Vertices[2] - m_Vertices[0];

        Vector3Float u = Vector3Float(AC.X, AB.X, PA.X).CrossProduct(Vector3Float(AC.Y, AB.Y, PA.Y));

        // degenerate triangle
        if (std::abs(u.Z) < 1)
        {
            return Vector3Float(-1, 1, 1);
        }

        float alpha = 1.0f - (u.X + u.Y) / u.Z;
        float beta = u.Y / u.Z;
        float gamma = u.X / u.Z;

        return Vector3Float(alpha, beta, gamma);
    }

    std::shared_ptr<Triangle3D>& Triangle3D::GetInstance()
    {
        if (s_Instance == nullptr)
        {
            s_Instance = std::make_shared<Triangle3D>();
        }

        return s_Instance;
    }

    void Triangle3D::DrawWire(const Vector3Float& v0,
                              const Vector3Float& v1,
                              const Vector3Float& v2,
                              const Color& color)
    {
        auto& instance = GetInstance();
        instance->m_Vertices[0] = v0;
        instance->m_Vertices[1] = v1;
        instance->m_Vertices[2] = v2;
        instance->DrawWire(color);
    }

    void Triangle3D::DrawWire(const Vector3Int & v0,
                              const Vector3Int& v1,
                              const Vector3Int& v2,
                              const Color& color)
    {
        auto& instance = GetInstance();
        instance->m_Vertices[0] = Utils::Vector3Int2Float(v0);
        instance->m_Vertices[1] = Utils::Vector3Int2Float(v1);
        instance->m_Vertices[2] = Utils::Vector3Int2Float(v2);
        instance->DrawWire(color);
    }

    void Triangle3D::DrawInterpolated(const Vector3Float* vertices, VGLShaderBase* shader)
    {
        auto& instance = GetInstance();
        instance->m_Vertices[0] = vertices[0];
        instance->m_Vertices[1] = vertices[1];
        instance->m_Vertices[2] = vertices[2];
        instance->DrawInterpolated(shader);
    }
} // namespace VSoftRenderer