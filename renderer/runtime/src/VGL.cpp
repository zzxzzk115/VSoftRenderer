//
// VGL.cpp
//
// Created or modified by Kexuan Zhang on 2023/11/1 14:56.
//

#include "VSoftRenderer/VGL.h"
#include "VSoftRenderer/FrameBuffer.h"

namespace VSoftRenderer
{
    VGLState g_vglState = {};

    void glClearColor(float r, float g, float b, float a)
    {
        // clamp
        r = std::max(0.0f, std::min(r, 1.0f));
        g = std::max(0.0f, std::min(g, 1.0f));
        b = std::max(0.0f, std::min(b, 1.0f));
        a = std::max(0.0f, std::min(a, 1.0f));

        g_vglState.ClearColor = {
            static_cast<unsigned char>(r * 255),
            static_cast<unsigned char>(g * 255),
            static_cast<unsigned char>(b * 255),
            static_cast<unsigned char>(a * 255)
        };
    }

    void glClearColor(const Color& color)
    {
        g_vglState.ClearColor = color;
    }

    void glClear()
    {
        FrameBuffer::GetInstance()->Clear(g_vglState.ClearColor);
    }

    void glViewPort(int x, int y, int w, int h)
    {
        FrameBuffer::GetInstance()->SetSize(w, h);

        g_vglState.ViewportMatrix.SetIdentity();

        g_vglState.ViewportMatrix[0][3] = x + w / 2.0f;
        g_vglState.ViewportMatrix[1][3] = y + h / 2.0f;
        g_vglState.ViewportMatrix[2][3] = g_vglState.ViewDepth / 2.0f;

        g_vglState.ViewportMatrix[0][0] = w / 2.0f;
        g_vglState.ViewportMatrix[1][1] = h / 2.0f;
        g_vglState.ViewportMatrix[2][2] = g_vglState.ViewDepth / 2.0f;
    }
} // namespace VSoftRenderer