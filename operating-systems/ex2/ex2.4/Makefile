.PHONY: make-expr-tree clean

make-expr-tree: make-expr-tree.o proc-common.o tree.o
	gcc -o make-expr-tree make-expr-tree.o proc-common.o tree.o

make-expr-tree.o: make-expr-tree.c proc-common.h tree.h
	gcc -Wall -c make-expr-tree.c

ex1:
	./make-expr-tree expr.tree   #10+4*(5+7)

ex2:
	./make-expr-tree test.tree   #10*(5+6)

ex3:
	./make-expr-tree testagain.tree #2*(3+4)+6*(1+3)

ex4:
	./make-expr-tree bad.tree

ex5:
	./make-expr-tree expr.tree test.tree

clean:
	rm -f make-expr-tree.o make-expr-tree
