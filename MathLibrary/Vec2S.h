#pragma once

#include <algorithm>
#include <cmath>
#include <concepts>
#include <stdexcept>

namespace Maths
{
    // Scalar teaching baseline. No SIMD, custom alignment or forced inlining.
    class Vec2S
    {
    public:
        float x;
        float y;

        Vec2S();
        Vec2S(float _x, float _y);
        Vec2S(const Vec2S& other);

        static __m128 Load(const Maths::Vec2S& v);
        static Vec2S Store(__m128 val);

        Vec2S operator+(const Vec2S& rhs) const;
        Vec2S operator-(const Vec2S& rhs) const;
        Vec2S operator*(const Vec2S& rhs) const;
        Vec2S operator/(const Vec2S& rhs) const;
        Vec2S operator-() const;
        Vec2S operator*(float scalar) const;
        Vec2S operator/(float scalar) const;
        Vec2S& operator+=(const Vec2S& rhs);
        Vec2S& operator-=(const Vec2S& rhs);
        Vec2S& operator*=(const Vec2S& rhs);
        Vec2S& operator/=(const Vec2S& rhs);
        Vec2S& operator*=(float scalar);
        Vec2S& operator/=(float scalar);
        bool operator==(const Vec2S& rhs) const;
        bool operator!=(const Vec2S& rhs) const;

        float Dot(const Vec2S& rhs) const;
        Vec2S Cross(const Vec2S& rhs) const;
        float MagnitudeSquared() const;
        float Magnitude() const;
        // Returns a new vector. Throws domain_error for zero or non-finite input.
        Vec2S Normalize() const;
        float DistanceSquared(const Vec2S& rhs) const;
        float Distance(const Vec2S& rhs) const;
        float Angle(const Vec2S& rhs) const;
        static Vec2S Lerp(const Vec2S& a, const Vec2S& b, float t);
        static Vec2S Min(const Vec2S& a, const Vec2S& b);
        static Vec2S Max(const Vec2S& a, const Vec2S& b);

        static const Vec2S Zero;
        static const Vec2S One;
        static const Vec2S UnitX;
        static const Vec2S UnitY;
    };
}

#include "Vec2S.inl"
