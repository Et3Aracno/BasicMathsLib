#pragma once

inline Maths::Vec2S::Vec2S() : v(0) {}

inline Maths::Vec2S::Vec2S(float _x, float _y) {
	v = _mm_setr_ps(_x, _y, 0.f, 0.f);
}

inline Maths::Vec2S::Vec2S(const __m128& other) {v = other; }

inline Maths::Vec2S Maths::Vec2S::operator+(const __m128& rhs) const
{
	//return _mm_add_ps(v, rhs);

	return Vec2S(_mm_add_ps(v, rhs));
}

//inline Maths::Vec2S Maths::Vec2S::operator-(const Maths::Vec2S& rhs) const
//{
//	const __m128 vp = _mm_setr_ps(x, y, 0, 0);
//	const __m128 vrhs = Load(rhs);
//	return Store(_mm_sub_ps(vp, vrhs));
//}
//
//inline Maths::Vec2S Maths::Vec2S::operator*(const Maths::Vec2S& rhs) const
//{
//	__m128 vp = _mm_setr_ps(x, y, 0, 0);
//	__m128 vrhs = Load(rhs);
//	return Store(_mm_mul_ps(vp, vrhs));
//}
//
//inline Maths::Vec2S Maths::Vec2S::operator/(const Maths::Vec2S& rhs) const
//{
//	__m128 vrhs = Load(rhs);
//	if (rhs.x == 0.f || rhs.y == 0.f)
//	{
//		throw std::domain_error("Cannot divide by a zero component");
//	}
//	__m128 vp = _mm_setr_ps(x, y, 0, 0);
//	return Store(_mm_div_ps(vp, vrhs));
//}
//
//inline Maths::Vec2S Maths::Vec2S::operator-() const
//{
//	return {-x, -y};
//}
//
//inline Maths::Vec2S Maths::Vec2S::operator*(float scalar) const
//{
//	__m128 vp = _mm_setr_ps(x, y, 0, 0);
//	__m128 vs = _mm_set_ps1(scalar);
//
//	return Store(_mm_mul_ps(vp, vs));
//}
//
//inline Maths::Vec2S Maths::Vec2S::operator/(float scalar) const
//{
//	__m128 vs = _mm_set_ps1(scalar);
//	__m128 vzero = _mm_set_ps1(0);
//	if (_mm_movemask_ps(_mm_cmpeq_ps(vs, vzero)))
//	{
//		throw std::domain_error("Cannot divide by zero");
//	}
//
//	__m128 vp = _mm_setr_ps(x, y, 0, 0);
//	return Store(_mm_div_ps(vp, vs));
//}
//
//inline Maths::Vec2S& Maths::Vec2S::operator+=(const Maths::Vec2S& rhs)
//{
//	__m128 vp = Load(*this);
//	__m128 vrhs = Load(rhs);
//
//	*this = Store(_mm_add_ps(vp, vrhs));
//	return *this;
//}
//
//inline Maths::Vec2S& Maths::Vec2S::operator-=(const Maths::Vec2S& rhs)
//{
//	__m128 vp = Load(*this);
//	__m128 vrhs = Load(rhs);
//
//	*this = Store(_mm_sub_ps(vp, vrhs));
//	return *this;
//}
//
//inline Maths::Vec2S& Maths::Vec2S::operator*=(const Maths::Vec2S& rhs)
//{
//	__m128 vp = Load(*this);
//	__m128 vrhs = Load(rhs);
//
//	*this = Store(_mm_mul_ps(vp, vrhs));
//	return *this;
//}
//
//inline Maths::Vec2S& Maths::Vec2S::operator/=(const Maths::Vec2S& rhs)
//{
//	if(rhs.x == 0.f || rhs.y == 0.f)
//	{
//		throw std::domain_error("Cannot divide by a zero component");
//	}
//
//	__m128 vp = Load(*this);
//	__m128 vrhs = Load(rhs);
//
//	*this = Store(_mm_div_ps(vp, vrhs));
//	return *this;
//}
//
//inline Maths::Vec2S& Maths::Vec2S::operator*=(float scalar)
//{
//	__m128 vp = Load(*this);
//	__m128 vrhs = _mm_set_ps1(scalar);
//
//	*this = Store(_mm_mul_ps(vp, vrhs));
//	return *this;
//}
//
//inline Maths::Vec2S& Maths::Vec2S::operator/=(float scalar)
//{
//	__m128 vs = _mm_set_ps1(scalar);
//	__m128 vzero = _mm_set_ps1(0);
//	if (_mm_movemask_ps(_mm_cmpeq_ps(vs, vzero)))
//	{
//		throw std::domain_error("Cannot divide by zero");
//	}
//	__m128 vp = Load(*this);
//	__m128 vrhs = _mm_set_ps1(scalar);
//
//	*this = Store(_mm_div_ps(vp, vrhs));
//	return *this;
//}
//
//inline bool Maths::Vec2S::operator==(const Maths::Vec2S& rhs) const
//{
//	__m128 vrhs = Load(rhs);
//	__m128 vp = _mm_setr_ps(x, y, 0, 0);
//
//	return _mm_movemask_ps(_mm_cmpeq_ps(vrhs, vp)) == 0xF;
//}
//
//inline bool Maths::Vec2S::operator!=(const Maths::Vec2S& rhs) const
//{
//	__m128 vrhs = Load(rhs);
//	__m128 vp = _mm_setr_ps(x, y, 0, 0);
//
//	return _mm_movemask_ps((_mm_cmpeq_ps(vrhs, vp))) != 0xF; // ALLER VOUS FAIRE METTRE Y'A PAS DE NOT
//}
//
//inline float Maths::Vec2S::Dot(const Maths::Vec2S& rhs) const
//{
//	__m128 vx = _mm_set_ps1(rhs.x);
//	__m128 vy = _mm_set_ps1(rhs.y);
//
//	__m128 va = _mm_set_ps1(x);
//	__m128 vb = _mm_set_ps1(y);
//
//	__m128 rx = _mm_mul_ps(va, vx);
//	__m128 ry = _mm_mul_ps(vb, vy);
//
//	__m128 result = _mm_add_ps(rx, ry);
//
//	return _mm_cvtss_f32(result);
//}
//
//inline float Maths::Vec2S::MagnitudeSquared() const
//{
//	return Dot(*this);
//}
//
//inline float Maths::Vec2S::Magnitude() const
//{
//	__m128 vx = _mm_set_ps1(x);
//	__m128 vy = _mm_set_ps1(y);
//
//	__m128 rx = _mm_mul_ps(vx, vx);
//	__m128 ry = _mm_mul_ps(vy, vy);
//
//	return _mm_cvtss_f32(_mm_sqrt_ss(_mm_add_ps(rx, ry)));
//}
//
//inline Maths::Vec2S Maths::Vec2S::Normalize() const // A REVOIR
//{
//	if (!std::isfinite(x) || !std::isfinite(y))
//	{
//		throw std::domain_error("Cannot normalize non-finite components");
//	}
//
//	// Scaling avoids overflowing/underflowing the squared magnitude.
//
//	__m128 vx = _mm_set_ps1(std::abs(x));
//	__m128 vy = _mm_set_ps1(std::abs(y));
//
//	const __m128 scale = _mm_max_ps(vx, vy);
//	float scalef = _mm_cvtss_f32(scale);
//	if (scalef == 0.f)
//	{
//		throw std::domain_error("Cannot normalize the zero vector");
//	}
//
//	__m128 vp = _mm_setr_ps(x, y, 0, 0);
//	const Maths::Vec2S scaled = Store(_mm_div_ps(vp, scale));
//	return scaled / scaled.Magnitude();
//} 
//
//inline float Maths::Vec2S::DistanceSquared(const Maths::Vec2S& rhs) const
//{
//	return Store(_mm_sub_ps(Load(*this), Load(rhs))).MagnitudeSquared();
//}
//
//inline float Maths::Vec2S::Distance(const Maths::Vec2S& rhs) const
//{
//	return Store(_mm_sub_ps(Load(*this), Load(rhs))).Magnitude();
//}
//
//inline float Maths::Vec2S::Angle(const Maths::Vec2S& rhs) const // A VOIR
//{
//	const float cosine = Normalize().Dot(rhs.Normalize());
//	return std::acos(std::clamp(cosine, -1.f, 1.f));
//}  // A REVOIRE ??
//
//inline Maths::Vec2S Maths::Vec2S::Lerp(const Maths::Vec2S& a, const Maths::Vec2S& b, float t)
//{
//	__m128 va = Load(a);
//	__m128 vb = Load(b);
//	__m128 vt = _mm_set_ps1(t);
//	__m128 v1 = _mm_set_ps1(1.f);
//
//	return Store(_mm_add_ps(_mm_mul_ps(va, _mm_sub_ps(v1, vt)), _mm_mul_ps(vb, vt)));
//}
//
//inline Maths::Vec2S Maths::Vec2S::Min(const Maths::Vec2S& a, const Maths::Vec2S& b)
//{
//	__m128 va = Load(a);
//	__m128 vb = Load(b);
//	return Store(_mm_min_ps(va, vb));
//}
//
//inline Maths::Vec2S Maths::Vec2S::Max(const Maths::Vec2S& a, const Maths::Vec2S& b)
//{
//	__m128 va = Load(a);
//	__m128 vb = Load(b);
//	return Store(_mm_max_ps(va, vb));
//}

inline const Maths::Vec2S  Maths::Vec2S::Zero{0, 0};

inline const Maths::Vec2S  Maths::Vec2S::One{1, 1};

inline const Maths::Vec2S  Maths::Vec2S::UnitX{1, 0};

inline const Maths::Vec2S  Maths::Vec2S::UnitY{0, 1};
