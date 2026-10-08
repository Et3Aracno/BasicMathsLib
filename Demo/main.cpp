#include "Benchmark/Benchmark.h"
#include "Platform/CpuFeatures.h"
#include "MathLibrary/MathLib.h"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>
#define ANKERL_NANOBENCH_IMPLEMENT
#include "External Lib/nanobench.h"
Maths::Vec4 Vct4A;
Maths::Vec4 Vct4B;
Maths::Vec4S Vct4ASIMD{ 1,2,3,4 };
Maths::Vec4S Vct4BSIMD{ 5,6,7,8 };

std::vector<Maths::Vec4<float>> Vec4vctA(10);
std::vector<Maths::Vec4<float>> Vec4vctB(10);
std::vector<Maths::Vec4<float>> outputCpp(10);
std::vector<Maths::Vec4S> outputSIMD(10);


float DotSIMD(const std::vector<Maths::Vec4S>& A, const std::vector<Maths::Vec4S>& B) {
    
        float result = 0.0f;

        for (std::size_t i = 0; i < A.size(); ++i)
        {
            result += A[i].Dot(B[i]);
        }
        return result;
    
}

float DotCpp(const std::vector<Maths::Vec4<float>>& A, const std::vector<Maths::Vec4<float>>& B) {
    
        float result = 0.0f;

        for (std::size_t i = 0; i < A.size(); ++i)
        {
            result += A[i].Dot(B[i]);
        }

        return result;
    
}

int main(const int _argc, char** _argv)
{
    using Maths::Vec3S;
    using Maths::Vec4;
    using Maths::Matrix4x4;
    Vec3S a{1.f,2.f,3.f};
    Vec3S b{4.f,5.f,6.f};
    Vec3S c = a * 2.f;
    std::cout << "idk: " << a.y << '\n';
    const auto matrix = Matrix4x4<>::Translation({10,20,30}) * Matrix4x4<>::Scale({2,3,4});
    //const auto point = matrix.TransformPoint(a);
    //std::cout << "Point: " << point.x << ", " << point.y << ", " << point.z << '\n';

#if defined(_MSC_VER) && (defined(_M_IX86) || defined(_M_X64))
    const auto cpu = Platform::CpuFeatures::Detect();
    std::cout << "CPU: " << cpu.Vendor() << " / " << cpu.Brand() << '\n';
    std::cout << std::boolalpha
              << "SSE usable: " << cpu.CanUse(Platform::CpuFeature::SSE) << '\n'
              << "AVX2 usable: " << cpu.CanUse(Platform::CpuFeature::AVX2) << '\n'
              << "FMA usable: " << cpu.CanUse(Platform::CpuFeature::FMA) << '\n';
#else
    std::cout << "CPU detection demo is MSVC/Windows-only.\n";


#endif

    // Runtime inputs. Optional integer seed allows reproducing a run.
    const auto seed = _argc > 1 ? static_cast<unsigned int>(std::strtoul(_argv[1], nullptr, 10))
                              : std::random_device{}();
    std::mt19937 engine(seed);
    std::uniform_real_distribution<float> distribution(-10.0f, 10.0f);
    const std::size_t count = 250000;
    std::vector<Vec4<>> Vec4CppA(count);
    std::vector<Vec4<>> Vec4CppB(count);
    std::vector<Vec4<>> outputCpp(count);
    std::vector<Maths::Vec4S> Vec4SIMDA(count);
    std::vector<Maths::Vec4S> Vec4SIMDB(count);
    std::vector<Maths::Vec4S> outputSIMD(count);
    std::vector<Maths::Matrix4x4SIMD> Matrix4x4SIMD(count);

    for (std::size_t i = 0; i < count; ++i)
    {
        Vec4CppA[i] = {distribution(engine), distribution(engine), distribution(engine), distribution(engine)};
        Vec4CppB[i] = {distribution(engine), distribution(engine), distribution(engine), distribution(engine)};
        Vec4SIMDA[i] = {distribution(engine), distribution(engine), distribution(engine), distribution(engine)};
        Vec4SIMDB[i] = {distribution(engine), distribution(engine), distribution(engine), distribution(engine)};
        Matrix4x4SIMD[i] = {distribution(engine), distribution(engine), distribution(engine), distribution(engine)};
    }





    const auto result = Benchmark::Run([&]
    {
        for (std::size_t i = 0; i < count; ++i)
        {
            //là ou on va mettre les fonctions 

        }
        // Included in the measured time. Simple and observable, not a magic barrier.
        double checksum = 0;
        for (const auto& v : output)
        {
            checksum += static_cast<double>(v.x) + v.y + v.z + v.w;
        }
        return checksum;
    });

    std::cout << std::fixed << std::setprecision(3)
        << "Seed: " << seed << ", vectors per batch: " << count << '\n'
        << "Batch incl. checksum: min " << result.minimumMs
        << " ms, median " << result.medianMs
        << " ms, max " << result.maximumMs << " ms\n"
        << "Observable checksum: " << result.checksum << '\n'
        << "Build: " << "Release x64" << result.checksum << '\n'
        << "Batch Size: " << "1000000" << result.checksum << '\n'
        << "Warmup Size: " << "10" << result.checksum << '\n'
        << "Epochs Size: "<< "100" << result.checksum << '\n';

    ankerl::nanobench::Bench bench;
    bench.epochs(1000);
    bench.warmup(10);

   

    //bench.run("Dot Vec4 C++", [&] {
    //    const auto result = DotCpp(Vec4vctA, Vec4vctB);
    //    ankerl::nanobench::doNotOptimizeAway(result);
    //    });

    //bench.run("Dot Vec4 SIMD", [&] {
    //    const auto result = DotSIMD(Vec4SIMDA, Vec4SIMDB);
    //    ankerl::nanobench::doNotOptimizeAway(result);
    //    });

}

