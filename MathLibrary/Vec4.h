#pragma once

#include <algorithm>
#include <cmath>
#include <concepts>
#include <stdexcept>

namespace Maths
{
    // Scalar teaching baseline. No SIMD, custom alignment or forced inlining.
    template <std::floating_point T = float>
    class Vec4
    {
    public:
        T x;
        T y;
        T z;
        T w;

        Vec4();
        Vec4(T _x, T _y, T _z, T _w);
        template <std::floating_point U>
        explicit Vec4(const Vec4<U>& other);

        Vec4 operator+(const Vec4& rhs) const;
        Vec4 operator-(const Vec4& rhs) const;
        Vec4 operator*(const Vec4& rhs) const;
        Vec4 operator/(const Vec4& rhs) const;
        Vec4 operator-() const;
        Vec4 operator*(T scalar) const;
        Vec4 operator/(T scalar) const;
        Vec4& operator+=(const Vec4& rhs);
        Vec4& operator-=(const Vec4& rhs);
        Vec4& operator*=(const Vec4& rhs);
        Vec4& operator/=(const Vec4& rhs);
        Vec4& operator*=(T scalar);
        Vec4& operator/=(T scalar);
        bool operator==(const Vec4& rhs) const;
        bool operator!=(const Vec4& rhs) const;

        T Dot(const Vec4& rhs) const;
        T MagnitudeSquared() const;
        T Magnitude() const;
        // Returns a new vector. Throws domain_error for zero or non-finite input.
        Vec4 Normalize() const;
        T DistanceSquared(const Vec4& rhs) const;
        T Distance(const Vec4& rhs) const;
        T Angle(const Vec4& rhs) const;
        static Vec4 Lerp(const Vec4& a, const Vec4& b, T t);
        static Vec4 Min(const Vec4& a, const Vec4& b);
        static Vec4 Max(const Vec4& a, const Vec4& b);

        static const Vec4 Zero;
        static const Vec4 One;
        static const Vec4 UnitX;
        static const Vec4 UnitY;
        static const Vec4 UnitZ;
        static const Vec4 UnitW;
    };

    using Vec4f = Vec4<float>;
    using Vec4d = Vec4<double>;
}
#include "Vec4.inl"