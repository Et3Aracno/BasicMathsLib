#pragma once

template <std::floating_point T>
inline __m128 Load(const Maths::Vec3S <T>& v)
{
	return _mm_setr_ps(v.x, v.y, v.z, 0);
}

template <std::floating_point T>
inline Maths::Vec3S<T> Store(__m128 val)
{
	float component[3];
	_mm_storeu_ps(component, val);

	return {
		component[0],
		component[1],
		component[2]
	};
}

template <std::floating_point T>
Maths::Vec3S<T>::Vec3S() : x(0), y(0), z(0) {}

template <std::floating_point T>
Maths::Vec3S<T>::Vec3S(T _x, T _y, T _z) : x(_x), y(_y), z(_z){}

template <std::floating_point T>
template <std::floating_point U>
Maths::Vec3S<T>::Vec3S(const Maths::Vec3S<U>& other) : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)), z(static_cast<T>(other.z)){}

template <std::floating_point T>
Maths::Vec3S<T> Maths::Vec3S<T>::operator+(const Maths::Vec3S<T>& rhs) const
{
    __m128 vp = _mm_setr_ps(x, y, z, 0);
	__m128 vrhs = Load(rhs);
    return Store(_mm_add_ps(vp, vrhs));
}

template <std::floating_point T>
Maths::Vec3S<T> Maths::Vec3S<T>::operator-(const Maths::Vec3S<T>& rhs) const
{
	__m128 vp = _mm_setr_ps(x, y, z, 0);
	__m128 vrhs = Load(rhs);
	return Store(_mm_sub_ps(vp, vrhs));
}

template <std::floating_point T>
Maths::Vec3S<T> Maths::Vec3S<T>::operator*(const Maths::Vec3S<T>& rhs) const
{
	__m128 vp = _mm_setr_ps(x, y, z, 0);
	__m128 vrhs = Load(rhs);
	return Store(_mm_mul_ps(vp, vrhs));
}

template <std::floating_point T>
Maths::Vec3S<T> Maths::Vec3S<T>::operator/(const Maths::Vec3S<T>& rhs) const
{
	__m128 vrhs = Load(rhs);
	if (rhs.x == T{ 0 } || rhs.y == T{ 0 } || rhs.z == T{ 0 })
	{
		throw std::domain_error("Cannot divide by a zero component");
	}
	__m128 vp = _mm_setr_ps(x, y, z, 0);
	return Store(_mm_div_ps(vp, vrhs));
}

template <std::floating_point T>
Maths::Vec3S<T> Maths::Vec3S<T>::operator-() const
{
	return { -x, -y, -z };
}

template <std::floating_point T>
Maths::Vec3S<T> Maths::Vec3S<T>::operator*(T scalar) const
{
	__m128 vp = _mm_setr_ps(x, y, z, 0);
	__m128 vs = _mm_set_ps1(scalar);

	return Store(_mm_mul_ps(vp, vs));
}

template <std::floating_point T>
Maths::Vec3S<T> Maths::Vec3S<T>::operator/(T scalar) const
{
	__m128 vs = _mm_set_ps1(scalar);
	__m128 vzero = _mm_set_ps1(0);
	if (_mm_cmpeq_ps(vs, vzero))
	{
		throw std::domain_error("Cannot divide by zero");
	}

	__m128 vp = _mm_setr_ps(x, y, z, 0);
	return Store(_mm_div_ps(vs, vp));
}

template <std::floating_point T>
Maths::Vec3S<T>& Maths::Vec3S<T>::operator+=(const Maths::Vec3S<T>& rhs)
{
	__m128 vrhs = Load(rhs);
	__m128 vp = _mm_setr_ps(x, y, z, 0);

	return Store(_mm_add_ps(vp, vrhs));
}

template <std::floating_point T>
Maths::Vec3S<T>& Maths::Vec3S<T>::operator-=(const Maths::Vec3S<T>& rhs)
{
	__m128 vrhs = Load(rhs);
	__m128 vp = _mm_setr_ps(x, y, z, 0);

	return Store(_mm_sub_ps(vp, vrhs));
}

