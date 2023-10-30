//
// FrameBuffer.h
//
// Created or modified by Kexuan Zhang on 2023/10/30 0:18.
//

#pragma once

#include "VSoftRenderer/Pixel.h"
#include "VSoftRenderer/RenderConfig.h"

#include <limits>
#include <stdexcept>

namespace VSoftRenderer
{
    class FrameBuffer
    {
    public:
        FrameBuffer(int width, int height, Pixel* data)
            : m_Width(width), m_Height(height),
              m_PixelData(data)
        {
            m_ZBuffer = new float [width * height];
            for (int i = 0; i < width * height; ++i)
            {
                m_ZBuffer[i] = -std::numeric_limits<float>::max();
            }
        }
        explicit FrameBuffer(Vector2Int size)
            : m_Width(size.X), m_Height(size.Y),
              m_PixelData(new Pixel[size.X * size.Y])
        {
            m_ZBuffer = new float [size.X * size.Y];
            for (int i = 0; i < size.X * size.Y; ++i)
            {
                m_ZBuffer[i] = -std::numeric_limits<float>::max();
            }
        }

        ~FrameBuffer()
        {
            delete[] m_PixelData;
            delete[] m_ZBuffer;

            m_PixelData = nullptr;
            m_ZBuffer = nullptr;
        }

        void SetSize(int width, int height)
        {
            m_PixelData = new Pixel[width * height];
            m_ZBuffer = new float[width * height];
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

        inline float GetZBufferValue(int x, int y) const
        {
            if (x < 0 || x > m_Width || y < 0 || y > m_Height)
            {
                throw std::runtime_error("Error: Out of range!");
            }
            return m_ZBuffer[y * m_Width + x];
        }

        inline void SetZBufferValue(int x, int y, float zValue)
        {
            if (x < 0 || x > m_Width || y < 0 || y > m_Height)
            {
                throw std::runtime_error("Error: Out of range!");
            }
            m_ZBuffer[y * m_Width + x] = zValue;
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
        float* m_ZBuffer;

        static FrameBuffer* s_Instance;
    };
} // namespace VSoftRenderer