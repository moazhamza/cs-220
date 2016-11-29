#include <stdio.h>
#include <time.h>

void forLoop(unsigned int n) {
	unsigned int i;
	for(i = 0; i < n; i++)
		;
}

void whileLoop(unsigned int n) {
	while(n > 0)
		n--;
}

void doWhileLoop(unsigned int n) {
	do { n--; } while (n > 0);
}

int main()
{
	unsigned int i = 1000000000;
    clock_t tic = clock();
    
	forLoop(i);
    
    clock_t toc = clock();	
	double numberOfSeconds = (double)(toc - tic) / CLOCKS_PER_SEC;
    printf("Elapsed: %f seconds\n", numberOfSeconds);
	printf("%f iterations per second\n", i/numberOfSeconds);
    return 0;
}
