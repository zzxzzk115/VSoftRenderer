//
// VGL.cpp
//
// Created or modified by Kexuan Zhang on 2023/11/1 14:56.
//

#include "VGL/VGL.h"
#include "VGL/FrameBuffer.h"
#include "VGL/Triangle3D.h"

namespace VGL
{
    VGLState g_vglState = {};

    Color VGLShaderBase::sample2D(int textureSlot, float u, float v)
    {
        if (g_vglState.TextureMap.count(textureSlot) == 0)
        {
            throw std::runtime_error("Texture not found!");
        }

        auto* texture = g_vglState.TextureMap[textureSlot];
        return texture->GetColorAt(u, v);
    }

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

    void glBindMesh(int meshSlot, Mesh* mesh)
    {
        g_vglState.MeshMap[meshSlot] = mesh;
    }

    void glDrawMeshIndexed(int meshSlot)
    {
        if (g_vglState.MeshMap.count(meshSlot) == 0)
        {
            throw std::runtime_error("MeshSlot not found!");
        }

        if (g_vglState.UsingShader == nullptr)
        {
            throw std::runtime_error("No shader bound!");
        }

        auto* mesh = g_vglState.MeshMap[meshSlot];
        g_vglState.UsingShader->TargetMesh = mesh;

        for (int faceIndex = 0; faceIndex < mesh->Faces.size(); ++faceIndex)
        {
            auto& face = mesh->Faces[faceIndex];

            Vector3Float screenCoords[3];
            for (int v = 0; v < 3; ++v)
            {
                auto vertexPosition = mesh->Vertices[face.VertexIndices[v]];

                g_vglState.UsingShader->vert(faceIndex, v, vertexPosition);
                screenCoords[v] = g_vglState.ViewportMatrix * vertexPosition;
            }
            Triangle3D::DrawInterpolated(screenCoords, g_vglState.UsingShader);
        }
    }

    void glBindTexture(int textureSlot, Texture2D* texture2D)
    {
        g_vglState.TextureMap[textureSlot] = texture2D;
    }

    void glBindShader(int shaderSlot, VGLShaderBase* shader)
    {
        g_vglState.ShaderMap[shaderSlot] = shader;
    }

    void glUseShaderProgram(int shaderSlot)
    {
        if (g_vglState.ShaderMap.count(shaderSlot) == 0)
        {
            throw std::runtime_error("ShaderSlot not found!");
        }

        g_vglState.UsingShader = g_vglState.ShaderMap[shaderSlot];
    }
} // namespace VGL