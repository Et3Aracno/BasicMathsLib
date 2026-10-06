//#pragma once
//
//__m128d Maths::Vec3dS::Load(const Maths::Vec3dS& v)
//{
//	return _mm_setr_ps(v.x, v.y, v.z, 0.f);
//}
//
//Maths::Vec3dS Maths::Vec3dS::Store(__m128d val)
//{
//	double component[4];
//	_mm_storeu_ps(component, val);
//	return {
//		component[0],
//		component[1],
//		component[2]
//	};
//}
//
//Maths::Vec3dS::Vec3dS() : x(0), y(0), z(0) {}
//
//Maths::Vec3dS::Vec3dS(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
//
//Maths::Vec3dS::Vec3dS(const Maths::Vec3dS& other) {
//	x = other.x; y = other.y; z = other.z;
//}
//
//Maths::Vec3dS Maths::Vec3dS::operator+(const Maths::Vec3dS& rhs) const
//{
//	__m128d vp = _mm_setr_ps(x, y, z, 0);
//	__m128d vrhs = Load(rhs);
//
//	return Store(_mm_add_ps(vp, vrhs));
//}
//
//Maths::Vec3dS Maths::Vec3dS::operator-(const Maths::Vec3dS& rhs) const
//{
//	const __m128d vp = _mm_setr_ps(x, y, z, 0);
//	const __m128d vrhs = Load(rhs);
//	return Store(_mm_sub_ps(vp, vrhs));
//}
//
//Maths::Vec3dS Maths::Vec3dS::operator*(const Maths::Vec3dS& rhs) const
//{
//	__m128d vp = _mm_setr_ps(x, y, z, 0);
//	__m128d vrhs = Load(rhs);
//	return Store(_mm_mul_ps(vp, vrhs));
//}
//
//Maths::Vec3dS Maths::Vec3dS::operator/(const Maths::Vec3dS& rhs) const
//{
//	__m128d vrhs = Load(rhs);
//	if (rhs.x == 0.f || rhs.y == 0.f || rhs.z == 0.f)
//	{
//		throw std::domain_error("Cannot divide by a zero component");
//	}
//	__m128d vp = _mm_setr_ps(x, y, z, 0);
//	return Store(_mm_div_ps(vp, vrhs));
//}
//
//Maths::Vec3dS Maths::Vec3dS::operator-() const
//{
//	return { -x, -y, -z };
//}
//
//Maths::Vec3dS Maths::Vec3dS::operator*(double scalar) const
//{
//	__m128d vp = Load(*this);
//	__m128d vs = _mm_set_ps1(scalar);
//
//	return Store(_mm_mul_ps(vp, vs));
//}
//
//Maths::Vec3dS Maths::Vec3dS::operator/(double scalar) const
//{
//	__m128d vs = _mm_set_ps1(scalar);
//	__m128d vzero = _mm_set_ps1(0);
//	if (_mm_movemask_ps(_mm_cmpeq_ps(vs, vzero)))
//	{
//		throw std::domain_error("Cannot divide by zero");
//	}
//
//	__m128d vp = _mm_setr_ps(x, y, z, 0);
//	return Store(_mm_div_ps(vp, vs));
//}
//
//Maths::Vec3dS& Maths::Vec3dS::operator+=(const Maths::Vec3dS& rhs)
//{
//	__m128d vp = Load(*this);
//	__m128d vrhs = Load(rhs);
//
//	*this = Store(_mm_add_ps(vp, vrhs));
//	return *this;
//}
//
//Maths::Vec3dS& Maths::Vec3dS::operator-=(const Maths::Vec3dS& rhs)
//{
//	__m128d vp = Load(*this);
//	__m128d vrhs = Load(rhs);
//
//	*this = Store(_mm_sub_ps(vp, vrhs));
//	return *this;
//}
//
//Maths::Vec3dS& Maths::Vec3dS::operator*=(const Maths::Vec3dS& rhs)
//{
//	__m128d vp = Load(*this);
//	__m128d vrhs = Load(rhs);
//
//	*this = Store(_mm_mul_ps(vp, vrhs));
//	return *this;
//}
//
//Maths::Vec3dS& Maths::Vec3dS::operator/=(const Maths::Vec3dS& rhs)
//{
//	if (rhs.x == 0.f || rhs.y == 0.f || rhs.z == 0.f)
//	{
//		throw std::domain_error("Cannot divide by a zero component");
//	}
//
//	__m128d vp = Load(*this);
//	__m128d vrhs = Load(rhs);
//
//	*this = Store(_mm_div_ps(vp, vrhs));
//	return *this;
//}
//
//Maths::Vec3dS& Maths::Vec3dS::operator*=(double scalar)
//{
//	__m128d vp = Load(*this);
//	__m128d vrhs = _mm_set_ps1(scalar);
//
//	*this = Store(_mm_mul_ps(vp, vrhs));
//	return *this;
//}
//
//Maths::Vec3dS& Maths::Vec3dS::operator/=(double scalar)
//{
//	__m128d vs = _mm_set_ps1(scalar);
//	__m128d vzero = _mm_set_ps1(0);
//	if (_mm_movemask_ps(_mm_cmpeq_ps(vs, vzero))) {
//		throw std::domain_error("Cannot divide by zero");
//	}
//
//	__m128d vp = Load(*this);
//	__m128d vrhs = _mm_set_ps1(scalar);
//
//	*this = Store(_mm_div_ps(vp, vrhs));
//	return *this;
//}
//
//Maths::Vec3dS operator*(double scalar, const Maths::Vec3dS& vector)
//{
//	__m128d vv = _mm_setr_ps(vector.x, vector.y, vector.z, 0.f);
//	__m128d vt = _mm_set_ps1(scalar);
//	__m128d result = _mm_mul_ps(vv, vt);
//
//	double component[4];
//	_mm_storeu_ps(component, result);
//	return {
//		component[0],
//		component[1],
//		component[2]
//	};
//}
//
//bool Maths::Vec3dS::operator==(const Maths::Vec3dS& rhs) const
//{
//	__m128d vrhs = Load(rhs);
//	__m128d vp = _mm_setr_ps(x, y, z, 0);
//
//	return _mm_movemask_ps(_mm_cmpeq_ps(vrhs, vp)) == 0xF;
//}
//
//bool Maths::Vec3dS::operator!=(const Maths::Vec3dS& rhs) const
//{
//	__m128d vrhs = Load(rhs);
//	__m128d vp = _mm_setr_ps(x, y, z, 0);
//
//	return _mm_movemask_ps((_mm_cmpeq_ps(vrhs, vp))) != 0xF; // ALLER VOUS FAIRE METTRE Y'A PAS DE NOT
//}
//
//double Maths::Vec3dS::Dot(const Maths::Vec3dS& rhs) const
//{
//	__m128d vx = _mm_set_ps1(rhs.x);
//	__m128d vy = _mm_set_ps1(rhs.y);
//	__m128d vz = _mm_set_ps1(rhs.z);
//
//	__m128d va = _mm_set_ps1(x);
//	__m128d vb = _mm_set_ps1(y);
//	__m128d vc = _mm_set_ps1(z);
//
//	__m128d rx = _mm_mul_ps(vx, va);
//	__m128d ry = _mm_mul_ps(vy, vb);
//	__m128d rz = _mm_mul_ps(vz, vc);
//
//	__m128d result = _mm_add_ps(rx, _mm_add_ps(ry, rz));
//
//	return _mm_cvtss_f32(result);
//}
//
//Maths::Vec3dS Maths::Vec3dS::Cross(const Maths::Vec3dS& rhs) const
//{
//	__m128d vx = _mm_set_ps1(rhs.x);
//	__m128d vy = _mm_set_ps1(rhs.y);
//	__m128d vz = _mm_set_ps1(rhs.z);
//
//	__m128d va = _mm_set_ps1(x);
//	__m128d vb = _mm_set_ps1(y);
//	__m128d vc = _mm_set_ps1(z);
//
//	__m128d rx = _mm_mul_ps(vb, vz);
//	__m128d ra = _mm_mul_ps(vc, vy);
//	__m128d ry = _mm_mul_ps(vc, vx);
//	__m128d rb = _mm_mul_ps(va, vz);
//	__m128d rz = _mm_mul_ps(va, vy);
//	__m128d rc = _mm_mul_ps(vb, vx);
//
//	double fx = _mm_cvtss_f32(_mm_sub_ps(rx, ra));
//	double fy = _mm_cvtss_f32(_mm_sub_ps(ry, rb));
//	double fz = _mm_cvtss_f32(_mm_sub_ps(rz, rc));
//
//	return { fx, fy, fz };
//}
//
//double Maths::Vec3dS::MagnitudeSquared() const
//{
//	return Dot(*this);
//}
//
//double Maths::Vec3dS::Magnitude() const
//{
//	__m128d vx = _mm_set_ps1(x);
//	__m128d vy = _mm_set_ps1(y);
//	__m128d vz = _mm_set_ps1(z);
//
//	__m128d rx = _mm_mul_ps(vx, vx);
//	__m128d ry = _mm_mul_ps(vy, vy);
//	__m128d rz = _mm_mul_ps(vz, vz);
//
//	return _mm_cvtss_f32(_mm_sqrt_ss(_mm_add_ps(rx, _mm_add_ps(ry, rz))));
//}
//
//Maths::Vec3dS Maths::Vec3dS::Normalize() const // A REVOIR
//{
//	if (!std::isfinite(x) || !std::isfinite(y) || !std::isfinite(z))
//	{
//		throw std::domain_error("Cannot normalize non-finite components");
//	}
//
//	// Scaling avoids overflowing/underflowing the squared magnitude.
//
//	__m128d vx = _mm_set_ps1(std::abs(x));
//	__m128d vy = _mm_set_ps1(std::abs(y));
//	__m128d vz = _mm_set_ps1(std::abs(z));
//
//	const __m128d scale = _mm_max_ps(vx, _mm_max_ps(vy, vz));
//	double scalef = _mm_cvtss_f32(scale);
//	if (scalef == 0.f)
//	{
//		throw std::domain_error("Cannot normalize the zero vector");
//	}
//
//	__m128d vp = _mm_setr_ps(x, y, z, 0);
//	const Maths::Vec3dS scaled = Store(_mm_div_ps(vp, scale));
//	return scaled / scaled.Magnitude();
//}
//
//double Maths::Vec3dS::DistanceSquared(const Maths::Vec3dS& rhs) const
//{
//	return Store(_mm_sub_ps(Load(*this), Load(rhs))).MagnitudeSquared();
//}
//
//double Maths::Vec3dS::Distance(const Maths::Vec3dS& rhs) const
//{
//	return Store(_mm_sub_ps(Load(*this), Load(rhs))).Magnitude();
//}
//
//double Maths::Vec3dS::Angle(const Maths::Vec3dS& rhs) const // A VOIR
//{
//	const double cosine = Normalize().Dot(rhs.Normalize());
//	return std::acos(std::clamp(cosine, -1.f, 1.f));
//}  // A REVOIRE ??
//
//Maths::Vec3dS Maths::Vec3dS::Lerp(const Maths::Vec3dS& a, const Maths::Vec3dS& b, double t)
//{
//
//	__m128d va = Load(a);
//	__m128d vb = Load(b);
//	__m128d vt = _mm_set_ps1(t);
//	__m128d v1 = _mm_set_ps1(1.f);
//
//	return Store(_mm_add_ps(_mm_mul_ps(va, _mm_sub_ps(v1, vt)), _mm_mul_ps(vb, vt)));
//}
//
//Maths::Vec3dS Maths::Vec3dS::Min(const Maths::Vec3dS& a, const Maths::Vec3dS& b)
//{
//	__m128d va = Load(a);
//	__m128d vb = Load(b);
//	return Store(_mm_min_ps(va, vb));
//}
//
//Maths::Vec3dS Maths::Vec3dS::Max(const Maths::Vec3dS& a, const Maths::Vec3dS& b)
//{
//	__m128d va = Load(a);
//	__m128d vb = Load(b);
//	return Store(_mm_max_ps(va, vb));
//}
//
//const Maths::Vec3dS  Maths::Vec3dS::Zero{ 0, 0, 0 };
//
//const Maths::Vec3dS  Maths::Vec3dS::One{ 1, 1, 1 };
//
//const Maths::Vec3dS  Maths::Vec3dS::UnitX{ 1, 0, 0 };
//
//const Maths::Vec3dS  Maths::Vec3dS::UnitY{ 0, 1, 0 };
//
//const Maths::Vec3dS  Maths::Vec3dS::UnitZ{ 0, 0, 1 };