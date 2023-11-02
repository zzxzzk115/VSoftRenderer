//
// VGL.h
//
// Created or modified by Kexuan Zhang on 2023/11/1 14:56.
//

#pragma once

#include "VGL/Color.h"
#include "VGL/Matrix4.h"
#include "VGL/Vector3.h"
#include "VGL/Mesh.h"
#include "VGL/Texture2D.h"

#include <map>

namespace VGL
{
    struct VGLShaderBase
    {
        virtual ~VGLShaderBase() = default;

        virtual Vector3Float vert(Vertex& vertex, int vertexIndexInFace);
        virtual bool frag(Vector3Float bc, Color& color) = 0;

        Color sample2D(int textureSlot, float u, float v);
    };

    struct VGLState
    {
        Color   ClearColor;

        Matrix4 ViewportMatrix = Matrix4::Identity();
        float   ViewDepth = 255.0f;

        std::map<int, Mesh*> MeshMap;
        std::map<int, VGLShaderBase*> ShaderMap;
        std::map<int, Texture2D*> TextureMap;

        VGLShaderBase* UsingShader;
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

    void glBindMesh(int meshSlot, Mesh& mesh);
    void glDrawMeshIndexed(int meshSlot);

    void glBindTexture(int textureSlot, Texture2D& texture2D);

    void glBindShader(int shaderSlot, VGLShaderBase* shader);
    void glUseShaderProgram(int shaderSlot);
} // namespace VGL