template <std::floating_point T>
Maths::Vec3S<T>& Maths::Vec3S<T>::operator*=(const Maths::Vec3S<T>& rhs)
{
	__m128 vrhs = Load(rhs);
	__m128 vp = _mm_setr_ps(x, y, z, 0);

	return Store(_mm_mul_ps(vp, vrhs));
}

template <std::floating_point T>
Maths::Vec3S<T>& Maths::Vec3S<T>::operator/=(const Maths::Vec3S<T>& rhs)
{
	__m128 vrhs = Load(rhs);
	__m128 vp = _mm_setr_ps(x, y, z, 0);

	return Store(_mm_div_ps(vp, vrhs));
}

template <std::floating_point T>
Maths::Vec3S<T>& Maths::Vec3S<T>::operator*=(T scalar)
{
	__m128 vs = _mm_set_ps1(scalar);
	__m128 vp = _mm_setr_ps(x, y, z, 0);

	return Store(_mm_mul_ps(vp, vs));
}

template <std::floating_point T>
Maths::Vec3S<T>& Maths::Vec3S<T>::operator/=(T scalar)
{
	__m128 vs = _mm_set_ps1(scalar);
	__m128 vp = _mm_setr_ps(x, y, z, 0);

	return Store(_mm_div_ps(vp, vs));
}

template <std::floating_point T>
Maths::Vec3S<T> operator*(T scalar, const Maths::Vec3S<T>& vector)
{
	__m128 vv = Load(vector);
	__m128 vt = _mm_set_ps1(scalar);
	return Store(_mm_mul_ps(vv * vt));
}

template <std::floating_point T>
bool Maths::Vec3S<T>::operator==(const Maths::Vec3S<T>& rhs) const
{
	__m128 vrhs = Load(rhs);
	__m128 vp = _mm_setr_ps(x, y, z, 0);

	return _mm_movemask_ps(_mm_cmpeq_ps(vrhs, vp)) == 0xF;
}

template <std::floating_point T>
bool Maths::Vec3S<T>::operator!=(const Maths::Vec3S<T>& rhs) const
{
	__m128 vrhs = Load(rhs);
	__m128 vp = _mm_setr_ps(x, y, z, 0);

	return _mm_not_ps(_mm_movemask_ps(_mm_cmpeq_ps(vrhs, vp)) == 0xF);
}

template <std::floating_point T>
T Maths::Vec3S<T>::Dot(const Maths::Vec3S<T>& rhs) const
{
	__m128 vx = _mm_set_ps1(rhs.x);
	__m128 vy = _mm_set_ps1(rhs.y);
	__m128 vz = _mm_set_ps1(rhs.z);

	__m128 va = _mm_set_ps1(x);
	__m128 vb = _mm_set_ps1(y);
	__m128 vc = _mm_set_ps1(z);

	__m128 rx = _mm_mul_ps(vx, va);
	__m128 ry = _mm_mul_ps(vy, vb);
	__m128 rz = _mm_mul_ps(vz, vc);

	float xS = _mm_cvtss_f32(rx);
	float yS = _mm_cvtss_f32(ry);
	float zS = _mm_cvtss_f32(rz);

	return Store(_mm_add_ps(xS, _mm_add_ps(yS, zS)));
}

template <std::floating_point T>
Maths::Vec3S<T> Maths::Vec3S<T>::Cross(const Maths::Vec3S<T>& rhs) const
{
	__m128 vx = _mm_set_ps1(rhs.x);
	__m128 vy = _mm_set_ps1(rhs.y);
	__m128 vz = _mm_set_ps1(rhs.z);

	__m128 va = _mm_set_ps1(x);
	__m128 vb = _mm_set_ps1(y);
	__m128 vc = _mm_set_ps1(z);

	__m128 rx = _mm_mul_ps(vx, va);
	__m128 ry = _mm_mul_ps(vy, vb);
	__m128 rz = _mm_mul_ps(vz, vc);

	float xS = _mm_cvtss_f32(rx);
	float yS = _mm_cvtss_f32(ry);
	float zS = _mm_cvtss_f32(rz);
	
	return Store(_mm_sub_ps(xS, _mm_sub_ps(yS, zS)));
}

