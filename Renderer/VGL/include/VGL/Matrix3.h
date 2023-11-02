//
// Matrix3.h
//
// Created or modified by Kexuan Zhang on 2023/11/2 17:41.
//

#pragma once

#include "VGL/Vector3.h"

#include <iostream>
#include <vector>

namespace VGL
{
    class Matrix3
    {
    public:
        Matrix3();

        std::vector<float>& operator [] (int i);
        Matrix3 operator + (Matrix3& other) const;
        Matrix3 operator - (Matrix3& other) const;
        Matrix3 operator * (Matrix3& other) const;
        Matrix3 operator * (float scalar) const;
        Matrix3 operator / (float scalar) const;

        friend std::ostream& operator << (std::ostream& s, Matrix3& m);

        template<typename T>
        Vector3<T> operator * (const Vector3<T>& other) const
        {
            Vector3<T> productVector;

            for (int row = 0; row < 3; row++)
            {
                for (int col = 0; col < 3; col++)
                {
                    productVector[row] += m_Matrix[row][col] * other[col];
                }
            }

            return productVector;
        }

        void SetIdentity();
        Matrix3 Transpose() const;

        float   Determinant() const;

        static Matrix3 Identity();

    private:
        std::vector<std::vector<float>> m_Matrix;
    };
} // namespace VGL