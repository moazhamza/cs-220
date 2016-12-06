#include <stdio.h>

int main(){
	unsigned int x1, edx, eax, x2, x3;
	for(x1 = 0; x1<100; x1++){
		edx = 0x929e9792;
		eax = x1;
		eax += edx;
		x2 = eax;
		eax = eax >> 3;
		x3 = eax;
		x3 = x3 << 3;
		if(x3 == x2){
		printf("This number works: %d\n", x1);
		}
	}
}
