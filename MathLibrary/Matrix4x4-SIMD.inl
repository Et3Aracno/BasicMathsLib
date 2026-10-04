namespace Maths
{
    inline Matrix4x4SIMD::Matrix4x4SIMD()
    {
                                //w,   z,    y,    x
        values[0] = _mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f);
        values[1] = _mm_set_ps(0.0f, 0.0f, 1.0f, 0.0f);
        values[2] = _mm_set_ps(0.0f, 1.0f, 0.0f, 0.0f);
        values[3] = _mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f);
    }

    inline Matrix4x4SIMD::Matrix4x4SIMD(const std::array<float, 16>& elements)
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
        values[3] = _mm_set_ps
        (
            0.0f,
            elements[11],
            elements[10],
            elements[9]
        );

    }


    inline Matrix4x4SIMD::Matrix4x4SIMD
    (
        __m128 row0,
        __m128 row1,
        __m128 row2,
        __m128 row3
    )
    {
        values[0] = row0;
        values[1] = row1;
        values[2] = row2;
		values[3] = row3;
    }


    inline Maths::Matrix4x4SIMD Maths::Matrix4x4SIMD::Identity()
    {
        return Maths::Matrix4x4SIMD();
    }

    inline Maths::Matrix4x4SIMD Maths::Matrix4x4SIMD::Zero()
    {
        return Maths::Matrix4x4SIMD
        (
            _mm_setzero_ps(),
            _mm_setzero_ps(),
            _mm_setzero_ps(),
            _mm_setzero_ps()
        );

    }

    inline float& Maths::Matrix4x4SIMD::operator()(std::size_t row, std::size_t column)
    {
        if (row >= 4 || column >= 4)
        {
            throw std::out_of_range("Matrix index is out of range");
        }
        return reinterpret_cast<float*>(&values[row])[column]; //permet de convertir notre __128 en "tableau" de type float pour pouvoir accéder à l'élément souhaité , 
        //donc on fait un reinterpret_cast pour convertir le type de données de __m128 en float* et ensuite on accède à l'élément souhaité en utilisant l'opérateur [] sur le pointeur.
        //besoin de test performance pour voir si il y a une différence entre cette méthode et l'utilisation de _mm_store_ps pour stocker les valeurs dans un tableau temporaire et ensuite accéder à l'élément souhaité.

    }

    inline const float& Maths::Matrix4x4SIMD::operator()(std::size_t row, std::size_t column) const
    {
        if (row >= 4 || column >= 4)
        {
            throw std::out_of_range("Matrix index is out of range");
        }

        return reinterpret_cast<const float*>(&values[row])[column];

    }

    inline Maths::Matrix4x4SIMD Maths::Matrix4x4SIMD::operator+(const Maths::Matrix4x4SIMD& rhs) const
    {
        Maths::Matrix4x4SIMD result = Zero();

        result.values[0] = _mm_add_ps(values[0], rhs.values[0]);
        result.values[1] = _mm_add_ps(values[1], rhs.values[1]);
        result.values[2] = _mm_add_ps(values[2], rhs.values[2]);
        result.values[3] = _mm_add_ps(values[3], rhs.values[3]);

        return result;
    }

    inline Maths::Matrix4x4SIMD Maths::Matrix4x4SIMD::operator-(const Maths::Matrix4x4SIMD& rhs) const
    {
        Maths::Matrix4x4SIMD result = Zero();

        result.values[0] = _mm_sub_ps(values[0], rhs.values[0]);
        result.values[1] = _mm_sub_ps(values[1], rhs.values[1]);
        result.values[2] = _mm_sub_ps(values[2], rhs.values[2]);
        result.values[3] = _mm_sub_ps(values[3], rhs.values[3]);

        return result;
    }

    inline Maths::Matrix4x4SIMD Maths::Matrix4x4SIMD::operator*(const Maths::Matrix4x4SIMD& rhs) const
    {

        Maths::Matrix4x4SIMD result = Zero();


        __m128 row0_0 = _mm_shuffle_ps(values[0], values[0], _MM_SHUFFLE(0, 0, 0, 0));          //ça demandera de faire un test de performance pour voir si il y a une différence
        __m128 row0_1 = _mm_shuffle_ps(values[0], values[0], _MM_SHUFFLE(1, 1, 1, 1));            //_MM_SHUFFLE ça permet  de ne pas écrire en binaire c'est un masque qui facilite la lecture du code après ça risque de prendre des performances , il faut tester 
        __m128 row0_2 = _mm_shuffle_ps(values[0], values[0], _MM_SHUFFLE(2, 2, 2, 2));
        __m128 row0_3 = _mm_shuffle_ps(values[0], values[0], _MM_SHUFFLE(3, 3, 3, 3));

        result.values[0] = _mm_add_ps(_mm_mul_ps(row0_0, rhs.values[0]), _mm_add_ps(_mm_mul_ps(row0_1, rhs.values[1]), _mm_add_ps(_mm_mul_ps(row0_2, rhs.values[2]), _mm_mul_ps(row0_3, rhs.values[3]))));


        __m128 row1_0 = _mm_shuffle_ps(values[1], values[1], _MM_SHUFFLE(0, 0, 0, 0));
        __m128 row1_1 = _mm_shuffle_ps(values[1], values[1], _MM_SHUFFLE(1, 1, 1, 1));
        __m128 row1_2 = _mm_shuffle_ps(values[1], values[1], _MM_SHUFFLE(2, 2, 2, 2));
        __m128 row1_3 = _mm_shuffle_ps(values[1], values[1], _MM_SHUFFLE(3, 3, 3, 3));

        result.values[1] = _mm_add_ps(_mm_mul_ps(row1_0, rhs.values[0]), _mm_add_ps(_mm_mul_ps(row1_1, rhs.values[1]), _mm_add_ps(_mm_mul_ps(row1_2, rhs.values[2]), _mm_mul_ps(row1_3, rhs.values[3]))));



        __m128 row2_0 = _mm_shuffle_ps(values[2], values[2], _MM_SHUFFLE(0, 0, 0, 0));
        __m128 row2_1 = _mm_shuffle_ps(values[2], values[2], _MM_SHUFFLE(1, 1, 1, 1));
        __m128 row2_2 = _mm_shuffle_ps(values[2], values[2], _MM_SHUFFLE(2, 2, 2, 2));
        __m128 row2_3 = _mm_shuffle_ps(values[2], values[2], _MM_SHUFFLE(3, 3, 3, 3));

        result.values[2] = _mm_add_ps(_mm_mul_ps(row2_0, rhs.values[0]), _mm_add_ps(_mm_mul_ps(row2_1, rhs.values[1]), _mm_add_ps(_mm_mul_ps(row2_2, rhs.values[2]), _mm_mul_ps(row2_3, rhs.values[3]))));



        __m128 row3_0 = _mm_shuffle_ps(values[3], values[3], _MM_SHUFFLE(0, 0, 0, 0));
        __m128 row3_1 = _mm_shuffle_ps(values[3], values[3], _MM_SHUFFLE(1, 1, 1, 1));
        __m128 row3_2 = _mm_shuffle_ps(values[3], values[3], _MM_SHUFFLE(2, 2, 2, 2));
		__m128 row3_3 = _mm_shuffle_ps(values[3], values[3], _MM_SHUFFLE(3, 3, 3, 3));      //

        result.values[3] = _mm_add_ps(_mm_mul_ps(row3_0, rhs.values[0]), _mm_add_ps(_mm_mul_ps(row3_1, rhs.values[1]), _mm_add_ps(_mm_mul_ps(row3_2, rhs.values[2]), _mm_mul_ps(row3_3, rhs.values[3]))));
        



        return result;
    }

    inline Maths::Vec4<float> Maths::Matrix4x4SIMD::operator*(const Maths::Vec4<float>& rhs) const
    {
        const __m128 vector = _mm_set_ps(
            rhs.w,
            rhs.z,
            rhs.y,
            rhs.x
        );

        const __m128 row0 = _mm_mul_ps(values[0], vector);

        const __m128 row1 = _mm_mul_ps(values[1], vector);

        const __m128 row2 = _mm_mul_ps(values[2], vector);

		const __m128 row3 = _mm_mul_ps(values[3], vector);

        alignas(16) float temp0[4];
        alignas(16) float temp1[4];
        alignas(16) float temp2[4];     // Alignas permet de convertir les float en tableau de float pour pouvoir les additionner ensuite
        alignas(16) float temp3[4];

        _mm_store_ps(temp0, row0);
        _mm_store_ps(temp1, row1);
        _mm_store_ps(temp2, row2);
        _mm_store_ps(temp3, row3);

        return Maths::Vec4<float>(
            temp0[0] + temp0[1] + temp0[2] + temp0[3],
            temp1[0] + temp1[1] + temp1[2] + temp1[3],
            temp2[0] + temp2[1] + temp2[2] + temp2[3],
			temp3[0] + temp3[1] + temp3[2] + temp3[3]
        );
    }

    inline Maths::Matrix4x4SIMD Maths::Matrix4x4SIMD::operator*(float scalar) const
    {
        __m128 Scalar = _mm_set_ps(0.0f, scalar, scalar, scalar);
        __m128 ScalarRow0 = _mm_mul_ps(values[0], Scalar);
        __m128 ScalarRow1 = _mm_mul_ps(values[1], Scalar);
        __m128 ScalarRow2 = _mm_mul_ps(values[2], Scalar);
        __m128 ScalarRow3 = _mm_mul_ps(values[3], Scalar);
        return Maths::Matrix4x4SIMD(ScalarRow0, ScalarRow1, ScalarRow2, ScalarRow3);
    }

    inline Maths::Matrix4x4SIMD& Maths::Matrix4x4SIMD::operator*=(const Maths::Matrix4x4SIMD& rhs)
    {
        *this = *this * rhs;
        return *this;
    }

    inline bool Maths::Matrix4x4SIMD::operator==(const Maths::Matrix4x4SIMD& rhs) const
    {
        return _mm_movemask_ps(_mm_cmpeq_ps(values[0], rhs.values[0])) == 0xF &&
            _mm_movemask_ps(_mm_cmpeq_ps(values[1], rhs.values[1])) == 0xF &&
            _mm_movemask_ps(_mm_cmpeq_ps(values[2], rhs.values[2])) == 0xF &&
            _mm_movemask_ps(_mm_cmpeq_ps(values[3], rhs.values[3])) == 0xF;
    }

    inline bool Maths::Matrix4x4SIMD::operator!=(const Maths::Matrix4x4SIMD& rhs) const
    {

        return _mm_movemask_ps(_mm_cmpeq_ps(values[0], rhs.values[0])) != 0xF &&
            _mm_movemask_ps(_mm_cmpeq_ps(values[1], rhs.values[1])) != 0xF &&
            _mm_movemask_ps(_mm_cmpeq_ps(values[2], rhs.values[2])) != 0xF &&
            _mm_movemask_ps(_mm_cmpeq_ps(values[3], rhs.values[3])) != 0xF;

    }

    inline Maths::Matrix4x4SIMD Maths::Matrix4x4SIMD::Transpose() const
    {

        Maths::Matrix4x4SIMD result = Zero();

        __m128 l0 = _mm_shuffle_ps(values[0], values[1], _MM_SHUFFLE(0, 3, 0, 3));
        __m128 resultL0 = _mm_shuffle_ps(l0, values[2], _MM_SHUFFLE(3, 0, 2, 0));

        __m128 l1 = _mm_shuffle_ps(values[0], values[1], _MM_SHUFFLE(0, 1, 0, 1));
        __m128 resultL1 = _mm_shuffle_ps(l1, values[2], _MM_SHUFFLE(3, 1, 0, 2));

        __m128 l2 = _mm_shuffle_ps(values[0], values[1], _MM_SHUFFLE(0, 2, 0, 2));
        __m128 resultL2 = _mm_shuffle_ps(l2, values[2], _MM_SHUFFLE(3, 2, 0, 2));


        return Maths::Matrix4x4SIMD(resultL0, resultL1, resultL2, values[3]);

    }

    //inline float Matrix4x4SIMD::Determinant() const
    //{

    //}

    //inline Matrix3x3SIMD Matrix3x3SIMD::Inverse(float relativeTolerance) const
    //{
    //}


    inline Maths::Matrix4x4SIMD Maths::Matrix4x4SIMD::Scale(const Maths::Vec4<float>& scale)
    {
        return Matrix4x4SIMD(
            _mm_set_ps(0.0f, 0.0f, 0.0f, scale.x),
            _mm_set_ps(0.0f, 0.0f, scale.y, 0.0f),
            _mm_set_ps(0.0f, scale.z, 0.0f, 0.0f),
            _mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f)
        );
    }

    inline Maths::Matrix4x4SIMD Maths::Matrix4x4SIMD::RotationX(float radians)
    {
        const float cosine = std::cos(radians);
        const float sine = std::sin(radians);

        return Maths::Matrix4x4SIMD(
            _mm_set_ps(0.0f, 1.0f, 0.0f, 0.0f),
            _mm_set_ps(0.0f, 0.0f, -sine, cosine),
            _mm_set_ps(0.0f, 0.0f, cosine, sine),
            _mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f)
        );
    }

    inline Maths::Matrix4x4SIMD Maths::Matrix4x4SIMD::RotationY(float radians)
    {
        const float cosine = std::cos(radians);
        const float sine = std::sin(radians);

        return Maths::Matrix4x4SIMD(
            _mm_set_ps(0.0f, sine, 0.0f, cosine),
            _mm_set_ps(0.0f, 0.0f, 1.0f, 0.0f),
            _mm_set_ps(0.0f, cosine, 0.0f, -sine),
            _mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f)
        );
    }

    inline Maths::Matrix4x4SIMD Maths::Matrix4x4SIMD::RotationZ(float radians)
    {
        const float cosine = std::cos(radians);
        const float sine = std::sin(radians);

        return Maths::Matrix4x4SIMD(
            _mm_set_ps(0.0f, 0.0f, -sine, cosine),
            _mm_set_ps(0.0f, 0.0f, cosine, sine),
            _mm_set_ps(0.0f, 1.0f, 0.0f, 0.0f),
            _mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f)
        );
    }
}