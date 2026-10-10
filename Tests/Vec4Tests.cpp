#include "TestHelpers.h"
#include "MathLibrary/Vec4.h"
#include <numbers>
#include <type_traits>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace TestHelpers;

namespace
{
    template <typename T>
    void DefaultConstructorIsZero()
    {
        using V = Maths::Vec4<T>;
        const V actual;
        VectorNear(V{0, 0, 0, 0}, actual);
    }

    template <typename T>
    void ComponentsAndCopyAreIndependent()
    {
        using V = Maths::Vec4<T>;
        const V original{1, 2, 3, 4};
        V copy = original;
        copy.x = T{99};
        VectorNear(V{1, 2, 3, 4}, original);
        Assert::IsTrue(copy.x == T{99});
    }

    template <typename T>
    void ExplicitConversionPreservesValues()
    {
        using V = Maths::Vec4<T>;
        const Maths::Vec4<double> source{1.5, 2.5, 3.5, 4.5};
        const V actual(source);
        VectorNear(V{T{1.5}, T{2.5}, T{3.5}, T{4.5}}, actual);
    }

    template <typename T>
    void AdditionHasKnownResult()
    {
        using V = Maths::Vec4<T>;
        const V a = V{1, 2, 3, 4};
        const V b = V{2, 3, 4, 5};
        const V actual = a + b;
        VectorNear(V{3, 5, 7, 9}, actual);
    }

    template <typename T>
    void SubtractionHasKnownResult()
    {
        using V = Maths::Vec4<T>;
        const V a = V{1, 2, 3, 4};
        const V b = V{2, 3, 4, 5};
        const V actual = a - b;
        VectorNear(V{-1, -1, -1, -1}, actual);
    }

    template <typename T>
    void ComponentProductHasKnownResult()
    {
        using V = Maths::Vec4<T>;
        const V a = V{1, 2, 3, 4};
        const V b = V{2, 3, 4, 5};
        const V actual = a * b;
        VectorNear(V{2, 6, 12, 20}, actual);
    }

    template <typename T>
    void ComponentDivisionHasKnownResult()
    {
        using V = Maths::Vec4<T>;
        const V a = V{2, 6, 12, 20};
        const V b = V{2, 3, 4, 5};
        const V actual = a / b;
        VectorNear(V{1, 2, 3, 4}, actual);
    }

    template <typename T>
    void ScalarOperationsAndNegation()
    {
        using V = Maths::Vec4<T>;
        const V a = V{1, 2, 3, 4};
        VectorNear(V{-1, -2, -3, -4}, -a);
        VectorNear(V{2, 4, 6, 8}, a * T{2});
        VectorNear(V{2, 4, 6, 8}, T{2} * a);
        VectorNear(a, (a * T{2}) / T{2});
    }

    template <typename T>
    void CompoundOperatorsReturnSelfAndSupportAliasing()
    {
        using V = Maths::Vec4<T>;
        V a = V{1, 2, 3, 4};
        Assert::IsTrue(&(a += a) == &a);
        VectorNear(V{2, 4, 6, 8}, a);
        a -= V{1, 2, 3, 4};
        a *= a;
        VectorNear(V{1, 4, 9, 16}, a);
        a /= V{1, 2, 3, 4};
        a *= T{2};
        a /= T{2};
        VectorNear(V{1, 2, 3, 4}, a);
    }

    template <typename T>
    void DivisionByZeroThrowsWithoutPartialMutation()
    {
        using V = Maths::Vec4<T>;
        const V original = V{1, 2, 3, 4};
        V actual = original;
        Assert::ExpectException<std::domain_error>([&] { actual /= T{0}; });
        VectorNear(original, actual);
        Assert::ExpectException<std::domain_error>([&] { actual /= V{0, 1, 1, 1}; });
        VectorNear(original, actual);
        Assert::ExpectException<std::domain_error>([&] { actual /= V{1, 0, 1, 1}; });
        VectorNear(original, actual);
        Assert::ExpectException<std::domain_error>([&] { actual /= V{1, 1, 0, 1}; });
        VectorNear(original, actual);
        Assert::ExpectException<std::domain_error>([&] { actual /= V{1, 1, 1, 0}; });
        VectorNear(original, actual);
    }

