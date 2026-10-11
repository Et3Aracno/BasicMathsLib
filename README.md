# Technical Benchmark

## Context

Ce document a été réalisé à la suite du développement d'une bibliothèque mathématique, afin de comparer les performances d'implémentations SIMD et C++ de mêmes fonctions, mais aussi de démontrer l'importance de l'optimisation des fonctions mathématiques.

---

## Benchmark

### Lot : 250 000

- idk: 2
- CPU: GenuineIntel / Intel(R) Core(TM) i5-14600KF
- SSE usable: true
- AVX2 usable: true
- FMA usable: true
- Seed: 2629990972
- Batch incl. checksum: min 0.225 ms, median 0.227 ms, max 0.233 ms
- Build: Release x64
- Batch Size: 250 000
- Warmup: 100.000
- Epochs: 1000.000

|               ns/op |                op/s |    err% |     total | benchmark |
|--------------------:|--------------------:|--------:|----------:|:----------|
|        9,627,150.00 |              103.87 |    0.8% |      0.97 | `Normalize C++` |
|        1,757,850.00 |              568.88 |    1.6% |      0.18 | `Normalize SIMD` |
|          221,695.00 |            4,510.70 |    3.0% |      0.11 | `Dot C++` |
|          315,812.50 |            3,166.44 |    0.6% |      0.11 | `Dot SIMD` |
|        1,502,600.00 |              665.51 |    5.4% |      0.14 | `Matrix4x4 * Vec4 C++` (Unstable with ~1.0 iters. Increase `minEpochIterations` to e.g. 10) |
|        1,334,600.00 |              749.29 |   11.2% |      0.13 | `Matrix4x4 * Vec4 SIMD` (Unstable with ~1.0 iters. Increase `minEpochIterations` to e.g. 10) |

- Speedup Normalize : 5.48x
- Speedup Dot : ≈ 0.70x
- Speedup Matrix4x4 * Vec4 : ≈ 1.13x

---

### Lot : 2000

- idk: 2
- CPU: GenuineIntel / Intel(R) Core(TM) i5-14600KF
- SSE usable: true
- AVX2 usable: true
- FMA usable: true
- Seed: 1487105735
- Batch incl. checksum: min 0.002 ms, median 0.002 ms, max 0.002 ms
- Build: Release x64
- Batch Size: 2000
- Warmup: 100
- Epochs: 1000

|               ns/op |                op/s |    err% |     total | benchmark |
|--------------------:|--------------------:|--------:|----------:|:----------|
|           76,299.45 |           13,106.25 |    1.0% |      0.11 | `Normalize C++` |
|           40,535.86 |           24,669.52 |    0.4% |      0.11 | `Normalize SIMD` |
|            1,701.42 |          587,745.50 |    0.9% |      0.11 | `Dot C++` |
|            2,529.32 |          395,363.01 |    0.8% |      0.11 | `Dot SIMD` |
|            8,031.86 |          124,504.09 |    1.1% |      0.11 | `Matrix4x4 * Vec4 C++` |
|            7,643.90 |          130,823.24 |    1.0% |      0.11 | `Matrix4x4 * Vec4 SIMD` |

- Speedup Normalize : 5.32x
- Speedup Dot : 0.67x
- Speedup Matrix4x4 * Vec4 : 1.05x

---

### Lot : 20

- idk: 2
- CPU: GenuineIntel / Intel(R) Core(TM) i5-14600KF
- SSE usable: true
- AVX2 usable: true
- FMA usable: true
- Seed: 4027332694
- Batch incl. checksum: min 0.000 ms, median 0.000 ms, max 0.000 ms
- Build: Release x64
- Batch Size: 20.000
- Warmup Size: 100.000
- Epochs Size: 1000.000

