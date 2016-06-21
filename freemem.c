// Trent Ishii and Scott Sol
// 1230147
// freemem.c implements the function of freeing memory in a list

#include "mem.h"
#include "mem_impl.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void freemem(void* p) {
  if (p == NULL) {
    return;
  }
  Block* curr = free_list;
  Block* pBlock = (Block*) ((char*) p - header_size);
  if (curr != NULL && (uintptr_t)pBlock >= (uintptr_t)curr) {
    while((uintptr_t)pBlock > (uintptr_t)curr->next && curr->next != NULL) {
      curr = curr->next;
    }
    if (curr->next != NULL) {
      pBlock->next = curr->next;
      curr->next = pBlock;
    } else {
      curr->next = pBlock;
      pBlock->next = NULL;
    }
  } else {
    pBlock->next = curr;
    free_list = pBlock;  
  }
  curr = free_list;
  while(curr != NULL && curr->next != NULL) {
    if((uintptr_t)curr + curr->size + header_size != (uintptr_t)curr->next) {
      curr = curr->next;
    } else {
      curr->size = curr->size + curr->next->size;
      curr->next = curr->next->next;
    }
  }
 
}
