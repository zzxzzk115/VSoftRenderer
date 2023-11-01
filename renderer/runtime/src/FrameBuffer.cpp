//
// FrameBuffer.cpp
//
// Created or modified by Kexuan Zhang on 2023/10/30 0:46.
//

#include "VSoftRenderer/FrameBuffer.h"

namespace VSoftRenderer
{
    FrameBuffer* FrameBuffer::s_Instance = nullptr;

    FrameBuffer::FrameBuffer(int width, int height, Pixel* data)
        : m_Width(width), m_Height(height),
        m_PixelData(data)
    {
        m_ZBuffer = new float [width * height];
        for (int i = 0; i < width * height; ++i)
        {
            m_ZBuffer[i] = -std::numeric_limits<float>::max();
        }
    }

    FrameBuffer::FrameBuffer(Vector2Int size)
        : m_Width(size.X), m_Height(size.Y),
        m_PixelData(new Pixel[size.X * size.Y])
    {
        m_ZBuffer = new float [size.X * size.Y];
        for (int i = 0; i < size.X * size.Y; ++i)
        {
            m_ZBuffer[i] = -std::numeric_limits<float>::max();
        }
    }

    FrameBuffer::~FrameBuffer()
    {
        delete[] m_PixelData;
        delete[] m_ZBuffer;

        m_PixelData = nullptr;
        m_ZBuffer = nullptr;
    }

    void FrameBuffer::SetSize(int width, int height)
    {
        m_PixelData = new Pixel[width * height];
        m_ZBuffer = new float[width * height];
    }

    Pixel FrameBuffer::GetPixel(int x, int y) const
    {
        if (x < 0 || x > m_Width || y < 0 || y > m_Height)
        {
            throw std::out_of_range("x or y out of range");
        }
        return m_PixelData[y * m_Width + x];
    }

    void FrameBuffer::SetPixel(int x, int y, const Color& color)
    {
        if (x < 0 || x > m_Width || y < 0 || y > m_Height)
        {
            throw std::out_of_range("x or y out of range");
        }
        m_PixelData[y * m_Width + x].PixelColor = color;
    }

    float FrameBuffer::GetZBufferValue(int x, int y) const
    {
        if (x < 0 || x > m_Width || y < 0 || y > m_Height)
        {
            throw std::out_of_range("x or y out of range");
        }
        return m_ZBuffer[y * m_Width + x];
    }

    void FrameBuffer::SetZBufferValue(int x, int y, float zValue)
    {
        if (x < 0 || x > m_Width || y < 0 || y > m_Height)
        {
            throw std::out_of_range("x or y out of range");
        }
        m_ZBuffer[y * m_Width + x] = zValue;
    }

    FrameBuffer* FrameBuffer::GetInstance()
    {
        if (s_Instance == nullptr)
        {
            s_Instance = new FrameBuffer(RenderConfig::GetFrameBufferSize());
        }
        return s_Instance;
    }
} // namespace VSoftRenderer