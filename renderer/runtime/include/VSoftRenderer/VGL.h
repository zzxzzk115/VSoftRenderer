//
// VGL.h
//
// Created or modified by Kexuan Zhang on 2023/11/1 14:56.
//

#pragma once

#include "VSoftRenderer/Color.h"
#include "VSoftRenderer/Matrix4.h"
#include "VSoftRenderer/Vector3.h"

namespace VSoftRenderer
{
    struct VGLState
    {
        Color   ClearColor;

        Matrix4 ViewportMatrix = Matrix4::Identity();
        float   ViewDepth = 255.0f;
    };

    extern VGLState g_vglState;

    void glClearColor(float r, float g, float b, float a);
    void glClearColor(const Color& color);
    void glClear();

    void glViewPort(int x, int y, int w, int h);

    template<typename T>
    Matrix4 glLookAt(Vector3<T> eye, Vector3<T> center, Vector3<T> up)
    {
        Vector3<T> z = (eye - center).Normalized();
        Vector3<T> x = up.CrossProduct(z).Normalized();
        Vector3<T> y = z.CrossProduct(x).Normalized();

        Matrix4 viewMatrix = Matrix4::Identity();

        for (int i = 0; i < 3; ++i)
        {
            viewMatrix[0][i] = x[i];
            viewMatrix[1][i] = y[i];
            viewMatrix[2][i] = z[i];
            viewMatrix[i][3] = -center[i];
        }

        return viewMatrix;
    }

    template<typename T>
    Matrix4 glProjection(Vector3<T> eye, Vector3<T> center)
    {
        Matrix4 projectionMatrix = Matrix4::Identity();
        projectionMatrix[3][2] = -1.0f / (eye - center).GetLength();
        return projectionMatrix;
    }
} // namespace VSoftRenderer