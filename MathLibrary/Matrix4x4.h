#pragma once

#include "Vec4.h"
#include "Vec3.h"
#include <array>
#include <limits>
#include <utility>

namespace Maths
{
    // Row-major storage, column vectors: result = matrix * vector.
    // A * B applies B first. Angles are radians, right-handed rotations.
    template <std::floating_point T = float>
    class Matrix4x4
    {
    public:
        T values[4][4];

        Matrix4x4(); // Identity.
        explicit Matrix4x4(const std::array<T, 16>& elements);
        static Matrix4x4 Identity();
        static Matrix4x4 Zero();
        T& operator()(std::size_t row, std::size_t column);
        const T& operator()(std::size_t row, std::size_t column) const;
        Matrix4x4 operator+(const Matrix4x4& rhs) const;
        Matrix4x4 operator-(const Matrix4x4& rhs) const;
        Matrix4x4 operator*(const Matrix4x4& rhs) const;
        Vec4<T> operator*(const Vec4<T>& rhs) const;
        Matrix4x4 operator*(T scalar) const;
        Matrix4x4& operator*=(const Matrix4x4& rhs);
        bool operator==(const Matrix4x4& rhs) const;
        bool operator!=(const Matrix4x4& rhs) const;
        Matrix4x4 Transpose() const;
        T Determinant() const;
        // Gauss-Jordan with scaled partial pivoting. Rejects singular/ill-conditioned input.
        Matrix4x4 Inverse(T relativeTolerance = T{64} * std::numeric_limits<T>::epsilon()) const;
        static Matrix4x4 Scale(const Vec3<T>& scale);
        static Matrix4x4 RotationX(T radians);
        static Matrix4x4 RotationY(T radians);
        static Matrix4x4 RotationZ(T radians);
        static Matrix4x4 Translation(const Vec3<T>& offset);
        Vec3<T> TransformPoint(const Vec3<T>& point) const; // Affine only, w = 1.
        Vec3<T> TransformDirection(const Vec3<T>& direction) const; // Affine only, w = 0.
    };

}
#include "Matrix4x4.inl"
