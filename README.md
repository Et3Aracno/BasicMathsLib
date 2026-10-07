# Technical Benchmark





## Context







## Matrix

### Matrix 4x4









### Matrix 3x3

CPU: AuthenticAMD / AMD Ryzen 7 5700G with Radeon Graphics
SSE usable: true
AVX2 usable: true
FMA usable: true
Seed: 739805003, vectors per batch: 250000
Batch incl. checksum: min 0.719 ms, median 0.958 ms, max 1.299 ms
Observable checksum: -83346.152

|               ns/op |                op/s |    err% |     total | benchmark
|--------------------:|--------------------:|--------:|----------:|:----------
|                5.82 |      171,719,680.50 |    0.0% |      2.14 | `Matrix3x3 Add`
|                1.51 |      662,325,923.20 |    0.0% |      2.19 | `Matrix3x3 SIMD Add`
|                5.82 |      171,722,099.66 |    0.0% |      2.20 | `Matrix3x3 Subtract`
|                1.51 |      662,325,402.01 |    0.0% |      2.20 | `Matrix3x3 SIMD Subtract`
|                8.42 |      118,694,372.42 |    0.1% |      2.21 | `Matrix3x3 Multiply`
|                2.16 |      463,529,547.56 |    0.0% |      2.19 | `Matrix3x3 SIMD Multiply`
|                5.82 |      171,735,522.50 |    0.0% |      2.20 | `Matrix3x3 Scalar Multiply`
|                1.51 |      662,324,743.72 |    0.0% |      2.20 | `Matrix3x3 SIMD Scalar Multiply`
|                5.82 |      171,758,236.88 |    0.0% |      2.20 | `Matrix3x3 Transpose`
|                1.51 |      662,331,844.12 |    0.0% |      2.20 | `Matrix3x3 SIMD Transpose`
|               23.79 |       42,027,726.38 |    0.1% |      2.20 | `Matrix3x3 Determinant`
|                1.94 |      515,022,382.28 |    0.0% |      2.20 | `Matrix3x3 SIMD Determinant`
|              104.10 |        9,606,389.17 |    0.3% |      2.27 | `Matrix3x3 Inverse`
|                9.46 |      105,719,963.87 |    0.1% |      2.20 | `Matrix3x3 SIMD Inverse`
  
  
## Vector



### Vector 3





### Vector 4



