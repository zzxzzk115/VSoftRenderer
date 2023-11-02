//
// DirectionalLight.h
//
// Created or modified by Kexuan Zhang on 2023/10/30 18:45.
//

#pragma once

#include "VSoftRenderer/Vector3.h"

namespace VSoftRenderer
{
    class DirectionalLight
    {
    public:
        explicit DirectionalLight(Vector3Float direction) : m_Direction(direction) {}

        inline Vector3Float GetDirection() const { return m_Direction; }

    private:
        Vector3Float m_Direction;
    };
} // namespace VSoftRenderer