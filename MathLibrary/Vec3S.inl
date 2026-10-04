#pragma once

__m128 Maths::Vec3S::Load(const Maths::Vec3S& v)
{
	return _mm_setr_ps(v.x, v.y, v.z, 0.f);
}

Maths::Vec3S Maths::Vec3S::Store(__m128 val) 
{
	float component[4];
	_mm_storeu_ps(component, val);
	return {
		component[0],
		component[1],
		component[2]
	};
}

Maths::Vec3S::Vec3S() : x(0), y(0), z(0) {}

Maths::Vec3S::Vec3S(float _x, float _y, float _z) : x(_x), y(_y), z(_z){}

Maths::Vec3S::Vec3S(const Maths::Vec3S& other) : x(other.x), y(other.y), z(other.z){}

Maths::Vec3S Maths::Vec3S::operator+(const Maths::Vec3S& rhs) const
{
    __m128 vp = _mm_setr_ps(x, y, z, 0);
	__m128 vrhs = Load(rhs);

	return Store(_mm_add_ps(vp, vrhs));

	/*__m128 result = _mm_add_ps(vp, vrhs);

	float component[4];
	_mm_storeu_ps(component, result);

	return {
		component[0],
		component[1],
		component[2]
	};*/
}

Maths::Vec3S Maths::Vec3S::operator-(const Maths::Vec3S& rhs) const
{
	const __m128 vp = _mm_setr_ps(x, y, z, 0);
	const __m128 vrhs = Load(rhs);
	return Store(_mm_sub_ps(vp, vrhs));
}

Maths::Vec3S Maths::Vec3S::operator*(const Maths::Vec3S& rhs) const
{
	__m128 vp = _mm_setr_ps(x, y, z, 0);
	__m128 vrhs = Load(rhs);
	return Store(_mm_mul_ps(vp, vrhs));
}

Maths::Vec3S Maths::Vec3S::operator/(const Maths::Vec3S& rhs) const
{
	__m128 vrhs = Load(rhs);
	if (rhs.x == 0.f || rhs.y == 0.f || rhs.z == 0.f)
	{
		throw std::domain_error("Cannot divide by a zero component");
	}
	__m128 vp = _mm_setr_ps(x, y, z, 0);
	return Store(_mm_div_ps(vp, vrhs));
}

Maths::Vec3S Maths::Vec3S::operator-() const
{
	return { -x, -y, -z };
}

Maths::Vec3S Maths::Vec3S::operator*(float scalar) const
{
	__m128 vp = _mm_setr_ps(x, y, z, 0);
	__m128 vs = _mm_set_ps1(scalar);

	return Store(_mm_mul_ps(vp, vs));
}

Maths::Vec3S Maths::Vec3S::operator/(float scalar) const
{
	__m128 vs = _mm_set_ps1(scalar);
	__m128 vzero = _mm_set_ps1(0);
	if (_mm_movemask_ps(_mm_cmpeq_ps(vs, vzero)))
	{
		throw std::domain_error("Cannot divide by zero");
	}

	__m128 vp = _mm_setr_ps(x, y, z, 0);
	return Store(_mm_div_ps(vs, vp));
}

Maths::Vec3S& Maths::Vec3S::operator+=(const Maths::Vec3S& rhs)
{
	__m128 vp = Load(*this);
	__m128 vrhs = Load(rhs);

	*this = Store(_mm_add_ps(vp, vrhs));
	return *this;
}

Maths::Vec3S& Maths::Vec3S::operator-=(const Maths::Vec3S& rhs)
{
	__m128 vp = Load(*this);
	__m128 vrhs = Load(rhs);

	*this = Store(_mm_sub_ps(vp, vrhs));
	return *this;
}

Maths::Vec3S& Maths::Vec3S::operator*=(const Maths::Vec3S& rhs)
{
	__m128 vp = Load(*this);
	__m128 vrhs = Load(rhs);

	*this = Store(_mm_mul_ps(vp, vrhs));
	return *this;
}

Maths::Vec3S& Maths::Vec3S::operator/=(const Maths::Vec3S& rhs)
{
	__m128 vp = Load(*this);
	__m128 vrhs = Load(rhs);

	*this = Store(_mm_div_ps(vp, vrhs));   
	return *this;                          
}

Maths::Vec3S& Maths::Vec3S::operator*=(float scalar)
{
	__m128 vp = Load(*this);
	__m128 vrhs = _mm_set_ps1(scalar);

	*this = Store(_mm_mul_ps(vp, vrhs));
	return *this;
}

Maths::Vec3S& Maths::Vec3S::operator/=(float scalar)
{
	__m128 vp = Load(*this);
	__m128 vrhs = _mm_set_ps1(scalar);

	*this = Store(_mm_div_ps(vp, vrhs));
	return *this;
}

//Maths::Vec3S Maths::Vec3S::operator*(float scalar, const Maths::Vec3S& vector)
//{
//	__m128 vv = Load(vector);
//	__m128 vt = _mm_set_ps1(scalar);
//	return Store(_mm_mul_ps(vv, vt));
//}

