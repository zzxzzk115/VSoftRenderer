//
// Utils.h
//
// Created or modified by Kexuan Zhang on 2023/10/30 11:29.
//

#pragma once

#include "VGL/Vector3.h"

namespace VGL
{
    class Utils
    {
    public:
        static Vector3Float Vector3Int2Float(const Vector3Int& v);
        static Vector2Float Vector2Int2Float(const Vector2Int& v);
        static Vector3Int   Vector3Float2Int(const Vector3Float& v);
        static Vector2Int   Vector2Float2Int(const Vector2Float& v);
    };
} // namespace VGL