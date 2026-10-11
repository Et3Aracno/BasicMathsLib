#pragma once
#include <xmmintrin.h>

namespace Maths
{
	class alignas(16) Vec3AOS {

	public:
		float x, y, z, w; // w for alignment

		Vec3AOS() : x(0), y(0), z(0), w(0) {}

		Vec3AOS(float x, float y, float z) : x(x), y(y), z(z), w(w) {}

		inline float Dot(const Vec3AOS& rhs) const
		{
			return x * rhs.x + y * rhs.y + z * rhs.z;
		}

		inline float DotSIMD(const Vec3AOS& rhs) const
		{
			__m128 a = _mm_setr_ps(x, y, z, 0.0f);
			__m128 b = _mm_setr_ps(rhs.x, rhs.y, rhs.z, 0.0f);

			__m128 r = _mm_dp_ps(a, b, 0x71); // multiply & add | Need to put it in the main vec3S to test too because the original SIMD is ugly as hell

			return _mm_cvtss_f32(r);
		}
	};

	class Vec3SOA {
	public:

		static constexpr int Count = 1024; // better adaptability
		alignas(16) float x[Count];
		alignas(16) float y[Count];
		alignas(16) float z[Count];

		Vec3SOA() {
			for (int i = 0; i < 1024; ++i) {
				x[i] = 0.0f;
				y[i] = 0.0f;
				z[i] = 0.0f;
			}
		}

		inline float Dot(const Vec3SOA& rhs, size_t index) const
		{
			return x[index] * rhs.x[index] + y[index] * rhs.y[index] + z[index] * rhs.z[index];
		}

		inline float DotSIMD(const Vec3SOA& rhs) const
		{
			__m128 sum = _mm_setzero_ps();

			for (int i = 0; i < Count; i += 4)
			{
				__m128 ax = _mm_load_ps(&x[i]);
				__m128 ay = _mm_load_ps(&y[i]);
				__m128 az = _mm_load_ps(&z[i]);
				__m128 bx = _mm_load_ps(&rhs.x[i]);
				__m128 by = _mm_load_ps(&rhs.y[i]);
				__m128 bz = _mm_load_ps(&rhs.z[i]);

				__m128 r = _mm_add_ps(_mm_add_ps(_mm_mul_ps(ax, bx), _mm_mul_ps(ay, by)), _mm_mul_ps(az, bz));
				sum = _mm_add_ps(sum, r);        
			}

			__m128 shuf = _mm_movehdup_ps(sum);    
			__m128 sums = _mm_add_ps(sum, shuf);  
			shuf = _mm_movehl_ps(shuf, sums);      
			sums = _mm_add_ss(sums, shuf);        
			return _mm_cvtss_f32(sums);
		}

		static void AosToSoa(const Vec3AOS* src, Vec3SOA& dst)
		{
			for (int i = 0; i < Vec3SOA::Count; i += 4)
			{
				__m128 r0 = _mm_load_ps(&src[i + 0].x);
				__m128 r1 = _mm_load_ps(&src[i + 1].x);
				__m128 r2 = _mm_load_ps(&src[i + 2].x);
				__m128 r3 = _mm_load_ps(&src[i + 3].x);

				_MM_TRANSPOSE4_PS(r0, r1, r2, r3);

				_mm_store_ps(&dst.x[i], r0);
				_mm_store_ps(&dst.y[i], r1);
				_mm_store_ps(&dst.z[i], r2);   // no r3 because not needed for Vec3S
			}
		}

		static void SoaToAos(const Vec3SOA& src, Vec3AOS* dst) // usable to return values
		{
			for (int i = 0; i < Vec3SOA::Count; i += 4)
			{
				__m128 r0 = _mm_load_ps(&src.x[i]);
				__m128 r1 = _mm_load_ps(&src.y[i]);
				__m128 r2 = _mm_load_ps(&src.z[i]);
				__m128 r3 = _mm_setzero_ps();

				_MM_TRANSPOSE4_PS(r0, r1, r2, r3);

				_mm_store_ps(&dst[i + 0].x, r0);
				_mm_store_ps(&dst[i + 1].x, r1);
				_mm_store_ps(&dst[i + 2].x, r2);
				_mm_store_ps(&dst[i + 3].x, r3);
			}
		}
	};
}