all: fconc

fconc: fconc.c
	gcc fconc.c -o fconc

ex1:
	./fconc A

ex2:
	./fconc A B

ex3:
	./fconc infile1 infile2
	cat fconc.out

ex4:
	./fconc infile1 infile2 my_output.out
	cat my_output.out

ex5:
	./fconc infile1 infile2 infile2  #copies infile1 to infile2
	cat infile2

clean:
	rm -f fconc fconc.out my_output.out
