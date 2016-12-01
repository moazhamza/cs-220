#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main(){
	int x = 1;
	pid_t pid;
	pid = fork();

	if (pid == 0) {
		x++;
		printf("%d\n", x);
		printf("Child's pid: %u\n", getpid());
		printf("Child's parent pid: %u\n", getppid());
	} else{
		sleep(1);
		x--;
		printf("%d\n", x);
		printf("In parent\n");
		printf("Parent's pid: %u\n", getpid());
		printf("Parent's parent pid: %u\n", getppid());
	}
	return (0);
}
