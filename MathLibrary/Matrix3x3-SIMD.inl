#include "Matrix3x3-SIMD.h"
#pragma once 
namespace Maths
{
    inline Matrix3x3SIMD::Matrix3x3SIMD()
    {
		                       //w,   z,    y,    x
        values[0] = _mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f);
        values[1] = _mm_set_ps(0.0f, 0.0f, 1.0f, 0.0f);
        values[2] = _mm_set_ps(0.0f, 1.0f, 0.0f, 0.0f);

    }

    inline Matrix3x3SIMD::Matrix3x3SIMD(const std::array<float, 9>& elements)
    {
        values[0] = _mm_set_ps
        (
            0.0f,
            elements[2],
            elements[1],
            elements[0]
        );

        values[1] = _mm_set_ps
        (
            0.0f,
            elements[5],
            elements[4],
            elements[3]
        );

        values[2] = _mm_set_ps
        (
            0.0f,
            elements[8],
            elements[7],
            elements[6]
        );

    }


    inline Matrix3x3SIMD::Matrix3x3SIMD
        (
            __m128 row0,
            __m128 row1,
            __m128 row2
        )
    {
        values[0] = row0;
        values[1] = row1;
        values[2] = row2;
    }



    inline Matrix3x3SIMD Matrix3x3SIMD::Store(const __m128 row0, const __m128 row1, const __m128 row2)
    {
		return Matrix3x3SIMD
		{
			row0,
			row1,
			row2
		};

    }

    inline Matrix3x3SIMD Matrix3x3SIMD::Identity()
    {
        return Maths::Matrix3x3SIMD();
    }

    inline Matrix3x3SIMD Matrix3x3SIMD::Zero()
    {
		return Maths::Matrix3x3SIMD
		(
			_mm_setzero_ps(),
			_mm_setzero_ps(),
			_mm_setzero_ps()
		);

    }

    //inline __m128& Matrix3x3SIMD::operator()(std::size_t row, std::size_t column)
    //{
    //}

    //inline const __m128& Matrix3x3SIMD::operator()(std::size_t row, std::size_t column) const
    //{
    //}

    inline Matrix3x3SIMD Matrix3x3SIMD::operator+(const Matrix3x3SIMD& rhs) const
    {
		Maths::Matrix3x3SIMD result = Zero();

		result.values[0] = _mm_add_ps(values[0], rhs.values[0]);
		result.values[1] = _mm_add_ps(values[1], rhs.values[1]);
		result.values[2] = _mm_add_ps(values[2], rhs.values[2]);

		return result;
    }

    inline Matrix3x3SIMD Matrix3x3SIMD::operator-(const Matrix3x3SIMD& rhs) const
    {
		Maths::Matrix3x3SIMD result = Zero();

		result.values[0] = _mm_sub_ps(values[0], rhs.values[0]);
		result.values[1] = _mm_sub_ps(values[1], rhs.values[1]);
		result.values[2] = _mm_sub_ps(values[2], rhs.values[2]);

		return result;
    }

  //  inline Matrix3x3SIMD Matrix3x3SIMD::operator*(const Matrix3x3SIMD& rhs) const
  //  {
		//Maths::Matrix3x3SIMD result = Zero();

		////result.values[0] = _mm_shuffle_ps() // En gros il faut utiliser _mm_shuffle_ps pour réorganiser les éléments de la matrice de droite et ensuite faire des multiplications et additions pour obtenir le résultat
  //      // je sais pas encore comment faire.
  //  }

   /* inline Maths::Vec3<float> Matrix3x3SIMD::operator*(const Maths::Vec3<float>& rhs) const
    {
    }

    inline Matrix3x3SIMD Matrix3x3SIMD::operator*(__m128 scalar) const
    {
    }

    inline Matrix3x3SIMD& Matrix3x3SIMD::operator*=(const Matrix3x3SIMD& rhs)
    {
    }

    inline bool Matrix3x3SIMD::operator==(const Matrix3x3SIMD& rhs) const
    {
    }

    inline bool Matrix3x3SIMD::operator!=(const Matrix3x3SIMD& rhs) const
    {
    }*/

    //inline Matrix3x3SIMD Matrix3x3SIMD::Transpose() const
    //{
    //}

    //inline __m128 Matrix3x3SIMD::Determinant() const
    //{
    //}

    //inline Matrix3x3SIMD Matrix3x3SIMD::Inverse(float relativeTolerance) const
    //{
    //}

    //inline Matrix3x3SIMD Matrix3x3SIMD::Scale(const Maths::Vec3<float>& scale)
    //{
    //}

    //inline Matrix3x3SIMD Matrix3x3SIMD::RotationX(__m128 radians)
    //{
    //}

    //inline Matrix3x3SIMD Matrix3x3SIMD::RotationY(__m128 radians)
    //{
    //}

    //inline Matrix3x3SIMD Matrix3x3SIMD::RotationZ(__m128 radians)
    //{
    //}
}