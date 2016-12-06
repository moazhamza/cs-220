#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

char **split_on_spaces(char *str){
	    int i, numArgs = 1, j=0;
	    for(i=0; i < strlen(str); i++) if(str[i] == ' ') numArgs++;
	    char **args = malloc(numArgs * sizeof(char));
	    i = 0;
	    while(str[i] != '\n' && str[i] != '\0'){
		    if(str[i] == ' ') {
			    str[i] = '\0';
			    args[j] = str;
			    str = &(str[i+1]);
			    j++; i=0;
		    }
		    else{    
			    i++;
		    }
	    }
	    args[j] = str; 
	    args[j+1] = NULL;
	    return args;
}

int main(){
	char line[1024];
	int pid, i, error=0;
	unsigned char multipleCommands = 0;
	char *secondLine;
	while(1){
		printf("Hello!!>");
		if(!fgets(line, 1023, stdin)){
			break;
		}
		if(strcmp(line, "exit\n")  == 0) break;
		for (i=0; i< strlen(line); i++) {
			if(line[i] == '\n') line[i] = '\0';
		}
		for (i=0; i< strlen(line); i++) {
			if(line[i] == '&' && line[i+1] == '&'){
				line[i] == '\0';
				secondLine = &(line[i+3]);
				multipleCommands = 1;
			}	
		}
		char **args = split_on_spaces(line);
		
		pid = fork();
		if(pid == 0) { /* This is the child */
			error = execvp(line, args);
			if(multipleCommands && error != -1){
				char **args2 = split_on_spaces(line);
				pid = fork();
				if(pid == 0){
					execvp(secondLine, args2);
					fprintf(stderr, "Hello!!: %s\n", strerror(errno));
					exit(errno);
			}else{
					wait(NULL);
			}
			fprintf(stderr, "Hello!!: %s\n", strerror(errno));
			exit(errno);
			}
		} else {
			wait(NULL);
		}
	}
	return 0;
}

