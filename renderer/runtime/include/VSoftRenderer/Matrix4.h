//
// Matrix4.h
//
// Created or modified by Kexuan Zhang on 30/10/2023 22:15.
//

#pragma once

#include <vector>

namespace VSoftRenderer
{
    class Matrix4
    {
    public:
        Matrix4() = default;

        std::vector<float>& operator [] (int i);

        void SetIdentity();

        static Matrix4 Identity();

    private:
        std::vector<std::vector<float>> m_Matrix;
    };
} // namespace VSoftRenderer