    template <typename T>
    void EqualityChecksEveryComponentExactly()
    {
        using V = Maths::Vec4<T>;
        const V a = V{1, 2, 3, 4};
        Assert::IsTrue(a == a);
        V changedx = a;
        changedx.x += T{1};
        Assert::IsTrue(changedx != a);
        V changedy = a;
        changedy.y += T{1};
        Assert::IsTrue(changedy != a);
        V changedz = a;
        changedz.z += T{1};
        Assert::IsTrue(changedz != a);
        V changedw = a;
        changedw.w += T{1};
        Assert::IsTrue(changedw != a);
        V nan = a;
        nan.x = std::numeric_limits<T>::quiet_NaN();
        Assert::IsFalse(nan == nan);
    }

    template <typename T>
    void DotHasKnownResult()
    {
        using V = Maths::Vec4<T>;
        const V a = V{1, 2, 3, 4};
        const V b = V{2, 3, 4, 5};
        Near(T{40}, a.Dot(b));
    }

    template <typename T>
    void MagnitudeHasKnownResult()
    {
        using V = Maths::Vec4<T>;
        const V a = V{3, 4, 0, 0};
        Near(T{25}, a.MagnitudeSquared());
        Near(T{5}, a.Magnitude());
        Near(T{0}, V{}.Magnitude());
    }

    template <typename T>
    void NormalizeReturnsNewUnitVector()
    {
        using V = Maths::Vec4<T>;
        const V a = V{3, 4, 0, 0};
        const V actual = a.Normalize();
        VectorNear(V{T{0.6}, T{0.8}, T{0}, T{0}}, actual);
        Near(T{1}, actual.Magnitude());
        VectorNear(V{3, 4, 0, 0}, a);
    }

    template <typename T>
    void NormalizeRejectsZeroAndNonFinite()
    {
        using V = Maths::Vec4<T>;
        Assert::ExpectException<std::domain_error>([] { (void)V{}.Normalize(); });
        V invalid = V{1, 2, 3, 4};
        invalid.x = std::numeric_limits<T>::infinity();
        Assert::ExpectException<std::domain_error>([&] { (void)invalid.Normalize(); });
        invalid.x = std::numeric_limits<T>::quiet_NaN();
        Assert::ExpectException<std::domain_error>([&] { (void)invalid.Normalize(); });
    }

    template <typename T>
    void NormalizeHandlesVeryLargeAndSmallFiniteValues()
    {
        using V = Maths::Vec4<T>;
        const T large = std::numeric_limits<T>::max();
        const T small = std::numeric_limits<T>::min();
        const V expected = V{T{1}, T{1}, T{1}, T{1}} / std::sqrt(T{4});
        VectorNear(expected, V{large, large, large, large}.Normalize());
        VectorNear(expected, V{small, small, small, small}.Normalize());
    }

    template <typename T>
    void DistanceHasKnownResult()
    {
        using V = Maths::Vec4<T>;
        const V a = V{1, 2, 3, 3};
        const V b = V{4, 6, 3, 3};
        Near(T{25}, a.DistanceSquared(b));
        Near(T{5}, a.Distance(b));
    }

    template <typename T>
    void AngleUsesRadians()
    {
        using V = Maths::Vec4<T>;
        Near(std::numbers::pi_v<T> / T{2}, V::UnitX.Angle(V::UnitY));
        Near(std::numbers::pi_v<T>, V::UnitX.Angle(-V::UnitX));
        Near(T{0}, V::UnitX.Angle(V::UnitX));
        Assert::ExpectException<std::domain_error>([] { (void)V::Zero.Angle(V::UnitX); });
    }

