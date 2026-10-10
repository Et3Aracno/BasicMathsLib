#pragma once
#include "CppUnitTest.h"
#include "MathLibrary/Vec3.h"
#include "MathLibrary/Vec3S.h"
#include "MathLibrary/Vec4.h"
#include "MathLibrary/Vec4S.h"
#include <cmath>
#include <limits>
#include <iterator>
#include <sstream>

namespace TestHelpers
{
    using Microsoft::VisualStudio::CppUnitTestFramework::Assert;

    template <typename T>
    inline void Near(T expected, T actual, const wchar_t* context = L"value")
    {
        // A failed NaN/Inf result must never silently pass a tolerance check.
        const T absoluteTolerance = T{ 64 } * std::numeric_limits<T>::epsilon();
        const T relativeTolerance = T{ 128 } * std::numeric_limits<T>::epsilon();
        const T tolerance = absoluteTolerance + relativeTolerance * std::abs(expected);
        const bool close = std::isfinite(expected) && std::isfinite(actual) &&
            std::abs(expected - actual) <= tolerance;
        std::wostringstream message;
        message << context << L": expected " << expected << L", actual " << actual
            << L", tolerance " << tolerance;
        Assert::IsTrue(close, message.str().c_str());
    }

    template <typename T>
    inline void VectorNear(const Maths::Vec3<T>& expected, const Maths::Vec3<T>& actual)
    {
        Near(expected.x, actual.x, L"x");
        Near(expected.y, actual.y, L"y");
        Near(expected.z, actual.z, L"z");
    }

    template <typename T>
    inline void VectorNear(const Maths::Vec4<T>& expected, const Maths::Vec4<T>& actual)
    {
        Near(expected.x, actual.x, L"x");
        Near(expected.y, actual.y, L"y");
        Near(expected.z, actual.z, L"z");
        Near(expected.w, actual.w, L"w");
    }

    template <typename Matrix>
    inline void MatrixNear(const Matrix& expected, const Matrix& actual)
    {
        const std::size_t count = std::size(expected.values);
        for (std::size_t row = 0; row < count; ++row)
        {
            for (std::size_t column = 0; column < count; ++column)
            {
                std::wostringstream context;
                context << L"matrix[" << row << L"][" << column << L"]";
                Near(expected.values[row][column], actual.values[row][column], context.str().c_str());
            }
        }
    }

    template <typename Matrix>
    inline void MatrixNearSIMD(const Matrix& expected, const Matrix& actual)
    {
        const std::size_t count = std::size(expected.values);

        for (std::size_t row = 0; row < count; ++row)
        {
            for (std::size_t column = 0; column < count; ++column)
            {
                std::wostringstream context;
                context << L"matrix[" << row << L"][" << column << L"]";

                Near(
                    expected(row, column),
                    actual(row, column),
                    context.str().c_str()
                );
            }
        }
    }

    template <typename MatrixType>
    inline void MatrixNearSIMDv4(const MatrixType& expected, const MatrixType& actual)
    {
        for (std::size_t row = 0; row < 4; ++row)
            for (std::size_t column = 0; column < 4; ++column)
            {
                std::wostringstream context;
                context << L"matrix[" << row << L"][" << column << L"]";
                Near<float>(expected(row, column), actual(row, column), context.str().c_str());
            }
    }

    inline void VectorNearSIMDV4(const Maths::Vec4S& expected, const Maths::Vec4S& actual)
    {
        float xE = expected.x;
        float xA = actual.x;
        float yE = expected.y;
        float yA = actual.y;
        float zE = expected.z;
        float zA = actual.z;
        float wE = expected.w;
        float wA = actual.w;

        Near(xE, xA, L"x");
        Near(yE, yA, L"y");
        Near(zE, zA, L"z");
        Near(wE, wA, L"w");
    }

    inline void VectorNearSIMDV3(const Maths::Vec3S& expected, const Maths::Vec3S& actual)
    {
        float xE = expected.x;
        float xA = actual.x;
        float yE = expected.y;
        float yA = actual.y;
        float zE = expected.z;
        float zA = actual.z;

        Near(xE, xA, L"x");
        Near(yE, yA, L"y");
        Near(zE, zA, L"z");
    }
}