bool Maths::Vec3S::operator==(const Maths::Vec3S& rhs) const
{
	__m128 vrhs = Load(rhs);
	__m128 vp = _mm_setr_ps(x, y, z, 0);

	return _mm_movemask_ps(_mm_cmpeq_ps(vrhs, vp)) == 0xF;
}

bool Maths::Vec3S::operator!=(const Maths::Vec3S& rhs) const
{
	__m128 vrhs = Load(rhs);
	__m128 vp = _mm_setr_ps(x, y, z, 0);

	return _mm_movemask_ps((_mm_cmpeq_ps(vrhs, vp))) == 0xF; // ALLER VOUS FAIRE METTRE Y'A PAS DE NOT
}

float Maths::Vec3S::Dot(const Maths::Vec3S& rhs) const
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

	__m128 result = _mm_add_ps(rx, _mm_add_ps(ry, rz));

	return _mm_cvtss_f32(result);
}

Maths::Vec3S Maths::Vec3S::Cross(const Maths::Vec3S& rhs) const
{
	__m128 vx = _mm_set_ps1(rhs.x);
	__m128 vy = _mm_set_ps1(rhs.y);
	__m128 vz = _mm_set_ps1(rhs.z);

	__m128 va = _mm_set_ps1(x);
	__m128 vb = _mm_set_ps1(y);
	__m128 vc = _mm_set_ps1(z);

	__m128 rx = _mm_mul_ps(vb, vz);
	__m128 ra = _mm_mul_ps(vc, vy);
	__m128 ry = _mm_mul_ps(vc, vx);
	__m128 rb = _mm_mul_ps(va, vz);
	__m128 rz = _mm_mul_ps(va, vy);
	__m128 rc = _mm_mul_ps(vb, vx);

	float x = _mm_cvtss_f32(_mm_sub_ps(rx, ra));
	float y = _mm_cvtss_f32(_mm_sub_ps(ry, rb));
	float z= _mm_cvtss_f32(_mm_sub_ps(rz, rc));

	return {x, y, z};
}

float Maths::Vec3S::MagnitudeSquared() const
{
	return Dot(*this);
}

float Maths::Vec3S::Magnitude() const
{
	__m128 vp = _mm_setr_ps(x, y, z, 0);
	return _mm_cvtss_f32(_mm_sqrt_ps(vp));
}

Maths::Vec3S Maths::Vec3S::Normalize() const // A REVOIR
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
	if (scalef == 0.f)
	{
		throw std::domain_error("Cannot normalize the zero vector");
	}

	__m128 vp = _mm_setr_ps(x, y, z, 0);
	const Maths::Vec3S scaled = Store(_mm_div_ps(vp, scale));
	return scaled / scaled.Magnitude();
}

float Maths::Vec3S::DistanceSquared(const Maths::Vec3S& rhs) const
{
	return Store(_mm_sub_ps(Load(*this), Load(rhs))).MagnitudeSquared();
}

float Maths::Vec3S::Distance(const Maths::Vec3S& rhs) const
{
	return Store(_mm_sub_ps(Load(*this), Load(rhs))).Magnitude();
}

float Maths::Vec3S ::Angle(const Maths::Vec3S & rhs) const // A VOIR
{
	const float cosine = Normalize().Dot(rhs.Normalize());
	return std::acos(std::clamp(cosine, -1.f, 1.f));
}  // A REVOIRE ??

Maths::Vec3S Maths::Vec3S::Lerp(const Maths::Vec3S& a, const Maths::Vec3S& b, float t)
{

	__m128 va = Load(a);
	__m128 vb = Load(b);
	__m128 vt = _mm_set_ps1(t);
	__m128 v1 = _mm_set_ps1(1.f);

	return Store(_mm_mul_ps(va, _mm_add_ps(_mm_sub_ps(v1, vt), _mm_mul_ps(vb, vt))));
}

Maths::Vec3S Maths::Vec3S::Min(const Maths::Vec3S& a, const Maths::Vec3S& b)
{	
	__m128 va = Load(a);
	__m128 vb = Load(b);
	return Store(_mm_min_ps(va, vb));
}

Maths::Vec3S Maths::Vec3S::Max(const Maths::Vec3S& a, const Maths::Vec3S& b)
{
	__m128 va = Load(a);
	__m128 vb = Load(b);
	return Store(_mm_max_ps(va, vb));
}

const Maths::Vec3S  Maths::Vec3S ::Zero{ 0, 0, 0 };

const Maths::Vec3S  Maths::Vec3S ::One{ 1, 1, 1 };

const Maths::Vec3S  Maths::Vec3S ::UnitX{ 1, 0, 0 };

const Maths::Vec3S  Maths::Vec3S ::UnitY{ 0, 1, 0 };

const Maths::Vec3S  Maths::Vec3S ::UnitZ{ 0, 0, 1 };