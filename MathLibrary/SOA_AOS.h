#pragma once
#include <xmmintrin.h>

namespace Maths
{
	class Vec3AOS {

	public:
		float x, y, z;

		Vec3AOS() : x(0), y(0), z(0) {}

		Vec3AOS(float x, float y, float z) : x(x), y(y), z(z) {}

		inline float Dot(const Vec3AOS& rhs) const
		{
			return x * rhs.x + y * rhs.y + z * rhs.z;
		}

		inline float DotSIMD(const Vec3AOS& rhs) const
		{
			__m128 a = _mm_setr_ps(x, y, z, 0.0f);
			__m128 b = _mm_setr_ps(rhs.x, rhs.y, rhs.z, 0.0f);

			// 0x71 : multiplie les lanes 0,1,2 (masque 0x7_) et ecrit la somme dans la lane 0 (masque _1)
			__m128 r = _mm_dp_ps(a, b, 0x71);

			return _mm_cvtss_f32(r);
		}

	};

	class Vec3SOA {
	public:

		static constexpr int Count = 1024;
		alignas(32) float x[Count];
		alignas(32) float y[Count];
		alignas(32) float z[Count];

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

		void DotSIMD(const Vec3SOA& rhs, float* out) const
		{
			for (int i = 0; i < Count; i += 4)
			{
				__m128 ax = _mm_load_ps(&x[i]);
				__m128 ay = _mm_load_ps(&y[i]);
				__m128 az = _mm_load_ps(&z[i]);
				__m128 bx = _mm_load_ps(&rhs.x[i]);
				__m128 by = _mm_load_ps(&rhs.y[i]);
				__m128 bz = _mm_load_ps(&rhs.z[i]);

				__m128 r = _mm_add_ps(_mm_add_ps(_mm_mul_ps(ax, bx),
					_mm_mul_ps(ay, by)),
					_mm_mul_ps(az, bz));
				_mm_storeu_ps(&out[i], r);
			}
		}
	};
}