#include "TestHelpers.h"
#include "MathLibrary/Matrix4x4-SIMD.h"
#include <numbers>
#include <type_traits>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace TestHelpers;

namespace
{
    void DefaultAndFactoryAreIdentity()
    {
        using M = Maths::Matrix4x4SIMD;
        const M expected = M(std::array<float, 16>{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1});
        MatrixNear(expected, M{});
        MatrixNear(expected, M::Identity());
        MatrixNear(M(std::array<float, 16>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}), M::Zero());
    }

    void ConstructorAndIndexUseRowMajorOrder()
    {
        using M = Maths::Matrix4x4SIMD;
        M matrix = M(std::array<float, 16>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16});
        Near(float{ 2 }, matrix(0, 1));
        Near(float{ 5 }, matrix(1, 0));
        matrix(1, 0) = float{ 99 };
        const M& view = matrix;
        Near(float{ 99 }, view(1, 0));
        Assert::ExpectException<std::out_of_range>([&] { (void)matrix(4, 0); });
        Assert::ExpectException<std::out_of_range>([&] { (void)view(0, 4); });
    }

    void ArithmeticHasIndependentExpectedValues()
    {
        using M = Maths::Matrix4x4SIMD;
        const M a = M(std::array<float, 16>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16});
        const M b = M(std::array<float, 16>{-1, 2, -2, 1, -3, 0, 3, -1, 2, -2, 1, -3, 0, 3, -1, 2});
        MatrixNear(M(std::array<float, 16>{0, 4, 1, 5, 2, 6, 10, 7, 11, 8, 12, 9, 13, 17, 14, 18}), a + b);
        MatrixNear(M(std::array<float, 16>{2, 0, 5, 3, 8, 6, 4, 9, 7, 12, 10, 15, 13, 11, 16, 14}), a - b);
        MatrixNearSIMD(M(std::array<float, 16>{2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32}), a* float{ 2 });
    }

    void MatrixProductHasIndependentExpectedValues()
    {
        using M = Maths::Matrix4x4SIMD;
        const M a = M(std::array<float, 16>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16});
        const M b = M(std::array<float, 16>{-1, 2, -2, 1, -3, 0, 3, -1, 2, -2, 1, -3, 0, 3, -1, 2});
        const M expected = M(std::array<float, 16>{-1, 8, 3, -2, -9, 20, 7, -6, -17, 32, 11, -10, -25, 44, 15, -14});
        MatrixNear(expected, a * b);
        Assert::IsTrue(a * b != b * a);
    }

    void MultiplyAssignSupportsSelfAliasing()
    {
        using M = Maths::Matrix4x4SIMD;
        M matrix = M(std::array<float, 16>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16});
        Assert::IsTrue(&(matrix *= matrix) == &matrix);
        MatrixNear(M(std::array<float, 16>{90, 100, 110, 120, 202, 228, 254, 280, 314, 356, 398, 440, 426, 484, 542, 600}), matrix);
    }

    void MatrixVectorUsesColumnVectorConvention()
    {
        using M = Maths::Matrix4x4SIMD;
        using V = Maths::Vec4S;
        const M matrix = M(std::array<float, 16>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16});
        const V vector{ 1, 2, 3, 4 };
        VectorNearSIMD(V{ 30, 70, 110, 150 }, matrix.operator*(vector));
    }

    void TransposeMovesEveryElement()
    {
        using M = Maths::Matrix4x4SIMD;
        const M matrix = M(std::array<float, 16>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16});
        MatrixNear(M(std::array<float, 16>{1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16}), matrix.Transpose());
    }

    void EqualityChecksEveryElement()
    {
        using M = Maths::Matrix4x4SIMD;
        const M a;
        for (std::size_t r = 0; r < 4; ++r)
        {
            for (std::size_t c = 0; c < 4; ++c)
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
        using M = Maths::Matrix4x4SIMD;
        const M scale = M::Scale(Maths::Vec3<>{2, 3, 4});
        MatrixNear(M(std::array<float, 16>{2, 0, 0, 0, 0, 3, 0, 0, 0, 0, 4, 0, 0, 0, 0, 1}), scale);
        Near(float{ 24 }, scale.Determinant());
    }

    void RotationXIsRightHanded()
    {
        using M = Maths::Matrix4x4SIMD;
        using V = Maths::Vec4S;
        const M rotation = M::RotationX(std::numbers::pi_v<float> / float{ 2 });
        VectorNear(V{ 0, 0, 1, 0 }, rotation * V{ 0, 1, 0, 0 });
        Near(float{ 1 }, rotation.Determinant());
    }

    void RotationYIsRightHanded()
    {
        using M = Maths::Matrix4x4SIMD;
        using V = Maths::Vec4S;
        const M rotation = M::RotationY(std::numbers::pi_v<float> / float{ 2 });
        VectorNear(V{ 1, 0, 0, 0 }, rotation * V{ 0, 0, 1, 0 });
        Near(float{ 1 }, rotation.Determinant());
    }

    void RotationZIsRightHanded()
    {
        using M = Maths::Matrix4x4SIMD;
        using V = Maths::Vec4S;
        const M rotation = M::RotationZ(std::numbers::pi_v<float> / float{ 2 });
        VectorNear(V{ 0, 1, 0, 0 }, rotation * V{ 1, 0, 0, 0 });
        Near(float{ 1 }, rotation.Determinant());
    }

    void InverseUsesPivotingAndKnownExpectedValues()
    {
        using M = Maths::Matrix4x4SIMD;
        const M matrix = M(std::array<float, 16>{0, 2, 0, 0, 1, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1});
        const M expected = M(std::array<float, 16>{float{ -1.5 }, 1, 0, 0, float{ 0.5 }, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1});
        const M actual = matrix.Inverse();
        MatrixNear(expected, actual);
        MatrixNear(M::Identity(), matrix * actual);
        MatrixNear(M::Identity(), actual * matrix);
        Near(float{ -2 }, matrix.Determinant());
    }

    void DenseInverseMatchesRationalFixture()
    {
        using M = Maths::Matrix4x4SIMD;
        const M matrix = M(std::array<float, 16>{4, 1, -1, 1, 2, 5, 2, 0, 1, -1, 6, -1, 0, 2, 0, 7});
        const M expected = M(std::array<float, 16>{float{ 44 } / float{ 175 }, float{ -1 } / float{ 35 }, float{ 9 } / float{ 175 }, float{ -1 } / float{ 35 }, float{ -2 } / float{ 25 }, float{ 1 } / float{ 5 }, float{ -2 } / float{ 25 }, float{ 0 } / float{ 1 }, float{ -9 } / float{ 175 }, float{ 1 } / float{ 35 }, float{ 26 } / float{ 175 }, float{ 1 } / float{ 35 }, float{ 4 } / float{ 175 }, float{ -2 } / float{ 35 }, float{ 4 } / float{ 175 }, float{ 1 } / float{ 7 }});
        MatrixNear(expected, matrix.Inverse());
    }

    void InverseRejectsSingularAndNonFinite()
    {
        using M = Maths::Matrix4x4SIMD;
        Assert::ExpectException<std::domain_error>([] { (void)M::Zero().Inverse(); });
        M duplicate;
        for (std::size_t c = 0; c < 4; ++c)
        {
            duplicate(1, c) = duplicate(0, c);
        }
        Near(float{ 0 }, duplicate.Determinant());
        Assert::ExpectException<std::domain_error>([&] { (void)duplicate.Inverse(); });
        M invalid;
        invalid(0, 0) = std::numeric_limits<float>::infinity();
        Assert::ExpectException<std::domain_error>([&] { (void)invalid.Inverse(); });
        invalid(0, 0) = std::numeric_limits<float>::quiet_NaN();
        Assert::ExpectException<std::domain_error>([&] { (void)invalid.Inverse(); });
    }

    void InverseValidatesTolerance()
    {
        using M = Maths::Matrix4x4SIMD;
        Assert::ExpectException<std::invalid_argument>([] { (void)M {}.Inverse(float{ -1 }); });
        Assert::ExpectException<std::invalid_argument>([] { (void)M {}.Inverse(float{ 1 }); });
        Assert::ExpectException<std::invalid_argument>([] { (void)M {}.Inverse(std::numeric_limits<float>::quiet_NaN()); });
    }

    void InverseToleranceCanRejectNearDependentRows()
    {
        using M = Maths::Matrix4x4SIMD;
        M matrix;
        matrix(0, 0) = float{ 1 };
        matrix(0, 1) = float{ 1 };
        matrix(1, 0) = float{ 1 };
        matrix(1, 1) = float{ 1 } + std::numeric_limits<T>::epsilon();
        Assert::ExpectException<std::domain_error>([&] { (void)matrix.Inverse(); });
    }

    void InverseHandlesDifferentRowScales()
    {
        using M = Maths::Matrix4x4SIMD;
        M matrix;
        matrix(0, 0) = float{ 0.0001 };
        matrix(1, 1) = float{ 10000 };
        M expected;
        expected(0, 0) = float{ 10000 };
        expected(1, 1) = float{ 0.0001 };
        MatrixNear(expected, matrix.Inverse());
    }

    void TranslationAffectsPointsButNotDirections()
    {
        using M = Maths::Matrix4x4SIMD;
        const M matrix = M::Translation(Maths::Vec3<float>{10, 20, 30});
        const Maths::Vec3<float> input{ 1,2,3 };
        VectorNear(Maths::Vec3<float>{11, 22, 33}, matrix.TransformPoint(input));
        VectorNear(input, matrix.TransformDirection(input));
    }

    void CompositionAppliesRightMatrixFirst()
    {
        using M = Maths::Matrix4x4SIMD;
        const M translate = M::Translation(Maths::Vec3<float>{10, 20, 30});
        const M scale = M::Scale(Maths::Vec3<float>{2, 3, 4});
        const Maths::Vec3<float> point{ 1,2,3 };
        VectorNear(Maths::Vec3<float>{12, 26, 42}, (translate * scale).TransformPoint(point));
        VectorNear(Maths::Vec3<float>{22, 66, 132}, (scale * translate).TransformPoint(point));
    }

    void AffineHelpersRejectPerspective()
    {
        using M = Maths::Matrix4x4SIMD;
        M matrix;
        matrix(3, 2) = float{ 1 };
        Assert::ExpectException<std::domain_error>([&] { (void)matrix.TransformPoint(Maths::Vec3<float>{1, 2, 3}); });
        Assert::ExpectException<std::domain_error>([&] { (void)matrix.TransformDirection(Maths::Vec3<float>{1, 2, 3}); });
    }

}

