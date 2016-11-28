#include <stdio.h>
#include <stdlib.h>

extern unsigned int *get_ebp_asm();
extern int main();

unsigned char *getMaxBound(){
	unsigned char *ptr = (unsigned char *)&main;
	do{
        	ptr++;
	} while ( *ptr != 0xc3);
	return ptr;
}

void print_backtrace(int count){
	unsigned int *curr_ebp = get_ebp_asm();
	while(count > 0){
		unsigned int *ret_addr = (unsigned int*) (*(curr_ebp+1));
		printf("%p\n",ret_addr);
		if (ret_addr >= ((unsigned int *) &main) && ret_addr <= (unsigned int *) getMaxBound()) return;
		curr_ebp = (unsigned int*) *(curr_ebp);
		count--;
	}
}

