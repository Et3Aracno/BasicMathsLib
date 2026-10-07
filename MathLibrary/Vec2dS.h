#pragma once

#include <algorithm>
#include <cmath>
#include <concepts>
#include <stdexcept>

namespace Maths
{
    // Scalar teaching baseline. No SIMD, custom alignment or forced inlining.
    class Vec2dS
    {
    public:
        double x;
        double y;

        Vec2dS();
        Vec2dS(double _x, double _y);
        Vec2dS(const Vec2dS& other);

        static __m128 Load(const Maths::Vec2dS& v);
        static Vec2dS Store(__m128 val);

        Vec2dS operator+(const Vec2dS& rhs) const;
        Vec2dS operator-(const Vec2dS& rhs) const;
        Vec2dS operator*(const Vec2dS& rhs) const;
        Vec2dS operator/(const Vec2dS& rhs) const;
        Vec2dS operator-() const;
        Vec2dS operator*(double scalar) const;
        Vec2dS operator/(double scalar) const;
        Vec2dS& operator+=(const Vec2dS& rhs);
        Vec2dS& operator-=(const Vec2dS& rhs);
        Vec2dS& operator*=(const Vec2dS& rhs);
        Vec2dS& operator/=(const Vec2dS& rhs);
        Vec2dS& operator*=(double scalar);
        Vec2dS& operator/=(double scalar);
        bool operator==(const Vec2dS& rhs) const;
        bool operator!=(const Vec2dS& rhs) const;

        double Dot(const Vec2dS& rhs) const;
        double MagnitudeSquared() const;
        double Magnitude() const;
        // Returns a new vector. Throws domain_error for zero or non-finite input.
        Vec2dS Normalize() const;
        double DistanceSquared(const Vec2dS& rhs) const;
        double Distance(const Vec2dS& rhs) const;
        double Angle(const Vec2dS& rhs) const;
        static Vec2dS Lerp(const Vec2dS& a, const Vec2dS& b, double t);
        static Vec2dS Min(const Vec2dS& a, const Vec2dS& b);
        static Vec2dS Max(const Vec2dS& a, const Vec2dS& b);

        static const Vec2dS Zero;
        static const Vec2dS One;
        static const Vec2dS UnitX;
        static const Vec2dS UnitY;
    };
}

#include "Vec2dS.inl"

