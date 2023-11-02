//
// Matrix3.cpp
//
// Created or modified by Kexuan Zhang on 2023/11/2 17:44.
//

#include "VGL/Matrix3.h"

namespace VGL
{
    Matrix3::Matrix3()
    {
        m_Matrix = std::vector<std::vector<float>>(3, std::vector<float>(3, 0));
    }

    std::vector<float>& Matrix3::operator[](int i)
    {
        return m_Matrix[i];
    }

    Matrix3 Matrix3::operator + (Matrix3& other) const
    {
        Matrix3 matrix3 = *this;

        for (int row = 0; row < 3; ++row)
        {
            for (int col = 0; col < 3; ++col)
            {
                matrix3[row][col] += other[row][col];
            }
        }

        return matrix3;
    }

    Matrix3 Matrix3::operator - (Matrix3& other) const
    {
        Matrix3 matrix3 = *this;

        for (int row = 0; row < 3; ++row)
        {
            for (int col = 0; col < 3; ++col)
            {
                matrix3[row][col] -= other[row][col];
            }
        }

        return matrix3;
    }

    Matrix3 Matrix3::operator * (float scalar) const
    {
        Matrix3 matrix3 = *this;

        for (int row = 0; row < 3; ++row)
        {
            for (int col = 0; col < 3; ++col)
            {
                matrix3[row][col] *= scalar;
            }
        }

        return matrix3;
    }

    Matrix3 Matrix3::operator / (float scalar) const
    {
        if (std::abs(scalar) < 1e-6)
        {
            throw std::runtime_error("Divided by Zero!!!");
        }

        Matrix3 matrix3 = *this;

        for (int row = 0; row < 3; ++row)
        {
            for (int col = 0; col < 3; ++col)
            {
                matrix3[row][col] /= scalar;
            }
        }

        return matrix3;
    }

    Matrix3 Matrix3::operator * (Matrix3& other) const
    {
        Matrix3 matrix3;

        for (int row = 0; row < 3; ++row)
        {
            for (int col = 0; col < 3; ++col)
            {
                for (int entry = 0; entry < 4; ++entry)
                {
                    matrix3.m_Matrix[row][col] += m_Matrix[row][entry] * other.m_Matrix[entry][col];
                }
            }
        }

        return matrix3;
    }

    std::ostream& operator << (std::ostream& s, Matrix3& m)
    {
        for (int row = 0; row <  3; ++row)
        {
            for (int col = 0; col < 3; col++)
            {
                s << m[row][col];
                if (col < 2) s << "\t";
            }
            s << std::endl;
        }
        return s;
    }

    void Matrix3::SetIdentity()
    {
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                m_Matrix[i][j] = i==j ? 1 : 0;
            }
        }
    }

    Matrix3 Matrix3::Transpose() const
    {
        Matrix3 transposeMatrix;

        for (int row = 0; row < 4; row++)
        {
            for (int col = 0; col < 4; col++)
            {
                transposeMatrix.m_Matrix[row][col] = m_Matrix[col][row];
            }
        }

        return transposeMatrix;
    }

    float Matrix3::Determinant() const
    {
        Matrix3 matrix3 = *this;
        float det = 1.0f;

        for (int col = 0; col < 3; col++)
        {
            for (int row = col + 1; row < 3; row++)
            {
                float factor = matrix3.m_Matrix[row][col] / matrix3.m_Matrix[col][col];
                for (int i = col; i < 3; i++)
                {
                    matrix3.m_Matrix[row][i] -= matrix3.m_Matrix[col][i] * factor;
                }
            }
        }

        for (int i = 0; i < 3; i++)
        {
            det *= matrix3.m_Matrix[i][i];
        }

        return det;
    }

    Matrix3 Matrix3::Identity()
    {
        Matrix3 result;
        result.m_Matrix = {
            {1, 0, 0},
            {0, 1, 0},
            {0, 0, 1},
        };
        return result;
    }
} // namespace VGL