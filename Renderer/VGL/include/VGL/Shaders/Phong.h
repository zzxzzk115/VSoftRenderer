//
// Gouraud.h
//
// Created or modified by Kexuan Zhang on 2023/11/2 23:04.
//

#pragma once

#include "VGL/VGL.h"

namespace VGL
{
    struct PhongShader : public VGLShaderBase
    {
        int BindDiffuseTextureSlot;
        int BindNormalTextureSlot;
        int BindSpecularTextureSlot;

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
            Vector3Float r = (n*(n*l*2.f) - l).Normalized();
            float diffuseIntensity = std::max(0.0f, n * l);
            Color diffuseColor = sample2D(BindDiffuseTextureSlot, uv.X, uv.Y);
            float specularIntensity = std::pow(std::max(0.0f, r.Z), sample2D(BindSpecularTextureSlot, uv.X, uv.Y).R / 1.0f);
            gl_FragColor = (diffuseColor * (diffuseIntensity + 0.4f * specularIntensity)).Clamped().IgnoreAlpha();
            return false;
        }
    };
} // namespace VGL