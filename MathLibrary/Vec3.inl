#pragma once


template <std::floating_point T>
Maths::Vec3<T>::Vec3() : x(0), y(0), z(0){}

template <std::floating_point T>
Maths::Vec3<T>::Vec3(T _x, T _y, T _z) : x(_x), y(_y), z(_z){}

template <std::floating_point T> 
template <std::floating_point U>
Maths::Vec3<T>::Vec3(const Maths::Vec3<U>& other) : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)), z(static_cast<T>(other.z)){}

template <std::floating_point T>
Maths::Vec3<T> Maths::Vec3<T>::operator+(const Maths::Vec3<T>& rhs) const
{
    return { x + rhs.x, y + rhs.y, z + rhs.z };
}

template <std::floating_point T>
Maths::Vec3<T> Maths::Vec3<T>::operator-(const Maths::Vec3<T>& rhs) const
{
    return { x - rhs.x, y - rhs.y, z - rhs.z };
}

template <std::floating_point T>
Maths::Vec3<T> Maths::Vec3<T>::operator*(const Maths::Vec3<T>& rhs) const
{
    return { x * rhs.x, y * rhs.y, z * rhs.z };
}

template <std::floating_point T>
Maths::Vec3<T> Maths::Vec3<T>::operator/(const Maths::Vec3<T>& rhs) const
{
    if (rhs.x == T{ 0 } || rhs.y == T{ 0 } || rhs.z == T{ 0 })
    {
        throw std::domain_error("Cannot divide by a zero component");
    }

    return { x / rhs.x, y / rhs.y, z / rhs.z };
}

template <std::floating_point T>
Maths::Vec3<T> Maths::Vec3<T>::operator-() const
{
    return { -x, -y, -z };
}

template <std::floating_point T>
Maths::Vec3<T> Maths::Vec3<T>::operator*(T scalar) const
{
    return { x * scalar, y * scalar, z * scalar };
}

template <std::floating_point T>
Maths::Vec3<T> Maths::Vec3<T>::operator/(T scalar) const
{
    if (scalar == T{ 0 })
    {
        throw std::domain_error("Cannot divide by zero");
    }

    return { x / scalar, y / scalar, z / scalar };
}

template <std::floating_point T>
Maths::Vec3<T>& Maths::Vec3<T>::operator+=(const Maths::Vec3<T>& rhs)
{
    *this = *this + rhs;
    return *this;
}

template <std::floating_point T>
Maths::Vec3<T>& Maths::Vec3<T>::operator-=(const Maths::Vec3<T>& rhs)
{
    *this = *this - rhs;
    return *this;
}

template <std::floating_point T>
Maths::Vec3<T>& Maths::Vec3<T>::operator*=(const Maths::Vec3<T>& rhs)
{
    *this = *this * rhs;
    return *this;
}

template <std::floating_point T>
Maths::Vec3<T>& Maths::Vec3<T>::operator/=(const Maths::Vec3<T>& rhs)
{
    *this = *this / rhs;
    return *this;
}

template <std::floating_point T>
Maths::Vec3<T>& Maths::Vec3<T>::operator*=(T scalar)
{
    *this = *this * scalar;
    return *this;
}

template <std::floating_point T>
Maths::Vec3<T>& Maths::Vec3<T>::operator/=(T scalar)
{
    *this = *this / scalar;
    return *this;
}

template <std::floating_point T>
bool Maths::Vec3<T>::operator==(const Maths::Vec3<T>& rhs) const
{
    return x == rhs.x && y == rhs.y && z == rhs.z;
}

template <std::floating_point T>
bool Maths::Vec3<T>::operator!=(const Maths::Vec3<T>& rhs) const
{
    return !(*this == rhs);
}

template <std::floating_point T>
T Maths::Vec3<T>::Dot(const Maths::Vec3<T>& rhs) const
{
    return x * rhs.x + y * rhs.y + z * rhs.z;
}

template <std::floating_point T>
Maths::Vec3<T> Maths::Vec3<T>::Cross(const Maths::Vec3<T>& rhs) const
{
    return { y * rhs.z - z * rhs.y,
            z * rhs.x - x * rhs.z,
            x * rhs.y - y * rhs.x };
}

template <std::floating_point T>
T Maths::Vec3<T>::MagnitudeSquared() const
{
    return Dot(*this);
}

template <std::floating_point T>
T Maths::Vec3<T>::Magnitude() const
{
    return std::hypot(x, y, z);
}

template <std::floating_point T>
Maths::Vec3<T> Maths::Vec3<T>::Normalize() const
{
    if (!std::isfinite(x) || !std::isfinite(y) || !std::isfinite(z))
    {
        throw std::domain_error("Cannot normalize non-finite components");
    }

    // Scaling avoids overflowing/underflowing the squared magnitude.
    const T scale = std::max({ std::abs(x), std::abs(y), std::abs(z) });
    if (scale == T{ 0 })
    {
        throw std::domain_error("Cannot normalize the zero vector");
    }

    const Maths::Vec3 scaled = *this / scale;
    return scaled / scaled.Magnitude();
}

template <std::floating_point T>
T Maths::Vec3<T>::DistanceSquared(const Maths::Vec3<T>& rhs) const
{
    return (*this - rhs).MagnitudeSquared();
}

template <std::floating_point T>
T Maths::Vec3<T>::Distance(const Maths::Vec3<T>& rhs) const
{
    return (*this - rhs).Magnitude();
}

template <std::floating_point T>
T Maths::Vec3<T>::Angle(const Maths::Vec3<T>& rhs) const
{
    const T cosine = Normalize().Dot(rhs.Normalize());
    return std::acos(std::clamp(cosine, T{ -1 }, T{ 1 }));
}

template <std::floating_point T>
Maths::Vec3<T> Maths::Vec3<T>::Lerp(const Maths::Vec3<T>& a, const Maths::Vec3<T>& b, T t)
{
    return a * (T{ 1 } - t) + b * t;
}

template <std::floating_point T>
Maths::Vec3<T> Maths::Vec3<T>::Min(const Maths::Vec3<T>& a, const Maths::Vec3<T>& b)
{
    return { std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z) };
}

template <std::floating_point T>
Maths::Vec3<T> Maths::Vec3<T>::Max(const Maths::Vec3<T>& a, const Maths::Vec3<T>& b)
{
    return { std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z) };
}

template <std::floating_point T>
const Maths::Vec3<T> Maths::Vec3<T>::Zero{ 0, 0, 0 };

template <std::floating_point T>
const Maths::Vec3<T> Maths::Vec3<T>::One{ 1, 1, 1 };

template <std::floating_point T>
const Maths::Vec3<T> Maths::Vec3<T>::UnitX{ 1, 0, 0 };

template <std::floating_point T>
const Maths::Vec3<T> Maths::Vec3<T>::UnitY{ 0, 1, 0 };

template <std::floating_point T>
const Maths::Vec3<T> Maths::Vec3<T>::UnitZ{ 0, 0, 1 };

template <std::floating_point T>
Maths::Vec3<T> operator*(T scalar, const Maths::Vec3<T>& vector)
{
    return vector * scalar;
}
