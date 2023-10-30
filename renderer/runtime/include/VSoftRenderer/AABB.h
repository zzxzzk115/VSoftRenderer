//
// AABB.h
//
// Created or modified by Kexuan Zhang on 2023/10/28 17:48.
//

#pragma once

#include "VSoftRenderer/Vector2.h"

namespace VSoftRenderer
{
    template <typename T>
    class AABB
    {
    public:
        AABB() : m_Min(), m_Max() {}

        void SetMin(const T& min) { m_Min = min; }
        void SetMax(const T& max) { m_Max = max; }

        const T& GetMin() const { return m_Min; }
        const T& GetMax() const { return m_Max; }

    private:
        T m_Min;
        T m_Max;
    };

    using AABBInt = AABB<Vector2Int>;
    using AABBFloat = AABB<Vector2Float>;
} // namespace VSoftRenderer