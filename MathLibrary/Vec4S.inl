#pragma once

__m128 Maths::Vec4S::Load(const Maths::Vec4S& v)
{
	return _mm_setr_ps(v.x, v.y, v.z, v.w);
}

Maths::Vec4S Maths::Vec4S::Store(__m128 val)
{
	float component[4];
	_mm_storeu_ps(component, val);
	return {
		component[0],
		component[1],
		component[2],
		component[3]
	};
}

Maths::Vec4S::Vec4S() : x(0), y(0), z(0), w(0) {}

Maths::Vec4S::Vec4S(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}

Maths::Vec4S::Vec4S(const Maths::Vec4S& other) {
	x = other.x; y = other.y; z = other.z; w = other.w;
}

Maths::Vec4S Maths::Vec4S::operator+(const Maths::Vec4S& rhs) const
{
	__m128 vp = Load(*this);
	__m128 vrhs = Load(rhs);

	return Store(_mm_add_ps(vp, vrhs));
}

Maths::Vec4S Maths::Vec4S::operator-(const Maths::Vec4S& rhs) const
{
	const __m128 vp = _mm_setr_ps(x, y, z, w);
	const __m128 vrhs = Load(rhs);
	return Store(_mm_sub_ps(vp, vrhs));
}

Maths::Vec4S Maths::Vec4S::operator*(const Maths::Vec4S& rhs) const
{
	__m128 vp = _mm_setr_ps(x, y, z, w);
	__m128 vrhs = Load(rhs);
	return Store(_mm_mul_ps(vp, vrhs));
}

Maths::Vec4S Maths::Vec4S::operator/(const Maths::Vec4S& rhs) const
{
	__m128 vrhs = Load(rhs);
	if (rhs.x == 0.f || rhs.y == 0.f || rhs.z == 0.f || rhs.w == 0.f)
	{
		throw std::domain_error("Cannot divide by a zero component");
	}
	__m128 vp = _mm_setr_ps(x, y, z, w);
	return Store(_mm_div_ps(vp, vrhs));
}

Maths::Vec4S Maths::Vec4S::operator-() const
{
	return { -x, -y, -z, -w };
}

Maths::Vec4S Maths::Vec4S::operator*(float scalar) const
{
	__m128 vp = Load(*this);
	__m128 vs = _mm_set_ps1(scalar);

	return Store(_mm_mul_ps(vp, vs));
}

Maths::Vec4S Maths::Vec4S::operator/(float scalar) const
{
	__m128 vs = _mm_set_ps1(scalar);
	__m128 vzero = _mm_set_ps1(0);
	if (_mm_movemask_ps(_mm_cmpeq_ps(vs, vzero)))
	{
		throw std::domain_error("Cannot divide by zero");
	}

	__m128 vp = _mm_setr_ps(x, y, z, w);
	return Store(_mm_div_ps(vp, vs));
}

Maths::Vec4S& Maths::Vec4S::operator+=(const Maths::Vec4S& rhs)
{
	__m128 vp = Load(*this);
	__m128 vrhs = Load(rhs);

	*this = Store(_mm_add_ps(vp, vrhs));
	return *this;
}

Maths::Vec4S& Maths::Vec4S::operator-=(const Maths::Vec4S& rhs)
{
	__m128 vp = Load(*this);
	__m128 vrhs = Load(rhs);

	*this = Store(_mm_sub_ps(vp, vrhs));
	return *this;
}

Maths::Vec4S& Maths::Vec4S::operator*=(const Maths::Vec4S& rhs)
{
	__m128 vp = Load(*this);
	__m128 vrhs = Load(rhs);

	*this = Store(_mm_mul_ps(vp, vrhs));
	return *this;
}

Maths::Vec4S& Maths::Vec4S::operator/=(const Maths::Vec4S& rhs)
{
	if (rhs.x == 0.f || rhs.y == 0.f || rhs.z == 0.f || rhs.w == 0.f)
	{
		throw std::domain_error("Cannot divide by a zero component");
	}

	__m128 vp = Load(*this);
	__m128 vrhs = Load(rhs);

	*this = Store(_mm_div_ps(vp, vrhs));
	return *this;
}

Maths::Vec4S& Maths::Vec4S::operator*=(float scalar)
{
	__m128 vp = Load(*this);
	__m128 vrhs = _mm_set_ps1(scalar);

	*this = Store(_mm_mul_ps(vp, vrhs));
	return *this;
}

Maths::Vec4S& Maths::Vec4S::operator/=(float scalar)
{
	__m128 vs = _mm_set_ps1(scalar);
	__m128 vzero = _mm_set_ps1(0);
	if (_mm_movemask_ps(_mm_cmpeq_ps(vs, vzero))) {
		throw std::domain_error("Cannot divide by zero");
	}

	__m128 vp = Load(*this);
	__m128 vrhs = _mm_set_ps1(scalar);

	*this = Store(_mm_div_ps(vp, vrhs));
	return *this;
}

Maths::Vec4S operator*(float scalar, const Maths::Vec4S& vector)
{
	__m128 vv = _mm_setr_ps(vector.x, vector.y, vector.z, vector.w);
	__m128 vt = _mm_set_ps1(scalar);
	__m128 result = _mm_mul_ps(vv, vt);

	float component[4];
	_mm_storeu_ps(component, result);
	return {
		component[0],
		component[1],
		component[2],
		component[3]
	};
}

bool Maths::Vec4S::operator==(const Maths::Vec4S& rhs) const
{
	__m128 vrhs = Load(rhs);
	__m128 vp = _mm_setr_ps(x, y, z, w);

	return _mm_movemask_ps(_mm_cmpeq_ps(vrhs, vp)) == 0xF;
}

