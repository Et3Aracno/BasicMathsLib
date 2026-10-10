#pragma once
#include <xmmintrin.h>
#include <array>
#include <limits>
#include <utility>
#include "Vec4S.h"
#include "Vec3S.h"

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
        Maths::Vec4S operator*(const Maths::Vec4S& rhs) const;
        Matrix4x4SIMD operator*(float scalar) const;
        Matrix4x4SIMD& operator*=(const Matrix4x4SIMD& rhs);
        bool operator==(const Matrix4x4SIMD& rhs) const;
        bool operator!=(const Matrix4x4SIMD& rhs) const;
        Matrix4x4SIMD Transpose() const;
        float Determinant() const;
        //Gauss-Jordan with scaled partial pivoting. Rejects singular/ill-conditioned input.
        Matrix4x4SIMD Inverse(float relativeTolerance = 64.0f * std::numeric_limits<float>::epsilon()) const;
        static Matrix4x4SIMD Scale(const Maths::Vec3S& scale);
        static Matrix4x4SIMD RotationX(float radians);
        static Matrix4x4SIMD RotationY(float radians);
        static Matrix4x4SIMD RotationZ(float radians);
        static Matrix4x4SIMD Translation(const Vec3S& offset);
        Vec3S TransformPoint(const Vec3S& point) const; // Affine only, w = 1.
        Vec3S TransformDirection(const Vec3S& direction) const; // Affine only, w = 0.
    };
}

#include "Matrix4x4-SIMD.inl"