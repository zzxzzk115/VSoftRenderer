//
// Matrix4.h
//
// Created or modified by Kexuan Zhang on 30/10/2023 22:15.
//

#pragma once

#include "VSoftRenderer/Vector3.h"
#include "VSoftRenderer/Vector4.h"

#include <vector>

namespace VSoftRenderer
{
    class Matrix4
    {
    public:
        Matrix4();

        std::vector<float>& operator [] (int i);
        Matrix4 operator + (Matrix4& other) const;
        Matrix4 operator - (Matrix4& other) const;
        Matrix4 operator * (Matrix4& other) const;
        Matrix4 operator * (float scalar) const;
        Matrix4 operator / (float scalar) const;

        template<typename T>
        Vector4<T> operator * (const Vector4<T>& other) const;

        template<typename T>
        Vector3<T> operator * (const Vector3<T>& other) const;

        void SetIdentity();
        Matrix4 Transpose() const;

        static Matrix4 Identity();

    private:
        std::vector<std::vector<float>> m_Matrix;
    };
} // namespace VSoftRenderer