default: pointers

pointers.o: pointers.c
	gcc -c pointers.c -o pointers.o

pointers: pointers.o
	gcc pointers.o -o pointers

clean:
	-rm -f pointers.o
	-rm -f pointers
