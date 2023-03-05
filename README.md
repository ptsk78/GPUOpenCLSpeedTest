# GPUOpenCLSpeedTest

### Comparison of single threaded CPU execution vs GPU execution (speed up of newton's algorithm)

### Works on [AMD Ryzen 7 5825U](https://www.amd.com/en/products/apu/amd-ryzen-7-5825u) processor

./run.sh

  -- GPU 0 --
  
  DEVICE_NAME = gfx90c:xnack-
  
  DEVICE_VENDOR = Advanced Micro Devices, Inc.
  
  DEVICE_VERSION = OpenCL 2.0 
  
  DRIVER_VERSION = 3513.0 (HSA1.1,LC)
  
  DEVICE_MAX_COMPUTE_UNITS = 8
  
  DEVICE_MAX_CLOCK_FREQUENCY = 2000
  
  DEVICE_GLOBAL_MEM_SIZE = 2147483648
  
Kernels built succesfully!

Elapsed time CPU: 30.622689 seconds

2048000 2048000 256

Elapsed time GPU: 0.133850 seconds

Speedup: 228.783631x


4.987580 4.987580

4.990047 4.990047

4.992507 4.992507

4.994951 4.994951

4.997340 4.997340

5.000000 5.000000

5.002660 5.002660

5.005049 5.005049

5.007493 5.007493

5.009953 5.009953


./run.sh

Output:

  -- GPU 0 --
  
  DEVICE_NAME = [GeForce RTX 3090](https://www.nvidia.com/en-us/geforce/graphics-cards/30-series/rtx-3090/)
  
  DEVICE_VENDOR = NVIDIA Corporation
  
  DEVICE_VERSION = [OpenCL](https://www.khronos.org/registry/OpenCL/) 1.2 [CUDA](https://developer.nvidia.com/cuda-zone)
  
  DRIVER_VERSION = 455.38
  
  DEVICE_MAX_COMPUTE_UNITS = 82
  
  DEVICE_MAX_CLOCK_FREQUENCY = 1695
  
  DEVICE_GLOBAL_MEM_SIZE = 25411846144
  
Kernels built succesfully!

Elapsed time CPU: 15.362196 seconds

Elapsed time GPU: 0.003654 seconds

Speedup: 4204.213465x


4.987580 4.987580

4.990047 4.990047

4.992507 4.992507

4.994951 4.994951

4.997340 4.997340

5.000000 5.000000

5.002660 5.002660

5.005049 5.005049

5.007493 5.007493

5.009953 5.009953
