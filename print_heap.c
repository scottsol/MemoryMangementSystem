// Trent Ishii and Scott Sol
// 1230147
// print_heap.c prints the memory of the heap in a readable format to an input file f

#include "mem.h"
#include "mem_impl.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void print_heap(FILE * f) {
  Block* curr = free_list;
  int blockNumber = 1;
  while(curr != NULL) {
    fprintf(f, "Address = %p Size = %lu Free Block Number %d\n", curr, curr->size + header_size, blockNumber);
    blockNumber++;
    curr = curr->next;
  }
}
