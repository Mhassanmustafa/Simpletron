simpletron: libutility.a
	gcc -o simpletron.exe simpletron.c -L. -lutility

libutility.a: utility.o
	ar cr libutility.a utility.o
	
utility.o: utility.c
	gcc -c utility.c
