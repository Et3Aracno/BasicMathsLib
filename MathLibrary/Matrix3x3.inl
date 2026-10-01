#pragma once 
#include "Matrix3x3.h"

template <std::floating_point T>
Maths::Matrix3x3<T>::Matrix3x3() : values{}
{
    for (std::size_t i = 0; i < 3; ++i)
    {
        values[i][i] = T{ 1 };
    }
}


template <std::floating_point T>
Maths::Matrix3x3<T>::Matrix3x3(const std::array<T, 9>& elements) : values{}
{
    for (std::size_t row = 0; row < 3; ++row)
    {
        for (std::size_t column = 0; column < 3; ++column)
        {
            values[row][column] = elements[row * 3 + column];
        }
    }
}

template <std::floating_point T>
Maths::Matrix3x3<T> Maths::Matrix3x3<T>::Identity()
{
    return Maths::Matrix3x3<T>();
}



template <std::floating_point T>
Maths::Matrix3x3<T> Maths::Matrix3x3<T>::Zero()
{
    return Maths::Matrix3x3(std::array<T, 9>{});
}




template <std::floating_point T>
T& Maths::Matrix3x3<T>::operator()(std::size_t row, std::size_t column)
{
    if (row >= 3 || column >= 3)
    {
        throw std::out_of_range("Matrix index is out of range");
    }
    return values[row][column];
}


template <std::floating_point T>
const T& Maths::Matrix3x3<T>::operator()(std::size_t row, std::size_t column) const
{
    if (row >= 3 || column >= 3)
    {
        throw std::out_of_range("Matrix index is out of range");
    }
    return values[row][column];
}





template <std::floating_point T>
Maths::Matrix3x3<T> Maths::Matrix3x3<T>::operator+(const Matrix3x3& rhs) const
{
    Maths::Matrix3x3 result = Zero();
    for (std::size_t row = 0; row < 3; ++row)
    {
        for (std::size_t column = 0; column < 3; ++column)
        {
            result.values[row][column] = values[row][column] + rhs.values[row][column];
        }
    }
    return result;
}





template <std::floating_point T>
Maths::Matrix3x3<T> Maths::Matrix3x3<T>::operator-(const Matrix3x3& rhs) const
{
    Maths::Matrix3x3 result = Zero();
    for (std::size_t row = 0; row < 3; ++row)
    {
        for (std::size_t column = 0; column < 3; ++column)
        {
            result.values[row][column] = values[row][column] - rhs.values[row][column];
        }
    }
    return result;
}




template <std::floating_point T>
Maths::Matrix3x3<T> Maths::Matrix3x3<T>::operator*(const Matrix3x3& rhs) const
{
    Maths::Matrix3x3 result = Zero();
    for (std::size_t row = 0; row < 3; ++row)
    {
        for (std::size_t column = 0; column < 3; ++column)
        {
            for (std::size_t k = 0; k < 3; ++k)
            {
                result.values[row][column] += values[row][k] * rhs.values[k][column];
            }
        }
    }
    return result;
}

template <std::floating_point T>
Maths::Vec3<T> Maths::Matrix3x3<T>::operator*(const Vec3<T>& rhs) const
{
    return {
        values[0][0] * rhs.x + values[0][1] * rhs.y + values[0][2] * rhs.z,
        values[1][0] * rhs.x + values[1][1] * rhs.y + values[1][2] * rhs.z,
        values[2][0] * rhs.x + values[2][1] * rhs.y + values[2][2] * rhs.z
    };
}

template <std::floating_point T>
Maths::Matrix3x3<T> Maths::Matrix3x3<T>::operator*(T scalar) const
{
    Maths::Matrix3x3 result = Zero();
    for (std::size_t row = 0; row < 3; ++row)
    {
        for (std::size_t column = 0; column < 3; ++column)
        {
            result.values[row][column] = values[row][column] * scalar;
        }
    }
    return result;
}

template <std::floating_point T>
Maths::Matrix3x3<T>& Maths::Matrix3x3<T>::operator*=(const Matrix3x3& rhs)
{
    *this = *this * rhs;
    return *this;
}

template <std::floating_point T>
bool Maths::Matrix3x3<T>::operator==(const Matrix3x3& rhs) const
{
    for (std::size_t row = 0; row < 3; ++row)
    {
        for (std::size_t column = 0; column < 3; ++column)
        {
            if (values[row][column] != rhs.values[row][column])
            {
                return false;
            }
        }
    }
    return true;
}

template <std::floating_point T>
bool Maths::Matrix3x3<T>::operator!=(const Matrix3x3& rhs) const
{
    return !(*this == rhs);
}

template <std::floating_point T>
Maths::Matrix3x3<T> Maths::Matrix3x3<T>::Transpose() const
{
    Maths::Matrix3x3 result = Zero();
    for (std::size_t row = 0; row < 3; ++row)
    {
        for (std::size_t column = 0; column < 3; ++column)
        {
            result.values[column][row] = values[row][column];
        }
    }
    return result;
}

