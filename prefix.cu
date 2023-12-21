%%writefile hello.cu
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cuda_runtime.h>

#define BLOCK_SIZE 256

// Kernel for parallel prefix sum
__global__ void prefixSum(int *input, int *output, int n) {
    extern __shared__ int temp[];

    int tid = threadIdx.x;
    int idx = blockIdx.x * blockDim.x + tid;

    // Load input into shared memory
    temp[tid] = (idx < n) ? input[idx] : 0;
    __syncthreads();

    // Reduction phase
    for (int stride = 1; stride < blockDim.x; stride *= 2) {
        int index = 2 * stride * (tid + 1) - 1;
        if (index < blockDim.x) {
            temp[index] += temp[index - stride];
        }
        __syncthreads();
    }

    // Downsweep phase
    for (int stride = blockDim.x / 2; stride > 0; stride /= 2) {
        int index = 2 * stride * (tid + 1) - 1;
        if (index + stride < blockDim.x) {
            temp[index + stride] += temp[index];
        }
        __syncthreads();
    }

    // Store result to output
    if (idx < n) {
        output[idx] = temp[tid];
    }
}

// Wrapper function for inclusive prefix sum calculation
void inclusivePrefixSum(int *d_input, int *d_output, int n) {
    int numBlocks = (n + BLOCK_SIZE - 1) / BLOCK_SIZE;

    // Create CUDA events for timing
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    // Record start time
    cudaEventRecord(start);

    // Perform parallel prefix sum
    prefixSum<<<numBlocks, BLOCK_SIZE, BLOCK_SIZE * sizeof(int)>>>(d_input, d_output, n);
    cudaDeviceSynchronize();

    // Record stop time
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);

    // Calculate elapsed time
    float milliseconds = 0;
    cudaEventElapsedTime(&milliseconds, start, stop);

   std::cout << "Execution Time: " << milliseconds * 1000 << " microseconds" << std::endl;
}

int main() {
    int n = 5; // Size of the array (assuming 32n elements)
    int arraySize = 32 * n;

    // Host array
    int *h_input = new int[arraySize];

    // Seed for random number generation
    srand(time(nullptr));

    // Generate random numbers for the array
    for (int i = 0; i < arraySize; ++i) {
        h_input[i] = rand() % 100; //
    }

    // Device arrays
    int *d_input, *d_output;
    cudaMalloc(&d_input, arraySize * sizeof(int));
    cudaMalloc(&d_output, arraySize * sizeof(int));

    // Copy data from host to device
    cudaMemcpy(d_input, h_input, arraySize * sizeof(int), cudaMemcpyHostToDevice);

    // Perform inclusive prefix sum
    inclusivePrefixSum(d_input, d_output, arraySize);

    // Copy result back to host
    int *h_output = new int[arraySize];
    cudaMemcpy(h_output, d_output, arraySize * sizeof(int), cudaMemcpyDeviceToHost);

    // Print results
    std::cout << "Input array: ";
    for (int i = 0; i < arraySize; ++i) {
        std::cout << h_input[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Inclusive Prefix Sum: ";
    for (int i = 0; i < arraySize; ++i) {
        std::cout << h_output[i] << " ";
    }
    std::cout << std::endl;

    // Clean up
    delete[] h_input;
    delete[] h_output;
    cudaFree(d_input);
    cudaFree(d_output);

    return 0;
}

