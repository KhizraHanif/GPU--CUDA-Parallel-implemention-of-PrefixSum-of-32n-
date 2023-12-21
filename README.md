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

I have used Google collab for execution as well as profiling for my cuda code using Nsight Systems.

Run the following commands in a Colab cell to install Nsight Systems:

!wget https://developer.download.nvidia.com/devtools/repos/ubuntu1804/x86_64/nvidia-nsight-systems-2022_2022.1.1.8-1_amd64.deb
!dpkg -i nvidia-nsight-systems-2022_2022.1.1.8-1_amd64.deb
!apt-get install -f

# Compile the CUDA code
!nvcc -o prefix prefix.cu

# Run the executable with Nsight Systems profiling
!nsys profile -t cuda --stats=true ./prefix