template <std::floating_point T>
T Maths::Vec3S<T>::MagnitudeSquared() const
{
	return Dot(*this);
}

template <std::floating_point T>
T Maths::Vec3S<T>::Magnitude() const
{
	__m128 vp = _mm_set_ps1(x, y, z, 0);
	return Store(_mm_sqrt_ps(vp));
}

template <std::floating_point T>
Maths::Vec3S<T> Maths::Vec3S<T>::Normalize() const // A REVOIR
{
	if (!std::isfinite(x) || !std::isfinite(y) || !std::isfinite(z))
	{
		throw std::domain_error("Cannot normalize non-finite components");
	}

	// Scaling avoids overflowing/underflowing the squared magnitude.

	__m128 vx = _mm_set_ps1(std::abs(x));
	__m128 vy = _mm_set_ps1(std::abs(y));
	__m128 vz = _mm_set_ps1(std::abs(z));

	const __m128 scale = _mm_max_ps(vx, _mm_max_ps(vy, vz));
	float scalef = _mm_cvtss_f32(scale);
	if (scalef == T{ 0 })
	{
		throw std::domain_error("Cannot normalize the zero vector");
	}

	const Maths::Vec3S scaled = Store(Load(*this) / scale);
	return scaled / scaled.Magnitude();
}

template <std::floating_point T>
T Maths::Vec3S<T>::DistanceSquared(const Maths::Vec3S<T>& rhs) const
{
	return Srore(Load(*this) - Load(rhs)).MagnitudeSquared();
}

template <std::floating_point T>
T Maths::Vec3S<T>::Distance(const Maths::Vec3S<T>& rhs) const
{
	return Srore(Load(*this) - Load(rhs)).Magnitude();
}

template <std::floating_point T>
T Maths::Vec3S<T>::Angle(const Maths::Vec3S<T>& rhs) const // A VOIR
{
	const T cosine = Normalize().Dot(rhs.Normalize());
	return std::acos(std::clamp(cosine, T{ -1 }, T{ 1 }));
}

template <std::floating_point T> // A REVOIRE
Maths::Vec3S<T> Maths::Vec3S<T>::Lerp(const Maths::Vec3S<T>& a, const Maths::Vec3S<T>& b, T t)
{

	__m128 va = Load(a);
	__m128 vb = Load(b);

	return Store(_mm_mul_ps(va, _mm_add_ps((T{ 1 } - t), _mm_mul_ps(vb * t))));
}

template <std::floating_point T>
Maths::Vec3S<T> Maths::Vec3S<T>::Min(const Maths::Vec3S<T>& a, const Maths::Vec3S<T>& b)
{	
	__m128 va = Load(a);
	__m128 vb = Load(b);
	return Store(_mm_min_ps(va, vb));
}

template <std::floating_point T>
Maths::Vec3S<T> Maths::Vec3S<T>::Max(const Maths::Vec3S<T>& a, const Maths::Vec3S<T>& b)
{
	__m128 va = Load(a);
	__m128 vb = Load(b);
	return Store(_mm_max_ps(va, vb));
}

template <std::floating_point T>
const Maths::Vec3S<T> Maths::Vec3S<T>::Zero{ 0, 0, 0 };

template <std::floating_point T>
const Maths::Vec3S<T> Maths::Vec3S<T>::One{ 1, 1, 1 };

template <std::floating_point T>
const Maths::Vec3S<T> Maths::Vec3S<T>::UnitX{ 1, 0, 0 };

template <std::floating_point T>
const Maths::Vec3S<T> Maths::Vec3S<T>::UnitY{ 0, 1, 0 };

template <std::floating_point T>
const Maths::Vec3S<T> Maths::Vec3S<T>::UnitZ{ 0, 0, 1 };