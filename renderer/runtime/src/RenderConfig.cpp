//
// RenderConfig.cpp
//
// Created or modified by Kexuan Zhang on 2023/10/28 19:48.
//

#include "VSoftRenderer/RenderConfig.h"

namespace VSoftRenderer
{
    Vector2Int RenderConfig::s_FrameBufferSize = {600, 600};

    void RenderConfig::SetFrameBufferSize(const Vector2Int& size) { s_FrameBufferSize = size; }

    const Vector2Int& RenderConfig::GetFrameBufferSize() { return s_FrameBufferSize; }
} // namespace VSoftRenderer