template <std::floating_point T>
T Maths::Matrix3x3<T>::Determinant() const
{
    Maths::Matrix3x3 working = *this;
    T determinant = T{ 1 };
    for (std::size_t column = 0; column < 3; ++column)
    {
        std::size_t pivot = column;
        for (std::size_t row = column + 1; row < 3; ++row)
        {
            if (std::abs(working.values[row][column]) > std::abs(working.values[pivot][column]))
            {
                pivot = row;
            }
        }
        if (working.values[pivot][column] == T{ 0 })
        {
            return T{ 0 };
        }
        if (pivot != column)
        {
            for (std::size_t j = 0; j < 3; ++j)
            {
                std::swap(working.values[pivot][j], working.values[column][j]);
            }
            determinant = -determinant;
        }
        const T diagonal = working.values[column][column];
        determinant *= diagonal;
        for (std::size_t row = column + 1; row < 3; ++row)
        {
            const T factor = working.values[row][column] / diagonal;
            for (std::size_t j = column + 1; j < 3; ++j)
            {
                working.values[row][j] -= factor * working.values[column][j];
            }
        }
    }
    return determinant;
}

template <std::floating_point T>
Maths::Matrix3x3<T> Maths::Matrix3x3<T>::Inverse(T relativeTolerance) const
{
    if (!std::isfinite(relativeTolerance) || relativeTolerance < T{ 0 } || relativeTolerance >= T{ 1 })
    {
        throw std::invalid_argument("Inverse tolerance must be finite and in [0, 1)");
    }
    Maths::Matrix3x3<T> left = *this;
    Maths::Matrix3x3<T> right;
    T scales[3]{};
    for (std::size_t row = 0; row < 3; ++row)
    {
        for (std::size_t column = 0; column < 3; ++column)
        {
            if (!std::isfinite(left.values[row][column]))
            {
                throw std::domain_error("Cannot invert a non-finite matrix");
            }
            scales[row] = std::max(scales[row], std::abs(left.values[row][column]));
        }
        if (scales[row] == T{ 0 })
        {
            throw std::domain_error("Cannot invert a singular matrix");
        }
    }
    for (std::size_t column = 0; column < 3; ++column)
    {
        std::size_t pivot = column;
        for (std::size_t row = column + 1; row < 3; ++row)
        {
            if (std::abs(left.values[row][column]) / scales[row] >
                std::abs(left.values[pivot][column]) / scales[pivot])
            {
                pivot = row;
            }
        }
        if (std::abs(left.values[pivot][column]) / scales[pivot] <= relativeTolerance)
        {
            throw std::domain_error("Matrix is singular or too ill-conditioned");
        }
        for (std::size_t j = 0; j < 3; ++j)
        {
            std::swap(left.values[column][j], left.values[pivot][j]);
            std::swap(right.values[column][j], right.values[pivot][j]);
        }
        std::swap(scales[column], scales[pivot]);
        const T diagonal = left.values[column][column];
        for (std::size_t j = 0; j < 3; ++j)
        {
            left.values[column][j] /= diagonal;
            right.values[column][j] /= diagonal;
        }
        for (std::size_t row = 0; row < 3; ++row)
        {
            if (row == column)
            {
                continue;
            }
            const T factor = left.values[row][column];
            for (std::size_t j = 0; j < 3; ++j)
            {
                left.values[row][j] -= factor * left.values[column][j];
                right.values[row][j] -= factor * right.values[column][j];
            }
        }
    }
    for (std::size_t row = 0; row < 3; ++row)
    {
        for (std::size_t column = 0; column < 3; ++column)
        {
            if (!std::isfinite(right.values[row][column]))
            {
                throw std::domain_error("Inverse is not representable");
            }
        }
    }
    return right;
}

template <std::floating_point T>
Maths::Matrix3x3<T> Maths::Matrix3x3<T>::Scale(const Vec3<T>& scale)
{
    Maths::Matrix3x3<T> result;
    result.values[0][0] = scale.x;
    result.values[1][1] = scale.y;
    result.values[2][2] = scale.z;
    return result;
}

template <std::floating_point T>
Maths::Matrix3x3<T> Maths::Matrix3x3<T>::RotationX(T radians)
{
    Maths::Matrix3x3<T> result;
    const T cosine = std::cos(radians);
    const T sine = std::sin(radians);
    result.values[1][1] = cosine;
    result.values[2][2] = cosine;
    result.values[1][2] = -sine;
    result.values[2][1] = sine;
    return result;
}

template <std::floating_point T>
Maths::Matrix3x3<T> Maths::Matrix3x3<T>::RotationY(T radians)
{
    Maths::Matrix3x3<T> result;
    const T cosine = std::cos(radians);
    const T sine = std::sin(radians);
    result.values[2][2] = cosine;
    result.values[0][0] = cosine;
    result.values[2][0] = -sine;
    result.values[0][2] = sine;
    return result;
}

template <std::floating_point T>
Maths::Matrix3x3<T> Maths::Matrix3x3<T>::RotationZ(T radians)
{
    Maths::Matrix3x3<T> result;
    const T cosine = std::cos(radians);
    const T sine = std::sin(radians);
    result.values[0][0] = cosine;
    result.values[1][1] = cosine;
    result.values[0][1] = -sine;
    result.values[1][0] = sine;
    return result;
}