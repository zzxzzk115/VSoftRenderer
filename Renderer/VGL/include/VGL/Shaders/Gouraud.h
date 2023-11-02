//
// Gouraud.h
//
// Created or modified by Kexuan Zhang on 2023/11/2 23:04.
//

#pragma once

#include "VGL/VGL.h"

namespace VGL
{
    struct GouraudShader : public VGLShaderBase
    {
        int BindDiffuseTextureSlot;
        int BindNormalTextureSlot;

        Vector3Float UniformLightDirection;
        Matrix4      UniformMVP;
        Matrix4      UniformMVPIT;

        std::vector<Vector2Float> VaryingUVs {3};

        virtual void vert(int faceIndex, int vertexIndexInFace, Vector3Float& gl_Position) override
        {
            VaryingUVs[vertexIndexInFace] = TargetMesh->GetUV(faceIndex, vertexIndexInFace);
            gl_Position = UniformMVP * gl_Position;
        }

        virtual bool frag(Vector3Float bc, VGL::Color& gl_FragColor) override
        {
            Vector2Float uv = VaryingUVs[0] * bc.X + VaryingUVs[1] * bc.Y + VaryingUVs[2] * bc.Z;
            Vector3Float n = (UniformMVPIT * sample2D(BindNormalTextureSlot, uv.X, uv.Y).XYZ()).Normalized();
            Vector3Float l = (UniformMVP * UniformLightDirection).Normalized();
            float intensity = std::max(0.0f, n * l);
            gl_FragColor = sample2D(BindDiffuseTextureSlot, uv.X, uv.Y) * intensity;
            return false;
        }
    };
} // namespace VGL