//
// Utils.h
//
// Created or modified by Kexuan Zhang on 2023/10/30 11:29.
//

#pragma once

#include "VSoftRenderer/Vector3.h"

namespace VSoftRenderer
{
    class Utils
    {
    public:
        static Vector3Int   World2Screen(const Vector3Float& v);
        static Vector3Float World2ScreenFloat(const Vector3Float& v);
        static Vector3Float Vector3Int2Float(const Vector3Int& v);
        static Vector2Float Vector2Int2Float(const Vector2Int& v);
    };
} // namespace VSoftRenderer