#include "TestHelpers.h"
#include "MathLibrary/Matrix4x4.h"
#include <numbers>
#include <type_traits>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace TestHelpers;

namespace
{
    template <typename T>
    void DefaultAndFactoryAreIdentity()
    {
        using M = Maths::Matrix4x4<T>;
        const M expected = M(std::array<T, 16>{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1});
        MatrixNear(expected, M{});
        MatrixNear(expected, M::Identity());
        MatrixNear(M(std::array<T, 16>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}), M::Zero());
    }

    template <typename T>
    void ConstructorAndIndexUseRowMajorOrder()
    {
        using M = Maths::Matrix4x4<T>;
        M matrix = M(std::array<T, 16>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16});
        Near(T{2}, matrix(0, 1));
        Near(T{5}, matrix(1, 0));
        matrix(1, 0) = T{99};
        const M& view = matrix;
        Near(T{99}, view(1, 0));
        Assert::ExpectException<std::out_of_range>([&] { (void)matrix(4, 0); });
        Assert::ExpectException<std::out_of_range>([&] { (void)view(0, 4); });
    }

    template <typename T>
    void ArithmeticHasIndependentExpectedValues()
    {
        using M = Maths::Matrix4x4<T>;
        const M a = M(std::array<T, 16>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16});
        const M b = M(std::array<T, 16>{-1, 2, -2, 1, -3, 0, 3, -1, 2, -2, 1, -3, 0, 3, -1, 2});
        MatrixNear(M(std::array<T, 16>{0, 4, 1, 5, 2, 6, 10, 7, 11, 8, 12, 9, 13, 17, 14, 18}), a + b);
        MatrixNear(M(std::array<T, 16>{2, 0, 5, 3, 8, 6, 4, 9, 7, 12, 10, 15, 13, 11, 16, 14}), a - b);
        MatrixNear(M(std::array<T, 16>{2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32}), a * T{2});
    }

    template <typename T>
    void MatrixProductHasIndependentExpectedValues()
    {
        using M = Maths::Matrix4x4<T>;
        const M a = M(std::array<T, 16>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16});
        const M b = M(std::array<T, 16>{-1, 2, -2, 1, -3, 0, 3, -1, 2, -2, 1, -3, 0, 3, -1, 2});
        const M expected = M(std::array<T, 16>{-1, 8, 3, -2, -9, 20, 7, -6, -17, 32, 11, -10, -25, 44, 15, -14});
        MatrixNear(expected, a * b);
        Assert::IsTrue(a * b != b * a);
    }

    template <typename T>
    void MultiplyAssignSupportsSelfAliasing()
    {
        using M = Maths::Matrix4x4<T>;
        M matrix = M(std::array<T, 16>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16});
        Assert::IsTrue(&(matrix *= matrix) == &matrix);
        MatrixNear(M(std::array<T, 16>{90, 100, 110, 120, 202, 228, 254, 280, 314, 356, 398, 440, 426, 484, 542, 600}), matrix);
    }

    template <typename T>
    void MatrixVectorUsesColumnVectorConvention()
    {
        using M = Maths::Matrix4x4<T>;
        using V = Maths::Vec4<T>;
        const M matrix = M(std::array<T, 16>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16});
        const V vector{1, 2, 3, 4};
        VectorNear(V{30, 70, 110, 150}, matrix * vector);
    }

    template <typename T>
    void TransposeMovesEveryElement()
    {
        using M = Maths::Matrix4x4<T>;
        const M matrix = M(std::array<T, 16>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16});
        MatrixNear(M(std::array<T, 16>{1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16}), matrix.Transpose());
    }

    template <typename T>
    void EqualityChecksEveryElement()
    {
        using M = Maths::Matrix4x4<T>;
        const M a;
        for (std::size_t r=0; r<4; ++r)
        {
            for (std::size_t c=0; c<4; ++c)
            {
                M b = a;
                b(r,c) += T{1};
                Assert::IsTrue(a != b);
            }
        }
        Assert::IsTrue(a == a);
    }

    template <typename T>
    void ScaleHasKnownResult()
    {
        using M = Maths::Matrix4x4<T>;
        const M scale = M::Scale(Maths::Vec3<T>{2,3,4});
        MatrixNear(M(std::array<T, 16>{2, 0, 0, 0, 0, 3, 0, 0, 0, 0, 4, 0, 0, 0, 0, 1}), scale);
        Near(T{24}, scale.Determinant());
    }

    template <typename T>
    void RotationXIsRightHanded()
    {
        using M = Maths::Matrix4x4<T>;
        using V = Maths::Vec4<T>;
        const M rotation = M::RotationX(std::numbers::pi_v<T> / T{2});
        VectorNear(V{0, 0, 1, 0}, rotation * V{0, 1, 0, 0});
        Near(T{1}, rotation.Determinant());
    }

    template <typename T>
    void RotationYIsRightHanded()
    {
        using M = Maths::Matrix4x4<T>;
        using V = Maths::Vec4<T>;
        const M rotation = M::RotationY(std::numbers::pi_v<T> / T{2});
        VectorNear(V{1, 0, 0, 0}, rotation * V{0, 0, 1, 0});
        Near(T{1}, rotation.Determinant());
    }

    template <typename T>
    void RotationZIsRightHanded()
    {
        using M = Maths::Matrix4x4<T>;
        using V = Maths::Vec4<T>;
        const M rotation = M::RotationZ(std::numbers::pi_v<T> / T{2});
        VectorNear(V{0, 1, 0, 0}, rotation * V{1, 0, 0, 0});
        Near(T{1}, rotation.Determinant());
    }

    template <typename T>
    void InverseUsesPivotingAndKnownExpectedValues()
    {
        using M = Maths::Matrix4x4<T>;
        const M matrix = M(std::array<T, 16>{0, 2, 0, 0, 1, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1});
        const M expected = M(std::array<T, 16>{T{-1.5}, 1, 0, 0, T{0.5}, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1});
        const M actual = matrix.Inverse();
        MatrixNear(expected, actual);
        MatrixNear(M::Identity(), matrix * actual);
        MatrixNear(M::Identity(), actual * matrix);
        Near(T{-2}, matrix.Determinant());
    }

    template <typename T>
    void DenseInverseMatchesRationalFixture()
    {
        using M = Maths::Matrix4x4<T>;
        const M matrix = M(std::array<T, 16>{4, 1, -1, 1, 2, 5, 2, 0, 1, -1, 6, -1, 0, 2, 0, 7});
        const M expected = M(std::array<T, 16>{T{44} / T{175}, T{-1} / T{35}, T{9} / T{175}, T{-1} / T{35}, T{-2} / T{25}, T{1} / T{5}, T{-2} / T{25}, T{0} / T{1}, T{-9} / T{175}, T{1} / T{35}, T{26} / T{175}, T{1} / T{35}, T{4} / T{175}, T{-2} / T{35}, T{4} / T{175}, T{1} / T{7}});
        MatrixNear(expected, matrix.Inverse());
    }

    template <typename T>
    void InverseRejectsSingularAndNonFinite()
    {
        using M = Maths::Matrix4x4<T>;
        Assert::ExpectException<std::domain_error>([] { (void)M::Zero().Inverse(); });
        M duplicate;
        for (std::size_t c=0; c<4; ++c)
        {
            duplicate(1,c) = duplicate(0,c);
        }
        Near(T{0}, duplicate.Determinant());
        Assert::ExpectException<std::domain_error>([&] { (void)duplicate.Inverse(); });
        M invalid;
        invalid(0,0) = std::numeric_limits<T>::infinity();
        Assert::ExpectException<std::domain_error>([&] { (void)invalid.Inverse(); });
        invalid(0,0) = std::numeric_limits<T>::quiet_NaN();
        Assert::ExpectException<std::domain_error>([&] { (void)invalid.Inverse(); });
    }

    template <typename T>
    void InverseValidatesTolerance()
    {
        using M = Maths::Matrix4x4<T>;
        Assert::ExpectException<std::invalid_argument>([] { (void)M{}.Inverse(T{-1}); });
        Assert::ExpectException<std::invalid_argument>([] { (void)M{}.Inverse(T{1}); });
        Assert::ExpectException<std::invalid_argument>([] { (void)M{}.Inverse(std::numeric_limits<T>::quiet_NaN()); });
    }

    template <typename T>
    void InverseToleranceCanRejectNearDependentRows()
    {
        using M = Maths::Matrix4x4<T>;
        M matrix;
        matrix(0,0) = T{1};
        matrix(0,1) = T{1};
        matrix(1,0) = T{1};
        matrix(1,1) = T{1} + std::numeric_limits<T>::epsilon();
        Assert::ExpectException<std::domain_error>([&] { (void)matrix.Inverse(); });
    }

    template <typename T>
    void InverseHandlesDifferentRowScales()
    {
        using M = Maths::Matrix4x4<T>;
        M matrix;
        matrix(0,0) = T{0.0001};
        matrix(1,1) = T{10000};
        M expected;
        expected(0,0) = T{10000};
        expected(1,1) = T{0.0001};
        MatrixNear(expected, matrix.Inverse());
    }

    template <typename T>
    void TranslationAffectsPointsButNotDirections()
    {
        using M = Maths::Matrix4x4<T>;
        const M matrix = M::Translation(Maths::Vec3<T>{10,20,30});
        const Maths::Vec3<T> input{1,2,3};
        VectorNear(Maths::Vec3<T>{11,22,33}, matrix.TransformPoint(input));
        VectorNear(input, matrix.TransformDirection(input));
    }

    template <typename T>
    void CompositionAppliesRightMatrixFirst()
    {
        using M = Maths::Matrix4x4<T>;
        const M translate = M::Translation(Maths::Vec3<T>{10,20,30});
        const M scale = M::Scale(Maths::Vec3<T>{2,3,4});
        const Maths::Vec3<T> point{1,2,3};
        VectorNear(Maths::Vec3<T>{12,26,42}, (translate * scale).TransformPoint(point));
        VectorNear(Maths::Vec3<T>{22,66,132}, (scale * translate).TransformPoint(point));
    }

    template <typename T>
    void AffineHelpersRejectPerspective()
    {
        using M = Maths::Matrix4x4<T>;
        M matrix;
        matrix(3,2) = T{1};
        Assert::ExpectException<std::domain_error>([&] { (void)matrix.TransformPoint(Maths::Vec3<T>{1,2,3}); });
        Assert::ExpectException<std::domain_error>([&] { (void)matrix.TransformDirection(Maths::Vec3<T>{1,2,3}); });
    }

}

