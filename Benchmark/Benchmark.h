#pragma once

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <functional>
#include <stdexcept>
#include <vector>

namespace Benchmark
{
    struct Settings
    {
        std::size_t warmupCount = 2;
        std::size_t sampleCount = 9;
    };

    struct Result
    {
        std::vector<double> milliseconds;
        double minimumMs = 0;
        double medianMs = 0;
        double maximumMs = 0;
        double checksum = 0;
    };

    // One callback = one complete batch. Input creation belongs outside Run().
    // work() returns a checksum depending on ALL its computed results.
    // Print/use Result::checksum. This is not a portable optimization barrier.
    template <typename Work>
    Result Run(Work&& work, const Settings settings = {})
    {
        if (settings.sampleCount == 0)
        {
            throw std::invalid_argument("A benchmark needs at least one sample");
        }
        Result result;
        result.milliseconds.reserve(settings.sampleCount);

        for (std::size_t i = 0; i < settings.warmupCount; ++i)
        {
            result.checksum += static_cast<double>(std::invoke(work));
        }
        for (std::size_t i = 0; i < settings.sampleCount; ++i)
        {
            const auto start = std::chrono::steady_clock::now();
            const double checksum = static_cast<double>(std::invoke(work));
            const auto end = std::chrono::steady_clock::now();

            result.checksum += checksum;
            result.milliseconds.push_back(
                std::chrono::duration<double, std::milli>(end - start).count());
        }
        if (!std::isfinite(result.checksum))
        {
            throw std::runtime_error("Benchmark checksum is not finite");
        }

        auto sorted = result.milliseconds;
        std::sort(sorted.begin(), sorted.end());
        result.minimumMs = sorted.front();
        result.maximumMs = sorted.back();
        const std::size_t middle = sorted.size() / 2;
        result.medianMs = sorted[middle];
        if (sorted.size() % 2 == 0)
        {
            result.medianMs = sorted[middle - 1] / 2 + sorted[middle] / 2;
        }
        return result;
    }
}
