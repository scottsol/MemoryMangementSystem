
bench: getmem.o freemem.o get_mem_stats.o print_heap.o bench.o 
	gcc -std=c99 -Wall -g -o bench bench.o getmem.o freemem.o get_mem_stats.o print_heap.o

bench.o: bench.c mem.h 
	gcc -std=c99 -Wall -g -c bench.c

freemem.o: freemem.c mem_impl.h 
	gcc -std=c99 -Wall -g -c freemem.c

getmem.o: getmem.c mem_impl.h
	gcc -std=c99 -Wall -g -c getmem.c

print_heap.o: print_heap.c mem_impl.h 
	gcc -std=c99 -Wall -g -c print_heap.c

get_mem_stats.o: get_mem_stats.c mem_impl.h 
	gcc -std=c99 -Wall -g -c get_mem_stats.c

test: bench 
	./bench

dist: bench
	git log > ./git.log
	tar cf hw6.tar ./*.c ./*.h ./README.md ./git.log ./Makefile

clean:
	rm -f *.o *~ git.log hw6.tar bench