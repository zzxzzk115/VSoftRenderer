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

        std::vector<float>& operator [] (const int i)
        {
            return m_Matrix[i];
        }

        void SetIdentity()
        {
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    m_Matrix[i][j] = i==j ? 1 : 0;
                }
            }
        }

        static Matrix4 Identity()
        {
            Matrix4 result;
            result.SetIdentity();
            return result;
        }

    private:
        std::vector<std::vector<float>> m_Matrix;
    };
} // namespace VSoftRenderer