namespace MathStarterTests
{
    TEST_CLASS(Matrix4x4SIMDTests)
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

        TEST_METHOD(TransposeMovesEveryElement_double)
        {
            TransposeMovesEveryElement();
        }

        TEST_METHOD(EqualityChecksEveryElement_float)
        {
            EqualityChecksEveryElement();
        }

        TEST_METHOD(EqualityChecksEveryElement_double)
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

        TEST_METHOD(RotationXIsRightHanded_double)
        {
            RotationXIsRightHanded();
        }

        TEST_METHOD(RotationYIsRightHanded_float)
        {
            RotationYIsRightHanded();
        }

        TEST_METHOD(RotationYIsRightHanded_double)
        {
            RotationYIsRightHanded();
        }

        TEST_METHOD(RotationZIsRightHanded_float)
        {
            RotationZIsRightHanded();
        }

        TEST_METHOD(RotationZIsRightHanded_double)
        {
            RotationZIsRightHanded();
        }

        TEST_METHOD(InverseUsesPivotingAndKnownExpectedValues_float)
        {
            InverseUsesPivotingAndKnownExpectedValues();
        }

        TEST_METHOD(InverseUsesPivotingAndKnownExpectedValues_double)
        {
            InverseUsesPivotingAndKnownExpectedValues();
        }

