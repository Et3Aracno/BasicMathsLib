#pragma once

#include <algorithm>
#include <cmath>
#include <concepts>
#include <stdexcept>

namespace Maths
{
    // Scalar teaching baseline. No SIMD, custom alignment or forced inlining.
    template <std::floating_point T = float>
    class Vec3
    {
    public:
        T x;
        T y;
        T z;

        Vec3();
        Vec3(T _x, T _y, T _z);
        template <std::floating_point U>
        explicit Vec3(const Vec3<U>& other);

        Vec3 operator+(const Vec3& rhs) const;
        Vec3 operator-(const Vec3& rhs) const;
        Vec3 operator*(const Vec3& rhs) const;
        Vec3 operator/(const Vec3& rhs) const;
        Vec3 operator-() const;
        Vec3 operator*(T scalar) const;
        Vec3 operator/(T scalar) const;
        Vec3& operator+=(const Vec3& rhs);
        Vec3& operator-=(const Vec3& rhs);
        Vec3& operator*=(const Vec3& rhs);
        Vec3& operator/=(const Vec3& rhs);
        Vec3& operator*=(T scalar);
        Vec3& operator/=(T scalar);
        bool operator==(const Vec3& rhs) const;
        bool operator!=(const Vec3& rhs) const;

        T Dot(const Vec3& rhs) const;
        Vec3 Cross(const Vec3& rhs) const;
        T MagnitudeSquared() const;
        T Magnitude() const;
        // Returns a new vector. Throws domain_error for zero or non-finite input.
        Vec3 Normalize() const;
        T DistanceSquared(const Vec3& rhs) const;
        T Distance(const Vec3& rhs) const;
        T Angle(const Vec3& rhs) const;
        static Vec3 Lerp(const Vec3& a, const Vec3& b, T t);
        static Vec3 Min(const Vec3& a, const Vec3& b);
        static Vec3 Max(const Vec3& a, const Vec3& b);

        static const Vec3 Zero;
        static const Vec3 One;
        static const Vec3 UnitX;
        static const Vec3 UnitY;
        static const Vec3 UnitZ;
    };


    using Vec3f = Maths::Vec3<float>;
    using Vec3d = Maths::Vec3<double>;
}

#include "Vec3.inl"
#include "Vec3S.inl"
