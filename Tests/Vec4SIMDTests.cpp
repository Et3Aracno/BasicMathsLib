#include "TestsHelpersSIMD.h"
#include "MathLibrary/Vec4S.h"
#include <numbers>
#include <type_traits>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SIMDTests {

    TEST_CLASS(Vec4STests)
    {
    public:

        TEST_METHOD(DefaultConstructorIsZero)
        {
            const Maths::Vec4S actual;
            TestHelpersSIMD::VectorNear4(Maths::Vec4S{ 0.f, 0.f, 0.f, 0.f }, actual);
        }

        TEST_METHOD(ComponentsAndCopyAreIndependent)
        {
            const Maths::Vec4S original{ 1.f, 2.f, 3.f, 4.f };
            Maths::Vec4S copy = original;
            copy.x = 99.f;
            TestHelpersSIMD::VectorNear4(Maths::Vec4S{ 1.f, 2.f, 3.f, 4.f }, original);
            Assert::IsTrue(copy.x == 99.f);
        }

        TEST_METHOD(ExplicitConversionPreservesValues)
        {
            const Maths::Vec4S source{ 1.5f, 2.5f, 3.5f, 4.5 };
            const Maths::Vec4S actual(source);
            TestHelpersSIMD::VectorNear4(Maths::Vec4S{ 1.5f, 2.5f, 3.5f, 4.5 }, actual);
        }

        TEST_METHOD(AdditionHasKnownResult)
        {
            const Maths::Vec4S a = Maths::Vec4S{ 1.f, 2.f, 3.f, 4.f };
            const Maths::Vec4S b = Maths::Vec4S{ 2.f, 3.f, 4.f, 5.f };
            const Maths::Vec4S actual = a + b;
            TestHelpersSIMD::VectorNear4(Maths::Vec4S{ 3.f, 5.f, 7.f, 9.f }, actual);
        }

        TEST_METHOD(SubtractionHasKnownResult)
        {
            const Maths::Vec4S a = Maths::Vec4S{ 1.f, 2.f, 3.f, 4.f };
            const Maths::Vec4S b = Maths::Vec4S{ 2.f, 3.f, 4.f, 5.f };
            const Maths::Vec4S actual = a - b;
            TestHelpersSIMD::VectorNear4(Maths::Vec4S{ -1.f, -1.f, -1.f, -1.f }, actual);
        }

        TEST_METHOD(ComponentProductHasKnownResult)
        {
            const Maths::Vec4S a = Maths::Vec4S{ 1.f, 2.f, 3.f, 4.f };
            const Maths::Vec4S b = Maths::Vec4S{ 2.f, 3.f, 4.f, 5.f };
            const Maths::Vec4S actual = a * b;
            TestHelpersSIMD::VectorNear4(Maths::Vec4S{ 2, 6, 12, 20 }, actual);
        }

        TEST_METHOD(ComponentDivisionHasKnownResult)
        {
            const Maths::Vec4S a = Maths::Vec4S{ 2.f, 6.f, 12.f, 20.f };
            const Maths::Vec4S b = Maths::Vec4S{ 2.f, 3.f, 4.f, 5.f };
            const Maths::Vec4S actual = a / b;
            TestHelpersSIMD::VectorNear4(Maths::Vec4S{ 1.f, 2.f, 3.f, 4.f }, actual);
        }

        TEST_METHOD(ScalarOperationsAndNegation) // A VOIR
        {
            const Maths::Vec4S a = Maths::Vec4S{ 1.f, 2.f, 3.f, 4.f };
            TestHelpersSIMD::VectorNear4(Maths::Vec4S{ -1.f, -2.f, -3.f, -4.f }, -a);
            TestHelpersSIMD::VectorNear4(Maths::Vec4S{ 2.f, 4.f, 6.f, 8.f }, a * 2.f);
            TestHelpersSIMD::VectorNear4(Maths::Vec4S{ 2.f, 4.f, 6.f, 8.f }, a * 2.f);
            TestHelpersSIMD::VectorNear4(a, (a * 2.f) / 2.f);
        }

        TEST_METHOD(CompoundOperatorsReturnSelfAndSupportAliasing)
        {
            Maths::Vec4S a = Maths::Vec4S{ 1.f, 2.f, 3.f, 4.f };
            Assert::IsTrue(&(a += a) == &a);
            TestHelpersSIMD::VectorNear4(Maths::Vec4S{ 2.f, 4.f, 6.f, 8.f }, a);
            a -= Maths::Vec4S{ 1.f, 2.f, 3.f, 4.f };
            a *= a;
            TestHelpersSIMD::VectorNear4(Maths::Vec4S{ 1.f, 4.f, 9.f, 16.f }, a);
            a /= Maths::Vec4S{ 1.f, 2.f, 3.f, 4.f };
            a *= 2.f;
            a /= 2.f;
            TestHelpersSIMD::VectorNear4(Maths::Vec4S{ 1.f, 2.f, 3.f, 4.f }, a);
        }

        TEST_METHOD(DivisionByZeroThrowsWithoutPartialMutation)
        {
            const Maths::Vec4S original = Maths::Vec4S{ 1.f, 2.f, 3.f, 4.f };
            Maths::Vec4S actual = original;
            Assert::ExpectException<std::domain_error>([&] { actual /= 0.f; });
            TestHelpersSIMD::VectorNear4(original, actual);
            Assert::ExpectException<std::domain_error>([&] { actual /= Maths::Vec4S{ 0.f, 1.f, 1.f, 1.f }; });
            TestHelpersSIMD::VectorNear4(original, actual);
            Assert::ExpectException<std::domain_error>([&] { actual /= Maths::Vec4S{ 1.f, 0.f, 1.f, 1.f }; });
            TestHelpersSIMD::VectorNear4(original, actual);
            Assert::ExpectException<std::domain_error>([&] { actual /= Maths::Vec4S{ 1.f, 1.f, 0.f, 1.f }; });
            TestHelpersSIMD::VectorNear4(original, actual);
            Assert::ExpectException<std::domain_error>([&] { actual /= Maths::Vec4S{ 1.f, 1.f, 1.f, 0.f }; });
            TestHelpersSIMD::VectorNear4(original, actual);
        }

        TEST_METHOD(EqualityChecksEveryComponentExactly)
        {
            const Maths::Vec4S a = Maths::Vec4S{ 1.f, 2.f, 3.f, 4.f };
            Assert::IsTrue(a == a);
            Maths::Vec4S changedx = a;
            changedx.x += 1.f;
            Assert::IsTrue(changedx != a);
            Maths::Vec4S changedy = a;
            changedy.y += 1.f;
            Assert::IsTrue(changedy != a);
            Maths::Vec4S changedz = a;
            changedz.z += 1.f;
            Assert::IsTrue(changedz != a);
            Maths::Vec4S changedw = a;
            changedw.w += 1.f;
            Assert::IsTrue(changedw != a);
            Maths::Vec4S nan = a;
            nan.x = std::numeric_limits<float>::quiet_NaN();
            Assert::IsFalse(nan == nan);
        }

        TEST_METHOD(DotHasKnownResult)
        {
            const Maths::Vec4S a = Maths::Vec4S{ 1.f, 2.f, 3.f, 4.f };
            const Maths::Vec4S b = Maths::Vec4S{ 2.f, 3.f, 4.f, 5.f };
            TestHelpersSIMD::Near(40.f, a.Dot(b));
        }

        TEST_METHOD(MagnitudeHasKnownResult)
        {
            const Maths::Vec4S a = Maths::Vec4S{ 3.f, 4.f, 0.f, 0.f };
            TestHelpersSIMD::Near(25.f, a.MagnitudeSquared());
            TestHelpersSIMD::Near(5.f, a.Magnitude());
            TestHelpersSIMD::Near(0.f, Maths::Vec4S{}.Magnitude());
        }

        TEST_METHOD(NormalizeReturnsNewUnitVector) // A VOIR
        {
            const Maths::Vec4S a = Maths::Vec4S{ 3.f, 4.f, 0.f, 0.f };
            const Maths::Vec4S actual = a.Normalize();
            TestHelpersSIMD::VectorNear4(Maths::Vec4S{ 0.6f, 0.8f, 0.f, 0.f }, actual);
            TestHelpersSIMD::Near(1.f, actual.Magnitude());
            TestHelpersSIMD::VectorNear4(Maths::Vec4S{ 3.f, 4.f, 0.f, 0.f }, a);
        }

        TEST_METHOD(NormalizeRejectsZeroAndNonFinite)
        {
            Assert::ExpectException<std::domain_error>([] { (void)Maths::Vec4S{}.Normalize(); });
            Maths::Vec4S invalid = Maths::Vec4S{ 1.f, 2.f, 3.f, 4.f };
            invalid.x = std::numeric_limits<float>::infinity();
            Assert::ExpectException<std::domain_error>([&] { (void)invalid.Normalize(); });
            invalid.x = std::numeric_limits<float>::quiet_NaN();
            Assert::ExpectException<std::domain_error>([&] { (void)invalid.Normalize(); });
        }

        TEST_METHOD(NormalizeHandlesVeryLargeAndSmallFiniteValues)
        {
            const float large = std::numeric_limits<float>::max();
            const float small = std::numeric_limits<float>::min();
            const Maths::Vec4S expected = Maths::Vec4S{ 1.f, 1.f, 1.f, 1.f } / std::sqrt(4.f);
            TestHelpersSIMD::VectorNear4(expected, Maths::Vec4S{ large, large, large, large }.Normalize());
            TestHelpersSIMD::VectorNear4(expected, Maths::Vec4S{ small, small, small, small }.Normalize());
        }

        TEST_METHOD(DistanceHasKnownResult) // A VOIR
        {
            const Maths::Vec4S a = Maths::Vec4S{ 1.f, 2.f, 3.f, 3.f };
            const Maths::Vec4S b = Maths::Vec4S{ 4.f, 6.f, 3.f, 3.f };
            TestHelpersSIMD::Near(25.f, a.DistanceSquared(b));
            TestHelpersSIMD::Near(5.f, a.Distance(b));
        }

        TEST_METHOD(AngleUsesRadians) // A VOIR
        {
            TestHelpersSIMD::Near(std::numbers::pi_v<float> / 2.f, Maths::Vec4S::UnitX.Angle(Maths::Vec4S::UnitY));
            TestHelpersSIMD::Near(std::numbers::pi_v<float>, Maths::Vec4S::UnitX.Angle(-Maths::Vec4S::UnitX));
            TestHelpersSIMD::Near(0.f, Maths::Vec4S::UnitX.Angle(Maths::Vec4S::UnitX));
            Assert::ExpectException<std::domain_error>([] { (void)Maths::Vec4S::Zero.Angle(Maths::Vec4S::UnitX); });
        }

        TEST_METHOD(LerpSupportsEndpointsMidpointAndExtrapolation) // A VOIR
        {
            const Maths::Vec4S a = Maths::Vec4S{ 0.f, 0.f, 0.f, 0.f };
            const Maths::Vec4S b = Maths::Vec4S{ 2.f, 4.f, 6.f, 8.f };
            TestHelpersSIMD::VectorNear4(a, Maths::Vec4S::Lerp(a, b, 0.f));
            TestHelpersSIMD::VectorNear4(b, Maths::Vec4S::Lerp(a, b, 1.f));
            TestHelpersSIMD::VectorNear4(Maths::Vec4S{ 1.f, 2.f, 3.f, 4.f }, Maths::Vec4S::Lerp(a, b, 0.5f));
            TestHelpersSIMD::VectorNear4(Maths::Vec4S{ 4.f, 8.f, 12.f, 16.f }, Maths::Vec4S::Lerp(a, b, 2.f));
        }

        TEST_METHOD(MinMaxAreComponentWise)
        {
            const Maths::Vec4S a = Maths::Vec4S{ 1.f, -4.f, 7.f, 2.f };
            const Maths::Vec4S b = Maths::Vec4S{ 3.f, -2.f, 5.f, -8.f };
            TestHelpersSIMD::VectorNear4(Maths::Vec4S{ 1.f, -4.f, 5.f, -8.f }, Maths::Vec4S::Min(a, b));
            TestHelpersSIMD::VectorNear4(Maths::Vec4S{ 3.f, -2.f, 7.f, 2.f }, Maths::Vec4S::Max(a, b));
        }

        TEST_METHOD(NamedConstantsHaveExpectedComponents)
        {
            TestHelpersSIMD::VectorNear4(Maths::Vec4S{ 0.f, 0.f, 0.f, 0.f }, Maths::Vec4S::Zero);
            TestHelpersSIMD::VectorNear4(Maths::Vec4S{ 1.f, 1.f, 1.f, 1.f }, Maths::Vec4S::One);
            TestHelpersSIMD::VectorNear4(Maths::Vec4S{ 1.f, 0.f, 0.f, 0.f }, Maths::Vec4S::UnitX);
            TestHelpersSIMD::VectorNear4(Maths::Vec4S{ 0.f, 1.f, 0.f, 0.f }, Maths::Vec4S::UnitY);
            TestHelpersSIMD::VectorNear4(Maths::Vec4S{ 0.f, 0.f, 1.f, 0.f }, Maths::Vec4S::UnitZ);
            TestHelpersSIMD::VectorNear4(Maths::Vec4S{ 0.f, 0.f, 0.f, 1.f }, Maths::Vec4S::UnitW);
        }
    };
}

