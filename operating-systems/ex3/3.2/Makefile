CC = gcc
CFLAGS = -Wno-pointer-to-int-cast -Wno-int-to-pointer-cast -O2 -pthread

.PHONY: all clean
all: mandel_sem mandel_cond 
mandel_sem: mandel-lib.o mandel_sem.o
	$(CC) $(CFLAGS) -o mandel_sem mandel-lib.o mandel_sem.o

mandel_cond: mandel-lib.o mandel_cond.o
	$(CC) $(CFLAGS) -o mandel_cond mandel-lib.o mandel_cond.o

mandel-lib.o: mandel-lib.h mandel-lib.c
	$(CC) $(CFLAGS) -c -o mandel-lib.o mandel-lib.c 

mandel_sem.o: mandel_sem.c mandel-lib.h
	$(CC) $(CFLAGS) -c -o mandel_sem.o mandel_sem.c

mandel_cond.o: mandel_cond.c mandel-lib.h
	$(CC) $(CFLAGS) -c -o mandel_cond.o mandel_cond.c

clean:
	rm -f mandel_sem.o mandel_sem mandel-lib.o mandel_cond.o mandel_cond 

