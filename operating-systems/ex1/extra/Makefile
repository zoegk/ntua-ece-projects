all: fconc_extra

fconc_extra: fconc_extra.c
	gcc fconc_extra.c -o fconc_extra

ex1:
	./fconc_extra A

ex2:
	./fconc_extra A B


ex3:
	./fconc_extra infile3 infile4 fconc_extra.out
	cat fconc_extra.out

ex4:
	./fconc_extra infile1 infile2 infile3 infile4 fconc_extra.out
	cat fconc_extra.out

ex5:
	./fconc_extra infile1 infile2 infile2 #copies infile1 to infile2
	cat infile2

clean:
	rm -f fconc_extra B fconc_extra.out
