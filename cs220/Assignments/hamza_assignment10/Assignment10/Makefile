all:
	gcc -c get_ebp.S -o get_ebp.o -I$PWD 
	gcc -c -std=c89 -Wall -fPIC -I$PWD bt.c get_ebp.o
	rm -f get_ebp.o
	gcc -shared -o libbt.so bt.o 
	ar rcs libbt.a bt.o
	rm -f bt.o
clean:
	rm -f libbt.a libbt.so bt.o 

