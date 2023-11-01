//
// Matrix4.cpp
//
// Created or modified by Kexuan Zhang on 2023/11/1 11:21.
//

#include "VSoftRenderer/Matrix4.h"

namespace VSoftRenderer
{
    Matrix4::Matrix4()
    {
        m_Matrix.resize(4);
        for (int row = 0; row < 4; ++row)
        {
            m_Matrix[row].resize(4);
        }
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

    template<typename T>
    Vector4<T> Matrix4::operator*(const Vector4<T>& other) const
    {
        Vector4<T> productVector;

        for (int row = 0; row < 4; row++)
        {
            for (int col = 0; col < 4; col++)
            {
                productVector[row] += m_Matrix[row][col] * other[col];
            }
        }

        return productVector;
    }

    template<typename T>
    Vector3<T> Matrix4::operator * (const Vector3<T>& other) const
    {
        Vector4<T> productVector = (*this) * Vector4(other);
        return productVector.ToPoint3();
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