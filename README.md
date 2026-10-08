# Technical Benchmark





## Context


## Benchmark
lot : 250 000  
  
idk: 2
CPU: GenuineIntel / Intel(R) Core(TM) i5-14600KF
SSE usable: true
AVX2 usable: true
FMA usable: true
Seed: 2629990972, vectors per batch: 250000
Batch incl. checksum: min 0.225 ms, median 0.227 ms, max 0.233 ms
Observable checksum: 0.000
Build: Release x640.000
Batch Size: 2500000.000
Warmup Size: 100.000
Epochs Size: 1000.000

|               ns/op |                op/s |    err% |     total | benchmark
|--------------------:|--------------------:|--------:|----------:|:----------
|        9,627,150.00 |              103.87 |    0.8% |      0.97 | `Normalize C++`
|        1,757,850.00 |              568.88 |    1.6% |      0.18 | `Normalize SIMD`
|          221,695.00 |            4,510.70 |    3.0% |      0.11 | `Dot C++`
|          315,812.50 |            3,166.44 |    0.6% |      0.11 | `Dot SIMD`
|        1,502,600.00 |              665.51 |    5.4% |      0.14 | :wavy_dash: `Matrix4x4 * Vec4 C++` (Unstable with ~1.0 iters. Increase `minEpochIterations` to e.g. 10)
|        1,334,600.00 |              749.29 |   11.2% |      0.13 | :wavy_dash: `Matrix4x4 * Vec4 SIMD` (Unstable with ~1.0 iters. Increase `minEpochIterations` to e.g. 10)


  Lot : 2000  
idk: 2
CPU: GenuineIntel / Intel(R) Core(TM) i5-14600KF
SSE usable: true
AVX2 usable: true
FMA usable: true
Seed: 1487105735, vectors per batch: 2000
Batch incl. checksum: min 0.002 ms, median 0.002 ms, max 0.002 ms
Observable checksum: 0.000
Build: Release x640.000
Batch Size: 2500000.000
Warmup Size: 100.000
Epochs Size: 1000.000

|               ns/op |                op/s |    err% |     total | benchmark
|--------------------:|--------------------:|--------:|----------:|:----------
|           76,299.45 |           13,106.25 |    1.0% |      0.11 | `Normalize C++`
|           40,535.86 |           24,669.52 |    0.4% |      0.11 | `Normalize SIMD`
|            1,701.42 |          587,745.50 |    0.9% |      0.11 | `Dot C++`
|            2,529.32 |          395,363.01 |    0.8% |      0.11 | `Dot SIMD`
|            8,031.86 |          124,504.09 |    1.1% |      0.11 | `Matrix4x4 * Vec4 C++`
|            7,643.90 |          130,823.24 |    1.0% |      0.11 | `Matrix4x4 * Vec4 SIMD`


  
  Lot : 20  
idk: 2
CPU: GenuineIntel / Intel(R) Core(TM) i5-14600KF
SSE usable: true
AVX2 usable: true
FMA usable: true
Seed: 4027332694, vectors per batch: 20
Batch incl. checksum: min 0.000 ms, median 0.000 ms, max 0.000 ms
Observable checksum: 0.000
Build: Release x640.000
Batch Size: 2500000.000
Warmup Size: 100.000
Epochs Size: 1000.000

|               ns/op |                op/s |    err% |     total | benchmark
|--------------------:|--------------------:|--------:|----------:|:----------
|              762.65 |        1,311,212.12 |    0.8% |      0.11 | `Normalize C++`
|              150.50 |        6,644,507.17 |    0.7% |      0.11 | `Normalize SIMD`
|               16.28 |       61,420,641.83 |    0.2% |      0.11 | `Dot C++`
|               25.29 |       39,545,371.72 |    1.6% |      0.11 | `Dot SIMD`
|               78.39 |       12,757,028.08 |    1.5% |      0.11 | `Matrix4x4 * Vec4 C++`
|               73.98 |       13,517,474.51 |    0.3% |      0.11 | `Matrix4x4 * Vec4 SIMD`


## Analysis


