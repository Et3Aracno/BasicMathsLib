#include "TestHelpers.h"
#include "MathLibrary/Matrix3x3.h"
#include <numbers>
#include <type_traits>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace TestHelpers;

namespace
{
    template <typename T>
    void DefaultAndFactoryAreIdentity()
    {
        using M = Maths::Matrix3x3<T>;
        const M expected = M(std::array<T, 9>{1, 0, 0, 0, 1, 0, 0, 0, 1});
        MatrixNear(expected, M{});
        MatrixNear(expected, M::Identity());
        MatrixNear(M(std::array<T, 9>{0, 0, 0, 0, 0, 0, 0, 0, 0}), M::Zero());
    }

    template <typename T>
    void ConstructorAndIndexUseRowMajorOrder()
    {
        using M = Maths::Matrix3x3<T>;
        M matrix = M(std::array<T, 9>{1, 2, 3, 4, 5, 6, 7, 8, 9});
        Near(T{2}, matrix(0, 1));
        Near(T{4}, matrix(1, 0));
        matrix(1, 0) = T{99};
        const M& view = matrix;
        Near(T{99}, view(1, 0));
        Assert::ExpectException<std::out_of_range>([&] { (void)matrix(3, 0); });
        Assert::ExpectException<std::out_of_range>([&] { (void)view(0, 3); });
    }

    template <typename T>
    void ArithmeticHasIndependentExpectedValues()
    {
        using M = Maths::Matrix3x3<T>;
        const M a = M(std::array<T, 9>{1, 2, 3, 4, 5, 6, 7, 8, 9});
        const M b = M(std::array<T, 9>{-1, 2, -2, 1, -3, 0, 3, -1, 2});
        MatrixNear(M(std::array<T, 9>{0, 4, 1, 5, 2, 6, 10, 7, 11}), a + b);
        MatrixNear(M(std::array<T, 9>{2, 0, 5, 3, 8, 6, 4, 9, 7}), a - b);
        MatrixNear(M(std::array<T, 9>{2, 4, 6, 8, 10, 12, 14, 16, 18}), a * T{2});
    }

    template <typename T>
    void MatrixProductHasIndependentExpectedValues()
    {
        using M = Maths::Matrix3x3<T>;
        const M a = M(std::array<T, 9>{1, 2, 3, 4, 5, 6, 7, 8, 9});
        const M b = M(std::array<T, 9>{-1, 2, -2, 1, -3, 0, 3, -1, 2});
        const M expected = M(std::array<T, 9>{10, -7, 4, 19, -13, 4, 28, -19, 4});
        MatrixNear(expected, a * b);
        Assert::IsTrue(a * b != b * a);
    }

    template <typename T>
    void MultiplyAssignSupportsSelfAliasing()
    {
        using M = Maths::Matrix3x3<T>;
        M matrix = M(std::array<T, 9>{1, 2, 3, 4, 5, 6, 7, 8, 9});
        Assert::IsTrue(&(matrix *= matrix) == &matrix);
        MatrixNear(M(std::array<T, 9>{30, 36, 42, 66, 81, 96, 102, 126, 150}), matrix);
    }

    template <typename T>
    void MatrixVectorUsesColumnVectorConvention()
    {
        using M = Maths::Matrix3x3<T>;
        using V = Maths::Vec3<T>;
        const M matrix = M(std::array<T, 9>{1, 2, 3, 4, 5, 6, 7, 8, 9});
        const V vector{1, 2, 3};
        VectorNear(V{14, 32, 50}, matrix * vector);
    }

    template <typename T>
    void TransposeMovesEveryElement()
    {
        using M = Maths::Matrix3x3<T>;
        const M matrix = M(std::array<T, 9>{1, 2, 3, 4, 5, 6, 7, 8, 9});
        MatrixNear(M(std::array<T, 9>{1, 4, 7, 2, 5, 8, 3, 6, 9}), matrix.Transpose());
    }

