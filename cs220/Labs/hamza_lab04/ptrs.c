#include <stdio.h>
int main(){
	int a = 0xe;
	int *b = &a;
	int **c = &b;
	int ***d = &c;
	
	printf("a - Address: %p Value: %x\nb - Address: %p Value: %x\nc - Address: %p Value: %x\nd - Address: %p Value: %x\n", &a, a, &b, b, &c, c, &d, d);
}


