all:
	gcc -c -std=c89 -g -Wall sorter.c -I$PWD
	ar rcs libsort.a sorter.o
	gcc -c -std=c89 -g -Wall sorter.c -I$PWD -fPIC
	gcc -shared -o libsort.so sorter.o
	gcc -c estimator.S -o estimator.o
	gcc -std=c89 estimator.c estimator.o -o estimator
	rm -f estimator.o

clean:
	rm -f libsort.a
	rm -f libsort.so
	rm -f sorter.o
	rm -f estimator
	