|               ns/op |                op/s |    err% |     total | benchmark |
|--------------------:|--------------------:|--------:|----------:|:----------|
|              762.65 |        1,311,212.12 |    0.8% |      0.11 | `Normalize C++` |
|              150.50 |        6,644,507.17 |    0.7% |      0.11 | `Normalize SIMD` |
|               16.28 |       61,420,641.83 |    0.2% |      0.11 | `Dot C++` |
|               25.29 |       39,545,371.72 |    1.6% |      0.11 | `Dot SIMD` |
|               78.39 |       12,757,028.08 |    1.5% |      0.11 | `Matrix4x4 * Vec4 C++` |
|               73.98 |       13,517,474.51 |    0.3% |      0.11 | `Matrix4x4 * Vec4 SIMD` |

- Speedup Normalize : 5.07x
- Speedup Dot : 0.64x
- Speedup Matrix4x4 * Vec4 : 1.06x

---

## Analyse

### Profiling CPU

Nous avons choisi de sélectionner la normalisation de vecteurs pour le profiling CPU, car cette dernière, avec un lot de 250 000 vecteurs distincts, avait montré des performances explicitement différentes, notamment avec la fonction SIMD, qui s'exécute 5,48 fois plus rapidement que la fonction C++.

- Configuration : Release
- Architecture : x64
- CPU : Intel Core i5-14600KF
- Traitement : normalisation de Vec4
- Nombre de vecteurs : 250 000
- Implémentation comparée : C++ / SSE
- Allocations : effectuées avant la mesure
- Profiler : Visual Studio CPU Usage
- Warmup : 10
- Nombre d'epochs : 100

<img width="1557" height="720" alt="image" src="https://github.com/user-attachments/assets/16f7e94e-dc0e-4e44-8b32-6ad0607d5a06" />

Le nom des deux fonctions est masqué par les lambdas. Cependant, grâce aux résultats du benchmark, on peut facilement distinguer laquelle correspond à l'implémentation C++ et laquelle correspond à l'implémentation SIMD. On peux observer une différence importante entre les temps processeur consacrés aux deux implémentations. Cette différence est cohérente avec les résultats obtenus lors du benchmark, dans lequel le SIMD s'exécute 5,48 fois plus rapidement que le C++ pour un lot de 250 000 vecteurs.

Cette différence de performance vient avant tout du fait qu'en C++, les opérations doivent toutes être effectuées individuellement avant d'être exploitées, contrairement au SIMD qui, bien qu'il suive le même chemin de calcul, peut effectuer les calculs simultanément grâce à la linéarité des `__m128`. Ces derniers sont la raison même pour laquelle le gain est si important. N'ayant pas à traiter les données séparément grâce au registre `__m128`, le processeur effectue les calculs beaucoup plus rapidement. C'est dans ce genre de situation, où les éléments peuvent être traités simultanément, que le SIMD présente un gros avantage face au C++.

de plus , même en retirant les vérification présente dans l'implémentation C++ de Normalize on remarque toujours cette différence aussi importante :

|               ns/op |                op/s |    err% |     total | benchmark |
|--------------------:|--------------------:|--------:|----------:|:----------|
|        3,954,550.00 |              252.87 |    0.3% |      0.40 | `Normalize C++` |
|        1,753,900.00 |              570.16 |    1.0% |      0.18 | `Normalize SIMD` |

**Speedup: 2,25**

Cependant , SIMD ne veux pas dire meilleure , en effet si on regarde les résultats de l'implémentation SIMD de Dot , ces derniers sont inférieure en terme de performance à ceux de l'implémentation C++ sur 250 000 éléments . L'implémentation SIMD obtient un speed-up de seulement 0,70× par rapport à la version C++, ce qui signifie qu'elle est environ 1,43 fois plus lente.

---

### Dot

Comme on peut le voir dans le benchmark, avec nos 250 000 vecteurs, l'implémentation SIMD de Dot est moins rapide que l'implémentation C++. En effet, l'implémentation SIMD est 1,42 fois plus lente que l'implémentation C++. Le produit scalaire de vecteurs est une opération simple. En C++, cette dernière nécessite seulement les opérateurs `*` et peut être effectuée en une ligne. De plus, en Release x64, avec l'auto-vectorisation activée, le compilateur s'occupe déjà de transformer certaines parties du code en SIMD.

