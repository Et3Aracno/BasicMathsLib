//#include "TestsHelpersSIMD.h"
//#include "MathLibrary/Vec2S.h"
//#include <numbers>
//#include <type_traits>
//
//using namespace Microsoft::VisualStudio::CppUnitTestFramework;
//
//namespace MathStarterTests
//{
//    TEST_CLASS(Vec3Tests)
//    {
//    public:
//
//        TEST_METHOD(DefaultConstructorIsZero)
//        {
//            const Maths::Vec2S actual;
//            TestHelpersSIMD::VectorNear(Maths::Vec2S{ 0.f, 0.f }, actual);
//        }
//
//        TEST_METHOD(ComponentsAndCopyAreIndependent)
//        {
//            const Maths::Vec2S original{ 1.f, 2.f};
//            Maths::Vec2S copy = original;
//            copy.x = 99.f;
//            TestHelpersSIMD::VectorNear(Maths::Vec2S{ 1.f, 2.f}, original);
//            Assert::IsTrue(copy.x == 99.f);
//        }
//
//        TEST_METHOD(ExplicitConversionPreservesValues)
//        {
//            const Maths::Vec2S source{ 1.5f, 2.5f};
//            const Maths::Vec2S actual(source);
//            TestHelpersSIMD::VectorNear(Maths::Vec2S{ 1.5f, 2.5f}, actual);
//        }
//
//        TEST_METHOD(AdditionHasKnownResult)
//        {
//            const Maths::Vec2S a = Maths::Vec2S{ 1.f, 2.f};
//            const Maths::Vec2S b = Maths::Vec2S{ 2.f, 3.f};
//            const Maths::Vec2S actual = a + b;
//            TestHelpersSIMD::VectorNear(Maths::Vec2S{ 3, 5}, actual);
//        }
//
//        TEST_METHOD(SubtractionHasKnownResult)
//        {
//            const Maths::Vec2S a = Maths::Vec2S{ 1.f, 2.f};
//            const Maths::Vec2S b = Maths::Vec2S{ 2.f, 3.f};
//            const Maths::Vec2S actual = a - b;
//            TestHelpersSIMD::VectorNear(Maths::Vec2S{ -1.f, -1.f}, actual);
//        }
//
//        TEST_METHOD(ComponentProductHasKnownResult)
//        {
//            const Maths::Vec2S a = Maths::Vec2S{ 1.f, 2.f};
//            const Maths::Vec2S b = Maths::Vec2S{ 2.f, 3.f};
//            const Maths::Vec2S actual = a * b;
//            TestHelpersSIMD::VectorNear(Maths::Vec2S{ 2, 6}, actual);
//        }
//
//        TEST_METHOD(ComponentDivisionHasKnownResult)
//        {
//            const Maths::Vec2S a = Maths::Vec2S{ 2.f, 6.f};
//            const Maths::Vec2S b = Maths::Vec2S{ 2.f, 3.f};
//            const Maths::Vec2S actual = a / b;
//            TestHelpersSIMD::VectorNear(Maths::Vec2S{ 1.f, 2.f}, actual);
//        }
//
//        TEST_METHOD(ScalarOperationsAndNegation) // A VOIR
//        {
//            const Maths::Vec2S a = Maths::Vec2S{ 1.f, 2.f};
//            TestHelpersSIMD::VectorNear(Maths::Vec2S{ -1.f, -2.f}, -a);
//            TestHelpersSIMD::VectorNear(Maths::Vec2S{ 2.f, 4.f}, a * 2.f);
//            TestHelpersSIMD::VectorNear(Maths::Vec2S{ 2.f, 4.f}, a * 2.f);
//            TestHelpersSIMD::VectorNear(a, (a * 2.f) / 2.f);
//        }
//
//        TEST_METHOD(CompoundOperatorsReturnSelfAndSupportAliasing)
//        {
//            Maths::Vec2S a = Maths::Vec2S{ 1.f, 2.f};
//            Assert::IsTrue(&(a += a) == &a);
//            TestHelpersSIMD::VectorNear(Maths::Vec2S{ 2.f, 4.f}, a);
//            a -= Maths::Vec2S{ 1.f, 2.f};
//            a *= a;
//            TestHelpersSIMD::VectorNear(Maths::Vec2S{ 1.f, 4.f}, a);
//            a /= Maths::Vec2S{ 1, 2};
//            a *= 2.f;
//            a /= 2.f;
//            TestHelpersSIMD::VectorNear(Maths::Vec2S{ 1.f, 2.f}, a);
//        }
//
//        TEST_METHOD(DivisionByZeroThrowsWithoutPartialMutation)
//        {
//            const Maths::Vec2S original = Maths::Vec2S{ 1.f, 2.f};
//            Maths::Vec2S actual = original;
//            Assert::ExpectException<std::domain_error>([&] { actual /= 0.f; });
//            TestHelpersSIMD::VectorNear(original, actual);
//            Assert::ExpectException<std::domain_error>([&] { actual /= Maths::Vec2S{ 0.f, 1.f}; });
//            TestHelpersSIMD::VectorNear(original, actual);
//            Assert::ExpectException<std::domain_error>([&] { actual /= Maths::Vec2S{ 1.f, 0.f}; });
//            TestHelpersSIMD::VectorNear(original, actual);
//            Assert::ExpectException<std::domain_error>([&] { actual /= Maths::Vec2S{ 1.f, 1.f}; });
//            TestHelpersSIMD::VectorNear(original, actual);
//        }
//
//        TEST_METHOD(EqualityChecksEveryComponentExactly)
//        {
//            const Maths::Vec2S a = Maths::Vec2S{ 1.f, 2.f};
//            Assert::IsTrue(a == a);
//            Maths::Vec2S changedx = a;
//            changedx.x += 1.f;
//            Assert::IsTrue(changedx != a);
//            Maths::Vec2S changedy = a;
//            changedy.y += 1.f;
//            Assert::IsTrue(changedy != a);
//            Maths::Vec2S changedz = a;
//            Maths::Vec2S nan = a;
//            nan.x = std::numeric_limits<float>::quiet_NaN();
//            Assert::IsFalse(nan == nan);
//        }
//
//        TEST_METHOD(DotHasKnownResult)
//        {
//            const Maths::Vec2S a = Maths::Vec2S{ 1.f, 2.f};
//            const Maths::Vec2S b = Maths::Vec2S{ 2.f, 3.f};
//            TestHelpersSIMD::Near(20.f, a.Dot(b));
//        }
//
//        TEST_METHOD(MagnitudeHasKnownResult)
//        {
//            const Maths::Vec2S a = Maths::Vec2S{ 3.f, 4.f};
//            TestHelpersSIMD::Near(25.f, a.MagnitudeSquared());
//            TestHelpersSIMD::Near(5.f, a.Magnitude());
//            TestHelpersSIMD::Near(0.f, Maths::Vec2S{}.Magnitude());
//        }
//
//        TEST_METHOD(NormalizeReturnsNewUnitVector) // A VOIR
//        {
//            const Maths::Vec2S a = Maths::Vec2S{ 3.f, 4.f };
//            const Maths::Vec2S actual = a.Normalize();
//            TestHelpersSIMD::VectorNear(Maths::Vec2S{ 0.6f, 0.8f}, actual);
//            TestHelpersSIMD::Near(1.f, actual.Magnitude());
//            TestHelpersSIMD::VectorNear(Maths::Vec2S{ 3.f, 4.f}, a);
//        }
//
//        TEST_METHOD(NormalizeRejectsZeroAndNonFinite)
//        {
//            Assert::ExpectException<std::domain_error>([] { (void)Maths::Vec2S{}.Normalize(); });
//            Maths::Vec2S invalid = Maths::Vec2S{ 1.f, 2.f};
//            invalid.x = std::numeric_limits<float>::infinity();
//            Assert::ExpectException<std::domain_error>([&] { (void)invalid.Normalize(); });
//            invalid.x = std::numeric_limits<float>::quiet_NaN();
//            Assert::ExpectException<std::domain_error>([&] { (void)invalid.Normalize(); });
//        }
//
//        TEST_METHOD(NormalizeHandlesVeryLargeAndSmallFiniteValues)
//        {
//            const float large = std::numeric_limits<float>::max();
//            const float small = std::numeric_limits<float>::min();
//            const Maths::Vec2S expected = Maths::Vec2S{ 1.f, 1.f} / std::sqrt(3.f);
//            TestHelpersSIMD::VectorNear(expected, Maths::Vec2S{ large, large}.Normalize());
//            TestHelpersSIMD::VectorNear(expected, Maths::Vec2S{ small, small}.Normalize());
//        }
//
//        TEST_METHOD(DistanceHasKnownResult) // A VOIR
//        {
//            const Maths::Vec2S a = Maths::Vec2S{ 1.f, 2.f};
//            const Maths::Vec2S b = Maths::Vec2S{ 4.f, 6.f};
//            TestHelpersSIMD::Near(25.f, a.DistanceSquared(b));
//            TestHelpersSIMD::Near(5.f, a.Distance(b));
//        }
//
//        TEST_METHOD(AngleUsesRadians) // A VOIR
//        {
//            TestHelpersSIMD::Near(std::numbers::pi_v<float> / 2.f, Maths::Vec2S::UnitX.Angle(Maths::Vec2S::UnitY));
//            TestHelpersSIMD::Near(std::numbers::pi_v<float>, Maths::Vec2S::UnitX.Angle(-Maths::Vec2S::UnitX));
//            TestHelpersSIMD::Near(0.f, Maths::Vec2S::UnitX.Angle(Maths::Vec2S::UnitX));
//            Assert::ExpectException<std::domain_error>([] { (void)Maths::Vec2S::Zero.Angle(Maths::Vec2S::UnitX); });
//        }
//
//        TEST_METHOD(LerpSupportsEndpointsMidpointAndExtrapolation) // A VOIR
//        {
//            const Maths::Vec2S a = Maths::Vec2S{ 0.f, 0.f};
//            const Maths::Vec2S b = Maths::Vec2S{ 2.f, 4.f};
//            TestHelpersSIMD::VectorNear(a, Maths::Vec2S::Lerp(a, b, 0.f));
//            TestHelpersSIMD::VectorNear(b, Maths::Vec2S::Lerp(a, b, 1.f));
//            TestHelpersSIMD::VectorNear(Maths::Vec2S{ 1.f, 2.f}, Maths::Vec2S::Lerp(a, b, 0.5f));
//            TestHelpersSIMD::VectorNear(Maths::Vec2S{ 4.f, 8.f}, Maths::Vec2S::Lerp(a, b, 2.f));
//        }
//
//        TEST_METHOD(MinMaxAreComponentWise)
//        {
//            const Maths::Vec2S a = Maths::Vec2S{ 1.f, -4.f};
//            const Maths::Vec2S b = Maths::Vec2S{ 3.f, -2.f};
//            TestHelpersSIMD::VectorNear(Maths::Vec2S{ 1.f, -4.f}, Maths::Vec2S::Min(a, b));
//            TestHelpersSIMD::VectorNear(Maths::Vec2S{ 3.f, -2.f}, Maths::Vec2S::Max(a, b));
//        }
//
//        TEST_METHOD(NamedConstantsHaveExpectedComponents)
//        {
//            TestHelpersSIMD::VectorNear(Maths::Vec2S{ 0.f, 0.f}, Maths::Vec2S::Zero);
//            TestHelpersSIMD::VectorNear(Maths::Vec2S{ 1.f, 1.f}, Maths::Vec2S::One);
//            TestHelpersSIMD::VectorNear(Maths::Vec2S{ 1.f, 0.f}, Maths::Vec2S::UnitX);
//            TestHelpersSIMD::VectorNear(Maths::Vec2S{ 0.f, 1.f}, Maths::Vec2S::UnitY);
//        }
//
//        TEST_METHOD(CrossUsesRightHandedOrientation)
//        {
//            TestHelpersSIMD::VectorNear(Maths::Vec2S{ 0.f, 0.f}, Maths::Vec2S::UnitX.Cross(Maths::Vec2S::UnitY)); // 1
//            TestHelpersSIMD::VectorNear(Maths::Vec2S{ 0.f, 0.f}, Maths::Vec2S::UnitY.Cross(Maths::Vec2S::UnitX)); // -1
//            const Maths::Vec2S a{ 1.f, 2.f};
//            const Maths::Vec2S b{ 4.f, 5.f};
//            TestHelpersSIMD::VectorNear(Maths::Vec2S{ -3.f, 6.f}, a.Cross(b));
//            TestHelpersSIMD::VectorNear(Maths::Vec2S::Zero, a.Cross(a));
//        }
//    };
//
//}
//
