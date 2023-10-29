//
// RenderConfig.h
//
// Created or modified by Kexuan Zhang on 2023/10/28 19:46.
//

#pragma once

#include "VSoftRenderer/Vector2Int.h"

namespace VSoftRenderer
{
    class RenderConfig
    {
    public:
        static void SetFrameBufferSize(const Vector2Int& size);
        static const Vector2Int& GetFrameBufferSize();

    private:
        static Vector2Int s_FrameBufferSize;
    };

} // namespace VSoftRenderer