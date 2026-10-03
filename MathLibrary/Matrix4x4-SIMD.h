#pragma once
#include <xmmintrin.h>
#include "Vec4.h"
#include <array>
#include <limits>
#include <utility>

namespace Maths
{
    // Row-major storage, column vectors: result = matrix * vector.
    // A * B applies B first. Angles are radians, right-handed rotations.
    class Matrix4x4SIMD
    {
    protected:


    public:
        __m128 values[4];

        Matrix4x4SIMD(); // Identity.
        explicit Matrix4x4SIMD(const std::array<float, 16>& elements);
        Matrix4x4SIMD(__m128 row0, __m128 row1, __m128 row2, __m128 row3);


        static Matrix4x4SIMD Identity();
        static Matrix4x4SIMD Zero();
        float& operator()(std::size_t row, std::size_t column);
        const float& operator()(std::size_t row, std::size_t column) const;
        Matrix4x4SIMD operator+(const Matrix4x4SIMD& rhs) const;
        Matrix4x4SIMD operator-(const Matrix4x4SIMD& rhs) const;
        Matrix4x4SIMD operator*(const Matrix4x4SIMD& rhs) const;
        Maths::Vec4<float> operator*(const Maths::Vec4<float>& rhs) const;
        Matrix4x4SIMD operator*(float scalar) const;
        Matrix4x4SIMD& operator*=(const Matrix4x4SIMD& rhs);
        bool operator==(const Matrix4x4SIMD& rhs) const;
        bool operator!=(const Matrix4x4SIMD& rhs) const;
        Matrix4x4SIMD Transpose() const;
        __m128 Determinant() const;
        //Gauss-Jordan with scaled partial pivoting. Rejects singular/ill-conditioned input.
        Matrix4x4SIMD Inverse(float relativeTolerance = 64.0f * std::numeric_limits<float>::epsilon()) const;
        static Matrix4x4SIMD Scale(const Maths::Vec4<float>& scale);
        static Matrix4x4SIMD RotationX(float radians);
        static Matrix4x4SIMD RotationY(float radians);
        static Matrix4x4SIMD RotationZ(float radians);
    };
}

#include "Matrix4x4-SIMD.inl"