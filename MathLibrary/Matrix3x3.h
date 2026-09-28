#pragma once

#include "Vec3.h"
#include <array>
#include <limits>
#include <utility>

namespace Maths
{
    // Row-major storage, column vectors: result = matrix * vector.
    // A * B applies B first. Angles are radians, right-handed rotations.
    template <std::floating_point T = float>
    class Matrix3x3
    {
    public:
        T values[3][3];

        Matrix3x3(); // Identity.
        explicit Matrix3x3(const std::array<T, 9>& elements);
        static Matrix3x3 Identity();
        static Matrix3x3 Zero();
        T& operator()(std::size_t row, std::size_t column);
        const T& operator()(std::size_t row, std::size_t column) const;
        Matrix3x3 operator+(const Matrix3x3& rhs) const;
        Matrix3x3 operator-(const Matrix3x3& rhs) const;
        Matrix3x3 operator*(const Matrix3x3& rhs) const;
        Vec3<T> operator*(const Vec3<T>& rhs) const;
        Matrix3x3 operator*(T scalar) const;
        Matrix3x3& operator*=(const Matrix3x3& rhs);
        bool operator==(const Matrix3x3& rhs) const;
        bool operator!=(const Matrix3x3& rhs) const;
        Matrix3x3 Transpose() const;
        T Determinant() const;
        // Gauss-Jordan with scaled partial pivoting. Rejects singular/ill-conditioned input.
        Matrix3x3 Inverse(T relativeTolerance = T{64} * std::numeric_limits<T>::epsilon()) const;
        static Matrix3x3 Scale(const Vec3<T>& scale);
        static Matrix3x3 RotationX(T radians);
        static Matrix3x3 RotationY(T radians);
        static Matrix3x3 RotationZ(T radians);
    };
}

#include "Matrix3x3.inl"
