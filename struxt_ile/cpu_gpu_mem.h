#pragma once

struct Racer
{
	void* racerID_gpu;
	void* racerID_cpu;

	void* racerSpeed_gpu;
	void* racerSpeed_cpu;

	void* racerLocation_cpu;
	void* racerLocation_gpu;

	int nc;
};