    template <typename T>
    void EqualityChecksEveryElement()
    {
        using M = Maths::Matrix3x3<T>;
        const M a;
        for (std::size_t r=0; r<3; ++r)
        {
            for (std::size_t c=0; c<3; ++c)
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
        using M = Maths::Matrix3x3<T>;
        const M scale = M::Scale(Maths::Vec3<T>{2,3,4});
        MatrixNear(M(std::array<T, 9>{2, 0, 0, 0, 3, 0, 0, 0, 4}), scale);
        Near(T{24}, scale.Determinant());
    }

    template <typename T>
    void RotationXIsRightHanded()
    {
        using M = Maths::Matrix3x3<T>;
        using V = Maths::Vec3<T>;
        const M rotation = M::RotationX(std::numbers::pi_v<T> / T{2});
        VectorNear(V{0, 0, 1}, rotation * V{0, 1, 0});
        Near(T{1}, rotation.Determinant());
    }

    template <typename T>
    void RotationYIsRightHanded()
    {
        using M = Maths::Matrix3x3<T>;
        using V = Maths::Vec3<T>;
        const M rotation = M::RotationY(std::numbers::pi_v<T> / T{2});
        VectorNear(V{1, 0, 0}, rotation * V{0, 0, 1});
        Near(T{1}, rotation.Determinant());
    }

    template <typename T>
    void RotationZIsRightHanded()
    {
        using M = Maths::Matrix3x3<T>;
        using V = Maths::Vec3<T>;
        const M rotation = M::RotationZ(std::numbers::pi_v<T> / T{2});
        VectorNear(V{0, 1, 0}, rotation * V{1, 0, 0});
        Near(T{1}, rotation.Determinant());
    }

    template <typename T>
    void InverseUsesPivotingAndKnownExpectedValues()
    {
        using M = Maths::Matrix3x3<T>;
        const M matrix = M(std::array<T, 9>{0, 2, 0, 1, 3, 0, 0, 0, 1});
        const M expected = M(std::array<T, 9>{T{-1.5}, 1, 0, T{0.5}, 0, 0, 0, 0, 1});
        const M actual = matrix.Inverse();
        MatrixNear(expected, actual);
        MatrixNear(M::Identity(), matrix * actual);
        MatrixNear(M::Identity(), actual * matrix);
        Near(T{-2}, matrix.Determinant());
    }

    template <typename T>
    void DenseInverseMatchesRationalFixture()
    {
        using M = Maths::Matrix3x3<T>;
        const M matrix = M(std::array<T, 9>{4, 1, -1, 2, 5, 2, 1, -1, 6});
        const M expected = M(std::array<T, 9>{T{32} / T{125}, T{-1} / T{25}, T{7} / T{125}, T{-2} / T{25}, T{1} / T{5}, T{-2} / T{25}, T{-7} / T{125}, T{1} / T{25}, T{18} / T{125}});
        MatrixNear(expected, matrix.Inverse());
    }

    template <typename T>
    void InverseRejectsSingularAndNonFinite()
    {
        using M = Maths::Matrix3x3<T>;
        Assert::ExpectException<std::domain_error>([] { (void)M::Zero().Inverse(); });
        M duplicate;
        for (std::size_t c=0; c<3; ++c)
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
        using M = Maths::Matrix3x3<T>;
        Assert::ExpectException<std::invalid_argument>([] { (void)M{}.Inverse(T{-1}); });
        Assert::ExpectException<std::invalid_argument>([] { (void)M{}.Inverse(T{1}); });
        Assert::ExpectException<std::invalid_argument>([] { (void)M{}.Inverse(std::numeric_limits<T>::quiet_NaN()); });
    }

    template <typename T>
    void InverseToleranceCanRejectNearDependentRows()
    {
        using M = Maths::Matrix3x3<T>;
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
        using M = Maths::Matrix3x3<T>;
        M matrix;
        matrix(0,0) = T{0.0001};
        matrix(1,1) = T{10000};
        M expected;
        expected(0,0) = T{10000};
        expected(1,1) = T{0.0001};
        MatrixNear(expected, matrix.Inverse());
    }

}

namespace MathStarterTests
{
    TEST_CLASS(Matrix3x3Tests)
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

    };
}
