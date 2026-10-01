#pragma once

#include <algorithm>
#include <cmath>
#include <concepts>
#include <stdexcept>

namespace Maths
{
    // Scalar teaching baseline. No SIMD, custom alignment or forced inlining.
    template <std::floating_point T = float>
    class Vec3S
    {
    public:
        T x;
        T y;
        T z;

        Vec3S();
        Vec3S(T _x, T _y, T _z);
        template <std::floating_point U>
        explicit Vec3S(const Vec3S<U>& other);

        Vec3S operator+(const Vec3S& rhs) const;
        Vec3S operator-(const Vec3S& rhs) const;
        Vec3S operator*(const Vec3S& rhs) const;
        Vec3S operator/(const Vec3S& rhs) const;
        Vec3S operator-() const;
        Vec3S operator*(T scalar) const;
        Vec3S operator/(T scalar) const;
        Vec3S& operator+=(const Vec3S& rhs);
        Vec3S& operator-=(const Vec3S& rhs);
        Vec3S& operator*=(const Vec3S& rhs);
        Vec3S& operator/=(const Vec3S& rhs);
        Vec3S& operator*=(T scalar);
        Vec3S& operator/=(T scalar);
        bool operator==(const Vec3S& rhs) const;
        bool operator!=(const Vec3S& rhs) const;

        T Dot(const Vec3S& rhs) const;
        Vec3S Cross(const Vec3S& rhs) const;
        T MagnitudeSquared() const;
        T Magnitude() const;
        // Returns a new vector. Throws domain_error for zero or non-finite input.
        Vec3S Normalize() const;
        T DistanceSquared(const Vec3S& rhs) const;
        T Distance(const Vec3S& rhs) const;
        T Angle(const Vec3S& rhs) const;
        static Vec3S Lerp(const Vec3S& a, const Vec3S& b, T t);
        static Vec3S Min(const Vec3S& a, const Vec3S& b);
        static Vec3S Max(const Vec3S& a, const Vec3S& b);

        static const Vec3S Zero;
        static const Vec3S One;
        static const Vec3S UnitX;
        static const Vec3S UnitY;
        static const Vec3S UnitZ;
    };


    using Vec3Sf = Maths::Vec3S<float>;
    using Vec3Sd = Maths::Vec3S<double>;
}

#include "Vec3S.inl"