#include <stdio.h>
#include <stdlib.h>

int main()
{	
	while (1){
	unsigned int i;
	i+=100;
	int *p = (int *) malloc(i*0x1000);
	printf("%d\n", i*0x1000);	
}
	return 0;

}
