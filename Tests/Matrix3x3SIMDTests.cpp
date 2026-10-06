#include "TestHelpers.h"
#include "MathLibrary/Matrix3x3-SIMD.h"
#include <numbers>
#include <type_traits>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace TestHelpers;

namespace
{
    void DefaultAndFactoryAreIdentity()
    {
        using M = Maths::Matrix3x3SIMD;
        const M expected = M(std::array<float, 9>{1, 0, 0, 0, 1, 0, 0, 0, 1});
        MatrixNearSIMD(expected, M{});
        MatrixNearSIMD(expected, M::Identity());
        MatrixNearSIMD(M(std::array<float, 9>{0, 0, 0, 0, 0, 0, 0, 0, 0}), M::Zero());
    }

    void ConstructorAndIndexUseRowMajorOrder()
    {
        using M = Maths::Matrix3x3SIMD;
        M matrix = M(std::array<float, 9>{1, 2, 3, 4, 5, 6, 7, 8, 9});
        Near(float{ 2 }, matrix(0, 1));
        Near(float{ 4 }, matrix(1, 0));
        matrix(1, 0) = float{ 99 };
        const M& view = matrix;
        Near(float{ 99 }, view(1, 0));
        Assert::ExpectException<std::out_of_range>([&] { (void)matrix(3, 0); });
        Assert::ExpectException<std::out_of_range>([&] { (void)view(0, 3); });
    }

    void ArithmeticHasIndependentExpectedValues()
    {
        using M = Maths::Matrix3x3SIMD;
        const M a = M(std::array<float, 9>{1, 2, 3, 4, 5, 6, 7, 8, 9});
        const M b = M(std::array<float, 9>{-1, 2, -2, 1, -3, 0, 3, -1, 2});
        MatrixNearSIMD(M(std::array<float, 9>{0, 4, 1, 5, 2, 6, 10, 7, 11}), a + b);
        MatrixNearSIMD(M(std::array<float, 9>{2, 0, 5, 3, 8, 6, 4, 9, 7}), a - b);
        MatrixNearSIMD(M(std::array<float, 9>{2, 4, 6, 8, 10, 12, 14, 16, 18}), a* float{ 2 });
    }


    void MatrixProductHasIndependentExpectedValues()
    {
        using M = Maths::Matrix3x3SIMD;
        const M a = M(std::array<float, 9>{1, 2, 3, 4, 5, 6, 7, 8, 9});
        const M b = M(std::array<float, 9>{-1, 2, -2, 1, -3, 0, 3, -1, 2});
        const M expected = M(std::array<float, 9>{10, -7, 4, 19, -13, 4, 28, -19, 4});
        MatrixNearSIMD(expected, a * b);
        Assert::IsTrue(a * b != b * a);
    }


    void MultiplyAssignSupportsSelfAliasing()
    {
        using M = Maths::Matrix3x3SIMD;
        M matrix = M(std::array<float, 9>{1, 2, 3, 4, 5, 6, 7, 8, 9});
        Assert::IsTrue(&(matrix *= matrix) == &matrix);
        MatrixNearSIMD(M(std::array<float, 9>{30, 36, 42, 66, 81, 96, 102, 126, 150}), matrix);
    }


    void MatrixVectorUsesColumnVectorConvention()
    {
        using M = Maths::Matrix3x3SIMD;
        using V = Maths::Vec3<float>;
        const M matrix = M(std::array<float, 9>{1, 2, 3, 4, 5, 6, 7, 8, 9});
        const V vector{ 1, 2, 3 };
        VectorNear(V{ 14, 32, 50 }, matrix * vector);
    }


    void TransposeMovesEveryElement()
    {
        using M = Maths::Matrix3x3SIMD;
        const M matrix = M(std::array<float, 9>{1, 2, 3, 4, 5, 6, 7, 8, 9});
        MatrixNearSIMD(M(std::array<float, 9>{1, 4, 7, 2, 5, 8, 3, 6, 9}), matrix.Transpose());
    }


    void EqualityChecksEveryElement()
    {
        using M = Maths::Matrix3x3SIMD;
        const M a;
        for (std::size_t r = 0; r < 3; ++r)
        {
            for (std::size_t c = 0; c < 3; ++c)
            {
                M b = a;
                b(r, c) += float{ 1 };
                Assert::IsTrue(a != b);
            }
        }
        Assert::IsTrue(a == a);
    }


