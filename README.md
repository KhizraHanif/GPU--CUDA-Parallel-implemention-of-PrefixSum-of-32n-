# GPU--CUDA-Parallel-implemention-of-PrefixSum-of-32na-array

# Parallel Prefix Sum Implementation

This project implements the parallel prefix sum algorithm using inclusive scan. The goal is to calculate the prefix sums for each sub-array (32i-1, 32(i+1)) in an array of length 32n. The implementation includes both a CPU baseline and a GPU solution using CUDA.

## Requirements
- C++ compiler with support for C++17
- CUDA Toolkit (if running GPU solution)
- (Optional) Nvidia Visual Profiler for GPU profiling

  ### CPU Baseline
  For the CPU baseline, the code uses a for loop with calls to `std::inclusive_scan`. To compile and run:

```bash
g++ main.cpp -o main -std=c++17 -ltbb
./main

For GPU
nvcc prefix.cu -o prefix
./prefix

