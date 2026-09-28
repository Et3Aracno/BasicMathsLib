#pragma once
#include "Vec4.h"





template <std::floating_point T>
Maths::Vec4<T>::Vec4() : x(0), y(0), z(0), w(0)
{

}

template <std::floating_point T>
Maths::Vec4<T>::Vec4(T _x, T _y, T _z, T _w) : x(_x), y(_y), z(_z), w(_w)
{

}

template <std::floating_point T>
template <std::floating_point U>
Maths::Vec4<T>::Vec4(const Maths::Vec4<U>& other) : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)), z(static_cast<T>(other.z)), w(static_cast<T>(other.w))
{

}

template <std::floating_point T>
Maths::Vec4<T> Maths::Vec4<T>::operator+(const Maths::Vec4<T>& rhs) const
{
    return { x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w };
}

template <std::floating_point T>
Maths::Vec4<T> Maths::Vec4<T>::operator-(const Maths::Vec4<T>& rhs) const
{
    return { x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w };
}

template <std::floating_point T>
Maths::Vec4<T> Maths::Vec4<T>::operator*(const Maths::Vec4<T>& rhs) const
{
    return { x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w };
}

template <std::floating_point T>
Maths::Vec4<T> Maths::Vec4<T>::operator/(const Maths::Vec4<T>& rhs) const
{
    if (rhs.x == T{ 0 } || rhs.y == T{ 0 } || rhs.z == T{ 0 } || rhs.w == T{ 0 })
    {
        throw std::domain_error("Cannot divide by a zero component");
    }

    return { x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w };
}

template <std::floating_point T>
Maths::Vec4<T> Maths::Vec4<T>::operator-() const
{
    return { -x, -y, -z, -w };
}

template <std::floating_point T>
Maths::Vec4<T> Maths::Vec4<T>::operator*(T scalar) const
{
    return { x * scalar, y * scalar, z * scalar, w * scalar };
}

template <std::floating_point T>
Maths::Vec4<T> Maths::Vec4<T>::operator/(T scalar) const
{
    if (scalar == T{ 0 })
    {
        throw std::domain_error("Cannot divide by zero");
    }

    return { x / scalar, y / scalar, z / scalar, w / scalar };
}

template <std::floating_point T>
Maths::Vec4<T>& Maths::Vec4<T>::operator+=(const Maths::Vec4<T>& rhs)
{
    *this = *this + rhs;
    return *this;
}

template <std::floating_point T>
Maths::Vec4<T>& Maths::Vec4<T>::operator-=(const Maths::Vec4<T>& rhs)
{
    *this = *this - rhs;
    return *this;
}

template <std::floating_point T>
Maths::Vec4<T>& Maths::Vec4<T>::operator*=(const Maths::Vec4<T>& rhs)
{
    *this = *this * rhs;
    return *this;
}

template <std::floating_point T>
Maths::Vec4<T>& Maths::Vec4<T>::operator/=(const Maths::Vec4<T>& rhs)
{
    *this = *this / rhs;
    return *this;
}

template <std::floating_point T>
Maths::Vec4<T>& Maths::Vec4<T>::operator*=(T scalar)
{
    *this = *this * scalar;
    return *this;
}

template <std::floating_point T>
Maths::Vec4<T>& Maths::Vec4<T>::operator/=(T scalar)
{
    *this = *this / scalar;
    return *this;
}

template <std::floating_point T>
bool Maths::Vec4<T>::operator==(const Maths::Vec4<T>& rhs) const
{
    return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
}

template <std::floating_point T>
bool Maths::Vec4<T>::operator!=(const Maths::Vec4<T>& rhs) const
{
    return !(*this == rhs);
}

template <std::floating_point T>
T Maths::Vec4<T>::Dot(const Maths::Vec4<T>& rhs) const
{
    return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
}

template <std::floating_point T>
T Maths::Vec4<T>::MagnitudeSquared() const
{
    return Dot(*this);
}

template <std::floating_point T>
T Maths::Vec4<T>::Magnitude() const
{
    return std::hypot(std::hypot(x, y), std::hypot(z, w));
}

template <std::floating_point T>
Maths::Vec4<T> Maths::Vec4<T>::Normalize() const
{
    if (!std::isfinite(x) || !std::isfinite(y) || !std::isfinite(z) || !std::isfinite(w))
    {
        throw std::domain_error("Cannot normalize non-finite components");
    }

    // Scaling avoids overflowing/underflowing the squared magnitude.
    const T scale = std::max({ std::abs(x), std::abs(y), std::abs(z), std::abs(w) });
    if (scale == T{ 0 })
    {
        throw std::domain_error("Cannot normalize the zero vector");
    }

    const Maths::Vec4 scaled = *this / scale;
    return scaled / scaled.Magnitude();
}

template <std::floating_point T>
T Maths::Vec4<T>::DistanceSquared(const Maths::Vec4<T>& rhs) const
{
    return (*this - rhs).MagnitudeSquared();
}

template <std::floating_point T>
T Maths::Vec4<T>::Distance(const Maths::Vec4<T>& rhs) const
{
    return (*this - rhs).Magnitude();
}

template <std::floating_point T>
T Maths::Vec4<T>::Angle(const Maths::Vec4<T>& rhs) const
{
    const T cosine = Normalize().Dot(rhs.Normalize());
    return std::acos(std::clamp(cosine, T{ -1 }, T{ 1 }));
}

template <std::floating_point T>
Maths::Vec4<T> Maths::Vec4<T>::Lerp(const Maths::Vec4<T>& a, const Maths::Vec4<T>& b, T t)
{
    return a * (T{ 1 } - t) + b * t;
}

template <std::floating_point T>
Maths::Vec4<T> Maths::Vec4<T>::Min(const Maths::Vec4<T>& a, const Maths::Vec4<T>& b)
{
    return { std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z), std::min(a.w, b.w) };
}

template <std::floating_point T>
Maths::Vec4<T> Maths::Vec4<T>::Max(const Maths::Vec4<T>& a, const Maths::Vec4<T>& b)
{
    return { std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z), std::max(a.w, b.w) };
}

template <std::floating_point T>
const Maths::Vec4<T> Maths::Vec4<T>::Zero{ 0, 0, 0, 0 };

template <std::floating_point T>
const Maths::Vec4<T> Maths::Vec4<T>::One{ 1, 1, 1, 1 };

template <std::floating_point T>
const Maths::Vec4<T> Maths::Vec4<T>::UnitX{ 1, 0, 0, 0 };

template <std::floating_point T>
const Maths::Vec4<T> Maths::Vec4<T>::UnitY{ 0, 1, 0, 0 };

template <std::floating_point T>
const Maths::Vec4<T> Maths::Vec4<T>::UnitZ{ 0, 0, 1, 0 };

template <std::floating_point T>
const Maths::Vec4<T> Maths::Vec4<T>::UnitW{ 0, 0, 0, 1 };

template <std::floating_point T>
Maths::Vec4<T> operator*(T scalar, const Maths::Vec4<T>& vector)
{
    return vector * scalar;
}
