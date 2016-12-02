#include <stdio.h>
#include <unistd.h>

int main(){
	fork();
	printf("%u: %u: Line 1\n", getpid(), getppid());
	fork();
	printf("%u: %u: Line 2\n", getpid(), getppid());
	if (fork() == 0) printf("%u: %u: Line 3\n", getpid(), getppid());
	else printf("%u: %u: Line 4\n", getpid(), getppid());
	return 0;
}
