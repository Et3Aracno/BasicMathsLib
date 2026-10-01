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
	return Store(_mm_
	sub_ps(vp, vrhs));
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

	return Store(_mm_mul_ps(vp, vs);
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

	return _mm_not_ps(_mm_movemask_ps(_mm_cmpeq_ps(vrhs, vp))) == 0xF;
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

	return Store(_mm_add_ps(xS, _mm_add_ps(yS, zS));
}

template <std::floating_point T>
Maths::Vec3S<T> Maths::Vec3S<T>::Cross(const Maths::Vec3S<T>& rhs) const
{
	return { y * rhs.z - z * rhs.y,
			z * rhs.x - x * rhs.z,
			x * rhs.y - y * rhs.x };
}