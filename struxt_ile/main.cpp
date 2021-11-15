#include "cpu_gpu.h"
#include <thread>
#include <chrono>
#include<iostream>
#include "cpu_gpu_mem.h"

#include "kernel_gpu_racer.cuh"
using namespace std::chrono;
int main()
{
	
	Racer racer;

	racer.nc = 100;

	cpu_gpu_alloc(&racer);
	cpu_gpu_set_numbers(&racer);
	std::this_thread::sleep_for(100ms);

	cpu_gpu_h_to_d(&racer);
	
	cpu_gpu_execute(&racer);
		//std::this_thread::sleep_for(100ms);
	
	//cpu_gpu_execute(&racer);
	cpu_gpu_d_to_h(&racer);
	for (int i = 0; i < 20; i++) {
	
		cpu_gpu_print_results(&racer);
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	

	cpu_gpu_free(&racer);
}