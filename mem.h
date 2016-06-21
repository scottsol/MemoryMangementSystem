// Trent Ishii and Scott Sol
// 1231047 / 
// mem.h is the header file for public declarations

#ifndef MEM_H
#define MEM_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void* getmem(uintptr_t size);

void freemem(void* p);

void get_mem_stats(uintptr_t* total_size, uintptr_t* total_free,
		   uintptr_t* n_free_blocks);

void get_mem_stats(uintptr_t* total_size, uintptr_t* total_free, uintptr_t* n_free_blocks);

void print_heap(FILE * f);

void check_heap();

#endif
