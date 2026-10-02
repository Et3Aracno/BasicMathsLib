#include "Benchmark/Benchmark.h"
#include "Platform/CpuFeatures.h"
#include "MathLibrary/MathLib.h"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

int main(const int _argc, char** _argv)
{
    using Maths::Vec3;
    using Maths::Vec4;
    using Maths::Matrix4x4;
    const Vec3<> a{1.f,2.f,3.f};
    const Vec3<> b{4.f,5.f,6.f};
    std::cout << "Hypot: " << std::hypot(8.f, 6.f) << '\n';
    const auto matrix = Matrix4x4<>::Translation({10,20,30}) * Matrix4x4<>::Scale({2,3,4});
    const auto point = matrix.TransformPoint(a);
    std::cout << "Point: " << point.x << ", " << point.y << ", " << point.z << '\n';

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
    std::vector<Vec4<>> left(count);
    std::vector<Vec4<>> right(count);
    std::vector<Vec4<>> output(count);
    for (std::size_t i = 0; i < count; ++i)
    {
        left[i] = {distribution(engine), distribution(engine), distribution(engine), distribution(engine)};
        right[i] = {distribution(engine), distribution(engine), distribution(engine), distribution(engine)};
    }

    const auto result = Benchmark::Run([&]
    {
        for (std::size_t i = 0; i < count; ++i)
        {
            output[i] = left[i] + right[i];
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
              << "Observable checksum: " << result.checksum << '\n';
}
