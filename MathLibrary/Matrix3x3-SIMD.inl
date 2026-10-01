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

   inline Matrix3x3SIMD Matrix3x3SIMD::operator*(const Matrix3x3SIMD& rhs) const
    {

		Maths::Matrix3x3SIMD result = Zero();

       
		__m128 row0_0 = _mm_shuffle_ps(values[0], values[0], _MM_SHUFFLE(0, 0, 0, 0));          //ça demandera de faire un test de performance pour voir si il y a une différence
		__m128 row0_1 = _mm_shuffle_ps(values[0], values[0], _MM_SHUFFLE(1, 1, 1, 1));            //_MM_SHUFFLE ça permet  de ne pas écrire en binaire c'est un masque qui facilite la lecture du code après ça risque de prendre des performances , il faut tester 
        __m128 row0_2 = _mm_shuffle_ps(values[0],values[0],_MM_SHUFFLE(2, 2, 2, 2));

        result.values[0] = _mm_add_ps(_mm_mul_ps(row0_0, rhs.values[0]),_mm_add_ps(_mm_mul_ps(row0_1, rhs.values[1]),_mm_mul_ps(row0_2, rhs.values[2])));

        
        __m128 row1_0 = _mm_shuffle_ps(values[1],values[1],_MM_SHUFFLE(0, 0, 0, 0));
        __m128 row1_1 = _mm_shuffle_ps(values[1],values[1],_MM_SHUFFLE(1, 1, 1, 1));
        __m128 row1_2 = _mm_shuffle_ps(values[1],values[1],_MM_SHUFFLE(2, 2, 2, 2));

        result.values[1] = _mm_add_ps(_mm_mul_ps(row1_0, rhs.values[0]),_mm_add_ps(_mm_mul_ps(row1_1, rhs.values[1]),_mm_mul_ps(row1_2, rhs.values[2])));


       
        __m128 row2_0 = _mm_shuffle_ps(values[2],values[2],_MM_SHUFFLE(0, 0, 0, 0));
        __m128 row2_1 = _mm_shuffle_ps(values[2],values[2],_MM_SHUFFLE(1, 1, 1, 1));
        __m128 row2_2 = _mm_shuffle_ps(values[2],values[2],_MM_SHUFFLE(2, 2, 2, 2));

        result.values[2] = _mm_add_ps(_mm_mul_ps(row2_0, rhs.values[0]),_mm_add_ps(_mm_mul_ps(row2_1, rhs.values[1]),_mm_mul_ps(row2_2, rhs.values[2])));

        return result;
  }

    inline Maths::Vec3<float> Matrix3x3SIMD::operator*(const Maths::Vec3<float>& rhs) const
    {
        const __m128 vector = _mm_set_ps(
            0.0f,
            rhs.z,
            rhs.y,
            rhs.x
        );

       
        const __m128 row0 = _mm_mul_ps(values[0], vector);

        
        const __m128 row1 = _mm_mul_ps(values[1], vector);

        
        const __m128 row2 = _mm_mul_ps(values[2], vector);

        alignas(16) float temp0[4];
        alignas(16) float temp1[4];
		alignas(16) float temp2[4];     // Alignas permet de convertir les float en tableau de float pour pouvoir les additionner ensuite

        _mm_store_ps(temp0, row0);
        _mm_store_ps(temp1, row1);
        _mm_store_ps(temp2, row2);

        return Maths::Vec3<float>(
            temp0[0] + temp0[1] + temp0[2],
            temp1[0] + temp1[1] + temp1[2],
            temp2[0] + temp2[1] + temp2[2]
        );
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
    }

    inline Matrix3x3SIMD Matrix3x3SIMD::Transpose() const
    {
        Maths::Matrix3x3SIMD result = Zero();

        __m128 l0 = _mm_shuffle_ps(values[0], values[1], _MM_SHUFFLE(0, 3, 0, 3));
        __m128 resultL0 = _mm_shuffle_ps(l0 , values[2], _MM_SHUFFLE(3, 0, 2, 0));

        __m128 l1 = _mm_shuffle_ps(values[0], values[1], _MM_SHUFFLE(0, 1, 0, 1));
        __m128 resultL1 = _mm_shuffle_ps(l1, values[2],_MM_SHUFFLE(3, 1, 0, 2));

        __m128 l2 = _mm_shuffle_ps(values[0], values[1], _MM_SHUFFLE(0, 2, 0, 2));
        __m128 resultL2 = _mm_shuffle_ps(l2, values[2], _MM_SHUFFLE(3, 2, 0, 2));


		return Matrix3x3SIMD(resultL0, resultL1, resultL2);

    }

    //inline __m128 Matrix3x3SIMD::Determinant() const
    //{
    //}

    //inline Matrix3x3SIMD Matrix3x3SIMD::Inverse(float relativeTolerance) const
    //{
    //}


    inline Matrix3x3SIMD Matrix3x3SIMD::Scale(const Maths::Vec3<float>& scale)
    {
        return Matrix3x3SIMD(
            _mm_set_ps(0.0f, 0.0f, 0.0f, scale.x),
            _mm_set_ps(0.0f, 0.0f, scale.y, 0.0f),
            _mm_set_ps(0.0f, scale.z, 0.0f, 0.0f)
        );
    }

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