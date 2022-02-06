The directory contatins following files:

1. himenoBMT.c - Source code for himeno benchmark
2. Makefile - Uses GCC to generate executable. Note that the executable generated using this makefile will not be parallelized for GPU's.
3. run.sh - Generates GPU code using the PGI cmopiler.
4. README.txt - This file.

Addtional resources:

- Reference for metrics that can be collected using nvprof (flops, etc.): https://docs.nvidia.com/cuda/profiler-users-guide/index.html#metrics-reference