        TEST_METHOD(DenseInverseMatchesRationalFixture_float)
        {
            DenseInverseMatchesRationalFixture();
        }

        TEST_METHOD(DenseInverseMatchesRationalFixture_double)
        {
            DenseInverseMatchesRationalFixture();
        }

        TEST_METHOD(InverseRejectsSingularAndNonFinite_float)
        {
            InverseRejectsSingularAndNonFinite();
        }

        TEST_METHOD(InverseRejectsSingularAndNonFinite_double)
        {
            InverseRejectsSingularAndNonFinite();
        }

        TEST_METHOD(InverseValidatesTolerance_float)
        {
            InverseValidatesTolerance();
        }

        TEST_METHOD(InverseValidatesTolerance_double)
        {
            InverseValidatesTolerance();
        }

        TEST_METHOD(InverseToleranceCanRejectNearDependentRows_float)
        {
            InverseToleranceCanRejectNearDependentRows();
        }

        TEST_METHOD(InverseToleranceCanRejectNearDependentRows_double)
        {
            InverseToleranceCanRejectNearDependentRows();
        }

        TEST_METHOD(InverseHandlesDifferentRowScales_float)
        {
            InverseHandlesDifferentRowScales();
        }

        TEST_METHOD(InverseHandlesDifferentRowScales_double)
        {
            InverseHandlesDifferentRowScales();
        }

        TEST_METHOD(TranslationAffectsPointsButNotDirections_float)
        {
            TranslationAffectsPointsButNotDirections();
        }

        TEST_METHOD(TranslationAffectsPointsButNotDirections_double)
        {
            TranslationAffectsPointsButNotDirections();
        }

        TEST_METHOD(CompositionAppliesRightMatrixFirst_float)
        {
            CompositionAppliesRightMatrixFirst();
        }

        TEST_METHOD(CompositionAppliesRightMatrixFirst_double)
        {
            CompositionAppliesRightMatrixFirst();
        }

        TEST_METHOD(AffineHelpersRejectPerspective_float)
        {
            AffineHelpersRejectPerspective();
        }

        TEST_METHOD(AffineHelpersRejectPerspective_double)
        {
            AffineHelpersRejectPerspective();
        }

    };
}