    template <typename T>
    void LerpSupportsEndpointsMidpointAndExtrapolation()
    {
        using V = Maths::Vec4<T>;
        const V a = V{0, 0, 0, 0};
        const V b = V{2, 4, 6, 8};
        VectorNear(a, V::Lerp(a, b, T{0}));
        VectorNear(b, V::Lerp(a, b, T{1}));
        VectorNear(V{1, 2, 3, 4}, V::Lerp(a, b, T{0.5}));
        VectorNear(V{4, 8, 12, 16}, V::Lerp(a, b, T{2}));
    }

    template <typename T>
    void MinMaxAreComponentWise()
    {
        using V = Maths::Vec4<T>;
        const V a = V{1, -4, 7, 2};
        const V b = V{3, -2, 5, -8};
        VectorNear(V{1, -4, 5, -8}, V::Min(a,b));
        VectorNear(V{3, -2, 7, 2}, V::Max(a,b));
    }

    template <typename T>
    void NamedConstantsHaveExpectedComponents()
    {
        using V = Maths::Vec4<T>;
        VectorNear(V{0, 0, 0, 0}, V::Zero);
        VectorNear(V{1, 1, 1, 1}, V::One);
        VectorNear(V{1, 0, 0, 0}, V::UnitX);
        VectorNear(V{0, 1, 0, 0}, V::UnitY);
        VectorNear(V{0, 0, 1, 0}, V::UnitZ);
        VectorNear(V{0, 0, 0, 1}, V::UnitW);
    }

}

