//
// AABB.h
//
// Created or modified by Kexuan Zhang on 2023/10/28 17:48.
//

#pragma once

#include "VGL/Vector2.h"

namespace VGL
{
    template <typename T>
    class AABB
    {
    public:
        AABB() : m_Min(), m_Max() {}

        inline void SetMin(const T& min) { m_Min = min; }
        inline void SetMax(const T& max) { m_Max = max; }

        inline const T& GetMin() const { return m_Min; }
        inline const T& GetMax() const { return m_Max; }

    private:
        T m_Min;
        T m_Max;
    };

    using AABBInt = AABB<Vector2Int>;
    using AABBFloat = AABB<Vector2Float>;
} // namespace VGL