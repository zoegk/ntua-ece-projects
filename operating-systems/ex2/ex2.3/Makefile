.PHONY: make-tree-sig clean

make-tree-sig: make-tree-sig.o proc-common.o tree.o
	gcc -o make-tree-sig make-tree-sig.o proc-common.o tree.o

make-tree-sig.o: make-tree-sig.c proc-common.h tree.h
	gcc -Wall -c make-tree-sig.c

ex1:
	./make-tree-sig proc.tree

ex2:
	./make-tree-sig test.tree    #1.1 example

ex3:
	./make-tree-sig bad.tree

ex4:
	./make-tree-sig proc.tree bad.tree

clean:
	rm -f make-tree-sig.o make-tree-sig
