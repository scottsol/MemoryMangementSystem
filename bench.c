// Trent Ishii and Scott Sol
// 1231047
// bench.c is the main executable that runs multiple calls of free and getmem
// to show that everything is implemented correctly

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mem_impl.h"
#include "mem.h"

void printReport();

int main (int argc, char *argv[]) {
    
    int NTRIALS = 10000;
    int PCTGET = 50;
    int PCTLARGE = 10;
    int SMALL_LIMIT = 200;
    int LARGE_LIMIT = 20000;
    uintptr_t RANDOM_SEED = (uintptr_t) time(NULL);
    
    
    if (argc > 1) {
        NTRIALS = atoi(argv[1]);
        if (NTRIALS == 0) {
            printf("number of trials must be greater than 0");
            exit(1);
        }
    }
    if (argc > 2) {
        PCTGET = atoi(argv[2]);
        if (PCTGET == 0 || PCTGET > 100) {
            printf("PCTGET must be greater than 0 and less than or equal to 100");
            exit(1);
        }
    }
    if (argc > 3) {
        PCTLARGE = atoi(argv[3]);
        if (PCTLARGE <= 0 || PCTLARGE > 100) {
            printf("PCTLARGE must be between 0 and 100");
            exit(1);
        }
    }
    if (argc > 4) {
        SMALL_LIMIT = atoi(argv[4]);
        if (SMALL_LIMIT <= 0) {
            printf("Small limit must be greater than 0");
            exit(1);
        }
    }
    if (argc > 5) {
        LARGE_LIMIT = atoi(argv[5]);
        if (LARGE_LIMIT <= 1) {
            printf("large limit must be greater than 1");
            exit(1);
        }
    }
    if (argc > 6) {
        RANDOM_SEED = atoi(argv[6]);
        if (RANDOM_SEED <= 0) {
            printf("Random seed must be greater than zero");
            exit(1);
        }
    }
    if (argc > 7) {
        printf("Too many arguments");
        exit(1);
    }
    
    if (SMALL_LIMIT >= LARGE_LIMIT) {
        printf("Small limit has to be less than large limit");
        exit(1);
    }
    
    int choice;
    int numOfMems;
    int randomSize;
    int large;	// remove if not needed
    int small; // remove if not needed
    // intialize random generator
    srand(RANDOM_SEED);
    // array of allocated memory
    uintptr_t* mems = (uintptr_t*)malloc(NTRIALS*sizeof(uintptr_t));
    numOfMems = 0;
    
    choice = rand() % 100 + 1;
    large = 0;
    small = 0;
    
    int timeToReport = NTRIALS / 10 + (NTRIALS % 10 / 10);
    int reportTimer = NTRIALS - timeToReport;
    // start time
    uintptr_t startTime = clock();
    uintptr_t currentTime;
    
    
    // CHECK
    int counter = 0;
    
    for (int i = NTRIALS; i > 0; i--) {
        
        choice = rand() % 100 + 1;
        
        if (choice > PCTGET) {
            choice = rand() % 100 + 1;
            if (choice <= PCTLARGE) {
                
                randomSize = rand() % (LARGE_LIMIT - SMALL_LIMIT) + 1;
                large++;
            } else {
                randomSize = rand() % (SMALL_LIMIT) + 1;
                small++;
            }
            mems[numOfMems++] = (uintptr_t) getmem(randomSize);
            
            // if not allocating memory than we are freeing memory
        } else {
            if (numOfMems > 0) {
                int randIndex = rand() % numOfMems;
                freemem((uintptr_t*) mems[randIndex]);
                numOfMems--;
                if (numOfMems != randIndex) {
                    mems[randIndex] = mems[numOfMems];
                }
            }
        }
        currentTime = clock() - startTime;
        if (i == reportTimer) {
            printf("Report #%d: %lf elapsed time\n", ++counter, (double)currentTime / CLOCKS_PER_SEC);
            printReport();
            reportTimer -= timeToReport;
        }
    }
    
    // #10 REPORT
    printf("Report #%d: %lf elapsed time\n", ++counter, (double)currentTime / CLOCKS_PER_SEC);
    printReport();

    return 0;
}

// prints a report of the current status of the memory management system
// with information about the total size of allocated memory, total free'd
// memory, and the number of free blocks in the memory system. Average
// number of bytes per free block is printed as well.
void printReport() {
    uintptr_t total_size = 0;
    uintptr_t total_free = 0;
    uintptr_t n_free_blocks = 0;
    get_mem_stats(&total_size, &total_free, &n_free_blocks);
    printf("Total amount acquired from system: %lu ", total_size);
    printf("Total number of free blocks %lu ", total_free);
    if (n_free_blocks == 0) {
        printf("Average number of bytes in free blocks: 0\n");
    } else {
        printf("Average number of bytes in free blocks: %lu\n", total_free / n_free_blocks);
    }
    printf("total free block %lu\n\n", n_free_blocks);
}
