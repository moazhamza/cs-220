#include <stdio.h>
#include <stdlib.h>

extern unsigned long *get_ebp();
/*extern int system(char[]);*/

void ret2libc(int dummy){
	unsigned long *curr_ebp = get_ebp();
	curr_ebp[2] = curr_ebp[1];
	curr_ebp[1] = (unsigned long) &system;
	char *str = "/bin/bash";
	curr_ebp[3] = (unsigned long) str;
}
void ret2libc_generic(char *cmd){
	unsigned long *curr_ebp = get_ebp();
	char *str = cmd;
	curr_ebp[2] = curr_ebp[1];
	curr_ebp[1] = (unsigned long) &system;
	curr_ebp[3] = (unsigned long) str;
}
int main(){
	ret2libc_generic("cat ret2libc.c");
	printf("Done!\n");
	return 0;
}