Quant à l'implémentation SIMD, cette dernière ne bénéficie pas de la linéarité de ses valeurs. En effet, le produit scalaire produit un seul résultat flottant à partir des quatre composantes des deux vecteurs. Dans notre implémentation, chaque composante est d'abord dupliquée dans les quatre lanes d'un registre `__m128` à l'aide de `_mm_set_ps1`. Quatre multiplications SIMD sont ensuite effectuées. Par exemple, la valeur x est transformée en `[x, x, x, x]`. La multiplication avec `rhs.x` nous donne alors `[x·rhs.x, x·rhs.x, x·rhs.x, x·rhs.x]`. Les quatre lanes contiennent donc le même résultat, alors qu'une seule valeur sera finalement utilisée.

Pour conclure sur Dot(), nous avons constaté que notre implémentation SIMD peut encore être largement améliorée. L'utilisation actuelle des registres SIMD entraîne des calculs redondants, ce qui diminue beaucoup ses performances par rapport à l'implémentation C++.

---

### Matrix4x4 * Vec4

Comme on l'observe dans le benchmark, avec nos 250 000 vecteurs, l'implémentation SIMD de Matrix4x4 * Vec4 est 1,13× plus rapide que l'implémentation C++. Contrairement à Dot, ici, la linéarité des `__m128` confère un avantage à l'implémentation SIMD. Pour la multiplication de matrices, le nombre de calculs est important et, par conséquent, le nombre d'opérateurs et d'étapes nécessaires en C++ augmente, ce qui ralentit le processus, car ces derniers doivent être effectués séparément, contrairement au SIMD qui, lui, peut les effectuer simultanément.

Cependant, l'implémentation C++ bénéficie quand même des optimisations du compilateur. De plus, cette dernière possède un ratio d'erreur bien moins élevé que l'implémentation SIMD, ce qui peut être beaucoup plus intéressant au vu du moteur physique.

Dans notre implémentation SIMD, les quatre composantes du vecteur sont regroupées dans un registre `__m128`, puis `_mm_mul_ps` permet d'effectuer les quatre multiplications simultanément pour chaque ligne de la matrice. Cependant, nous perdons des performances à cause du fait qu'après chaque multiplication, le résultat contenu dans le registre `__m128` est stocké dans un tableau à l'aide de `_mm_store_ps`. Les quatre valeurs sont ensuite récupérées depuis ce tableau afin d'effectuer les additions de manière scalaire. Tout cela provoque une augmentation des calculs et, par conséquent, la perte du gain de performance que nous avions réalisé grâce au SIMD. On le remarque justement à cette légère augmentation de 1,13×.

Pour conclure, il est indéniable que nous avons gagné en performances par rapport à l'implémentation C++. Cependant, notre gain reste limité et n'est pas exploité à son paroxysme. Une voie d'amélioration permettant de dépasser les limites actuelles de notre implémentation SIMD serait de modifier la manière dont nous effectuons le produit scalaire, afin de privilégier le calcul et de limiter les stockages temporaires ainsi que les transformations intermédiaires.

## Désassemblage :
Pour cet exemple j'ai décidé de prendre l'opérateur ==
## Référence optimisée:

