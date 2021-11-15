
#pragma once

#include "cpu_gpu.h"
#include "cuda_runtime.h"
#include <thread>
#include <chrono>
using namespace std::chrono;


int get_allocation_size(const int number_count)
{
	return number_count * sizeof(int);
}

void cpu_gpu_alloc(Racer* p_racer)
{
	int allocation_size = get_allocation_size(p_racer->nc);

	p_racer->racerID_cpu = malloc(allocation_size);
	p_racer->racerSpeed_cpu = malloc(allocation_size);
	p_racer->racerLocation_cpu = malloc(allocation_size);

	cudaError_t result = cudaMalloc(&p_racer->racerID_gpu, allocation_size);
	assert(result == cudaSuccess);
	result = cudaMalloc(&p_racer->racerSpeed_gpu, allocation_size);
	assert(result == cudaSuccess);
	result = cudaMalloc(&p_racer->racerLocation_gpu, allocation_size);
	assert(result == cudaSuccess);
}
void cpu_gpu_free(Racer* p_racer)
{
	cudaError_t result = cudaFree(p_racer->racerID_gpu);
	assert(result == cudaSuccess);

	free(p_racer->racerID_cpu);

	result = cudaFree(p_racer->racerSpeed_gpu);
	assert(result == cudaSuccess);
	free(p_racer->racerSpeed_cpu);
	
	result = cudaFree(p_racer->racerLocation_gpu);
	assert(result == cudaSuccess);
	free(p_racer->racerLocation_cpu);
}



void cpu_gpu_set_numbers(Racer* p_racer)
{
	int* cpu_int100 = (int*)p_racer->racerID_cpu;
	int* cpu_int100Speed = (int*)p_racer->racerSpeed_cpu;
	
	int* cpu_Location = (int*)p_racer->racerLocation_cpu;
	//int* cpu_Location_new = nullptr;
	
	for (int i = 0; i < p_racer->nc; i++)
	{
		cpu_int100[i] = i;
		
	}
	for (int i = 0; i < p_racer->nc; i++)
	{
		cpu_int100Speed[i] = (rand()%5)+1;

	}
	
	for (int i = 0 ;i < p_racer->nc; i++ )
	{
		cpu_Location[i] = cpu_int100Speed[i] * 1;
		/*do
		{
			int a = 0;
			cpu_Location[i] = cpu_int100Speed[i] * (a + 1);
			a++;

		} while (cpu_Location[i] == 100);*/
		
	}
	
		
}

void cpu_gpu_h_to_d(Racer* p_racer)
{
	cudaError_t result = cudaMemcpy(p_racer->racerID_gpu, p_racer->racerID_cpu, get_allocation_size(p_racer->nc), cudaMemcpyHostToDevice);
	assert(result == cudaSuccess);

	result = cudaMemcpy(p_racer->racerSpeed_gpu, p_racer->racerSpeed_cpu, get_allocation_size(p_racer->nc), cudaMemcpyHostToDevice);
	assert(result == cudaSuccess);
}
void cpu_gpu_d_to_h(Racer* p_racer)
{
	cudaError_t result = cudaMemcpy(p_racer->racerID_cpu, p_racer->racerID_gpu, get_allocation_size(p_racer->nc), cudaMemcpyDeviceToHost);
	assert(result == cudaSuccess);

	result = cudaMemcpy(p_racer->racerSpeed_cpu, p_racer->racerSpeed_gpu, get_allocation_size(p_racer->nc), cudaMemcpyDeviceToHost);
	assert(result == cudaSuccess);
}

void cpu_gpu_print_results(Racer* p_racer)
{

	int* cpu_int100 = (int*)p_racer->racerID_cpu;
	int* cpu_int100Speed = (int*)p_racer->racerSpeed_cpu;
	int* cpu_Location = (int*)p_racer->racerLocation_cpu;
	for (int i = p_racer->nc -100; i < p_racer->nc; i++) {
		printf("Kosucu ID: %d\t Kosucu Hizi :%d\t  Konum: %d\n",  cpu_int100[i], cpu_int100Speed[i], cpu_Location[i]);
		
	}

	//std::this_thread::sleep_for(100ms);
}