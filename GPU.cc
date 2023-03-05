#include "GPU.h"

#include <cstdlib>
#include <cstdio>
#include <fstream>

using namespace std;

GPU::GPU()
{
	InitGPU();
}

GPU::~GPU()
{
	ReleaseGPU();
}

cl_mem GPU::GetMemory(size_t size)
{
	return clCreateBuffer(context, CL_MEM_WRITE_ONLY, size, NULL, NULL);
}

void GPU::FreeMemory(cl_mem mem)
{
	clReleaseMemObject(mem);
}

void GPU::CopyCPUtoGPU(void *cpu_mem, cl_mem gpu_mem, size_t size)
{
	cl_int err = clEnqueueWriteBuffer(queue, gpu_mem, CL_TRUE, 0, size, cpu_mem, 0, NULL, NULL);
	if(err != CL_SUCCESS)
	{
		fprintf(stderr, "Error copying cpu mem to gpu mem!\n");
		exit(-1);
	}
	WaitForGPUToFinish();
}

void GPU::CopyGPUtoCPU(void *cpu_mem, cl_mem gpu_mem, size_t size)
{
	cl_int err = clEnqueueReadBuffer(queue, gpu_mem, CL_TRUE, 0, size, cpu_mem, 0, NULL, NULL);
	if(err != CL_SUCCESS)
	{
		fprintf(stderr, "Error copying gpu mem to cpu mem!\n");
		exit(-1);
	}
	WaitForGPUToFinish();
}

void GPU::SetupExecute(char *function_name, char *pars, void **objects, int globalSize)
{
	cl_int err;
	kernel = clCreateKernel(program, function_name, &err);
	if(err != CL_SUCCESS)
	{
		fprintf(stderr, "Error creating kernel!\n");
		exit(-1);
	}

	err = CL_SUCCESS;
	int i = 0;
	while(pars[i]!='\0')
	{
		switch(pars[i])
		{
			case 'p':
				err |= clSetKernelArg(kernel, i, sizeof(cl_mem), &(objects[i]));
				break;
			case 'f':
				err |= clSetKernelArg(kernel, i, sizeof(float), objects[i]);
				break;
			case 'i':
				err |= clSetKernelArg(kernel, i, sizeof(int), objects[i]);
				break;
			default:
				fprintf(stderr, "Not implemented kernel parameter option\n");
				exit(-1);
				break;
		}
		i++;
	}
	if(err != CL_SUCCESS)
	{
		fprintf(stderr, "Error setting arguments for kernel!\n");
		exit(-1);
	}
}

