# Technical Benchmark





## Context







## Matrix

### Matrix 4x4

CPU: GenuineIntel / Intel(R) Core(TM) i5-14600KF  
SSE usable: true  
AVX2 usable: true  
FMA usable: true  
Batch incl. checksum: min 0.574 ms, median 0.599 ms, max 0.659 ms  
Observable checksum: -37821.203  
Epochs : 20  

|               ns/op |                op/s |    err% |     total | benchmark
|--------------------:|--------------------:|--------:|----------:|:----------
|                1.90 |      525,064,499.62 |    0.3% |      0.02 | `Matrix4x4 * Vec4`
|                2.27 |      439,956,458.69 |    0.2% |      0.02 | `Matrix4x4 SIMD * Vec4SIMD`
  
  
Seed: 4199792540, vectors per batch: 250000  
Batch incl. checksum: min 0.553 ms, median 0.572 ms, max 0.612 ms  
Observable checksum: 11168.087  
Epochs : 250 000  

|               ns/op |                op/s |    err% |     total | benchmark
|--------------------:|--------------------:|--------:|----------:|:----------
|                1.90 |      524,936,570.55 |    0.4% |    264.85 | `Matrix4x4 * Vec4`
|                2.27 |      439,812,020.29 |    0.2% |    275.24 | `Matrix4x4 SIMD * Vec4SIMD`




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
Seed: 3528253797, vectors per batch: 250000  
Batch incl. checksum: min 0.572 ms, median 0.603 ms, max 0.632 ms  
Observable checksum: -70450.920  
Epochs : 2000  
Vector values : {1.0f, 2.0f, 3.0f, 4.0f};  
  
|               ns/op |                op/s |    err% |     total | benchmark
|--------------------:|--------------------:|--------:|----------:|:----------
|                0.70 |    1,437,463,215.13 |    0.3% |    274.80 | ```Dot Vec4<float> `
|                0.76 |    1,309,038,734.29 |    1.0% |    298.46 | ```Dot Vec4 SIMD`  



Seed: 4044217307, vectors per batch: 250000  
Batch incl. checksum: min 0.637 ms, median 1.155 ms, max 1.709 ms  
Observable checksum: 10433.258  
Epochs : 20  
Vector values : {1.0f, 2.0f, 3.0f, 4.0f};  

|               ns/op |                op/s |    err% |     total | benchmark
|--------------------:|--------------------:|--------:|----------:|:----------
|                1.24 |      803,391,813.72 |   12.2% |      0.03 | :wavy_dash: ```Dot Vec4<float> ` (Unstable with ~1,128,720.1 iters. Increase `minEpochIterations` to e.g. 11287201)
|                1.28 |      781,966,427.06 |   17.1% |      0.02 | :wavy_dash: ```Dot Vec4 SIMD` (Unstable with ~721,267.2 iters. Increase `minEpochIterations` to e.g. 7212672)
  
Text  


CPU: GenuineIntel / Intel(R) Core(TM) i5-14600KF
SSE usable: true
AVX2 usable: true
FMA usable: true


Seed: 345291603, vectors per batch: 250000
Batch incl. checksum: min 0.665 ms, median 0.713 ms, max 1.040 ms
Observable checksum: -19234.624
Vector values : {1.0f, 2.0f, 3.0f, 4.0f};
Epochs : 250000

|               ns/op |                op/s |    err% |     total | benchmark
|--------------------:|--------------------:|--------:|----------:|:----------
|               49.84 |       20,063,026.07 |   11.1% |    284.65 | :wavy_dash: ```Normalize Vec4<float> ` (Unstable with ~23,426.9 iters. Increase `minEpochIterations` to e.g. 234269)
|               19.63 |       50,936,974.49 |    5.4% |    319.40 | :wavy_dash: ```Normalize Vec4 SIMD` (Unstable with ~70,090.9 iters. Increase `minEpochIterations` to e.g. 700909)





Seed: 109568798, vectors per batch: 250000
Batch incl. checksum: min 0.747 ms, median 0.816 ms, max 1.029 ms
Observable checksum: -159453.508
Vector values : {1.0f, 2.0f, 3.0f, 4.0f};
Epochs : 20

|               ns/op |                op/s |    err% |     total | benchmark
|--------------------:|--------------------:|--------:|----------:|:----------
|               37.15 |       26,917,102.23 |    2.8% |      0.02 | ```Normalize Vec4<float> `
|                8.89 |      112,546,450.55 |    4.3% |      0.02 | ```Normalize Vec4 SIMD`
  


