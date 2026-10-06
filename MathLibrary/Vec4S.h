#pragma once

#include <algorithm>
#include <cmath>
#include <concepts>
#include <stdexcept>

namespace Maths
{
    // Scalar teaching baseline. No SIMD, custom alignment or forced inlining.
    class Vec4S
    {
    public:
        float x;
        float y;
        float z;
        float w;

        Vec4S();
        Vec4S(float _x, float _y, float _z, float _w);
        Vec4S(const Vec4S& other);

        static __m128 Load(const Maths::Vec4S& v);
        static Vec4S Store(__m128 val);

        Vec4S operator+(const Vec4S& rhs) const;
        Vec4S operator-(const Vec4S& rhs) const;
        Vec4S operator*(const Vec4S& rhs) const;
        Vec4S operator/(const Vec4S& rhs) const;
        Vec4S operator-() const;
        Vec4S operator*(float scalar) const;
        Vec4S operator/(float scalar) const;
        Vec4S& operator+=(const Vec4S& rhs);
        Vec4S& operator-=(const Vec4S& rhs);
        Vec4S& operator*=(const Vec4S& rhs);
        Vec4S& operator/=(const Vec4S& rhs);
        Vec4S& operator*=(float scalar);
        Vec4S& operator/=(float scalar);
        bool operator==(const Vec4S& rhs) const;
        bool operator!=(const Vec4S& rhs) const;

        float Dot(const Vec4S& rhs) const;
        float MagnitudeSquared() const;
        float Magnitude() const;
        // Returns a new vector. Throws domain_error for zero or non-finite input.
        Vec4S Normalize() const;
        float DistanceSquared(const Vec4S& rhs) const;
        float Distance(const Vec4S& rhs) const;
        float Angle(const Vec4S& rhs) const;
        static Vec4S Lerp(const Vec4S& a, const Vec4S& b, float t);
        static Vec4S Min(const Vec4S& a, const Vec4S& b);
        static Vec4S Max(const Vec4S& a, const Vec4S& b);

        static const Vec4S Zero;
        static const Vec4S One;
        static const Vec4S UnitX;
        static const Vec4S UnitY;
        static const Vec4S UnitZ;
        static const Vec4S UnitW;
    };
}
#include "Vec4S.inl"