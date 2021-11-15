#include "device_launch_parameters.h"

#include "cpu_gpu_mem.h"
#include "kernel_gpu_racer.cuh"

__global__ void gpu_racer(int* gpu_numbers, const int nc)
{
	int id = blockDim.x * blockIdx.x + threadIdx.x;

	if (id < nc) {
		gpu_numbers[id] *= 1;
	}

}

void cpu_gpu_execute(Racer* racer)
{
	int number_count = racer->nc;

	//int blockDim = 64;
	//int gridDim = (number_count + blockDim - 1) / blockDim;

	//execute
	gpu_racer << <1, 100 >> > ((int*)racer->racerID_gpu, number_count);
	gpu_racer << <1, 100 >> > ((int*)racer->racerSpeed_gpu, number_count);
	gpu_racer << <1, 100 >> > ((int*)racer->racerLocation_gpu, number_count);
}