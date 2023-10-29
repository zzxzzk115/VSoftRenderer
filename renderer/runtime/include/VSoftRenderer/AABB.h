//
// AABB.h
//
// Created or modified by Kexuan Zhang on 2023/10/28 17:48.
//

#pragma once

#include "VSoftRenderer/Vector2Int.h"

namespace VSoftRenderer
{
    class AABB
    {
    public:
        AABB() : m_Min(0, 0), m_Max(0, 0) {}

        void SetMin(Vector2Int min) { m_Min = min; }
        void SetMax(Vector2Int max) { m_Max = max; }

        const Vector2Int& GetMin() const { return m_Min;}
        const Vector2Int& GetMax() const { return m_Max;}

    private:
        Vector2Int m_Min;
        Vector2Int m_Max;
    };
} // namespace VSoftRenderer