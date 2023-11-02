//
// Utils.cpp
//
// Created or modified by Kexuan Zhang on 2023/10/30 11:31.
//

#include "VSoftRenderer/Utils.h"

namespace VSoftRenderer
{
    Vector3Float Utils::Vector3Int2Float(const Vector3Int& v)
    {
        return Vector3Float(static_cast<float>(v.X),
                            static_cast<float>(v.Y),
                            static_cast<float>(v.Z));
    }

    Vector2Float Utils::Vector2Int2Float(const Vector2Int& v)
    {
        return Vector2Float(static_cast<float>(v.X),
                            static_cast<float>(v.Y));
    }

    Vector3Int Utils::Vector3Float2Int(const Vector3Float& v)
    {
        return Vector3Int(static_cast<int>(v.X),
                            static_cast<int>(v.Y),
                            static_cast<int>(v.Z));
    }

    Vector2Int Utils::Vector2Float2Int(const Vector2Float& v)
    {
        return Vector2Int(static_cast<int>(v.X),
                            static_cast<int>(v.Y));
    }
} // namespace VSoftRenderer