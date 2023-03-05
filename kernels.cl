/*inline float atomicAdd(volatile __global float* address, const float value){
    float old = value;
    while ((old = atomic_xchg(address, atomic_xchg(address, 0.0f)+old))!=0.0f);
    return old;
}*/

__kernel void make_step_kernel(__global float *outp, int batchSize)
{
	int tid = get_global_id(0);

	if (tid < batchSize)
	{
		float tmp = outp[tid];
		for(int j=1;j<30000;j++)
		{
			tmp -= 0.0001f * 2.0f * (tmp - 5.0f);
		}
		outp[tid] = tmp;
	}
}
