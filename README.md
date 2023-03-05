# [GPUOpenCLSpeedTest](https://www.frisky.world/2020/11/first-speed-test-of-gpu-rtx-3090-using.html)

### Comparison of single threaded CPU execution vs GPU execution (speed up of newton's algorithm)

from terminal execute: ./run.sh

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


Considering GPU freq is 1.7 GHz and CPU freq is 3.8 Ghz, relative speedup is 4204.213465 * 3.8 / 1.7 ~ 9397.65 (and I have [10496 gpu cores](https://www.nvidia.com/en-us/geforce/graphics-cards/30-series/rtx-3090/) -> meaning getting almost there to achieve 100% usage of all cores - of course there is some overhead, hence lower number).

To install OpenCL: 'sudo apt install ocl-icd-opencl-dev'