namespace MathStarterTests
{
    TEST_CLASS(Vec4Tests)
    {
    public:
        TEST_METHOD(DefaultConstructorIsZero_float)
        {
            DefaultConstructorIsZero<float>();
        }

        TEST_METHOD(DefaultConstructorIsZero_double)
        {
            DefaultConstructorIsZero<double>();
        }

        TEST_METHOD(ComponentsAndCopyAreIndependent_float)
        {
            ComponentsAndCopyAreIndependent<float>();
        }

        TEST_METHOD(ComponentsAndCopyAreIndependent_double)
        {
            ComponentsAndCopyAreIndependent<double>();
        }

        TEST_METHOD(ExplicitConversionPreservesValues_float)
        {
            ExplicitConversionPreservesValues<float>();
        }

        TEST_METHOD(ExplicitConversionPreservesValues_double)
        {
            ExplicitConversionPreservesValues<double>();
        }

        TEST_METHOD(AdditionHasKnownResult_float)
        {
            AdditionHasKnownResult<float>();
        }

        TEST_METHOD(AdditionHasKnownResult_double)
        {
            AdditionHasKnownResult<double>();
        }

        TEST_METHOD(SubtractionHasKnownResult_float)
        {
            SubtractionHasKnownResult<float>();
        }

        TEST_METHOD(SubtractionHasKnownResult_double)
        {
            SubtractionHasKnownResult<double>();
        }

        TEST_METHOD(ComponentProductHasKnownResult_float)
        {
            ComponentProductHasKnownResult<float>();
        }

        TEST_METHOD(ComponentProductHasKnownResult_double)
        {
            ComponentProductHasKnownResult<double>();
        }

        TEST_METHOD(ComponentDivisionHasKnownResult_float)
        {
            ComponentDivisionHasKnownResult<float>();
        }

        TEST_METHOD(ComponentDivisionHasKnownResult_double)
        {
            ComponentDivisionHasKnownResult<double>();
        }

        TEST_METHOD(ScalarOperationsAndNegation_float)
        {
            ScalarOperationsAndNegation<float>();
        }

        TEST_METHOD(ScalarOperationsAndNegation_double)
        {
            ScalarOperationsAndNegation<double>();
        }

        TEST_METHOD(CompoundOperatorsReturnSelfAndSupportAliasing_float)
        {
            CompoundOperatorsReturnSelfAndSupportAliasing<float>();
        }

        TEST_METHOD(CompoundOperatorsReturnSelfAndSupportAliasing_double)
        {
            CompoundOperatorsReturnSelfAndSupportAliasing<double>();
        }

        TEST_METHOD(DivisionByZeroThrowsWithoutPartialMutation_float)
        {
            DivisionByZeroThrowsWithoutPartialMutation<float>();
        }

        TEST_METHOD(DivisionByZeroThrowsWithoutPartialMutation_double)
        {
            DivisionByZeroThrowsWithoutPartialMutation<double>();
        }

        TEST_METHOD(EqualityChecksEveryComponentExactly_float)
        {
            EqualityChecksEveryComponentExactly<float>();
        }

        TEST_METHOD(EqualityChecksEveryComponentExactly_double)
        {
            EqualityChecksEveryComponentExactly<double>();
        }

        TEST_METHOD(DotHasKnownResult_float)
        {
            DotHasKnownResult<float>();
        }

        TEST_METHOD(DotHasKnownResult_double)
        {
            DotHasKnownResult<double>();
        }

        TEST_METHOD(MagnitudeHasKnownResult_float)
        {
            MagnitudeHasKnownResult<float>();
        }

        TEST_METHOD(MagnitudeHasKnownResult_double)
        {
            MagnitudeHasKnownResult<double>();
        }

        TEST_METHOD(NormalizeReturnsNewUnitVector_float)
        {
            NormalizeReturnsNewUnitVector<float>();
        }

        TEST_METHOD(NormalizeReturnsNewUnitVector_double)
        {
            NormalizeReturnsNewUnitVector<double>();
        }

        TEST_METHOD(NormalizeRejectsZeroAndNonFinite_float) //faux car les test sont en commentaires
        {
            NormalizeRejectsZeroAndNonFinite<float>();
        }

        TEST_METHOD(NormalizeRejectsZeroAndNonFinite_double)//faux car les test sont en commentaires
        {
            NormalizeRejectsZeroAndNonFinite<double>();
        }

        TEST_METHOD(NormalizeHandlesVeryLargeAndSmallFiniteValues_float)
        {
            NormalizeHandlesVeryLargeAndSmallFiniteValues<float>();
        }

        TEST_METHOD(NormalizeHandlesVeryLargeAndSmallFiniteValues_double)
        {
            NormalizeHandlesVeryLargeAndSmallFiniteValues<double>();
        }

        TEST_METHOD(DistanceHasKnownResult_float)
        {
            DistanceHasKnownResult<float>();
        }

        TEST_METHOD(DistanceHasKnownResult_double)
        {
            DistanceHasKnownResult<double>();
        }

        TEST_METHOD(AngleUsesRadians_float)
        {
            AngleUsesRadians<float>();
        }

        TEST_METHOD(AngleUsesRadians_double)
        {
            AngleUsesRadians<double>();
        }

        TEST_METHOD(LerpSupportsEndpointsMidpointAndExtrapolation_float)
        {
            LerpSupportsEndpointsMidpointAndExtrapolation<float>();
        }

        TEST_METHOD(LerpSupportsEndpointsMidpointAndExtrapolation_double)
        {
            LerpSupportsEndpointsMidpointAndExtrapolation<double>();
        }

        TEST_METHOD(MinMaxAreComponentWise_float)
        {
            MinMaxAreComponentWise<float>();
        }

        TEST_METHOD(MinMaxAreComponentWise_double)
        {
            MinMaxAreComponentWise<double>();
        }

        TEST_METHOD(NamedConstantsHaveExpectedComponents_float)
        {
            NamedConstantsHaveExpectedComponents<float>();
        }

        TEST_METHOD(NamedConstantsHaveExpectedComponents_double)
        {
            NamedConstantsHaveExpectedComponents<double>();
        }

    };
}
