#pragma once

#include <algorithm>
#include <cmath>
#include <concepts>
#include <stdexcept>

namespace Maths
{
    // Scalar teaching baseline. No SIMD, custom alignment or forced inlining.
    class Vec4dS
    {
    public:
        double x;
        double y;
        double z;
        double w;

        Vec4dS();
        Vec4dS(double _x, double _y, double _z, double _w);
        Vec4dS(const Vec4dS& other);

        static __m128 Load(const Maths::Vec4dS& v);
        static Vec4dS Store(__m128 val);

        Vec4dS operator+(const Vec4dS& rhs) const;
        Vec4dS operator-(const Vec4dS& rhs) const;
        Vec4dS operator*(const Vec4dS& rhs) const;
        Vec4dS operator/(const Vec4dS& rhs) const;
        Vec4dS operator-() const;
        Vec4dS operator*(double scalar) const;
        Vec4dS operator/(double scalar) const;
        Vec4dS& operator+=(const Vec4dS& rhs);
        Vec4dS& operator-=(const Vec4dS& rhs);
        Vec4dS& operator*=(const Vec4dS& rhs);
        Vec4dS& operator/=(const Vec4dS& rhs);
        Vec4dS& operator*=(double scalar);
        Vec4dS& operator/=(double scalar);
        bool operator==(const Vec4dS& rhs) const;
        bool operator!=(const Vec4dS& rhs) const;

        double Dot(const Vec4dS& rhs) const;
        double MagnitudeSquared() const;
        double Magnitude() const;
        // Returns a new vector. Throws domain_error for zero or non-finite input.
        Vec4dS Normalize() const;
        double DistanceSquared(const Vec4dS& rhs) const;
        double Distance(const Vec4dS& rhs) const;
        double Angle(const Vec4dS& rhs) const;
        static Vec4dS Lerp(const Vec4dS& a, const Vec4dS& b, double t);
        static Vec4dS Min(const Vec4dS& a, const Vec4dS& b);
        static Vec4dS Max(const Vec4dS& a, const Vec4dS& b);

        static const Vec4dS Zero;
        static const Vec4dS One;
        static const Vec4dS UnitX;
        static const Vec4dS UnitY;
        static const Vec4dS UnitZ;
        static const Vec4dS UnitW;
    };
}
#include "Vec4dS.inl"