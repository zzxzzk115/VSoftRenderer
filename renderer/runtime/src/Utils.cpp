//
// Utils.cpp
//
// Created or modified by Kexuan Zhang on 2023/10/30 11:31.
//

#include "VSoftRenderer/Utils.h"
#include "VSoftRenderer/FrameBuffer.h"

namespace VSoftRenderer
{
    Vector3Int Utils::World2Screen(const Vector3Float& v)
    {
        auto frameBufferSize = FrameBuffer::GetInstance()->GetSize();
        auto width = frameBufferSize.X;
        auto height = frameBufferSize.Y;
        return {
            static_cast<int>((v.X+1.0f)*width/2.0f+0.5f),
            static_cast<int>((v.Y+1.0f)*height/2.0f+0.5f),
            static_cast<int>(v.Z) };
    }

    Vector3Float Utils::World2ScreenFloat(const Vector3Float& v)
    {
        auto result = World2Screen(v);
        return {
            static_cast<float >(result.X),
                static_cast<float>(result.Y),
                static_cast<float>(result.Z)
        };
    }

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
} // namespace VSoftRenderer