//
// Matrix4.cpp
//
// Created or modified by Kexuan Zhang on 2023/11/1 11:21.
//

#include "VSoftRenderer/Matrix4.h"

namespace VSoftRenderer
{
    std::vector<float>& Matrix4::operator[](int i)
    {
        return m_Matrix[i];
    }

    void Matrix4::SetIdentity()
    {
        {
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    m_Matrix[i][j] = i==j ? 1 : 0;
                }
            }
        }
    }

    Matrix4 Matrix4::Identity()
    {
        Matrix4 result;
        result.SetIdentity();
        return result;
    }
} //