bool Maths::Vec4S::operator!=(const Maths::Vec4S& rhs) const
{
	__m128 vrhs = Load(rhs);
	__m128 vp = _mm_setr_ps(x, y, z, w);

	return _mm_movemask_ps((_mm_cmpeq_ps(vrhs, vp))) != 0xF; // ALLER VOUS FAIRE METTRE Y'A PAS DE NOT
}

float Maths::Vec4S::Dot(const Maths::Vec4S& rhs) const
{
	__m128 vx = _mm_set_ps1(rhs.x);
	__m128 vy = _mm_set_ps1(rhs.y);
	__m128 vz = _mm_set_ps1(rhs.z);
	__m128 vw = _mm_set_ps1(rhs.w);

	__m128 va = _mm_set_ps1(x);
	__m128 vb = _mm_set_ps1(y);
	__m128 vc = _mm_set_ps1(z);
	__m128 vd = _mm_set_ps1(w);

	__m128 rx = _mm_mul_ps(vx, va);
	__m128 ry = _mm_mul_ps(vy, vb);
	__m128 rz = _mm_mul_ps(vz, vc);
	__m128 rw = _mm_mul_ps(vw, vd);

	__m128 result = _mm_add_ps(rx, _mm_add_ps(ry, _mm_add_ps(rz, rw)));

	return _mm_cvtss_f32(result);
}

float Maths::Vec4S::MagnitudeSquared() const
{
	return Dot(*this);
}

float Maths::Vec4S::Magnitude() const
{
	__m128 vx = _mm_set_ps1(x);
	__m128 vy = _mm_set_ps1(y);
	__m128 vz = _mm_set_ps1(z);
	__m128 vw = _mm_set_ps1(w);

	__m128 rx = _mm_mul_ps(vx, vx);
	__m128 ry = _mm_mul_ps(vy, vy);
	__m128 rz = _mm_mul_ps(vz, vz);
	__m128 rw = _mm_mul_ps(vw, vw);

	return _mm_cvtss_f32(_mm_sqrt_ss(_mm_add_ps(rx, _mm_add_ps(ry, _mm_add_ps(rz, rw)))));
}

Maths::Vec4S Maths::Vec4S::Normalize() const // A REVOIR
{
	if (!std::isfinite(x) || !std::isfinite(y) || !std::isfinite(z) || !std::isfinite(w))
	{
		throw std::domain_error("Cannot normalize non-finite components");
	}

	// Scaling avoids overflowing/underflowing the squared magnitude.

	__m128 vx = _mm_set_ps1(std::abs(x));
	__m128 vy = _mm_set_ps1(std::abs(y));
	__m128 vz = _mm_set_ps1(std::abs(z));
	__m128 vw = _mm_set_ps1(std::abs(w));

	const __m128 scale = _mm_max_ps(vx, _mm_max_ps(vy, _mm_max_ps(vz, vw)));
	float scalef = _mm_cvtss_f32(scale);
	if (scalef == 0.f)
	{
		throw std::domain_error("Cannot normalize the zero vector");
	}

	__m128 vp = _mm_setr_ps(x, y, z, w);
	const Maths::Vec4S scaled = Store(_mm_div_ps(vp, scale));
	return scaled / scaled.Magnitude();
}

float Maths::Vec4S::DistanceSquared(const Maths::Vec4S& rhs) const
{
	return Store(_mm_sub_ps(Load(*this), Load(rhs))).MagnitudeSquared();
}

float Maths::Vec4S::Distance(const Maths::Vec4S& rhs) const
{
	return Store(_mm_sub_ps(Load(*this), Load(rhs))).Magnitude();
}

float Maths::Vec4S::Angle(const Maths::Vec4S& rhs) const // A VOIR
{
	const float cosine = Normalize().Dot(rhs.Normalize());
	return std::acos(std::clamp(cosine, -1.f, 1.f));
}  // A REVOIRE ??

Maths::Vec4S Maths::Vec4S::Lerp(const Maths::Vec4S& a, const Maths::Vec4S& b, float t)
{

	__m128 va = Load(a);
	__m128 vb = Load(b);
	__m128 vt = _mm_set_ps1(t);
	__m128 v1 = _mm_set_ps1(1.f);

	return Store(_mm_add_ps(_mm_mul_ps(va, _mm_sub_ps(v1, vt)), _mm_mul_ps(vb, vt)));
}

Maths::Vec4S Maths::Vec4S::Min(const Maths::Vec4S& a, const Maths::Vec4S& b)
{
	__m128 va = Load(a);
	__m128 vb = Load(b);
	return Store(_mm_min_ps(va, vb));
}

Maths::Vec4S Maths::Vec4S::Max(const Maths::Vec4S& a, const Maths::Vec4S& b)
{
	__m128 va = Load(a);
	__m128 vb = Load(b);
	return Store(_mm_max_ps(va, vb));
}

const Maths::Vec4S Maths::Vec4S::Zero{ 0, 0, 0, 0 };

const Maths::Vec4S Maths::Vec4S::One{ 1, 1, 1, 1 };

const Maths::Vec4S Maths::Vec4S::UnitX{ 1, 0, 0, 0 };

const Maths::Vec4S Maths::Vec4S::UnitY{ 0, 1, 0, 0 };

const Maths::Vec4S Maths::Vec4S::UnitZ{ 0, 0, 1, 0 };

const Maths::Vec4S Maths::Vec4S::UnitW{ 0, 0, 0, 1 };