#pragma once
#include "CppUnitTest.h"
#include "MathLibrary/Vec2S.h"
#include "MathLibrary/Vec3S.h"
#include "MathLibrary/Vec4S.h"
#include <cmath>
#include <limits>
#include <iterator>
#include <sstream>

namespace TestHelpersSIMD
{
    using Microsoft::VisualStudio::CppUnitTestFramework::Assert;

    void Near(float expected, float actual, const wchar_t* context = L"value")
    {
        // A failed NaN/Inf result must never silently pass a tolerance check.
        const float absoluteTolerance = 64.f *std::numeric_limits<float>::epsilon();
        const float relativeTolerance = 128.f *std::numeric_limits<float>::epsilon();
        const float tolerance = absoluteTolerance + relativeTolerance * std::abs(expected);
        const bool close = std::isfinite(expected) && std::isfinite(actual) &&
            std::abs(expected - actual) <= tolerance;
        std::wostringstream message;
        message << context << L": expected " << expected << L", actual " << actual
            << L", tolerance " << tolerance;
        Assert::IsTrue(close, message.str().c_str());
    }

    void VectorNear2(const Maths::Vec2S& expected, const Maths::Vec2S& actual)
    {
        Near(expected.x, actual.x, L"x");
        Near(expected.y, actual.y, L"y");
    }

    void VectorNear3(const Maths::Vec3S& expected, const Maths::Vec3S& actual)
    {
        Near(expected.x, actual.x, L"x");
        Near(expected.y, actual.y, L"y");
        Near(expected.z, actual.z, L"z");
    }

    /*template <typename T>
    void VectorNear(const Maths::Vec4S& expected, const Maths::Vec4S& actual)
    {
        Near(expected.x, actual.x, L"x");
        Near(expected.y, actual.y, L"y");
        Near(expected.z, actual.z, L"z");
        Near(expected.w, actual.w, L"w");
    }

    template <typename Matrix>
    void MatrixNear(const Matrix& expected, const Matrix& actual)
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
    }*/
}