namespace MathStarterTests
{
    TEST_CLASS(Matrix4x4Tests)
    {
    public:
        TEST_METHOD(DefaultAndFactoryAreIdentity_float)
        {
            DefaultAndFactoryAreIdentity<float>();
        }

        TEST_METHOD(DefaultAndFactoryAreIdentity_double)
        {
            DefaultAndFactoryAreIdentity<double>();
        }

        TEST_METHOD(ConstructorAndIndexUseRowMajorOrder_float)
        {
            ConstructorAndIndexUseRowMajorOrder<float>();
        }

        TEST_METHOD(ConstructorAndIndexUseRowMajorOrder_double)
        {
            ConstructorAndIndexUseRowMajorOrder<double>();
        }

        TEST_METHOD(ArithmeticHasIndependentExpectedValues_float)
        {
            ArithmeticHasIndependentExpectedValues<float>();
        }

        TEST_METHOD(ArithmeticHasIndependentExpectedValues_double)
        {
            ArithmeticHasIndependentExpectedValues<double>();
        }

        TEST_METHOD(MatrixProductHasIndependentExpectedValues_float)
        {
            MatrixProductHasIndependentExpectedValues<float>();
        }

        TEST_METHOD(MatrixProductHasIndependentExpectedValues_double)
        {
            MatrixProductHasIndependentExpectedValues<double>();
        }

        TEST_METHOD(MultiplyAssignSupportsSelfAliasing_float)
        {
            MultiplyAssignSupportsSelfAliasing<float>();
        }

        TEST_METHOD(MultiplyAssignSupportsSelfAliasing_double)
        {
            MultiplyAssignSupportsSelfAliasing<double>();
        }

        TEST_METHOD(MatrixVectorUsesColumnVectorConvention_float)
        {
            MatrixVectorUsesColumnVectorConvention<float>();
        }

        TEST_METHOD(MatrixVectorUsesColumnVectorConvention_double)
        {
            MatrixVectorUsesColumnVectorConvention<double>();
        }

        TEST_METHOD(TransposeMovesEveryElement_float)
        {
            TransposeMovesEveryElement<float>();
        }

        TEST_METHOD(TransposeMovesEveryElement_double)
        {
            TransposeMovesEveryElement<double>();
        }

        TEST_METHOD(EqualityChecksEveryElement_float)
        {
            EqualityChecksEveryElement<float>();
        }

        TEST_METHOD(EqualityChecksEveryElement_double)
        {
            EqualityChecksEveryElement<double>();
        }

        TEST_METHOD(ScaleHasKnownResult_float)
        {
            ScaleHasKnownResult<float>();
        }

        TEST_METHOD(ScaleHasKnownResult_double)
        {
            ScaleHasKnownResult<double>();
        }

        TEST_METHOD(RotationXIsRightHanded_float)
        {
            RotationXIsRightHanded<float>();
        }

        TEST_METHOD(RotationXIsRightHanded_double)
        {
            RotationXIsRightHanded<double>();
        }

        TEST_METHOD(RotationYIsRightHanded_float)
        {
            RotationYIsRightHanded<float>();
        }

        TEST_METHOD(RotationYIsRightHanded_double)
        {
            RotationYIsRightHanded<double>();
        }

        TEST_METHOD(RotationZIsRightHanded_float)
        {
            RotationZIsRightHanded<float>();
        }

        TEST_METHOD(RotationZIsRightHanded_double)
        {
            RotationZIsRightHanded<double>();
        }

        TEST_METHOD(InverseUsesPivotingAndKnownExpectedValues_float)
        {
            InverseUsesPivotingAndKnownExpectedValues<float>();
        }

        TEST_METHOD(InverseUsesPivotingAndKnownExpectedValues_double)
        {
            InverseUsesPivotingAndKnownExpectedValues<double>();
        }

        TEST_METHOD(DenseInverseMatchesRationalFixture_float)
        {
            DenseInverseMatchesRationalFixture<float>();
        }

        TEST_METHOD(DenseInverseMatchesRationalFixture_double)
        {
            DenseInverseMatchesRationalFixture<double>();
        }

        TEST_METHOD(InverseRejectsSingularAndNonFinite_float)
        {
            InverseRejectsSingularAndNonFinite<float>();
        }

        TEST_METHOD(InverseRejectsSingularAndNonFinite_double)
        {
            InverseRejectsSingularAndNonFinite<double>();
        }

        TEST_METHOD(InverseValidatesTolerance_float)
        {
            InverseValidatesTolerance<float>();
        }

        TEST_METHOD(InverseValidatesTolerance_double)
        {
            InverseValidatesTolerance<double>();
        }

        TEST_METHOD(InverseToleranceCanRejectNearDependentRows_float)
        {
            InverseToleranceCanRejectNearDependentRows<float>();
        }

        TEST_METHOD(InverseToleranceCanRejectNearDependentRows_double)
        {
            InverseToleranceCanRejectNearDependentRows<double>();
        }

        TEST_METHOD(InverseHandlesDifferentRowScales_float)
        {
            InverseHandlesDifferentRowScales<float>();
        }

        TEST_METHOD(InverseHandlesDifferentRowScales_double)
        {
            InverseHandlesDifferentRowScales<double>();
        }

        TEST_METHOD(TranslationAffectsPointsButNotDirections_float)
        {
            TranslationAffectsPointsButNotDirections<float>();
        }

        TEST_METHOD(TranslationAffectsPointsButNotDirections_double)
        {
            TranslationAffectsPointsButNotDirections<double>();
        }

        TEST_METHOD(CompositionAppliesRightMatrixFirst_float)
        {
            CompositionAppliesRightMatrixFirst<float>();
        }

        TEST_METHOD(CompositionAppliesRightMatrixFirst_double)
        {
            CompositionAppliesRightMatrixFirst<double>();
        }

        TEST_METHOD(AffineHelpersRejectPerspective_float)
        {
            AffineHelpersRejectPerspective<float>();
        }

        TEST_METHOD(AffineHelpersRejectPerspective_double)
        {
            AffineHelpersRejectPerspective<double>();
        }

    };
}