//https://stackoverflow.com/questions/24326432/convenient-way-to-show-opencl-error-codes
const char *getErrorString(cl_int error)
{
switch(error){
    // run-time and JIT compiler errors
    case 0: return "CL_SUCCESS";
    case -1: return "CL_DEVICE_NOT_FOUND";
    case -2: return "CL_DEVICE_NOT_AVAILABLE";
    case -3: return "CL_COMPILER_NOT_AVAILABLE";
    case -4: return "CL_MEM_OBJECT_ALLOCATION_FAILURE";
    case -5: return "CL_OUT_OF_RESOURCES";
    case -6: return "CL_OUT_OF_HOST_MEMORY";
    case -7: return "CL_PROFILING_INFO_NOT_AVAILABLE";
    case -8: return "CL_MEM_COPY_OVERLAP";
    case -9: return "CL_IMAGE_FORMAT_MISMATCH";
    case -10: return "CL_IMAGE_FORMAT_NOT_SUPPORTED";
    case -11: return "CL_BUILD_PROGRAM_FAILURE";
    case -12: return "CL_MAP_FAILURE";
    case -13: return "CL_MISALIGNED_SUB_BUFFER_OFFSET";
    case -14: return "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST";
    case -15: return "CL_COMPILE_PROGRAM_FAILURE";
    case -16: return "CL_LINKER_NOT_AVAILABLE";
    case -17: return "CL_LINK_PROGRAM_FAILURE";
    case -18: return "CL_DEVICE_PARTITION_FAILED";
    case -19: return "CL_KERNEL_ARG_INFO_NOT_AVAILABLE";

    // compile-time errors
    case -30: return "CL_INVALID_VALUE";
    case -31: return "CL_INVALID_DEVICE_TYPE";
    case -32: return "CL_INVALID_PLATFORM";
    case -33: return "CL_INVALID_DEVICE";
    case -34: return "CL_INVALID_CONTEXT";
    case -35: return "CL_INVALID_QUEUE_PROPERTIES";
    case -36: return "CL_INVALID_COMMAND_QUEUE";
    case -37: return "CL_INVALID_HOST_PTR";
    case -38: return "CL_INVALID_MEM_OBJECT";
    case -39: return "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
    case -40: return "CL_INVALID_IMAGE_SIZE";
    case -41: return "CL_INVALID_SAMPLER";
    case -42: return "CL_INVALID_BINARY";
    case -43: return "CL_INVALID_BUILD_OPTIONS";
    case -44: return "CL_INVALID_PROGRAM";
    case -45: return "CL_INVALID_PROGRAM_EXECUTABLE";
    case -46: return "CL_INVALID_KERNEL_NAME";
    case -47: return "CL_INVALID_KERNEL_DEFINITION";
    case -48: return "CL_INVALID_KERNEL";
    case -49: return "CL_INVALID_ARG_INDEX";
    case -50: return "CL_INVALID_ARG_VALUE";
    case -51: return "CL_INVALID_ARG_SIZE";
    case -52: return "CL_INVALID_KERNEL_ARGS";
    case -53: return "CL_INVALID_WORK_DIMENSION";
    case -54: return "CL_INVALID_WORK_GROUP_SIZE";
    case -55: return "CL_INVALID_WORK_ITEM_SIZE";
    case -56: return "CL_INVALID_GLOBAL_OFFSET";
    case -57: return "CL_INVALID_EVENT_WAIT_LIST";
    case -58: return "CL_INVALID_EVENT";
    case -59: return "CL_INVALID_OPERATION";
    case -60: return "CL_INVALID_GL_OBJECT";
    case -61: return "CL_INVALID_BUFFER_SIZE";
    case -62: return "CL_INVALID_MIP_LEVEL";
    case -63: return "CL_INVALID_GLOBAL_WORK_SIZE";
    case -64: return "CL_INVALID_PROPERTY";
    case -65: return "CL_INVALID_IMAGE_DESCRIPTOR";
    case -66: return "CL_INVALID_COMPILER_OPTIONS";
    case -67: return "CL_INVALID_LINKER_OPTIONS";
    case -68: return "CL_INVALID_DEVICE_PARTITION_COUNT";

    // extension errors
    case -1000: return "CL_INVALID_GL_SHAREGROUP_REFERENCE_KHR";
    case -1001: return "CL_PLATFORM_NOT_FOUND_KHR";
    case -1002: return "CL_INVALID_D3D10_DEVICE_KHR";
    case -1003: return "CL_INVALID_D3D10_RESOURCE_KHR";
    case -1004: return "CL_D3D10_RESOURCE_ALREADY_ACQUIRED_KHR";
    case -1005: return "CL_D3D10_RESOURCE_NOT_ACQUIRED_KHR";
    default: return "Unknown OpenCL error";
    }
}

void GPU::Execute(int globalSize)
{
	cl_int err;
	size_t localSize = 256;
	size_t  gs = ((size_t)(globalSize + localSize - 1) / localSize) * localSize;
	fprintf(stderr, "%d %d %d\n", globalSize, gs, localSize);
	err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &gs, &localSize, 0, NULL, NULL);
	if(err != CL_SUCCESS)
	{
		fprintf(stderr, "Error enqueing kernel!, %s \n", getErrorString(err));
		exit(-1);
	}
}

void GPU::ReleaseExecute()
{
	clReleaseKernel(kernel);
}

void GPU::WaitForGPUToFinish()
{
	cl_int err = clFinish(queue);
	if(err != CL_SUCCESS)
	{
		fprintf(stderr, "Error waiting for GPU to finish!\n");
		exit(-1);
	}
}


