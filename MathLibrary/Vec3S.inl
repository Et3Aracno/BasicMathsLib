//#pragma once
//
//template <std::floating_point T>
//inline __m128 Load(const Maths::Vec3<T>& v)
//{
//	return _mm_setr_ps(v.x, v.y, v.z, v.w);
//}
//
//template <std::floating_point T>
//inline Maths::Vec3<T> Store(__m128 val)
//{
//	float component[4];
//	_mm_storeu_ps(component, val);
//
//	return {
//		component[0],
//		component[1],
//		component[2],
//		component[3]
//	};
//}
//
//template <std::floating_point T>
//Maths::Vec3<T>::Vec3() : x(0), y(0), z(0) {}
//
//template <std::floating_point T>
//Maths::Vec3<T>::Vec3(T _x, T _y, T _z) : x(_x), y(_y), z(_z){}
//
//template <std::floating_point T>
//template <std::floating_point U>
//Maths::Vec3<T>::Vec3(const Maths::Vec3<U>& other) : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)), z(static_cast<T>(other.z)){}
//
//template <std::floating_point T>
//Maths::Vec3<T> Maths::Vec3<T>::operator+(const Maths::Vec3<T>& rhs) const
//{
//    __m128 vp = _mm_setr_ps(x, y, z, 0);
//	__m128 vrhs = Load(rhs);
//    return Store(_mm_add_ps(vp, vrhs));
//}
//
//template <std::floating_point T>
//Maths::Vec3<T> Maths::Vec3<T>::operator*(const Maths::Vec3<T>& rhs) const
//{
//	__m128 vp = _mm_setr_ps(x, y, z, 0);
//	__m128 vrhs = Load(rhs);
//	return Store(_mm_mul_ps(vp, vrhs));
//}
//
//template <std::floating_point T>
//Maths::Vec3<T> Maths::Vec3<T>::operator/(const Maths::Vec3<T>& rhs) const
//{
//	__m128 vrhs = Load(rhs);
//	if (_mm_cmpeq_ps(_mm_set_ps1(0), vrhs)
//	{
//		throw std::domain_error("Cannot divide by a zero component");
//	}
//	__m128 vp = _mm_setr_ps(x, y, z, 0);
//	return Store(_mm_div_ps(vp, vrhs));
//}