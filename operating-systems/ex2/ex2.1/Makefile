make-tree: make-tree.o proc-common.o
	gcc -o make-tree make-tree.o proc-common.o
make-tree.o: make-tree.c proc-common.h
	gcc -Wall -c make-tree.c
clean:
	rm -f make-tree.o make-tree