void GPU::InitGPU()
{
	cl_int err;

	// Bind to platform
	err = clGetPlatformIDs(1, &cpPlatform, NULL);
	if(err != CL_SUCCESS)
	{
		fprintf(stderr, "No platform id!\n");
		exit(-1);
	}

	// Get ID for the device
	cl_uint devices_n = 0;
	err = clGetDeviceIDs(cpPlatform, CL_DEVICE_TYPE_GPU, 1, &device_id, &devices_n);
	if(err != CL_SUCCESS)
	{
		fprintf(stderr, "No device id!\n");
		exit(-1);
	}
	
	for (cl_uint i=0; i<devices_n; i++)
	{
		char buffer[10240];
		cl_uint buf_uint;
		cl_ulong buf_ulong;
		printf("  -- GPU %d --\n", i);
		err = clGetDeviceInfo(device_id, CL_DEVICE_NAME, sizeof(buffer), buffer, NULL);
		if(err != CL_SUCCESS)
		{
			fprintf(stderr, "Device info error!\n");
			exit(-1);
		}
		printf("  DEVICE_NAME = %s\n", buffer);
		err = clGetDeviceInfo(device_id, CL_DEVICE_VENDOR, sizeof(buffer), buffer, NULL);
		if(err != CL_SUCCESS)
		{
			fprintf(stderr, "Device info error!\n");
			exit(-1);
		}
		printf("  DEVICE_VENDOR = %s\n", buffer);
		err = clGetDeviceInfo(device_id, CL_DEVICE_VERSION, sizeof(buffer), buffer, NULL);
		if(err != CL_SUCCESS)
		{
			fprintf(stderr, "Device info error!\n");
			exit(-1);
		}
		printf("  DEVICE_VERSION = %s\n", buffer);
		err = clGetDeviceInfo(device_id, CL_DRIVER_VERSION, sizeof(buffer), buffer, NULL);
		if(err != CL_SUCCESS)
		{
			fprintf(stderr, "Device info error!\n");
			exit(-1);
		}
		printf("  DRIVER_VERSION = %s\n", buffer);
		err = clGetDeviceInfo(device_id, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(buf_uint), &buf_uint, NULL);
		if(err != CL_SUCCESS)
		{
			fprintf(stderr, "Device info error!\n");
			exit(-1);
		}
		printf("  DEVICE_MAX_COMPUTE_UNITS = %u\n", (unsigned int)buf_uint);
		err = clGetDeviceInfo(device_id, CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(buf_uint), &buf_uint, NULL);
		if(err != CL_SUCCESS)
		{
			fprintf(stderr, "Device info error!\n");
			exit(-1);
		}
		printf("  DEVICE_MAX_CLOCK_FREQUENCY = %u\n", (unsigned int)buf_uint);
		err = clGetDeviceInfo(device_id, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(buf_ulong), &buf_ulong, NULL);
		if(err != CL_SUCCESS)
		{
			fprintf(stderr, "Device info error!\n");
			exit(-1);
		}
		printf("  DEVICE_GLOBAL_MEM_SIZE = %llu\n", (unsigned long long)buf_ulong);
	}

	// Create a context 
	context = clCreateContext(0, 1, &device_id, NULL, NULL, &err);
	if(err != CL_SUCCESS)
	{
		fprintf(stderr, "Context not created!\n");
		exit(-1);
	}

	// Create a command queue
#ifdef _WIN32
	queue = clCreateCommandQueue(context, device_id, 0, &err);
#else
	queue = clCreateCommandQueueWithProperties(context, device_id, 0, &err);
#endif

	if(err != CL_SUCCESS)
	{
		fprintf(stderr, "Command queue not created!\n");
		exit(-1);
	}

	// Create the compute program from the source buffer
	ifstream myfile ("./kernels.cl");
	size_t length;
	myfile.seekg(0, std::ios::end);
	length = myfile.tellg();
	myfile.seekg(0, std::ios::beg);
	char *kernelSource = new char[length+1];
	kernelSource[length] = '\0';
	myfile.read(kernelSource, length);
	myfile.close();

	program = clCreateProgramWithSource(context, 1,
	    (const char **) &kernelSource, NULL, &err);
	if(err != CL_SUCCESS)
	{
		fprintf(stderr, "Program creation problem!\n");
		exit(-1);
	}

	// Build the program executable
	err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
	if(err != CL_SUCCESS)
	{
		fprintf(stderr, "Kernels did not build!\n");
		size_t length;
    		char buffer[2048];
		clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &length);
		buffer[length+1] = '\0';
		fprintf(stderr, "%s\n", buffer);
		exit(-1);
	}

	fprintf(stdout, "Kernels built succesfully!\n");
}

void GPU::ReleaseGPU()
{
	clReleaseProgram(program);
	clReleaseCommandQueue(queue);
	clReleaseContext(context);
}