```asm

mov  qword ptr [rsp+10h],rdx   	  ; save &rhs 
mov  qword ptr [rsp+8],rcx     	  ; save this
push rbp
push rdi                       	
sub rsp,0F8h                  	  ; reserve 248 oct
lea rbp,[rsp+20h]            	
lea rcx,[__CFA4424A_Vec3@inl] 	  ; Debug related
call __CheckForDebuggerJustMyCode ; Debug related
nop

	return x == rhs.x && y == rhs.y && z == rhs.z;

mov  rax,qword ptr [this]     	; read this on stack
mov  rcx,qword ptr [rhs]      	; read rhs on stack
movss xmm0,dword ptr [rax]     	; xmm0 = this.x
ucomiss xmm0,dword ptr [rcx]    ; compare with rhs.x, put a flag coresponding to the result
jp Maths::Vec3<float>::operator==+80h (07FF7130407B0h) 	; conditional jump
jne Maths::Vec3<float>::operator==+80h (07FF7130407B0h) ; conditional jump

Do the same thing for y and z, rax become rax+4 and rax+8

mov dword ptr [rbp+0C0h],1    	; if everything equal, put a temporary value of 1
jmp Maths::Vec3<float>::operator==+8Ah (07FF7130407B0h) ; conditional jump end
mov dword ptr [rbp+0C0h],0    	; if all bit are not equal, put a temporary value of  0
movzx eax,byte ptr [rbp+0C0h]   ; read the temporary value, which will become the return value (booleen)
}
lea rsp,[rbp+0D8h]
pop rdi
pop rbp
ret                             ; return the value
```

## SIMD explicite:

```asm

mov   qword ptr [rsp+10h],rdx   	; save &rhs
mov   qword ptr [rsp+8],rcx     	; save this  
push  rbp                       
push  rdi
sub   rsp,1A8h                  	; reserve 424 oct
lea   rbp,[rsp+20h]             
lea   rcx,[__E23A1142_Vec3S@inl] 	; Debug related
call  __CheckForDebuggerJustMyCode 	; Debug related
nop

	__m128 vrhs = Load(rhs);

mov   rcx,qword ptr [rhs]       	; read rhs on the stack
call  Maths::Vec3S::Load        	; call the functon Load() which is not inline because of Debug
movaps xmmword ptr [vrhs],xmm0  	; result was in xmm0 and is copied in the variable vrhs


	__m128 vp = _mm_setr_ps(x, y, z, 0);

xorps  xmm0,xmm0                ; xmm0 = 0 
mov    rax,qword ptr [this]     ; read this
movss  xmm1,dword ptr [rax+8]   ; xmm1 = z
mov    rax,qword ptr [this]	; read this
movss  xmm2,dword ptr [rax+4]   ; xmm2 = y
mov    rax,qword ptr [this]	; read this
movss  xmm3,dword ptr [rax]     ; xmm3 = x
unpcklps xmm1,xmm0              ; xmm1 = (0, 0, z ,0)
unpcklps xmm3,xmm2              ; xmm3 = (x, y, 0, 0)
movaps xmm0,xmm3		; xmm0 = (x, y, 0, 0)
movlhps xmm0,xmm1               ; xmm0 = (x, y, z, 0); final register
movaps xmmword ptr [rbp+130h],xmm0  ; put the final register tremporary on the stack 
movaps xmm0,xmmword ptr [rbp+130h]  ; read the temporary register on the stack and put it in xmm0
movaps xmmword ptr [vp],xmm0        ; vp = xmm0

	return _mm_movemask_ps(_mm_cmpeq_ps(vrhs, vp)) == 0xF;

movaps xmm0,xmmword ptr [vrhs]	; xmm0 = vrhs
cmpeqps xmm0,xmmword ptr [vp]   ; compare the lanes with 0xFFFFFFFF to see it it's equal
movaps [rbp+160h],xmm0          
movaps xmm0,[rbp+160h]
movmskps eax,xmm0               ; extracting the sign bit of every lane
cmp    eax,0Fh                  ; compare all the signs 
jne    Maths::Vec3S::operator==+0AEh (07FF713040AEEh) ; conditional jump if it's false
mov    dword ptr [rbp+174h],1   ; return 1; it's true
jmp    Maths::Vec3S::operator==+0AEh (07FF713040AEEh) ; conditional jump end
mov    dword ptr [rbp+174h],0   ; return 1; it's flse
movzx  eax,byte ptr [rbp+174h]  ; read the return value(booleen)

lea  rsp,[rbp+188h]   
pop  rdi
pop  rbp
ret                   		; return the value
```
