//
// FrameBuffer.h
//
// Created or modified by Kexuan Zhang on 2023/10/30 0:18.
//

#pragma once

#include "VSoftRenderer/Pixel.h"
#include "VSoftRenderer/RenderConfig.h"
#include <stdexcept>

namespace VSoftRenderer
{
    class FrameBuffer
    {
    public:
        FrameBuffer() = default;
        FrameBuffer(int width, int height, Pixel* data)
            : m_Width(width), m_Height(height), m_PixelData(data) {}
        explicit FrameBuffer(Vector2Int size)
            : m_Width(size.X), m_Height(size.Y), m_PixelData(new Pixel[size.X * size.Y]) {}
        ~FrameBuffer() { delete[] m_PixelData; m_PixelData = nullptr; }

        void SetSize(int width, int height)
        {
            m_PixelData = new Pixel[width * height];
        }

        int GetWidth() const { return m_Width; }
        int GetHeight() const { return m_Height; }
        Vector2Int GetSize() const { return {m_Width, m_Height}; }

        inline Pixel GetPixel(int x, int y) const
        {
            if (x < 0 || x > m_Width || y < 0 || y > m_Height)
            {
                throw std::runtime_error("Error: Out of range!");
            }
            return m_PixelData[y * m_Width + x];
        }

        inline void SetPixel(int x, int y, const Color& color)
        {
            if (x < 0 || x > m_Width || y < 0 || y > m_Height)
            {
                throw std::runtime_error("Error: Out of range!");
            }
            m_PixelData[y * m_Width + x].PixelColor = color;
        }

        static FrameBuffer* GetInstance()
        {
            if (s_Instance == nullptr)
            {
                s_Instance = new FrameBuffer(RenderConfig::GetFrameBufferSize());
            }
            return s_Instance;
        }

    private:
        int    m_Width;
        int    m_Height;
        Pixel* m_PixelData;

        static FrameBuffer* s_Instance;
    };
} // namespace VSoftRenderer