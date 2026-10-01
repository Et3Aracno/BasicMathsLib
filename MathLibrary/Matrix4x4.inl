#pragma once
#include "Matrix4x4.h"




template <std::floating_point T>
Maths::Matrix4x4<T>::Matrix4x4() : values{}
{
    for (std::size_t i = 0; i < 4; ++i)
    {
        values[i][i] = T{ 1 };
    }
}

template <std::floating_point T>
Maths::Matrix4x4<T>::Matrix4x4(const std::array<T, 16>& elements) : values{}
{
    for (std::size_t row = 0; row < 4; ++row)
    {
        for (std::size_t column = 0; column < 4; ++column)
        {
            values[row][column] = elements[row * 4 + column];
        }
    }
}

template <std::floating_point T>
Maths::Matrix4x4<T> Maths::Matrix4x4<T>::Identity()
{
    return Maths::Matrix4x4<T>();
}

template <std::floating_point T>
Maths::Matrix4x4<T> Maths::Matrix4x4<T>::Zero()
{
    return Maths::Matrix4x4<T>(std::array<T, 16>{});
}

template <std::floating_point T>
T& Maths::Matrix4x4<T>::operator()(std::size_t row, std::size_t column)
{
    if (row >= 4 || column >= 4)
    {
        throw std::out_of_range("Matrix index is out of range");
    }
    return values[row][column];
}

template <std::floating_point T>
const T& Maths::Matrix4x4<T>::operator()(std::size_t row, std::size_t column) const
{
    if (row >= 4 || column >= 4)
    {
        throw std::out_of_range("Matrix index is out of range");
    }
    return values[row][column];
}

template <std::floating_point T>
Maths::Matrix4x4<T> Maths::Matrix4x4<T>::operator+(const Matrix4x4& rhs) const
{
    Maths::Matrix4x4 result = Zero();
    for (std::size_t row = 0; row < 4; ++row)
    {
        for (std::size_t column = 0; column < 4; ++column)
        {
            result.values[row][column] = values[row][column] + rhs.values[row][column];
        }
    }
    return result;
}

template <std::floating_point T>
Maths::Matrix4x4<T> Maths::Matrix4x4<T>::operator-(const Matrix4x4& rhs) const
{
    Maths::Matrix4x4<T> result = Zero();
    for (std::size_t row = 0; row < 4; ++row)
    {
        for (std::size_t column = 0; column < 4; ++column)
        {
            result.values[row][column] = values[row][column] - rhs.values[row][column];
        }
    }
    return result;
}

template <std::floating_point T>
Maths::Matrix4x4<T> Maths::Matrix4x4<T>::operator*(const Matrix4x4& rhs) const
{
    Maths::Matrix4x4<T> result = Zero();
    for (std::size_t row = 0; row < 4; ++row)
    {
        for (std::size_t column = 0; column < 4; ++column)
        {
            for (std::size_t k = 0; k < 4; ++k)
            {
                result.values[row][column] += values[row][k] * rhs.values[k][column];
            }
        }
    }
    return result;
}

template <std::floating_point T>
Maths::Vec4<T> Maths::Matrix4x4<T>::operator*(const Vec4<T>& rhs) const
{
    return {
        values[0][0] * rhs.x + values[0][1] * rhs.y + values[0][2] * rhs.z + values[0][3] * rhs.w,
        values[1][0] * rhs.x + values[1][1] * rhs.y + values[1][2] * rhs.z + values[1][3] * rhs.w,
        values[2][0] * rhs.x + values[2][1] * rhs.y + values[2][2] * rhs.z + values[2][3] * rhs.w,
        values[3][0] * rhs.x + values[3][1] * rhs.y + values[3][2] * rhs.z + values[3][3] * rhs.w
    };
}

template <std::floating_point T>
Maths::Matrix4x4<T> Maths::Matrix4x4<T>::operator*(T scalar) const
{
    Maths::Matrix4x4<T> result = Zero();
    for (std::size_t row = 0; row < 4; ++row)
    {
        for (std::size_t column = 0; column < 4; ++column)
        {
            result.values[row][column] = values[row][column] * scalar;
        }
    }
    return result;
}

template <std::floating_point T>
Maths::Matrix4x4<T>& Maths::Matrix4x4<T>::operator*=(const Matrix4x4& rhs)
{
    *this = *this * rhs;
    return *this;
}

