//
// FrameBuffer.h
//
// Created or modified by Kexuan Zhang on 2023/10/30 0:18.
//

#pragma once

#include "VSoftRenderer/Pixel.h"
#include "VSoftRenderer/Vector2.h"

#include <limits>
#include <stdexcept>

namespace VSoftRenderer
{
    class FrameBuffer
    {
    public:
        FrameBuffer(int width, int height, Pixel* data);
        explicit FrameBuffer(Vector2Int size);

        ~FrameBuffer();

        void Clear(const Color& clearColor);

        void SetSize(int width, int height);

        inline int GetWidth() const { return m_Width; }
        inline int GetHeight() const { return m_Height; }

        inline Vector2Int GetSize() const { return {m_Width, m_Height}; }

        Pixel GetPixel(int x, int y) const;
        void  SetPixel(int x, int y, const Color& color);

        float GetZBufferValue(int x, int y) const;
        void SetZBufferValue(int x, int y, float zValue);

        static FrameBuffer* GetInstance();

    private:
        int    m_Width;
        int    m_Height;
        Pixel* m_PixelData;
        float* m_ZBuffer;

        static FrameBuffer* s_Instance;
    };
} // namespace VSoftRenderer