//
// Matrix4.cpp
//
// Created or modified by Kexuan Zhang on 2023/11/1 11:21.
//

#include "VGL/Matrix4.h"

namespace VGL
{
    Matrix4::Matrix4()
    {
        m_Matrix = std::vector<std::vector<float>>(4, std::vector<float>(4, 0));
    }

    std::vector<float>& Matrix4::operator[](int i)
    {
        return m_Matrix[i];
    }

    Matrix4 Matrix4::operator + (Matrix4& other) const
    {
        Matrix4 matrix4 = *this;

        for (int row = 0; row < 4; ++row)
        {
            for (int col = 0; col < 4; ++col)
            {
                matrix4[row][col] += other[row][col];
            }
        }

        return matrix4;
    }

    Matrix4 Matrix4::operator - (Matrix4& other) const
    {
        Matrix4 matrix4 = *this;

        for (int row = 0; row < 4; ++row)
        {
            for (int col = 0; col < 4; ++col)
            {
                matrix4[row][col] -= other[row][col];
            }
        }

        return matrix4;
    }

    Matrix4 Matrix4::operator * (float scalar) const
    {
        Matrix4 matrix4 = *this;

        for (int row = 0; row < 4; ++row)
        {
            for (int col = 0; col < 4; ++col)
            {
                matrix4[row][col] *= scalar;
            }
        }

        return matrix4;
    }

    Matrix4 Matrix4::operator / (float scalar) const
    {
        if (std::abs(scalar) < 1e-6)
        {
            throw std::runtime_error("Divided by Zero!!!");
        }

        Matrix4 matrix4 = *this;

        for (int row = 0; row < 4; ++row)
        {
            for (int col = 0; col < 4; ++col)
            {
                matrix4[row][col] /= scalar;
            }
        }

        return matrix4;
    }

    Matrix4 Matrix4::operator * (Matrix4& other) const
    {
        Matrix4 matrix4;

        for (int row = 0; row < 4; ++row)
        {
            for (int col = 0; col < 4; ++col)
            {
                for (int entry = 0; entry < 4; ++entry)
                {
                    matrix4.m_Matrix[row][col] += m_Matrix[row][entry] * other.m_Matrix[entry][col];
                }
            }
        }

        return matrix4;
    }

    std::ostream& operator << (std::ostream& s, Matrix4& m)
    {
        for (int row = 0; row <  4; ++row)
        {
            for (int col = 0; col < 4; col++)
            {
                s << m[row][col];
                if (col < 3) s << "\t";
            }
            s << std::endl;
        }
        return s;
    }

    void Matrix4::SetIdentity()
    {
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                m_Matrix[i][j] = i==j ? 1 : 0;
            }
        }
    }

    Matrix4 Matrix4::Transpose() const
    {
        Matrix4 transposeMatrix;

        for (int row = 0; row < 4; row++)
        {
            for (int col = 0; col < 4; col++)
            {
                transposeMatrix.m_Matrix[row][col] = m_Matrix[col][row];
            }
        }

        return transposeMatrix;
    }

    Matrix4 Matrix4::Identity()
    {
        Matrix4 result;
        result.m_Matrix = {
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
        };
        return result;
    }
} //