//
// Triangle3D.cpp
//
// Created or modified by Kexuan Zhang on 2023/10/30 9:32.
//

#include "VSoftRenderer/Triangle3D.h"
#include "VSoftRenderer/FrameBuffer.h"
#include "VSoftRenderer/Line.h"
#include "VSoftRenderer/RenderConfig.h"
#include "VSoftRenderer/Utils.h"

#include <algorithm>

namespace VSoftRenderer
{
    std::shared_ptr<Triangle3D> Triangle3D::s_Instance = nullptr;

    void Triangle3D::DrawWire(const Color& color)
    {
        Line::Draw(m_Vertices[0].DiscardZInt(), m_Vertices[1].DiscardZInt(), color);
        Line::Draw(m_Vertices[1].DiscardZInt(), m_Vertices[2].DiscardZInt(), color);
        Line::Draw(m_Vertices[2].DiscardZInt(), m_Vertices[0].DiscardZInt(), color);
    }

    void Triangle3D::DrawFilled(const Color& color) const
    {
        Vector3Float p;
        auto aabb = GetAABB();
        for (p.X = aabb.GetMin().X; p.X <= aabb.GetMax().X; ++p.X)
        {
            for (p.Y = aabb.GetMin().Y; p.Y <= aabb.GetMax().Y; ++p.Y)
            {
                Vector3 bcScreen  = GetBarycentricCoordinates(p);
                if (bcScreen.X < 0 || bcScreen.Y < 0 || bcScreen.Z < 0) continue;
                p.Z = 0;
                p.Z += m_Vertices[0].Z * bcScreen.X;
                p.Z += m_Vertices[1].Z * bcScreen.Y;
                p.Z += m_Vertices[2].Z * bcScreen.Z;
                float zBufferValue =
                    FrameBuffer::GetInstance()->GetZBufferValue(static_cast<int>(p.X), static_cast<int>(p.Y));
                if (zBufferValue < p.Z)
                {
                    FrameBuffer::GetInstance()->SetZBufferValue(static_cast<int>(p.X), static_cast<int>(p.Y), p.Z);
                    FrameBuffer::GetInstance()->SetPixel(p.X, p.Y, color);
                }
            }
        }
    }

    void Triangle3D::DrawFilledSweeping(const Color& color)
    {
        auto v0 = m_Vertices[0].DiscardZInt();
        auto v1 = m_Vertices[1].DiscardZInt();
        auto v2 = m_Vertices[2].DiscardZInt();

        // old-school line sweeping
        // first sort the vertices by using bubble sort.
        if (v0.Y > v1.Y) std::swap(v0, v1);
        if (v0.Y > v2.Y) std::swap(v0, v2);
        if (v1.Y > v2.Y) std::swap(v1, v2);

        // get total height
        int totalHeight = v2.Y - v0.Y;

        // draw from bottom to mid
        for (int y = v0.Y; y < v1.Y; ++y)
        {
            int segmentHeight = v1.Y - v0.Y + 1;

            float alpha = static_cast<float>(y - v0.Y) / totalHeight;
            float beta = static_cast<float>(y - v0.Y) / segmentHeight;
            Vector2Int a = v0 + (v2 - v0) * alpha;
            Vector2Int b = v0 + (v1 - v0) * beta;
            if (a.X > b.X) std::swap(a, b);
            for (int j = a.X; j <= b.X; ++j)
            {
                FrameBuffer::GetInstance()->SetPixel(j, y, color);
            }
        }

        // draw from mid to top
        for (int y = v1.Y; y <= v2.Y; ++y)
        {
            int segmentHeight = v2.Y - v1.Y + 1;
            float alpha = static_cast<float>(y - v0.Y) / totalHeight;
            float beta = static_cast<float>(y - v1.Y) / segmentHeight;
            Vector2Int a = v0 + (v2 - v0) * alpha;
            Vector2Int b = v1 + (v2 - v1) * beta;
            if (a.X > b.X) std::swap(a, b);
            for (int j = a.X; j <= b.X; ++j)
            {
                FrameBuffer::GetInstance()->SetPixel(j, y, color);
            }
        }
    }

    AABBFloat Triangle3D::GetAABB() const
    {
        const auto& frameBufferSize = RenderConfig::GetFrameBufferSize();
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

    void Triangle3D::DrawWire(const Vector3Float& v0, const Vector3Float& v1, const Vector3Float& v2, const Color& color)
    {
        auto& instance = GetInstance();
        instance->m_Vertices[0] = v0;
        instance->m_Vertices[1] = v1;
        instance->m_Vertices[2] = v2;
        instance->DrawWire(color);
    }

    void Triangle3D::DrawFilled(const Vector3Float& v0, const Vector3Float& v1, const Vector3Float& v2, const Color& color)
    {
        auto& instance = GetInstance();
        instance->m_Vertices[0] = v0;
        instance->m_Vertices[1] = v1;
        instance->m_Vertices[2] = v2;
        instance->DrawFilled(color);
    }

    void Triangle3D::DrawFilledSweeping(const Vector3Float& v0, const Vector3Float& v1, const Vector3Float& v2, const Color& color)
    {
        auto& instance = GetInstance();
        instance->m_Vertices[0] = v0;
        instance->m_Vertices[1] = v1;
        instance->m_Vertices[2] = v2;
        instance->DrawFilledSweeping(color);
    }

    void Triangle3D::DrawWire(const Vector3Int & v0, const Vector3Int& v1, const Vector3Int& v2, const Color& color)
    {
        auto& instance = GetInstance();
        instance->m_Vertices[0] = Utils::Vector3Int2Float(v0);
        instance->m_Vertices[1] = Utils::Vector3Int2Float(v1);
        instance->m_Vertices[2] = Utils::Vector3Int2Float(v2);
        instance->DrawWire(color);
    }

    void Triangle3D::DrawFilled(const Vector3Int& v0, const Vector3Int& v1, const Vector3Int& v2, const Color& color)
    {
        auto& instance = GetInstance();
        instance->m_Vertices[0] = Utils::Vector3Int2Float(v0);
        instance->m_Vertices[1] = Utils::Vector3Int2Float(v1);
        instance->m_Vertices[2] = Utils::Vector3Int2Float(v2);
        instance->DrawFilled(color);
    }

    void Triangle3D::DrawFilledSweeping(const Vector3Int& v0, const Vector3Int& v1, const Vector3Int& v2, const Color& color)
    {
        auto& instance = GetInstance();
        instance->m_Vertices[0] = Utils::Vector3Int2Float(v0);
        instance->m_Vertices[1] = Utils::Vector3Int2Float(v1);
        instance->m_Vertices[2] = Utils::Vector3Int2Float(v2);
        instance->DrawFilledSweeping(color);
    }
} // namespace VSoftRenderer