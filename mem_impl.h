// Trent Ishii and Scott Sol
// 1231047
// mem_impl.h

#ifndef MEM_IMPL_H
#define MEM_IMPL_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define default_size 4096
#define header_size 16
#define block_padding 64

typedef struct free_block {
  uintptr_t size;
  struct free_block *next;
} Block;

Block* free_list;
int malloc_sum;


#endif
