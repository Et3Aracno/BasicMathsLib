#pragma once

#include <algorithm>
#include <cmath>
#include <concepts>
#include <stdexcept>

namespace Maths
{
    // Scalar teaching baseline. No SIMD, custom alignment or forced inlining.
    class Vec3dS
    {
    public:
        double x;
        double y;
        double z;

        Vec3dS();
        Vec3dS(double _x, double _y, double _z);
        Vec3dS(const Vec3dS& other);

        static __m128 Load(const Maths::Vec3dS& v);
        static Vec3dS Store(__m128 val);

        Vec3dS operator+(const Vec3dS& rhs) const;
        Vec3dS operator-(const Vec3dS& rhs) const;
        Vec3dS operator*(const Vec3dS& rhs) const;
        Vec3dS operator/(const Vec3dS& rhs) const;
        Vec3dS operator-() const;
        Vec3dS operator*(double scalar) const;
        Vec3dS operator/(double scalar) const;
        Vec3dS& operator+=(const Vec3dS& rhs);
        Vec3dS& operator-=(const Vec3dS& rhs);
        Vec3dS& operator*=(const Vec3dS& rhs);
        Vec3dS& operator/=(const Vec3dS& rhs);
        Vec3dS& operator*=(double scalar);
        Vec3dS& operator/=(double scalar);
        bool operator==(const Vec3dS& rhs) const;
        bool operator!=(const Vec3dS& rhs) const;

        double Dot(const Vec3dS& rhs) const;
        Vec3dS Cross(const Vec3dS& rhs) const;
        double MagnitudeSquared() const;
        double Magnitude() const;
        // Returns a new vector. Throws domain_error for zero or non-finite input.
        Vec3dS Normalize() const;
        double DistanceSquared(const Vec3dS& rhs) const;
        double Distance(const Vec3dS& rhs) const;
        double Angle(const Vec3dS& rhs) const;
        static Vec3dS Lerp(const Vec3dS& a, const Vec3dS& b, double t);
        static Vec3dS Min(const Vec3dS& a, const Vec3dS& b);
        static Vec3dS Max(const Vec3dS& a, const Vec3dS& b);

        static const Vec3dS Zero;
        static const Vec3dS One;
        static const Vec3dS UnitX;
        static const Vec3dS UnitY;
        static const Vec3dS UnitZ;
    };
}

#include "Vec3dS.inl"
