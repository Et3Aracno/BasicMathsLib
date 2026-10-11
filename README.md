# Technical Benchmark

## Context

This document was produced following the development of a math library, in order to compare the performance of SIMD and C++ implementations of the same functions, and also to demonstrate the importance of optimizing math functions.

---

## Benchmark  


### Batch: 250 000

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

### Batch: 2000

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

### Batch: 20

- idk: 2
- CPU: GenuineIntel / Intel(R) Core(TM) i5-14600KF
- SSE usable: true
- AVX2 usable: true
- FMA usable: true
- Seed: 4027332694
- Batch incl. checksum: min 0.000 ms, median 0.000 ms, max 0.000 ms
- Build: Release x64
- Batch Size: 20.000
- Warmup: 100.000
- Epochs: 1000.000

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

## Analysis

### CPU Profiling

We chose to use vector normalization for CPU profiling, because with a batch of 250 000 distinct vectors it showed clearly different performance, notably with the SIMD function, which runs 5.48 times faster than the C++ function.

- Configuration: Release
- Architecture: x64
- CPU: Intel Core i5-14600KF
- Processing: Vec4 normalization
- Number of vectors: 250 000
- Compared implementations: C++ / SSE
- Allocations: performed before the measurement
- Profiler: Visual Studio CPU Usage
- Warmup: 10
- Number of epochs: 100

<img width="1557" height="720" alt="image" src="https://github.com/user-attachments/assets/16f7e94e-dc0e-4e44-8b32-6ad0607d5a06" />

The names of the two functions are hidden by the lambdas. However, thanks to the benchmark results, it is easy to tell which one corresponds to the C++ implementation and which one corresponds to the SIMD implementation. We can observe a significant difference between the CPU times spent on the two implementations. This difference is consistent with the results obtained during the benchmark, in which SIMD runs 5.48 times faster than C++ for a batch of 250 000 vectors.

This performance difference comes first and foremost from the fact that in C++, the operations must all be performed individually before being used, unlike SIMD which, although it follows the same calculation path, can perform the calculations simultaneously thanks to the linearity of the `__m128`. These are the very reason why the gain is so significant. Since the data does not have to be processed separately thanks to the `__m128` register, the processor performs the calculations much faster. It is in this kind of situation, where the elements can be processed simultaneously, that SIMD has a big advantage over C++.

Moreover, even when removing the checks present in the C++ implementation of Normalize, we still observe this equally significant difference:

|               ns/op |                op/s |    err% |     total | benchmark |
|--------------------:|--------------------:|--------:|----------:|:----------|
|        3,954,550.00 |              252.87 |    0.3% |      0.40 | `Normalize C++` |
|        1,753,900.00 |              570.16 |    1.0% |      0.18 | `Normalize SIMD` |

**Speedup: 2.25**

However, SIMD does not mean better. Indeed, if we look at the results of the SIMD implementation of Dot, they are lower in terms of performance than those of the C++ implementation on 250 000 elements. The SIMD implementation obtains a speed-up of only 0.70× compared to the C++ version, which means it is about 1.43 times slower.

---

### Dot

As can be seen in the benchmark, with our 250 000 vectors, the SIMD implementation of Dot is slower than the C++ implementation. Indeed, the SIMD implementation is 1.42 times slower than the C++ implementation. The dot product of vectors is a simple operation. In C++, it only requires the `*` operators and can be done in one line. Moreover, in Release x64, with auto-vectorization enabled, the compiler already takes care of transforming some parts of the code into SIMD.

As for the SIMD implementation, it does not benefit from the linearity of its values. Indeed, the dot product produces a single float result from the four components of the two vectors. In our implementation, each component is first duplicated into the four lanes of an `__m128` register using `_mm_set_ps1`. Four SIMD multiplications are then performed. For example, the value x is transformed into `[x, x, x, x]`. Multiplying it with `rhs.x` then gives us `[x·rhs.x, x·rhs.x, x·rhs.x, x·rhs.x]`. The four lanes therefore contain the same result, whereas only one value will ultimately be used.

To conclude on Dot(), we found that our SIMD implementation can still be greatly improved. The current use of SIMD registers leads to redundant calculations, which greatly reduces its performance compared to the C++ implementation.

---

### Matrix4x4 * Vec4

As can be seen in the benchmark, with our 250 000 vectors, the SIMD implementation of Matrix4x4 * Vec4 is 1.13× faster than the C++ implementation. Unlike Dot, here the linearity of the `__m128` gives an advantage to the SIMD implementation. For matrix multiplication, the number of calculations is large and, consequently, the number of operators and steps required in C++ increases, which slows down the process, because these must be performed separately, unlike SIMD which can perform them simultaneously.

However, the C++ implementation still benefits from compiler optimizations. Moreover, it has a much lower error ratio than the SIMD implementation, which can be much more interesting with regard to the physics engine.

In our SIMD implementation, the four components of the vector are grouped in an `__m128` register, then `_mm_mul_ps` allows the four multiplications to be performed simultaneously for each row of the matrix. However, we lose performance because after each multiplication, the result contained in the `__m128` register is stored in an array using `_mm_store_ps`. The four values are then retrieved from this array in order to perform the additions in a scalar manner. All of this increases the number of calculations and, consequently, causes the loss of the performance gain that we had achieved thanks to SIMD. This is precisely noticeable in the slight increase of 1.13×.

