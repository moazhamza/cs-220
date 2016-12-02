#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	char line[1024];
	int pid, i;
        char *args[100];
	while(1){
		printf("Hello!!>");
		if(!fgets(line, 1023, stdin)){
			break;
		}
		if(strcmp(line, "exit\n")  == 0) break;

		unsigned int numArgs = 0;
		args[0] = &line;
		for (i=0; i < strlen(line); i++) if (line[i] == '\n') line[i] = '\0';	
		for (i=0; i < strlen(line); i++){
			if (line[i] == ' ') {
				line[i] = '\0';
				numArgs++;
				args[numArgs] = &(line[i+1]);
			}
		}			
		args[numArgs+1] = NULL;
		pid = fork();
		if(pid == 0) { /* This is the child */
			execvp(line, args);
			fprintf(stderr, "Hello!!: %s\n", strerror(errno));
			exit(errno);
		} else {
			wait(NULL);
		}
	}
	return 0;
}

