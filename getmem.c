// William Thing, Eeshan Londhe
// CSE374 Hw6
// 2/26/15
// getmem.c
// 
// This method allocates memory for the user to use and returns a pointer to the memory.

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "mem_impl.h"



// Passes in a size.
// This method returns a pointer to a block of memory that is atleast size bytes.
// Allocates a block of default mallocSize and adds it to the free list. Then divides
// the block into the correct size and returns a pointer to the block of memory.
void* getmem(uintptr_t size) {
    if (size <= 0) {
        return NULL;
    }
    Block* bigBlock;
    Block* temp;
    
    uintptr_t sizeBy16 = size;
    if (size % 16 != 0) {
        sizeBy16 = size/16;
        sizeBy16 = (sizeBy16 + 1) * 16;
    }
    //  Both cases must malloc new block needed with default or specific size
    if (freeList == NULL) { // list is Null
        if (sizeBy16 + headerSize > mallocSize) { // size too big
            bigBlock = (Block*) malloc((int)sizeBy16 + headerSize);
            bigBlock->size = (uintptr_t)sizeBy16;
            bigBlock->next = NULL;
            totalMalloced += (int)sizeBy16 + headerSize;
            return (void*)((uintptr_t)bigBlock + headerSize);
        } // default malloc size then add to list to be divided
        bigBlock = (Block*) malloc(mallocSize + headerSize);
        bigBlock->size = (uintptr_t)mallocSize;
        bigBlock->next = NULL;
        freeList = bigBlock;
        temp = freeList;
        totalMalloced += mallocSize + headerSize;
        freeList = divide(freeList, sizeBy16);
        return (void*)((uintptr_t)temp + headerSize);
    } else { // freeList is NOT Null
        // OVERALL FRONT CASE:
        // This  is if the front size is larger then we divide
        if (freeList->size >= sizeBy16 + headerSize) {
            temp = freeList;
            freeList = divide(freeList, sizeBy16);
            return (void*)((uintptr_t)temp + headerSize);
        }
        Block* prev = freeList;
        // used to find block in list that is bigger
        while (prev->next != NULL && prev->next->size < sizeBy16 + headerSize) {
            prev = prev->next;
        }
        if (prev->next != NULL) { // found in freeList
            temp = prev->next;
            prev->next = divide(prev->next, sizeBy16);
            return (void*)((uintptr_t)temp + headerSize);
        }
        // not found in freeList
        if (sizeBy16 + headerSize > mallocSize) {
            bigBlock = (Block*) malloc(sizeBy16 + headerSize);
            bigBlock->size = sizeBy16;
            bigBlock->next = NULL;
            totalMalloced += sizeBy16 + headerSize;
            return (void*)((uintptr_t)bigBlock + headerSize);
        }
        // malloc a default size block and sort the freeList according
        // to address
        bigBlock = (Block*) malloc(mallocSize + headerSize);
        totalMalloced += mallocSize + headerSize;
        bigBlock->size = mallocSize;
        bigBlock->next = NULL;
        // FRONT
        if (bigBlock < freeList) {
            temp = freeList;
            freeList = bigBlock;
            bigBlock->next = temp;
            temp = freeList;
            freeList = divide(freeList, sizeBy16);
            return (void*)((uintptr_t)temp + headerSize);
        }
        // GEN case
        prev = freeList;
        while (prev->next != NULL && prev->next < bigBlock) {
            prev = prev->next;
        }
        if (prev->next == NULL) {
            prev->next = bigBlock;  // end case
        } else {
            Block* tempPtr = prev->next;
            prev->next = bigBlock;
            bigBlock->next = tempPtr;
        }
        temp = prev->next;
        prev->next = divide(prev->next, sizeBy16);
        return (void*)((uintptr_t)temp + headerSize);
    }
}

// Passes in a pointer to a Block and a size
// Returns a pointer to the divided block that needs to be placed into the freeList.
Block* divide (Block* blocky, uintptr_t size) {
    if (size + thresh + headerSize >= blocky->size) {
        return blocky->next;
    } else {
        Block* newBlock = (Block*)((uintptr_t)blocky + size + headerSize);
        newBlock->size = blocky->size - size - headerSize;
        newBlock->next = blocky->next;
        blocky->size = size;// reason is because we don't want to override header
        blocky->next = NULL;
        return newBlock;
    }
}