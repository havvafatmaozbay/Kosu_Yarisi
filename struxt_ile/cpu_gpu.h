#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "cpu_gpu_mem.h"

void cpu_gpu_alloc( Racer* p_racer);
void cpu_gpu_free( Racer* p_racer);

void cpu_gpu_set_numbers( Racer* p_racer);

void cpu_gpu_h_to_d( Racer* p_racer);
void cpu_gpu_d_to_h( Racer* p_racer);

void cpu_gpu_print_results(Racer* p_racer);