/*
bench.run("Matrix3x3 Add", [&] {
    auto result = Matrix3x3A + Matrix3x3B;
    ankerl::nanobench::doNotOptimizeAway(result);
    });

bench.run("Matrix3x3 SIMD Add", [&] {
    auto result = Matrix3x3SIMDA + Matrix3x3SIMDB;
    ankerl::nanobench::doNotOptimizeAway(result);
    });


bench.run("Matrix3x3 Subtract", [&] {
    auto result = Matrix3x3A - Matrix3x3B;
    ankerl::nanobench::doNotOptimizeAway(result);
    });

bench.run("Matrix3x3 SIMD Subtract", [&] {
    auto result = Matrix3x3SIMDA - Matrix3x3SIMDB;
    ankerl::nanobench::doNotOptimizeAway(result);
    });


bench.run("Matrix3x3 Multiply", [&] {
    auto result = Matrix3x3A * Matrix3x3B;
    ankerl::nanobench::doNotOptimizeAway(result);
    });

bench.run("Matrix3x3 SIMD Multiply", [&] {
    auto result = Matrix3x3SIMDA * Matrix3x3SIMDB;
    ankerl::nanobench::doNotOptimizeAway(result);
    });

bench.run("Matrix3x3 Scalar Multiply", [&] {
    auto result = Matrix3x3A * scalarValue;
    ankerl::nanobench::doNotOptimizeAway(result);
    });

bench.run("Matrix3x3 SIMD Scalar Multiply", [&] {
    auto result = Matrix3x3SIMDA * scalarValue;
    ankerl::nanobench::doNotOptimizeAway(result);
    });

bench.run("Matrix3x3 Transpose", [&] {
    auto result = Matrix3x3A.Transpose();
    ankerl::nanobench::doNotOptimizeAway(result);
    });

bench.run("Matrix3x3 SIMD Transpose", [&] {
    auto result = Matrix3x3SIMDA.Transpose();
    ankerl::nanobench::doNotOptimizeAway(result);
    });

bench.run("Matrix3x3 Determinant", [&] {
    auto result = Matrix3x3A.Determinant();
    ankerl::nanobench::doNotOptimizeAway(result);
    });

bench.run("Matrix3x3 SIMD Determinant", [&] {
    auto result = Matrix3x3SIMDA.Determinant();
    ankerl::nanobench::doNotOptimizeAway(result);
    });


bench.run("Matrix3x3 Inverse", [&] {
    auto result = Matrix3x3A.Inverse();
    ankerl::nanobench::doNotOptimizeAway(result);
    });

bench.run("Matrix3x3 SIMD Inverse", [&] {
    auto result = Matrix3x3SIMDA.Inverse();
    ankerl::nanobench::doNotOptimizeAway(result);
    });*/
