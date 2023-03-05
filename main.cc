#include "GPU.h"

#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

void cpuTest(float *mem, int num)
{
	for(int i=0;i<num;i++)
	{
		float tmp = mem[i];
		for(int j=1;j<30000;j++)
		{
			tmp -= 0.0001f * 2.0f * (tmp - 5.0f);
		}
		mem[i] = tmp;
	}
}

int main(int argc, char *argv[])
{
	GPU *gpu = new GPU();

	int memSize = (1024 * 2 * 1000 / 1024) * 1024;
	float *mem = new float[memSize];
	float *mem2 = new float[memSize];
	
	for(int i=0;i<memSize;i++)
	{
		mem[i] = i;
		mem2[i] = i;
	}
	
	struct timeval start, end;

	long seconds, useconds;    
	double mtimeCPU, mtimeGPU;

	gettimeofday(&start, NULL);
	cpuTest(mem, memSize);
	gettimeofday(&end, NULL);
	seconds  = end.tv_sec  - start.tv_sec;
	useconds = end.tv_usec - start.tv_usec;
	mtimeCPU = (seconds + useconds/1000000.0);

	printf("Elapsed time CPU: %lf seconds\n", mtimeCPU);


	cl_mem mgpu = gpu->GetMemory(memSize * sizeof(float));
	gpu->WaitForGPUToFinish();
	
	
	gpu->CopyCPUtoGPU(mem2, mgpu, memSize * sizeof(float));
	gpu->WaitForGPUToFinish();

	void* pp[] = {(void*)mgpu, (void*)&memSize};

	gpu->SetupExecute((char*)"make_step_kernel", (char*)"pi\0", pp, memSize);
	
	gettimeofday(&start, NULL);
	gpu->Execute(memSize);
	gpu->WaitForGPUToFinish();
	gettimeofday(&end, NULL);
	
	gpu->ReleaseExecute();
	
	seconds  = end.tv_sec  - start.tv_sec;
	useconds = end.tv_usec - start.tv_usec;
	mtimeGPU = seconds + useconds/1000000.0;

	printf("Elapsed time GPU: %lf seconds\n", mtimeGPU);
	printf("Speedup: %lfx\n\n", ((double)mtimeCPU/mtimeGPU));
	
	gpu->CopyGPUtoCPU(mem2, mgpu, memSize * sizeof(float));
	gpu->WaitForGPUToFinish();
	for(int i=0;i<10;i++)
	{
		printf("%f %f\n", mem[i], mem2[i]);
	}
	
	for(int i=0;i<memSize;i++)
	{
		if(abs((mem[i]-mem2[i])/mem[i])>0.0001f)
		{
			printf("ERROR %f %f\n", mem[i], mem2[i]);
		}
	}
	
	gpu->FreeMemory(mgpu);
	delete[] mem;
	delete[] mem2;
	delete gpu;

	return 0;
}
