#pragma once
#include <xmmintrin.h>
#include "Vec3.h"
#include <array>
#include <limits>
#include <utility>

namespace Maths
{
    // Row-major storage, column vectors: result = matrix * vector.
    // A * B applies B first. Angles are radians, right-handed rotations.
	class Matrix3x3SIMD
    {
    protected:
        Matrix3x3SIMD Store(const __m128 row0, const __m128 row1, const __m128 row2);



    public:
        __m128 values[3];

        Matrix3x3SIMD(); // Identity.
        explicit Matrix3x3SIMD(const std::array<float, 9>& elements);
        Matrix3x3SIMD(__m128 row0, __m128 row1, __m128 row2);


        static Matrix3x3SIMD Identity();
        static Matrix3x3SIMD Zero();
        float& operator()(std::size_t row, std::size_t column);
        const float& operator()(std::size_t row, std::size_t column) const;
        Matrix3x3SIMD operator+(const Matrix3x3SIMD& rhs) const;
        Matrix3x3SIMD operator-(const Matrix3x3SIMD& rhs) const;
        Matrix3x3SIMD operator*(const Matrix3x3SIMD& rhs) const;
        Maths::Vec3<float> operator*(const Maths::Vec3<float>& rhs) const;
        Matrix3x3SIMD operator*(float scalar) const;
        Matrix3x3SIMD& operator*=(const Matrix3x3SIMD& rhs);
        bool operator==(const Matrix3x3SIMD& rhs) const;
        bool operator!=(const Matrix3x3SIMD& rhs) const;
        Matrix3x3SIMD Transpose() const;
        __m128 Determinant() const;
        //Gauss-Jordan with scaled partial pivoting. Rejects singular/ill-conditioned input.
        Matrix3x3SIMD Inverse(float relativeTolerance = 64.0f * std::numeric_limits<float>::epsilon()) const;
        static Matrix3x3SIMD Scale(const Maths::Vec3<float>& scale);
        static Matrix3x3SIMD RotationX(float radians);
        static Matrix3x3SIMD RotationY(float radians);
        static Matrix3x3SIMD RotationZ(float radians);
    };
}

#include "Matrix3x3-SIMD.inl"