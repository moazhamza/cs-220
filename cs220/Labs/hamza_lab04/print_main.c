#include <stdio.h>
int main(){
	unsigned char *ptr = (unsigned char*)&main;

	*ptr = 10;
	do{
		printf("Value of ptr: %x\n", *ptr);
		ptr++;
		
	} while ( *ptr != 0xc3);




}

