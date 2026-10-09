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

extern "C" void Vec3_Add(const Maths::Vec3S* a, const Maths::Vec3S* b, Maths::Vec3S* out);

int main(const int _argc, char** _argv)
{
    using Maths::Vec3S;
    using Maths::Vec4;
    using Maths::Matrix4x4;
    Vec3S a{ 1.f,2.f,3.f };
    Vec3S b{ 4.f,5.f,6.f };
    Vec3S c = a * 2.f;
    std::cout << "idk: " << a.y << '\n';
    const auto matrix = Matrix4x4<>::Translation({ 10,20,30 }) * Matrix4x4<>::Scale({ 2,3,4 });
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
    std::vector<Maths::Matrix4x4<float>> Matrix4x4Cpp(count);

    for (std::size_t i = 0; i < count; ++i)
    {
        const float ax = distribution(engine);
        const float ay = distribution(engine);
        const float az = distribution(engine);
        const float aw = distribution(engine);

        const float bx = distribution(engine);
        const float by = distribution(engine);
        const float bz = distribution(engine);
        const float bw = distribution(engine);

        Vec4CppA[i] = { ax, ay, az, aw };
        Vec4SIMDA[i] = { ax, ay, az, aw };

        Vec4CppB[i] = { bx, by, bz, bw };
        Vec4SIMDB[i] = { bx, by, bz, bw };


        const std::array<float, 16> matrix4x4Array =
        {
            distribution(engine), distribution(engine), distribution(engine), distribution(engine),
            distribution(engine), distribution(engine), distribution(engine), distribution(engine),
            distribution(engine), distribution(engine), distribution(engine), distribution(engine),
            distribution(engine), distribution(engine), distribution(engine), distribution(engine)
        };

        Matrix4x4Cpp[i] = Maths::Matrix4x4<float>(matrix4x4Array);
        Matrix4x4SIMD[i] = Maths::Matrix4x4SIMD(matrix4x4Array);
    }


    const auto result = Benchmark::Run([&]
        {
            //Endroit ou mettre les fonctions a benchmarker si besoin des cout pour tester certaine value sur les fonctions
        }
        // Included in the measured time. Simple and observable, not a magic barrier.
        double checksum = 0;
        for (const auto& v : outputCpp)
        {
            checksum += static_cast<double>(v.x) + v.y + v.z + v.w;
        }
        return checksum;
        
		
    });



    std::cout << std::fixed << std::setprecision(3)
        << "Seed: " << seed <<'\n'
        << "Batch incl. checksum: min " << result.minimumMs
        << " ms, median " << result.medianMs
        << " ms, max " << result.maximumMs << " ms\n"
        //<< "Observable checksum: " << result.checksum << '\n'
        << "Build: " << "Release x64" << '\n'
        << "Batch Size: " << count  << '\n'
        << "Warmup Size: " << "10"  << '\n'
        << "Epochs Size: " << "100"<< '\n';

    ankerl::nanobench::Bench bench;
    bench.epochs(100);
    bench.warmup(10);


    bench.run("Normalize C++", [&]
        {
            double checksum = 0.0;

            for (std::size_t i = 0; i < count; ++i)
            {
                outputCpp[i] = Vec4CppA[i].Normalize();

                checksum += static_cast<double>(outputCpp[i].x)
                    + outputCpp[i].y
                    + outputCpp[i].z
                    + outputCpp[i].w;
            }
			
            ankerl::nanobench::doNotOptimizeAway(checksum);
        });

    bench.run("Normalize SIMD", [&]
        {
            double checksum = 0.0;

            for (std::size_t i = 0; i < count; ++i)
            {
                outputSIMD[i] = Vec4SIMDA[i].Normalize();

                checksum += static_cast<double>(outputSIMD[i].x)
                    + outputSIMD[i].y
                    + outputSIMD[i].z
                    + outputSIMD[i].w;
            }

            ankerl::nanobench::doNotOptimizeAway(checksum);

        });


    //bench.run("Dot C++", [&]
    //    {
    //        double checksum = 0.0;

    //        for (std::size_t i = 0; i < count; ++i)
    //        {
    //            const float result = Vec4CppA[i].Dot(Vec4CppB[i]);

    //            checksum += static_cast<double>(result);
    //        }

    //        ankerl::nanobench::doNotOptimizeAway(checksum);
    //    });


    //bench.run("Dot SIMD", [&]
    //    {
    //        double checksum = 0.0;

    //        for (std::size_t i = 0; i < count; ++i)
    //        {
    //            const float result = Vec4SIMDA[i].Dot(Vec4SIMDB[i]);

    //            checksum += static_cast<double>(result);
    //        }

    //        ankerl::nanobench::doNotOptimizeAway(checksum);
    //    });
   

    //bench.run("Matrix4x4 * Vec4 C++", [&]
    //    {
    //        double checksum = 0.0;

    //        for (std::size_t i = 0; i < count; ++i)
    //        {
    //            outputCpp[i] = Matrix4x4Cpp[i].operator*(Vec4CppA[i]);

    //            checksum += static_cast<double>(outputCpp[i].x)
    //                + outputCpp[i].y
    //                + outputCpp[i].z
    //                + outputCpp[i].w;
    //        }

    //        ankerl::nanobench::doNotOptimizeAway(checksum);
    //    });

    //bench.run("Matrix4x4 * Vec4 SIMD", [&]
    //    {
    //        double checksum = 0.0;

    //        for (std::size_t i = 0; i < count; ++i)
    //        {
    //            outputSIMD[i] = Matrix4x4SIMD[i].operator*(Vec4SIMDA[i]);

    //            checksum += static_cast<double>(outputSIMD[i].x)
    //                + outputSIMD[i].y
    //                + outputSIMD[i].z
    //                + outputSIMD[i].w;
    //        }

    //        ankerl::nanobench::doNotOptimizeAway(checksum);
    //    });

    Maths::Vec3S g(1, 2, 3), s(4, 5, 6), r;
    Vec3_Add(&g, &s, &r);
    std::cout << r.x << r.y << r.z << std::endl;*/
}
