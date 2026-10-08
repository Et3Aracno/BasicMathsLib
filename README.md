# Technical Benchmark





## Context


## Benchmark  

Lot : 250 000   
idk: 2  
CPU: GenuineIntel / Intel(R) Core(TM) i5-14600KF  
SSE usable: true  
AVX2 usable: true  
FMA usable: true  
Seed: 2629990972  
Batch incl. checksum: min 0.225 ms, median 0.227 ms, max 0.233 ms  
Observable checksum: 0.000  
Build: Release x64  
Batch Size: 250 000  
Warmup: 100.000  
Epochs: 1000.000  

|               ns/op |                op/s |    err% |     total | benchmark
|--------------------:|--------------------:|--------:|----------:|:----------
|        9,627,150.00 |              103.87 |    0.8% |      0.97 | `Normalize C++`
|        1,757,850.00 |              568.88 |    1.6% |      0.18 | `Normalize SIMD`
|          221,695.00 |            4,510.70 |    3.0% |      0.11 | `Dot C++`
|          315,812.50 |            3,166.44 |    0.6% |      0.11 | `Dot SIMD`
|        1,502,600.00 |              665.51 |    5.4% |      0.14 | `Matrix4x4 * Vec4 C++` (Unstable with ~1.0 iters. Increase `minEpochIterations` to e.g. 10)
|        1,334,600.00 |              749.29 |   11.2% |      0.13 | `Matrix4x4 * Vec4 SIMD` (Unstable with ~1.0 iters. Increase `minEpochIterations` to e.g. 10)  

Speedup Normalize : 5.48x  
Speedup Dot : ≈ 0.70x  
Speedup Matrix4x4 * Vec4 : ≈ 1.13x  


Lot : 2000  
idk: 2  
CPU: GenuineIntel / Intel(R) Core(TM) i5-14600KF  
SSE usable: true  
AVX2 usable: true  
FMA usable: true  
Seed: 1487105735  
Batch incl. checksum: min 0.002 ms, median 0.002 ms, max 0.002 ms  
Observable checksum: 0.000  
Build: Release x64  
Batch Size: 2000  
Warmup: 100  
Epochs: 1000  

|               ns/op |                op/s |    err% |     total | benchmark
|--------------------:|--------------------:|--------:|----------:|:----------
|           76,299.45 |           13,106.25 |    1.0% |      0.11 | `Normalize C++`
|           40,535.86 |           24,669.52 |    0.4% |      0.11 | `Normalize SIMD`
|            1,701.42 |          587,745.50 |    0.9% |      0.11 | `Dot C++`
|            2,529.32 |          395,363.01 |    0.8% |      0.11 | `Dot SIMD`
|            8,031.86 |          124,504.09 |    1.1% |      0.11 | `Matrix4x4 * Vec4 C++`
|            7,643.90 |          130,823.24 |    1.0% |      0.11 | `Matrix4x4 * Vec4 SIMD`   

Speedup Normalize : 5.32x  
Speedup Dot : 0.67x  
Speedup Matrix4x4 * Vec4 : 1.05x  



  
Lot : 20  
idk: 2  
CPU: GenuineIntel / Intel(R) Core(TM) i5-14600KF  
SSE usable: true  
AVX2 usable: true  
FMA usable: true  
Seed: 4027332694  
Batch incl. checksum: min 0.000 ms, median 0.000 ms, max 0.000 ms  
Observable checksum: 0.000  
Build: Release x64  
Batch Size: 20.000  
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
  
Speedup Normalize : 5.07x  
Speedup Dot : 0.64x  
Speedup Matrix4x4 * Vec4 : 1.06x  



## Analyse  
  
### Profiling CPU  
Nous avons choisi de sélectionner la normalisation de vecteurs pour le profiling CPU, car cette dernière, avec un lot de 250 000 vecteurs distincts, avait montré des performances explicitement différentes, notamment avec la fonction SIMD, qui s'exécute 5,48 fois plus rapidement que la fonction C++.  

Configuration : Release
Architecture : x64
CPU : Intel Core i5-14600KF
Traitement : normalisation de Vec4
Nombre de vecteurs : 250 000
Implémentation comparée : C++ / SSE
Allocations : effectuées avant la mesure
Profiler : Visual Studio CPU Usage
Warmup : 10
Nombre d'epochs : 100  

<img width="1557" height="720" alt="image" src="https://github.com/user-attachments/assets/16f7e94e-dc0e-4e44-8b32-6ad0607d5a06" />  

Le nom des deux fonctions est masqué par les lambdas. Cependant, grâce aux résultats du benchmark, on peut facilement distinguer laquelle correspond à l'implémentation C++ et laquelle correspond à l'implémentation SIMD. On peux observer une différence importante entre les temps processeur consacrés aux deux implémentations. Cette différence est cohérente avec les résultats obtenus lors du benchmark, dans lequel le SIMD s'exécute 5,48 fois plus rapidement que le C++ pour un lot de 250 000 vecteurs.

.......Pk SIMD est plus rapide que CPP , expliquer le fonctionnement des fonctions Normalize c++ et SIMD , et la raison de leur rapidité .....  
de plus , même en retirant les vérification présente dans l'implémentation C++ de Normalize on remarque toujours cette différence aussi importante :   
  
|               ns/op |                op/s |    err% |     total | benchmark
|--------------------:|--------------------:|--------:|----------:|:----------
|        3,954,550.00 |              252.87 |    0.3% |      0.40 | `Normalize C++`
|        1,753,900.00 |              570.16 |    1.0% |      0.18 | `Normalize SIMD`   
Speedup: 2,25  



Cependant , SIMD ne veux pas dire meilleure , en effet si on regarde les résultats de l'implémentation SIMD de Dot , ces derniers sont inférieure en terme de performance à ceux de l'implémentation C++ sur 250 000 éléments . L'implémentation SIMD obtient un speed-up de seulement 0,70× par rapport à la version C++, ce qui signifie qu'elle est environ 1,43 fois plus lente.  
  
###Dot  
Comme on peux le voir dans le Benchmark , avec nos 250 000 vecteurs , l'implémentation SIMD de Dot est moins rapide que l'implémentation C++, en effet l'implémentation SIMD est 1,42 fois plus lente que l'implémentation C++ . Le produit scalaire de vecteur est une opération simple , en c++ cette dernière nécessite seulement les opérateur * et peux être effectuer en une ligne de plus en Release x64 , avec l'auto vectorisation d'activer , le compilateur s'occupe déjà de transformer certaine partie du code en SIMD . Quand à l'implémentation SIMD , cette dernière ne bénificie pas de la linéarité de ses valeurs , en effet cette fois ci le fait qu'un __m128 contiens chacune des valeurs du vecteurs complecifie l'opération , 









### Matrix


