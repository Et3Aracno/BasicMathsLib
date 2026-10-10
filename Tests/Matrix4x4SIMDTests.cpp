#include "TestHelpers.h"
#include "MathLibrary/Matrix4x4-SIMD.h"
#include <array>
#include <numbers>
#include <stdexcept>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace TestHelpers;

namespace
{
    using Mat = Maths::Matrix4x4SIMD;
    using Arr = std::array<float, 16>;
    using V3 = Maths::Vec3S;
    using V4 = Maths::Vec4S;

    constexpr float HalfPi = std::numbers::pi_v<float> / 2.0f;
}

namespace MathStarterTests
{
    TEST_CLASS(Matrix4x4SIMDTests)
    {
    public:
        TEST_METHOD(DefaultAndFactoryAreIdentity)
        {
            const Mat expected(Arr{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 });
            MatrixNearSIMDv4(expected, Mat{});
            MatrixNearSIMDv4(expected, Mat::Identity());
            MatrixNearSIMDv4(Mat(Arr{}), Mat::Zero());
        }

        TEST_METHOD(ConstructorAndIndexUseRowMajorOrder)
        {
            Mat matrix(Arr{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 });
            Near<float>(2.0f, matrix(0, 1));
            Near<float>(5.0f, matrix(1, 0));
            Near<float>(16.0f, matrix(3, 3));
            matrix(1, 0) = 99.0f;
            const Mat& view = matrix;
            Near<float>(99.0f, view(1, 0));
            Assert::ExpectException<std::out_of_range>([&] { (void)matrix(4, 0); });
            Assert::ExpectException<std::out_of_range>([&] { (void)view(0, 4); });
        }

        TEST_METHOD(ArithmeticHasIndependentExpectedValues)
        {
            const Mat a(Arr{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 });
            const Mat b(Arr{ -1, 2, -2, 1, -3, 0, 3, -1, 2, -2, 1, -3, 0, 3, -1, 2 });
            MatrixNearSIMDv4(Mat(Arr{ 0, 4, 1, 5, 2, 6, 10, 7, 11, 8, 12, 9, 13, 17, 14, 18 }), a + b);
            MatrixNearSIMDv4(Mat(Arr{ 2, 0, 5, 3, 8, 6, 4, 9, 7, 12, 10, 15, 13, 11, 16, 14 }), a - b);
            MatrixNearSIMDv4(Mat(Arr{ 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32 }), a * 2.0f);
        }

        TEST_METHOD(MatrixProductHasIndependentExpectedValues)
        {
            const Mat a(Arr{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 });
            const Mat b(Arr{ -1, 2, -2, 1, -3, 0, 3, -1, 2, -2, 1, -3, 0, 3, -1, 2 });
            const Mat expected(Arr{ -1, 8, 3, -2, -9, 20, 7, -6, -17, 32, 11, -10, -25, 44, 15, -14 });
            MatrixNearSIMDv4(expected, a * b);
            Assert::IsTrue(a * b != b * a);
        }

        TEST_METHOD(MultiplyAssignSupportsSelfAliasing)
        {
            Mat matrix(Arr{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 });
            Assert::IsTrue(&(matrix *= matrix) == &matrix);
            MatrixNearSIMDv4(Mat(Arr{ 90, 100, 110, 120, 202, 228, 254, 280, 314, 356, 398, 440, 426, 484, 542, 600 }), matrix);
        }

        TEST_METHOD(MatrixVectorUsesColumnVectorConvention)
        {
            const Mat matrix(Arr{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 });
            const V4 vector{ 1, 2, 3, 4 };
            VectorNearSIMDV4(V4{ 30, 70, 110, 150 }, matrix * vector);
        }

        TEST_METHOD(TransposeMovesEveryElement)
        {
            const Mat matrix(Arr{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 });
            MatrixNearSIMDv4(Mat(Arr{ 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16 }), matrix.Transpose());
        }

        TEST_METHOD(EqualityChecksEveryElement)
        {
            const Mat a;
            for (std::size_t r = 0; r < 4; ++r)
            {
                for (std::size_t c = 0; c < 4; ++c)
                {
                    Mat b = a;
                    b(r, c) += 1.0f;
                    Assert::IsTrue(a != b);
                    Assert::IsFalse(a == b);
                }
            }
            Assert::IsTrue(a == a);
            Assert::IsFalse(a != a);
        }

        TEST_METHOD(ScaleHasKnownResult)
        {
            const Mat scale = Mat::Scale(V3{ 2, 3, 4 });
            MatrixNearSIMDv4(Mat(Arr{ 2, 0, 0, 0, 0, 3, 0, 0, 0, 0, 4, 0, 0, 0, 0, 1 }), scale);
            // Near<float>(24.0f, scale.Determinant()); // à réactiver quand Determinant() sera implémentée
        }

        TEST_METHOD(RotationXIsRightHanded)
        {
            const Mat rotation = Mat::RotationX(HalfPi);
            VectorNearSIMDV4(V4{ 0, 0, 1, 0 }, rotation * V4{ 0, 1, 0, 0 });
            // Near<float>(1.0f, rotation.Determinant());
        }

        TEST_METHOD(RotationYIsRightHanded)
        {
            const Mat rotation = Mat::RotationY(HalfPi);
            VectorNearSIMDV4(V4{ 1, 0, 0, 0 }, rotation * V4{ 0, 0, 1, 0 });        //besoin de faire la fonction determinant et inverse de la matrice 4x4 SIMD , et de rajouter les nouveaux test en plus de retirer les commentaires 
            // Near<float>(1.0f, rotation.Determinant());
        }

        TEST_METHOD(RotationZIsRightHanded)
        {
            const Mat rotation = Mat::RotationZ(HalfPi);
            VectorNearSIMDV4(V4{ 0, 1, 0, 0 }, rotation * V4{ 1, 0, 0, 0 });
            // Near<float>(1.0f, rotation.Determinant()); 
        }

        TEST_METHOD(TranslationAffectsPointsButNotDirections)
        {
            const Mat matrix = Mat::Translation(V3{ 10, 20, 30 });
            const V3 input{ 1, 2, 3 };
            VectorNearSIMDV3(V3{ 11, 22, 33 }, matrix.TransformPoint(input));
            VectorNearSIMDV3(input, matrix.TransformDirection(input));
        }

        TEST_METHOD(CompositionAppliesRightMatrixFirst)
        {
            const Mat translate = Mat::Translation(V3{ 10, 20, 30 });
            const Mat scale = Mat::Scale(V3{ 2, 3, 4 });
            const V3 point{ 1, 2, 3 };
            VectorNearSIMDV3(V3{ 12, 26, 42 }, (translate * scale).TransformPoint(point));
            VectorNearSIMDV3(V3{ 22, 66, 132 }, (scale * translate).TransformPoint(point));
        }

        TEST_METHOD(AffineHelpersRejectPerspective)
        {
            Mat matrix;
            matrix(3, 2) = 1.0f;
            Assert::ExpectException<std::domain_error>([&] { (void)matrix.TransformPoint(V3{ 1, 2, 3 }); });
            Assert::ExpectException<std::domain_error>([&] { (void)matrix.TransformDirection(V3{ 1, 2, 3 }); });
        }
    };
}