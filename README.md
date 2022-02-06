Part 1. Performance and power assessment.
Node configuration information
CPU benchmarking: STREAM, GUPS, DGEMM, LinPack and [others](https://icl.utk.edu/hpcc/) on both memory-bound
(e.g. Matrix-Vector multiplication and sorting code) and CPU-bound operations (e.g. Matrix-Matrix multiplication)
STREAM and GUPS: performance of memory bandwidth (MB/s) for a single core (different compiler optimization and array size)
DGEMM and Linpack: GFLOPs for array sizes.
Performance is compared with Peak memory bandwidth (use L1 cache) and Peak FLOPS of CPU

Part 2. PAPI events and cache misses
Measure Power consumption (using Intel rapl-read) of processors and main memory (DRAM) and different cache behavior (using PAPI)
Part 3. Comparing  algorithms that are 'CPU' limited and algorithms that are memory bandwidth limited
GFlops of an operation (e.g. MM) is measured as: $\approx3n^2/[execution time]$. 
For simple algorithms, we measure execution time after each run and computational cost of each operation/program is known by hand.
$\rightarrow$ for more complicated operations we should use counters for FLOPS that is available for modern processors (e.g. [SDE toolkit](https://docs.nersc.gov/performance/arithmetic_intensity/) allows tracing only for specified sec of code and [VTUNE]() )
Memory bound-width [GB/s] for an operation (e.g. MV) is measured as: $\approx (n^2[matrix]+n[vector])*8 byte * 2[1 load + 1 store] * \frac{1}{T}$. Here we assumed data is loaded and stored once

Part 4. Insight into OpenMP parallelization strategies for various number of threads, optimization flags, trying out thread affinity for performance improvement.
Measured exec times, determined  computational rate (i.e. GFlops/s), efficiency (fraction of theoretical peak rate), and reported power consumption (watts) for the memory and L1, L2 , and L3 cache misses for each case of memory- and cpu- bound problems
and also arithmetic efficiency (percent of GFLOPs of operation to theoretical peak rate)

Part 5. Exploring GPU High-level programming OpenMP and OpenACC on Himeno benchmark code, Jacobi's method for 2D Laplace equation, and matrix-matrix multiplication.

Learn more on [roofline model](https://developer.download.nvidia.com/video/gputechconf/gtc/2019/presentation/s9624-performance-analysis-of-gpu-accelerated-applications-using-the-roofline-model.pdf)

Making good use of CPU/GPU's compute and bandwidth capabilities

Core parameter is [arithmetic intensity](https://crd.lbl.gov/departments/computer-science/par/research/roofline/introduction/) (GLOPs/byte): total FLOPs performed to Total Bytes moved (DRAM)

1. [collect roofline ceilings] find your machine limits:$GFLOPs=\min\begin{cases} & Peak~ GFLOPs\\  &AI * Peak~ GB/s \end{cases}$

2. [collect application performance] sort kernel by AI; kernels near roofline are making good use of computational resources

For complex kernel (apps) AI (FLOPS/Bytes) is achieved using nvprof FLOPs/ nvprof data movement And performance (GFLOP/s): nvprof FLOPs/Runtime

Part 6. Explore different MPI strategies (distributed memory paradigm)


Part 7. Cuda programming
for CUDA and CUDA fortran: use Nsight IDE
