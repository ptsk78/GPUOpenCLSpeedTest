# GPU OpenCL Speed Test

### Comparison of single threaded CPU execution vs GPU execution (speed up of Newton's algorithm on a GPU)

### Works on [AMD Ryzen 7 5825U](https://www.amd.com/en/products/apu/amd-ryzen-7-5825u) processor

./run.sh

  -- GPU 0 --
  
  DEVICE_NAME = gfx90c:xnack-
  
  DEVICE_VENDOR = [Advanced Micro Devices, Inc.](https://www.amd.com/)
  
  DEVICE_VERSION = [OpenCL 2.0](https://registry.khronos.org/OpenCL/specs/opencl-2.0.pdf)
  
  DRIVER_VERSION = 3513.0 (HSA1.1,LC)
  
  DEVICE_MAX_COMPUTE_UNITS = 8
  
  DEVICE_MAX_CLOCK_FREQUENCY = 2000
  
  DEVICE_GLOBAL_MEM_SIZE = 2147483648
  
Kernels built succesfully!

Elapsed time CPU: 30.622689 seconds

2048000 2048000 256

Elapsed time GPU: 0.133850 seconds

Speedup: 228.783631x


### Previously on NVIDIA's GPU.

./run.sh

  -- GPU 0 --
  
  DEVICE_NAME = [GeForce RTX 3090](https://www.nvidia.com/en-us/geforce/graphics-cards/30-series/rtx-3090/)
  
  DEVICE_VENDOR = [NVIDIA Corporation](https://www.nvidia.com/)
  
  DEVICE_VERSION = [OpenCL](https://www.khronos.org/registry/OpenCL/) 1.2 [CUDA](https://developer.nvidia.com/cuda-zone)
  
  DRIVER_VERSION = 455.38
  
  DEVICE_MAX_COMPUTE_UNITS = 82
  
  DEVICE_MAX_CLOCK_FREQUENCY = 1695
  
  DEVICE_GLOBAL_MEM_SIZE = 25411846144
  
Kernels built succesfully!

Speedup: 4204.213465x
