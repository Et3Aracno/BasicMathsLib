# Technical Benchmark





## Context







## Matrix

### Matrix 4x4

CPU: GenuineIntel / Intel(R) Core(TM) i5-14600KF
SSE usable: true
AVX2 usable: true
FMA usable: true
Seed: 3087803272, vectors per batch: 250000
Batch incl. checksum: min 0.545 ms, median 0.559 ms, max 0.600 ms
Observable checksum: 86413.074
Epochs : 2000
Matrix Value : Default  

|               ns/op |                op/s |    err% |     total | benchmark
|--------------------:|--------------------:|--------:|----------:|:----------
|                1.52 |      659,572,854.36 |    0.2% |      2.21 | `Matrix4x4 * Vec4`
|                2.27 |      440,033,378.97 |    0.2% |      2.21 | `Matrix4x4 SIMD * Vec4 SIMD`







### Matrix 3x3  
Les mêmes valeurs et le meme matériel sont utilisées pour les versions C++ et SIMD afin de garantir des conditions de comparaison identiques.
CPU: GenuineIntel / Intel(R) Core(TM) i5-14600KF
SSE usable: true
AVX2 usable: true
FMA usable: true
Seed: 4105796076, vectors per batch: 250000
Batch incl. checksum: min 0.580 ms, median 0.596 ms, max 0.821 ms
Observable checksum: -6347.378
Epochs : 2000
Matrix Values :   


#### Matrice A

|   | Colonne 1 | Colonne 2 | Colonne 3 |
|---|---:|---:|---:|
| **Ligne 1** | 1 | 2 | 3 |
| **Ligne 2** | 4 | 5 | 6 |
| **Ligne 3** | 7 | 8 | 10 |

#### Matrice B

|   | Colonne 1 | Colonne 2 | Colonne 3 |
|---|---:|---:|---:|
| **Ligne 1** | 2 | 4 | 1 |
| **Ligne 2** | 3 | 1 | 5 |
| **Ligne 3** | 6 | 2 | 4 |

La version C++ utilise les matrices `Matrix3x3<float>` tandis que la version SIMD utilise les mêmes valeurs avec `Matrix3x3SIMD`.


|               ns/op |                op/s |    err% |     total | benchmark
|--------------------:|--------------------:|--------:|----------:|:----------
|                1.21 |      823,276,157.18 |    0.2% |      2.18 | `Matrix3x3 Add`
|                0.57 |    1,758,139,712.36 |    0.3% |      2.19 | `Matrix3x3 SIMD Add`
|                1.21 |      823,623,590.44 |    0.1% |      2.20 | `Matrix3x3 Subtract`
|                0.57 |    1,760,653,520.28 |    0.1% |      2.20 | `Matrix3x3 SIMD Subtract`
|                3.79 |      264,106,048.03 |    0.1% |      2.20 | `Matrix3x3 Multiply`
|                1.57 |      638,567,123.78 |    0.5% |      2.20 | `Matrix3x3 SIMD Multiply`
|                0.57 |    1,760,788,352.47 |    0.1% |      2.20 | `Matrix3x3 Scalar Multiply`
|                0.63 |    1,583,995,496.02 |    0.2% |      2.20 | `Matrix3x3 SIMD Scalar Multiply`
|                1.14 |      880,355,581.15 |    0.1% |      2.19 | `Matrix3x3 Transpose`
|                0.66 |    1,508,128,109.08 |    0.2% |      2.20 | `Matrix3x3 SIMD Transpose`
|               11.66 |       85,728,069.86 |    0.8% |      2.20 | `Matrix3x3 Determinant`
|                1.54 |      649,998,126.85 |    0.1% |      2.20 | `Matrix3x3 SIMD Determinant`
|               59.56 |       16,790,216.58 |    0.4% |      2.20 | `Matrix3x3 Inverse`
|                5.69 |      175,655,701.09 |    0.1% |      2.20 | `Matrix3x3 SIMD Inverse`
  
  
## Vector



### Vector 3





### Vector 4

CPU: GenuineIntel / Intel(R) Core(TM) i5-14600KF
SSE usable: true
AVX2 usable: true
FMA usable: true
Seed: 1429762907, vectors per batch: 250000
Batch incl. checksum: min 0.544 ms, median 0.563 ms, max 0.599 ms
Observable checksum: 41821.994
Epochs : 2000
Vector values : {1.0f, 2.0f, 3.0f, 4.0f};

|               ns/op |                op/s |    err% |     total | benchmark
|--------------------:|--------------------:|--------:|----------:|:----------
|                0.69 |    1,440,618,017.11 |    0.1% |      2.20 | `Dot Vec4`
|                0.76 |    1,320,577,446.69 |    0.1% |      2.19 | `Dot Vec4S`  
Text  


CPU: GenuineIntel / Intel(R) Core(TM) i5-14600KF
SSE usable: true
AVX2 usable: true
FMA usable: true
Seed: 1310429572, vectors per batch: 250000
Batch incl. checksum: min 0.663 ms, median 0.732 ms, max 0.856 ms
Observable checksum: 3859.420
Epochs : 2000
Vector values : {1.0f, 2.0f, 3.0f, 4.0f};

|               ns/op |                op/s |    err% |     total | benchmark
|--------------------:|--------------------:|--------:|----------:|:----------
|               34.77 |       28,756,729.20 |    0.1% |      2.20 | `Normalize Vec4`
|                8.34 |      119,933,805.50 |    1.1% |      2.21 | `Normalize Vec4SIMD`
  
|               ns/op |                op/s |    err% |     total | benchmark
|--------------------:|--------------------:|--------:|----------:|:----------
|               34.77 |       28,756,729.20 |    0.1% |      2.20 | `Normalize Vec4`
|                8.34 |      119,933,805.50 |    1.1% |      2.21 | `Normalize Vec4SIMD`