template <std::floating_point T>
bool Maths::Matrix4x4<T>::operator==(const Matrix4x4& rhs) const
{
    for (std::size_t row = 0; row < 4; ++row)
    {
        for (std::size_t column = 0; column < 4; ++column)
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
bool Maths::Matrix4x4<T>::operator!=(const Matrix4x4& rhs) const
{
    return !(*this == rhs);
}

template <std::floating_point T>
Maths::Matrix4x4<T> Maths::Matrix4x4<T>::Transpose() const
{
    Maths::Matrix4x4<T> result = Zero();
    for (std::size_t row = 0; row < 4; ++row)
    {
        for (std::size_t column = 0; column < 4; ++column)
        {
            result.values[column][row] = values[row][column];
        }
    }
    return result;
}

template <std::floating_point T>
T Maths::Matrix4x4<T>::Determinant() const
{
    Maths::Matrix4x4<T> working = *this;
    T determinant = T{ 1 };
    for (std::size_t column = 0; column < 4; ++column)
    {
        std::size_t pivot = column;
        for (std::size_t row = column + 1; row < 4; ++row)
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
            for (std::size_t j = 0; j < 4; ++j)
            {
                std::swap(working.values[pivot][j], working.values[column][j]);
            }
            determinant = -determinant;
        }
        const T diagonal = working.values[column][column];
        determinant *= diagonal;
        for (std::size_t row = column + 1; row < 4; ++row)
        {
            const T factor = working.values[row][column] / diagonal;
            for (std::size_t j = column + 1; j < 4; ++j)
            {
                working.values[row][j] -= factor * working.values[column][j];
            }
        }
    }
    return determinant;
}

template <std::floating_point T>
Maths::Matrix4x4<T> Maths::Matrix4x4<T>::Inverse(T relativeTolerance) const
{
    if (!std::isfinite(relativeTolerance) || relativeTolerance < T{ 0 } || relativeTolerance >= T{ 1 })
    {
        throw std::invalid_argument("Inverse tolerance must be finite and in [0, 1)");
    }
    Maths::Matrix4x4<T> left = *this;
    Maths::Matrix4x4<T> right;
    T scales[4]{};
    for (std::size_t row = 0; row < 4; ++row)
    {
        for (std::size_t column = 0; column < 4; ++column)
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
    for (std::size_t column = 0; column < 4; ++column)
    {
        std::size_t pivot = column;
        for (std::size_t row = column + 1; row < 4; ++row)
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
        for (std::size_t j = 0; j < 4; ++j)
        {
            std::swap(left.values[column][j], left.values[pivot][j]);
            std::swap(right.values[column][j], right.values[pivot][j]);
        }
        std::swap(scales[column], scales[pivot]);
        const T diagonal = left.values[column][column];
        for (std::size_t j = 0; j < 4; ++j)
        {
            left.values[column][j] /= diagonal;
            right.values[column][j] /= diagonal;
        }
        for (std::size_t row = 0; row < 4; ++row)
        {
            if (row == column)
            {
                continue;
            }
            const T factor = left.values[row][column];
            for (std::size_t j = 0; j < 4; ++j)
            {
                left.values[row][j] -= factor * left.values[column][j];
                right.values[row][j] -= factor * right.values[column][j];
            }
        }
    }
    for (std::size_t row = 0; row < 4; ++row)
    {
        for (std::size_t column = 0; column < 4; ++column)
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
Maths::Matrix4x4<T> Maths::Matrix4x4<T>::Scale(const Vec3<T>& scale)
{
    Maths::Matrix4x4<T> result;
    result.values[0][0] = scale.x;
    result.values[1][1] = scale.y;
    result.values[2][2] = scale.z;
    return result;
}

template <std::floating_point T>
Maths::Matrix4x4<T> Maths::Matrix4x4<T>::RotationX(T radians)
{
    Maths::Matrix4x4<T> result;
    const T cosine = std::cos(radians);
    const T sine = std::sin(radians);
    result.values[1][1] = cosine;
    result.values[2][2] = cosine;
    result.values[1][2] = -sine;
    result.values[2][1] = sine;
    return result;
}

template <std::floating_point T>
Maths::Matrix4x4<T> Maths::Matrix4x4<T>::RotationY(T radians)
{
    Maths::Matrix4x4<T> result;
    const T cosine = std::cos(radians);
    const T sine = std::sin(radians);
    result.values[2][2] = cosine;
    result.values[0][0] = cosine;
    result.values[2][0] = -sine;
    result.values[0][2] = sine;
    return result;
}

template <std::floating_point T>
Maths::Matrix4x4<T> Maths::Matrix4x4<T>::RotationZ(T radians)
{
    Maths::Matrix4x4<T> result;
    const T cosine = std::cos(radians);
    const T sine = std::sin(radians);
    result.values[0][0] = cosine;
    result.values[1][1] = cosine;
    result.values[0][1] = -sine;
    result.values[1][0] = sine;
    return result;
}

template <std::floating_point T>
Maths::Matrix4x4<T> Maths::Matrix4x4<T>::Translation(const Vec3<T>& offset)
{
    Maths::Matrix4x4<T> result;
    result.values[0][3] = offset.x;
    result.values[1][3] = offset.y;
    result.values[2][3] = offset.z;
    return result;
}

template <std::floating_point T>
Maths::Vec3<T> Maths::Matrix4x4<T>::TransformPoint(const Vec3<T>& point) const
{
    if (values[3][0] != T{ 0 } || values[3][1] != T{ 0 } ||
        values[3][2] != T{ 0 } || values[3][3] != T{ 1 })
    {
        throw std::domain_error("Transform requires an affine matrix");
    }
    const Vec4<T> result = *this * Vec4<T>(point.x, point.y, point.z, T{ 1 });
    return { result.x, result.y, result.z };
}

template <std::floating_point T>
Maths::Vec3<T> Maths::Matrix4x4<T>::TransformDirection(const Vec3<T>& direction) const
{
    if (values[3][0] != T{ 0 } || values[3][1] != T{ 0 } ||
        values[3][2] != T{ 0 } || values[3][3] != T{ 1 })
    {
        throw std::domain_error("Transform requires an affine matrix");
    }
    const Vec4<T> result = *this * Vec4<T>(direction.x, direction.y, direction.z, T{ 0 });
    return { result.x, result.y, result.z };
}
