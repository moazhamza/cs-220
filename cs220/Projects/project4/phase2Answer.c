#include <stdio.h>

int func(int a, int b){
	return a | b;
}
int main(){
	printf("%d\n", func(10, 205));
	return 0;
}
