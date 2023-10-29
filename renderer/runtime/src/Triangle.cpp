//
// Triangle.cpp
//
// Created or modified by Kexuan Zhang on 2023/10/28 16:07.
//

#include "VSoftRenderer/Triangle.h"
#include "VSoftRenderer/Extern.h"
#include "VSoftRenderer/Line.h"
#include "VSoftRenderer/RenderConfig.h"

#include <algorithm>

namespace VSoftRenderer
{
    std::shared_ptr<Triangle> Triangle::s_Instance = nullptr;

    void Triangle::DrawWire(const Color& color)
    {
        Line::Draw(m_Vertices[0], m_Vertices[1], color);
        Line::Draw(m_Vertices[1], m_Vertices[2], color);
        Line::Draw(m_Vertices[2], m_Vertices[0], color);
    }

    void Triangle::DrawFilled(const Color& color) const
    {
        Vector2Int p;
        auto aabb = GetAABB();
        for (p.X = aabb.GetMin().X; p.X <= aabb.GetMax().X; ++p.X)
        {
            for (p.Y = aabb.GetMin().Y; p.Y <= aabb.GetMax().Y; ++p.Y)
            {
                Vector3 bcScreen  = GetBarycentricCoordinates(p);
                if (bcScreen.X < 0 || bcScreen.Y < 0 || bcScreen.Z < 0) continue;
                VDrawPixel(p.X, p.Y, color);
            }
        }
    }

    void Triangle::DrawFilledSweeping(const Color& color)
    {
        // old-school line sweeping
        // first sort the vertices by using bubble sort.
        if (m_Vertices[0].Y > m_Vertices[1].Y) std::swap(m_Vertices[0], m_Vertices[1]);
        if (m_Vertices[0].Y > m_Vertices[2].Y) std::swap(m_Vertices[0], m_Vertices[2]);
        if (m_Vertices[1].Y > m_Vertices[2].Y) std::swap(m_Vertices[1], m_Vertices[2]);
        
        // get total height
        int totalHeight = m_Vertices[2].Y - m_Vertices[0].Y;

        // draw from bottom to mid
        for (int y = m_Vertices[0].Y; y < m_Vertices[1].Y; ++y)
        {
            int segmentHeight = m_Vertices[1].Y - m_Vertices[0].Y + 1;

            float alpha = static_cast<float>(y - m_Vertices[0].Y) / totalHeight;
            float beta = static_cast<float>(y - m_Vertices[0].Y) / segmentHeight;
            Vector2Int a = m_Vertices[0] + (m_Vertices[2] - m_Vertices[0]) * alpha;
            Vector2Int b = m_Vertices[0] + (m_Vertices[1] - m_Vertices[0]) * beta;
            if (a.X > b.X) std::swap(a, b);
            for (int j = a.X; j <= b.X; ++j)
            {
                VDrawPixel(j, y, color);
            }
        }

        // draw from mid to top
        for (int y = m_Vertices[1].Y; y <= m_Vertices[2].Y; ++y)
        {
            int segmentHeight = m_Vertices[2].Y - m_Vertices[1].Y + 1;
            float alpha = static_cast<float>(y - m_Vertices[0].Y) / totalHeight;
            float beta = static_cast<float>(y - m_Vertices[1].Y) / segmentHeight;
            Vector2Int a = m_Vertices[0] + (m_Vertices[2] - m_Vertices[0]) * alpha;
            Vector2Int b = m_Vertices[1] + (m_Vertices[2] - m_Vertices[1]) * beta;
            if (a.X > b.X) std::swap(a, b);
            for (int j = a.X; j <= b.X; ++j)
            {
                VDrawPixel(j, y, color);
            }
        }
    }

    AABB Triangle::GetAABB() const
    {
        const auto& frameBufferSize = RenderConfig::GetFrameBufferSize();
        AABB aabb;
        Vector2Int clamp = {frameBufferSize.X - 1, frameBufferSize.Y - 1};
        aabb.SetMin(clamp);
        aabb.SetMax({0, 0});

        for (int i = 0; i < 3; ++i)
        {
            auto minX = std::max(0, std::min(aabb.GetMin().X, m_Vertices[i].X));
            auto minY = std::max(0, std::min(aabb.GetMin().Y, m_Vertices[i].Y));
            aabb.SetMin({minX, minY});

            auto maxX = std::min(clamp.X, std::max(aabb.GetMax().X, m_Vertices[i].X));
            auto maxY = std::min(clamp.Y, std::max(aabb.GetMax().Y, m_Vertices[i].Y));
            aabb.SetMax({maxX, maxY});
        }

        return aabb;
    }

    Vector3 Triangle::GetBarycentricCoordinates(Vector2Int p) const
    {
        Vector2Int PA(m_Vertices[0].X - p.X, m_Vertices[0].Y - p.Y);
        Vector2Int AB(m_Vertices[1].X - m_Vertices[0].X, m_Vertices[1].Y - m_Vertices[0].Y);
        Vector2Int AC(m_Vertices[2].X - m_Vertices[0].X, m_Vertices[2].Y - m_Vertices[0].Y);

        Vector3 u = Vector3(AC.X, AB.X, PA.X).CrossProduct(Vector3(AC.Y, AB.Y, PA.Y));

        // degenerate triangle
        if (std::abs(u.Z) < 1)
        {
            return Vector3(-1, 1, 1);
        }

        float alpha = 1.0f - (u.X + u.Y) / u.Z;
        float beta = u.Y / u.Z;
        float gamma = u.X / u.Z;

        return Vector3(alpha, beta, gamma);
    }


    std::shared_ptr<Triangle>& Triangle::GetInstance()
    {
        if (s_Instance == nullptr)
        {
            s_Instance = std::make_shared<Triangle>();
        }

        return s_Instance;
    }

    void Triangle::DrawWire(Vector2Int v0, Vector2Int v1, Vector2Int v2, const Color& color)
    {
        auto& instance = GetInstance();
        instance->m_Vertices[0] = v0;
        instance->m_Vertices[1] = v1;
        instance->m_Vertices[2] = v2;
        instance->DrawWire(color);
    }

    void Triangle::DrawFilled(Vector2Int v0, Vector2Int v1, Vector2Int v2, const Color& color)
    {
        auto& instance = GetInstance();
        instance->m_Vertices[0] = v0;
        instance->m_Vertices[1] = v1;
        instance->m_Vertices[2] = v2;
        instance->DrawFilled(color);
    }
    
    void Triangle::DrawFilledSweeping(Vector2Int v0, Vector2Int v1, Vector2Int v2, const Color& color)
    {
        auto& instance = GetInstance();
        instance->m_Vertices[0] = v0;
        instance->m_Vertices[1] = v1;
        instance->m_Vertices[2] = v2;
        instance->DrawFilledSweeping(color);
    }
} // namespace VSoftRenderer