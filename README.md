

|         ns/op       |         op/s        |   err%  |   total   |           benchmark         |                 CPU                  |         SSE         |  AVX2   |   FMA   | Observable checksum|
|--------------------:|--------------------:|--------:|----------:|:----------------------------|-------------------------------------:|--------------------:|--------:|--------:|:-------------------|
|              102.40 |        9,766,007.03 |    0.3% |     10.96 | `Matrix3x3 Inverse`         |AMD Ryzen 7 5700G with Radeon Graphics|     true            |    true |     true| 108942.256         |
|                9.44 |      105,944,583.45 |    0.1% |     10.98 | `Matrix3x3 Simd Inverse`    |AMD Ryzen 7 5700G with Radeon Graphics|     true            |    true |     true| 108942.256         |
|               15.43 |       64,807,234.46 |    0.6% |     11.10 | `Matrix3x3 Determinant`     |AMD Ryzen 7 5700G with Radeon Graphics|     true            |    true |     true| 108942.256         |
|                1.94 |      515,021,188.40 |    0.0% |     11.12 | `Matrix3x3 Simd Determinant`|AMD Ryzen 7 5700G with Radeon Graphics|     true            |    true |     true| 108942.256         |
