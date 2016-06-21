// Trent Ishii and Scott Sol
// 1230147
// get_mem_stats.c stores details about the current memory manager in three numbers

#include "mem.h"
#include "mem_impl.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void get_mem_stats(uintptr_t* total_size, uintptr_t* total_free, uintptr_t* n_free_blocks) {
  *total_size = malloc_sum;
  *total_free = 0;
  *n_free_blocks = 0;
  Block* current = free_list;
  while (current != NULL) {
  	*total_free = *total_free + current->size;
  	*n_free_blocks = *n_free_blocks + 1;
  	current = current->next;
  }
}
