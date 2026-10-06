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

    inline float& Matrix3x3SIMD::operator()(std::size_t row, std::size_t column)
    {
        if (row >= 3 || column >= 3)
        {
            throw std::out_of_range("Matrix index is out of range");
        }
		return reinterpret_cast<float*>(&values[row])[column]; //permet de convertir notre __128 en "tableau" de type float pour pouvoir accéder à l'élément souhaité , 
        //donc on fait un reinterpret_cast pour convertir le type de données de __m128 en float* et ensuite on accède à l'élément souhaité en utilisant l'opérateur [] sur le pointeur.
		//besoin de test performance pour voir si il y a une différence entre cette méthode et l'utilisation de _mm_store_ps pour stocker les valeurs dans un tableau temporaire et ensuite accéder à l'élément souhaité.

    }

    inline const float& Matrix3x3SIMD::operator()(std::size_t row, std::size_t column) const
    {
        if (row >= 3 || column >= 3)
        {
            throw std::out_of_range("Matrix index is out of range");
        }

        return reinterpret_cast<const float*>(&values[row])[column];

    }

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

    inline Matrix3x3SIMD Matrix3x3SIMD::operator*(float scalar) const
    {
		__m128 Scalar = _mm_set_ps(0.0f, scalar, scalar, scalar);
		__m128 ScalarRow0 = _mm_mul_ps(values[0], Scalar);
		__m128 ScalarRow1 = _mm_mul_ps(values[1], Scalar);
		__m128 ScalarRow2 = _mm_mul_ps(values[2], Scalar);
		return Matrix3x3SIMD(ScalarRow0, ScalarRow1, ScalarRow2);
    }

    inline Matrix3x3SIMD& Matrix3x3SIMD::operator*=(const Matrix3x3SIMD& rhs)
    {
        *this = *this * rhs;
        return *this;
    }

    inline bool Matrix3x3SIMD::operator==(const Matrix3x3SIMD& rhs) const
    {
        return _mm_movemask_ps(_mm_cmpeq_ps(values[0], rhs.values[0])) == 0xF &&
            _mm_movemask_ps(_mm_cmpeq_ps(values[1], rhs.values[1])) == 0xF &&
            _mm_movemask_ps(_mm_cmpeq_ps(values[2], rhs.values[2])) == 0xF;
    }

    inline bool Matrix3x3SIMD::operator!=(const Matrix3x3SIMD& rhs) const
    {

        return _mm_movemask_ps(_mm_cmpeq_ps(values[0], rhs.values[0])) != 0xF ||
            _mm_movemask_ps(_mm_cmpeq_ps(values[1], rhs.values[1])) != 0xF ||
            _mm_movemask_ps(_mm_cmpeq_ps(values[2], rhs.values[2])) != 0xF;

    }

    inline Matrix3x3SIMD Matrix3x3SIMD::Transpose() const
    {

        __m128 l0 = _mm_shuffle_ps(values[0], values[1], _MM_SHUFFLE(0, 0, 0, 0));
        __m128 resultL0 = _mm_shuffle_ps(l0 , values[2], _MM_SHUFFLE(3, 0, 2, 0));

        __m128 l1 = _mm_shuffle_ps(values[0], values[1], _MM_SHUFFLE(1, 1, 1, 1));
        __m128 resultL1 = _mm_shuffle_ps(l1, values[2],_MM_SHUFFLE(3, 1, 2, 0));

        __m128 l2 = _mm_shuffle_ps(values[0], values[1], _MM_SHUFFLE(2, 2, 2, 2));
        __m128 resultL2 = _mm_shuffle_ps(l2, values[2], _MM_SHUFFLE(3, 2, 2, 0));


		return Matrix3x3SIMD(resultL0, resultL1, resultL2);

    }

    inline float Matrix3x3SIMD::Determinant() const
    {
        __m128 c1_0 = _mm_shuffle_ps(values[1], values[1], _MM_SHUFFLE(1,1,1,1));
		__m128 c2_0 = _mm_shuffle_ps(values[2], values[2], _MM_SHUFFLE(2, 2, 2, 2));
		__m128 c3_0 = _mm_shuffle_ps(values[0], values[0], _MM_SHUFFLE(0, 0, 0, 0));
        __m128 c4_0 = _mm_shuffle_ps(values[2], values[2], _MM_SHUFFLE(1, 1, 1, 1));
        __m128 c5_0 = _mm_shuffle_ps(values[1], values[1], _MM_SHUFFLE(2, 2, 2, 2));

        __m128 c1_1 = _mm_shuffle_ps(values[1], values[1], _MM_SHUFFLE(0, 0, 0, 0));
        __m128 c2_1 = _mm_shuffle_ps(values[2], values[2], _MM_SHUFFLE(2, 2, 2, 2));
        __m128 c3_1 = _mm_shuffle_ps(values[0], values[0], _MM_SHUFFLE(1, 1, 1, 1));
        __m128 c4_1 = _mm_shuffle_ps(values[2], values[2], _MM_SHUFFLE(0, 0, 0, 0));
        __m128 c5_1 = _mm_shuffle_ps(values[1], values[1], _MM_SHUFFLE(2, 2, 2, 2));


        __m128 c1_2 = _mm_shuffle_ps(values[1], values[1], _MM_SHUFFLE(0, 0, 0, 0));
        __m128 c2_2 = _mm_shuffle_ps(values[2], values[2], _MM_SHUFFLE(1, 1, 1, 1));
        __m128 c3_2 = _mm_shuffle_ps(values[0], values[0], _MM_SHUFFLE(2, 2, 2, 2));
        __m128 c4_2 = _mm_shuffle_ps(values[2], values[2], _MM_SHUFFLE(0, 0, 0, 0));
        __m128 c5_2 = _mm_shuffle_ps(values[1], values[1], _MM_SHUFFLE(1, 1, 1, 1));



        return _mm_cvtss_f32(_mm_add_ps(_mm_sub_ps(_mm_mul_ps(c3_0, _mm_sub_ps(_mm_mul_ps(c1_0, c2_0), _mm_mul_ps(c4_0, c5_0))),
                                                    _mm_mul_ps(c3_1, _mm_sub_ps(_mm_mul_ps(c1_1, c2_1), _mm_mul_ps(c4_1, c5_1)))),
                                                      _mm_mul_ps(c3_2, _mm_sub_ps(_mm_mul_ps(c1_2, c2_2), _mm_mul_ps(c4_2, c5_2)))));
    }

    inline Matrix3x3SIMD Matrix3x3SIMD::Inverse(float relativeTolerance) const
    {

        if (!std::isfinite(relativeTolerance) || relativeTolerance < float{ 0 } || relativeTolerance >= float{ 1 })
        {
            throw std::invalid_argument("Inverse tolerance must be finite and in [0, 1)");
        }


        float det = this->Determinant();
        if (std::abs(det) <= relativeTolerance) {
            throw std::out_of_range("Det is 0 or lesser , Matrix is impossible to invert");
        };


        // 0 c b a
        // 0 f e d
        // 0 i h g

        __m128 a = _mm_shuffle_ps(values[0], values[0], _MM_SHUFFLE(0, 0, 0, 0));
        __m128 b = _mm_shuffle_ps(values[0], values[0], _MM_SHUFFLE(1, 1, 1, 1));
        __m128 c = _mm_shuffle_ps(values[0], values[0], _MM_SHUFFLE(2, 2, 2, 2));
        __m128 d = _mm_shuffle_ps(values[1], values[1], _MM_SHUFFLE(0, 0, 0, 0));
        __m128 e = _mm_shuffle_ps(values[1], values[1], _MM_SHUFFLE(1, 1, 1, 1));
        __m128 f = _mm_shuffle_ps(values[1], values[1], _MM_SHUFFLE(2, 2, 2, 2));
        __m128 g = _mm_shuffle_ps(values[2], values[2], _MM_SHUFFLE(0, 0, 0, 0));
        __m128 h = _mm_shuffle_ps(values[2], values[2], _MM_SHUFFLE(1, 1, 1, 1));
        __m128 i = _mm_shuffle_ps(values[2], values[2], _MM_SHUFFLE(2, 2, 2, 2));

        Matrix3x3SIMD result;
        result.values[0] = _mm_set_ps(0.f, _mm_cvtss_f32(_mm_sub_ps(_mm_mul_ps(b, f), _mm_mul_ps(c, e))) / det , _mm_cvtss_f32(_mm_sub_ps(_mm_mul_ps(c, h), _mm_mul_ps(b, i))) / det , _mm_cvtss_f32(_mm_sub_ps(_mm_mul_ps(e, i), _mm_mul_ps(f, h))) / det);
        result.values[1] = _mm_set_ps(0.f, _mm_cvtss_f32(_mm_sub_ps(_mm_mul_ps(c, d), _mm_mul_ps(a, f))) / det, _mm_cvtss_f32(_mm_sub_ps(_mm_mul_ps(a, i), _mm_mul_ps(c, g))) / det , _mm_cvtss_f32(_mm_sub_ps(_mm_mul_ps(f, g), _mm_mul_ps(d, i))) / det);
        result.values[2] = _mm_set_ps(0.f, _mm_cvtss_f32(_mm_sub_ps(_mm_mul_ps(a, e), _mm_mul_ps(b, d))) / det, _mm_cvtss_f32(_mm_sub_ps(_mm_mul_ps(b, g), _mm_mul_ps(a, h))) / det, _mm_cvtss_f32(_mm_sub_ps(_mm_mul_ps(d, h), _mm_mul_ps(e, g))) / det);
            
        return result;

    }


    inline Matrix3x3SIMD Matrix3x3SIMD::Scale(const Maths::Vec3<float>& scale)
    {
        return Matrix3x3SIMD(
            _mm_set_ps(0.0f, 0.0f, 0.0f, scale.x),
            _mm_set_ps(0.0f, 0.0f, scale.y, 0.0f),
            _mm_set_ps(0.0f, scale.z, 0.0f, 0.0f)
        );
    }

    inline Matrix3x3SIMD Matrix3x3SIMD::RotationX(float radians)
    {
        const float cosine = std::cos(radians);
        const float sine = std::sin(radians);
        
        return Matrix3x3SIMD(
            _mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f),
            _mm_set_ps(0.0f, -sine, cosine, 0.0f),
			_mm_set_ps(0.0f, cosine, sine, 0.0f));
    }

    inline Matrix3x3SIMD Matrix3x3SIMD::RotationY(float radians)
    {
        const float cosine = std::cos(radians);
        const float sine = std::sin(radians);

        return Matrix3x3SIMD(
            _mm_set_ps(0.0f, sine, 0.0f, cosine),
            _mm_set_ps(0.0f, 0.0f, 1.0f, 0.0f),
            _mm_set_ps(0.0f, cosine, 0.0f, -sine));
    }

    inline Matrix3x3SIMD Matrix3x3SIMD::RotationZ(float radians)
    {
        const float cosine = std::cos(radians);
        const float sine = std::sin(radians);

        return Matrix3x3SIMD(
            _mm_set_ps(0.0f, 0.0f, -sine, cosine),
            _mm_set_ps(0.0f, 0.0f, cosine, sine),
            _mm_set_ps(0.0f, 1.0f, 0.0f, 0.0f));
    }
}