#pragma once

#include <algorithm>
#include <xmmintrin.h>
#include <cmath>
#include <concepts>
#include <stdexcept>

namespace Maths
{
    // Scalar teaching baseline. No SIMD, custom alignment or forced inlining.
    class Vec3S
    {
    public:
        __m128 v;

        Vec3S();
        Vec3S(float _x, float _y, float _z);
        Vec3S(const Vec3S& other);
        Vec3S(const __m128& other);

        Vec3S operator+(const Vec3S& rhs) const;
        Vec3S operator-(const Vec3S& rhs) const;
        Vec3S operator*(const Vec3S& rhs) const;
        Vec3S operator/(const Vec3S& rhs) const;
        Vec3S operator-() const;
        Vec3S operator*(float scalar) const; 
        Vec3S operator/(float scalar) const;
        Vec3S& operator+=(const Vec3S& rhs);
        Vec3S& operator-=(const Vec3S& rhs);
        Vec3S& operator*=(const Vec3S& rhs);
        Vec3S& operator/=(const Vec3S& rhs);
        Vec3S& operator*=(float scalar);
        Vec3S& operator/=(float scalar);
        bool operator==(const Vec3S& rhs) const;
        bool operator!=(const Vec3S& rhs) const;

        float Dot(const Vec3S& rhs) const;
        Vec3S Cross(const Vec3S& rhs) const;
        float MagnitudeSquared() const;
        float Magnitude() const;
        // Returns a new vector. Throws domain_error for zero or non-finite input.
        Vec3S Normalize() const;
        float DistanceSquared(const Vec3S& rhs) const;
        float Distance(const Vec3S& rhs) const;
        float Angle(const Vec3S& rhs) const;
        static Vec3S Lerp(const Vec3S& a, const Vec3S& b, float t);
        static Vec3S Min(const Vec3S& a, const Vec3S& b);
        static Vec3S Max(const Vec3S& a, const Vec3S& b);

        static const Vec3S Zero;
        static const Vec3S One;
        static const Vec3S UnitX;
        static const Vec3S UnitY;
        static const Vec3S UnitZ;
    };
}

#include "Vec3S.inl"