    void ScaleHasKnownResult()
    {
        using M = Maths::Matrix3x3SIMD;
        const M scale = M::Scale(Maths::Vec3<float>{2, 3, 4});
        MatrixNearSIMD(M(std::array<float, 9>{2, 0, 0, 0, 3, 0, 0, 0, 4}), scale);
        Near(float{ 24 }, scale.Determinant());
    }


    void RotationXIsRightHanded()
    {
        using M = Maths::Matrix3x3SIMD;
        using V = Maths::Vec3<float>;
        const M rotation = M::RotationX(std::numbers::pi_v<float> / float{ 2 });
        VectorNear(V{ 0, 0, 1 }, rotation * V{ 0, 1, 0 });
        Near(float{ 1 }, rotation.Determinant());
    }

    void RotationYIsRightHanded()
    {
        using M = Maths::Matrix3x3SIMD;
        using V = Maths::Vec3<float>;
        const M rotation = M::RotationY(std::numbers::pi_v<float> / float{ 2 });
        VectorNear(V{ 1, 0, 0 }, rotation * V{ 0, 0, 1 });
        Near(float{ 1 }, rotation.Determinant());
    }


    void RotationZIsRightHanded()
    {
        using M = Maths::Matrix3x3SIMD;
        using V = Maths::Vec3<float>;
        const M rotation = M::RotationZ(std::numbers::pi_v<float> / float{ 2 });
        VectorNear(V{ 0, 1, 0 }, rotation * V{ 1, 0, 0 });
        Near(float{ 1 }, rotation.Determinant());
    }


    void InverseUsesPivotingAndKnownExpectedValues()
    {
        using M = Maths::Matrix3x3SIMD;
        const M matrix = M(std::array<float, 9>{0, 2, 0, 1, 3, 0, 0, 0, 1});
        const M expected = M(std::array<float, 9>{float{ -1.5 }, 1, 0, float{ 0.5 }, 0, 0, 0, 0, 1});
        const M actual = matrix.Inverse();
        MatrixNearSIMD(expected, actual);
        MatrixNearSIMD(M::Identity(), matrix * actual);
        MatrixNearSIMD(M::Identity(), actual * matrix);
        Near(float{ -2 }, matrix.Determinant());
    }


    void DenseInverseMatchesRationalFixture()
    {
        using M = Maths::Matrix3x3SIMD;
        const M matrix = M(std::array<float, 9>{4, 1, -1, 2, 5, 2, 1, -1, 6});
        const M expected = M(std::array<float, 9>{float{ 32 } / float{ 125 }, float{ -1 } / float{ 25 }, float{ 7 } / float{ 125 }, float{ -2 } / float{ 25 }, float{ 1 } / float{ 5 }, float{ -2 } / float{ 25 }, float{ -7 } / float{ 125 }, float{ 1 } / float{ 25 }, float{ 18 } / float    { 125 }});
        MatrixNearSIMD(expected, matrix.Inverse());
    }


    void InverseRejectsSingularAndNonFinite()
    {
        using M = Maths::Matrix3x3SIMD;

        Assert::ExpectException<std::out_of_range>(
            [] { (void)M::Zero().Inverse(); }
        );

        M duplicate;

        for (std::size_t c = 0; c < 3; ++c)
        {
            duplicate(1, c) = duplicate(0, c);
        }

        Near(float{ 0 }, duplicate.Determinant());

        Assert::ExpectException<std::out_of_range>(
            [&] { (void)duplicate.Inverse(); }
        );
    }

    void InverseValidatesTolerance()
    {
        using M = Maths::Matrix3x3SIMD;
        Assert::ExpectException<std::invalid_argument>([] { (void)M {}.Inverse(float{ -1 }); });
        Assert::ExpectException<std::invalid_argument>([] { (void)M {}.Inverse(float{ 1 }); });
        Assert::ExpectException<std::invalid_argument>([] { (void)M {}.Inverse(std::numeric_limits<float>::quiet_NaN()); });
    }

    void InverseAcceptsValidTolerance()
    {
        using M = Maths::Matrix3x3SIMD;

        (void)M {
        }.Inverse(0.0f);
        (void)M {
        }.Inverse(0.5f);
        (void)M {
        }.Inverse(0.999999f);
    }