To conclude, it is undeniable that we gained performance compared to the C++ implementation. However, our gain remains limited and is not exploited to its fullest. One way of improvement that would allow us to go beyond the current limits of our SIMD implementation would be to change the way we compute the dot product, in order to favor computation and limit temporary storage as well as intermediate transformations.

## Disassembly:
For this example I decided to take the == operator
## Optimized reference:

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

## Explicit SIMD:

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
mov    rax,qword ptr [this]		; read this
movss  xmm2,dword ptr [rax+4]   ; xmm2 = y
mov    rax,qword ptr [this]		; read this
movss  xmm3,dword ptr [rax]     ; xmm3 = x
unpcklps xmm1,xmm0              ; xmm1 = (0, 0, z ,0)
unpcklps xmm3,xmm2              ; xmm3 = (x, y, 0, 0)
movaps xmm0,xmm3				; xmm0 = (x, y, 0, 0)
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
ret                   			; return the value
```

## Désassemblage :
In this exemple I am going to use : operator==() 
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
mov    rax,qword ptr [this]		; read this
movss  xmm2,dword ptr [rax+4]   ; xmm2 = y
mov    rax,qword ptr [this]		; read this
movss  xmm3,dword ptr [rax]     ; xmm3 = x
unpcklps xmm1,xmm0              ; xmm1 = (0, 0, z ,0)
unpcklps xmm3,xmm2              ; xmm3 = (x, y, 0, 0)
movaps xmm0,xmm3				; xmm0 = (x, y, 0, 0)
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
ret                   			; return the value
```

## SOA vs AOS
## Structures

We are going to compare these two models to see which one is faster and in which conditions.
For this comparison we are going to use the Dot function.

AOS is the basic way of storing data. For a vector3 you are going to have this :

```cpp
float x, y, z, w;
```
With that you will have : `[ x | y | z | w ]`, in memory. Here, the w is for allignement purposes. 

On the other hand, SOA is going to be like this:

```cpp
static constexpr int Count = 1024; // better adaptability
alignas(16) float x[Count];
alignas(16) float y[Count];
alignas(16) float z[Count];
```
And here the egisters are going to look more like this:
```
[ x | x | x | x ]
[ y | y | y | y ] 
[ z | z | z | z ]
```

Test results for AOS scalar, AOS SIMD and SOA SIMD:

- CPU: GenuineIntel / Intel(R) Core(TM) i7-9800X CPU @ 3.80GHz
- SSE usable: true
- AVX2 usable: true
- FMA usable: true
- Batch Size: 1024
- epochs: 2000

|               ns/op |                op/s |    err% |     total | benchmark
|--------------------:|--------------------:|--------:|----------:|:----------
|                4.59 |      217,974,945.84 |    0.3% |      2.12 | `DotSOA SIMD 1024`
|               19.72 |       50,703,750.53 |    0.3% |      1.95 | `DotAOS SIMD 1024`
|               16.30 |       61,340,686.51 |    0.3% |      2.08 | `DotAOS scalaire 1024`

The SOA model is going to be faster because you have only vertical operations with `_mm_add_ps` and `_mm_mul_ps`.
Whereas the AOS model has horizontal operations: they need `_MM_SHUFFLE` or to get the values independently. (which are heavy calculations)

The Structures of arrays will also allow you to calculate 4 vectors at the same time because you are iterating by steps of 4
(one register holds 4 values of a component).


## Conversion

To be able to convert properly you need your AOS to be padded and aligned, in the way that best fits your needs.
Then you only need to transpose (`_MM_TRANSPOSE4_PS()`) your 4 AOS vectors which will give you this:
```
  r0=[x0 y0 z0 w0]    to    r0=[x0 x1 x2 x3]
  r1=[x1 y1 z1 w1]       	r1=[y0 y1 y2 y3]
  r2=[x2 y2 z2 w2]       	r2=[z0 z1 z2 z3]
  r3=[x3 y3 z3 w3]       	r3=[w0 w1 w2 w3]
```

Results of the tests for the conversions and the computations with and without conversions:

- CPU: GenuineIntel / Intel(R) Core(TM) i7-9800X CPU @ 3.80GHz
- SSE usable: true
- AVX2 usable: true
- FMA usable: true
- Batch Size: 1024
- epochs: 2000

|               ns/op |                op/s |    err% |     total | benchmark
|--------------------:|--------------------:|--------:|----------:|:----------
|                3.15 |      317,000,000.00 |    0.6% |      2.16 | `Conversion AoS->SoA`
|                3.22 |      310,925,370.05 |    0.5% |      2.18 | `Conversion SoA->Aos`
|               19.81 |       50,466,938.42 |    1.2% |      2.21 | `DotAOS SIMD 1024`
|               14.25 |       70,157,008.28 |    0.4% |      2.20 | `Conversion AoS->SoA, calcul, Conversion SoA->Aos`

For a single calculation, even if here it doesn't show, AOS might be faster because the conversion can cancel out your gains, so it is better to do all your processing in SOA and convert back at the end
or to have your class already in SOA which removes the conversions.