    void InverseToleranceCanRejectNearDependentRows()
    {
        using M = Maths::Matrix3x3SIMD;
        M matrix;
        matrix(0, 0) = float{ 1 };
        matrix(0, 1) = float{ 1 };
        matrix(1, 0) = float{ 1 };
        matrix(1, 1) = float{ 1 } + std::numeric_limits<float>::epsilon();
        Assert::ExpectException<std::out_of_range>([&] { (void)matrix.Inverse(); });
    }


    void InverseHandlesDifferentRowScales()
    {
        using M = Maths::Matrix3x3SIMD;
        M matrix;
        matrix(0, 0) = float{ 0.0001 };
        matrix(1, 1) = float{ 10000 };
        M expected;
        expected(0, 0) = float{ 10000 };
        expected(1, 1) = float{ 0.0001 };
        MatrixNearSIMD(expected, matrix.Inverse());
    }

}

namespace MathStarterTests
{
    TEST_CLASS(Matrix3x3SIMDTests)
    {
    public:
        TEST_METHOD(DefaultAndFactoryAreIdentity_float)
        {
            DefaultAndFactoryAreIdentity();
        }

        TEST_METHOD(DefaultAndFactoryAreIdentity_double)
        {
            DefaultAndFactoryAreIdentity();
        }

        TEST_METHOD(ConstructorAndIndexUseRowMajorOrder_float)
        {
            ConstructorAndIndexUseRowMajorOrder();
        }

        TEST_METHOD(ConstructorAndIndexUseRowMajorOrder_double)
        {
            ConstructorAndIndexUseRowMajorOrder();
        }

        TEST_METHOD(ArithmeticHasIndependentExpectedValues_float)
        {
            ArithmeticHasIndependentExpectedValues();
        }

        TEST_METHOD(ArithmeticHasIndependentExpectedValues_double)
        {
            ArithmeticHasIndependentExpectedValues();
        }

        TEST_METHOD(MatrixProductHasIndependentExpectedValues_float)
        {
            MatrixProductHasIndependentExpectedValues();
        }

        TEST_METHOD(MatrixProductHasIndependentExpectedValues_double)
        {
            MatrixProductHasIndependentExpectedValues();
        }

        TEST_METHOD(MultiplyAssignSupportsSelfAliasing_float)
        {
            MultiplyAssignSupportsSelfAliasing();
        }

        TEST_METHOD(MultiplyAssignSupportsSelfAliasing_double)
        {
            MultiplyAssignSupportsSelfAliasing();
        }

        TEST_METHOD(MatrixVectorUsesColumnVectorConvention_float)
        {
            MatrixVectorUsesColumnVectorConvention();
        }

        TEST_METHOD(MatrixVectorUsesColumnVectorConvention_double)
        {
            MatrixVectorUsesColumnVectorConvention();
        }

        TEST_METHOD(TransposeMovesEveryElement_float)
        {
            TransposeMovesEveryElement();
        }

        TEST_METHOD(EqualityChecksEveryElement_float)
        {
            EqualityChecksEveryElement();
        }

        TEST_METHOD(ScaleHasKnownResult_float)
        {
            ScaleHasKnownResult();
        }

        TEST_METHOD(ScaleHasKnownResult_double)
        {
            ScaleHasKnownResult();
        }

        TEST_METHOD(RotationXIsRightHanded_float)
        {
            RotationXIsRightHanded();
        }

        TEST_METHOD(RotationYIsRightHanded_float)
        {
            RotationYIsRightHanded();
        }

        TEST_METHOD(RotationZIsRightHanded_float)
        {
            RotationZIsRightHanded();
        }

        TEST_METHOD(InverseUsesPivotingAndKnownExpectedValues_float)
        {
            InverseUsesPivotingAndKnownExpectedValues();
        }

        TEST_METHOD(DenseInverseMatchesRationalFixture_float)
        {
            DenseInverseMatchesRationalFixture();
        }

        TEST_METHOD(InverseRejectsSingularAndNonFinite_float)
        {
            InverseRejectsSingularAndNonFinite();
        }

        TEST_METHOD(InverseValidatesTolerance_float)
        {
            InverseValidatesTolerance();
        }

		TEST_METHOD(InverseAcceptsValidTolerance_float)
		{
			InverseAcceptsValidTolerance();
		}

        TEST_METHOD(InverseToleranceCanRejectNearDependentRows_float)
        {
            InverseToleranceCanRejectNearDependentRows();
        }

        TEST_METHOD(InverseHandlesDifferentRowScales_float)
        {
            InverseHandlesDifferentRowScales();
        }

    };
}
